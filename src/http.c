#include "http.h"

#include "../properties.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void http_return_error(const int client_fd, const int e_code) {
    char buffer[HTTP_ERROR_RESPONSE_SIZE];
    sprintf(buffer, HTTP_ERROR_RESPONSE, e_code);
    send(client_fd, buffer, HTTP_ERROR_RESPONSE_SIZE, 0);
}

void http_return_file(const int client_fd,
                      const char* path,
                      const long file_size) {
    /* Send headers */
    char headers_buffer[HTTP_OK_RESPONSE_SIZE];
    const int header_size = sprintf(headers_buffer, HTTP_OK_RESPONSE, file_size);
    send(client_fd, headers_buffer, header_size, 0);

    /* Open the file for reading */
    const int file_fd = open(path, O_RDONLY);

    /* Read the data to the buffer and send it to the socket */
    char buffer[BUFFER_SIZE];
    int read_size;
    while ((read_size = read(file_fd, buffer, BUFFER_SIZE)) > 0)
        send(client_fd, buffer, read_size, 0);
}

void http_return_directory(const int client_fd, const char* const path) {
    /* Buffer for store the http response */
    char* buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Failed to memory allocation");
        return;
    }

    /* Write the response body head */
    strcpy(buffer, HTTP_OK_RESPONSE_BODY_HEAD);
    long buffer_offset = HTTP_OK_RESPONSE_BODY_HEAD_SIZE;
    long buffer_size = BUFFER_SIZE;

    /* Open the directory */
    DIR* const dir = opendir(path);
    if (dir == NULL) {
        perror("Cannot open a directory");
        free(buffer);
        return;
    }

    /* List the directory to the buffer */
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        /* Try to write the data to the buffer */
        write_entry:
        const int available_size = buffer_size - buffer_offset;
        const int result = snprintf(buffer + buffer_offset,
                                    available_size,
                                    "<li><a href='%s/%s'>%s</a></li>",
                                    path + 2,
                                    entry->d_name,
                                    entry->d_name);

        /* If the buffer is full */
        if (result >= available_size) {
            /* Realloc the memory */
            buffer_size += BUFFER_SIZE;
            char* allocated = realloc(buffer, buffer_size);
            if (allocated != NULL) buffer = allocated;
            else goto end;

            /* Write the last entry again */
            goto write_entry;
        }

        buffer_offset += result;
    }

    /* Send the header */
    char header_buffer[HTTP_OK_RESPONSE_SIZE];
    const int header_size = sprintf(header_buffer,
                                    HTTP_OK_RESPONSE,
                                    buffer_offset);
    send(client_fd, header_buffer, header_size, 0);

    /* Send the body */
    send(client_fd, buffer, buffer_offset, 0);

    end:
    closedir(dir);
    free(buffer);
}