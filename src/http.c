#include "../properties.h"
#include "http.h"

#if GET_MIME_TYPE
#include "mime.h"
#endif

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * A wrapper for the strcmp() function
 * @note { Only for usage in the qsort() function }
 * @warning { Use strcmp() instead }
 */
static int string_compare(const void* str1, const void* str2);

static int write_data(int client_fd,
                       const char* data,
                       unsigned int data_size);

/**
 * Write the http chunk to the socket
 * @param client_fd Client file descriptor
 * @param data A chunk buffer
 * @param data_size A Size of the chunk buffer
 */
static int write_chunk(int client_fd,
                        const char* data,
                        unsigned int data_size);

void http_return_error(const int client_fd, const int e_code) {
    char buffer[BUFFER_SIZE];
    const int response_size = sprintf(
        buffer,
        "HTTP/1.1 %d ERROR\r\n"
        "Content-Length: 0\r\n"
        "\r\n",
        e_code
    );
    if (write_data(client_fd, buffer, (unsigned long)response_size) == -1)
        perror("Failed to write the response to the client");
}

void http_return_redirect(const int client_fd,
                          const int code,
                          const char* const location) {
    char buffer[BUFFER_SIZE];
    const int response_size = sprintf(
        buffer,
        "HTTP/1.1 %d REDIRECT\r\n"
        "Location: %s\r\n"
        "Content-Length: 0\r\n"
        "\r\n",
        code,
        location
    );
    if (write_data(client_fd, buffer, (unsigned long)response_size) == -1)
        perror("Failed to write the response to the client");
}


void http_return_file(const int client_fd,
                      const char* path,
                      const long file_size) {
    /* Init the buffer to store the data */
    char buffer[BUFFER_SIZE];
    const int header_size = sprintf(
        buffer,
        "HTTP/1.1 200 OK\r\n"
#if GET_MIME_TYPE
        "Content-Type: %s\r\n"
#endif
        "Content-Length: %ld\r\n"
        "\r\n",
#if GET_MIME_TYPE
        mime_get_type(strrchr(path, '.') + 1),
#endif
        file_size
    );

    /* Send headers */
    if (write_data(client_fd, buffer, (unsigned long)header_size) == -1) {
        perror("Failed to write the response to the client");
        return;
    }

    /* Open the file for reading */
    const int file_fd = open(path, O_RDONLY);
    if (file_fd == -1) {
        perror("Failed to read the file");
        return;
    }

    /* Read the data to the buffer and send it to the socket */
    long read_size;
    while ((read_size = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
        if (read_size == -1) {
            perror("Failed to read the file");
            return;
        }
        if (write_data(client_fd, buffer, (unsigned long)read_size) == -1) {
            perror("Failed to write the response to the client");
            return;
        }
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstack-protector"
void http_return_directory(const int client_fd, const char* const path) {
    /* Open the directory for reading */
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to list the directory");
        return;
    }

    /* Get the number of entries in the directory */
    unsigned int entry_number = 0;
    while (readdir(dir) != NULL) entry_number++;
    closedir(dir);

    /* Open the directory for reading again */
    dir = opendir(path);
    if (dir == NULL) {
        perror("Failed to list the directory");
        return;
    }

    /* Get all entries (exclude '.' and '..') */
    entry_number -= 2;
#define ENTRY_NAME_SIZE sizeof(((struct dirent*)NULL)->d_name)
    char entry_names[entry_number][ENTRY_NAME_SIZE];
    struct dirent* entry;
    for (unsigned int i = 0; (entry = readdir(dir)) != NULL;) {
        /* Get the entry name */
        const char* const entry_name = entry->d_name;

        /* Skip '.' and '..' */
        if (strcmp(entry_name, ".") == 0 || strcmp(entry_name, "..") == 0)
            continue;

        /* Copy the entry name to the array */
        strcpy(entry_names[i], entry_name);

        /* Increment the iterator if all is OK */
        i++;
    }
    closedir(dir);

    /* Sort the array of entry names */
    qsort(entry_names, entry_number, ENTRY_NAME_SIZE, string_compare);

    /* Buffer to store and send the data */
    char buffer[BUFFER_SIZE];
    unsigned int buffer_offset = 0;

    /* Get the path size */
    unsigned long path_size = strlen(path);

    /* Send the beginning of the response  */
    const int response_beg_size = sprintf(
        buffer,
        "HTTP/1.1 200 OK\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n"
        "%lx\r\n"
        "<h1>Directory listing for %s</h1>"
        "<hr>"
        "<ul>"
        "<li><a href='../'>../</a></li>",
        path_size - 1 + 69,
        path + 1
    );
    if (write_data(client_fd, buffer, (unsigned long)response_beg_size) == -1) {
        perror("Failed to write the response to the client");
        return;
    }

    /* An array to store the entry path */
    char entry_path[path_size + ENTRY_NAME_SIZE];
    strcpy(entry_path, path);
    if (entry_path[path_size - 1] != '/') entry_path[path_size++] = '/';

    /* Send all directory entries to the client */
    for (unsigned int i = 0; i < entry_number;) {
        const char* entry_name = entry_names[i];

        /* Get stat for the entry */
        strcpy(entry_path + path_size, entry_name);
        struct stat st;
        if (stat(entry_path, &st) == -1) {
            fprintf(stderr, "%s: ", entry_path + 2);
            perror("Failed to get file stat");
            i++;
            continue;
        }

        /* Try to write the data to the buffer */
        const unsigned int available_size = BUFFER_SIZE - buffer_offset;
        const unsigned int result_size = (unsigned int)snprintf(
            buffer + buffer_offset,
            available_size,
            S_ISDIR(st.st_mode) ? "<li><a href='%s/'>%s/</a></li>"
                                : "<li><a href='%s'>%s</a></li>",
            entry_name,
            entry_name
        );

        /* If the buffer is full */
        if (result_size >= available_size) {
            /* Send the chunk to the client */
            write_chunk(client_fd, buffer, buffer_offset);

            /* Reset the buffer offset */
            buffer_offset = 0;

            /* Repeat this iteration */
            continue;
        }

        /* Increment the buffer offset */
        buffer_offset += result_size;

        /* Increment the iterator if all is OK */
        i++;
    }

    /* Drain the buffer */
    if (buffer_offset != 0) write_chunk(client_fd, buffer, buffer_offset);

    /* Send the close chunk */
    if (write_data(client_fd,
                   "\r\n"
                   "0\r\n"
                   "\r\n",
                   7) == -1)
        perror("Failed to write the response to the client");
}
#pragma GCC diagnostic pop

static int string_compare(const void* str1, const void* str2) {
    return strcmp(str1, str2);
}

static int write_data(const int client_fd,
                      const char* data,
                      unsigned int data_size){
    /* Try to write all the data */
    while (data_size > 0) {
        /* Write the data and get the length of written data */
        const long written_len = write(client_fd, data, data_size);

        /* If we get an error */
        if (written_len == -1) return -1;

        /* If all is OK, add an offset to the pointer and decrease
         * the data_size variable */
        data += written_len;
        data_size -= written_len;
    }

    /* If all is OK, return success code */
    return 0;
}

static int write_chunk(const int client_fd,
                        const char* const data,
                        const unsigned int data_size) {
    /* Buffer to store the chunk size */
    char size_buffer[sizeof("\r\n00000000\r\n")];

    /* Convert integer into the hex string
     * and write it to the buffer (right after '\r\n') */
    const int size_buffer_size = sprintf(size_buffer, "\r\n%x\r\n", data_size);

    /* Send this buffer and data to the client */
    if (write_data(
            client_fd, size_buffer, (unsigned long)size_buffer_size
        ) == -1
        || write_data(client_fd, data, data_size) == -1) return -1;
    else return 0;
}