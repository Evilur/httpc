#if GET_MIME_TYPE

#include "../properties.h"
#include "mime.h"

#include <string.h>

static int equal(const char* str1, const char* str2);

const char* mime_get_type(const char* ext) {
    /* Check for NULL */
    if (!ext) return "application/octet-stream";

    /* Text data */
    if (equal(ext, "html"))
        return "text/html; charset=UTF-8";
    if (equal(ext, "css"))
        return "text/css; charset=UTF-8";
    if (equal(ext, "js"))
        return "text/javascript; charset=UTF-8";
    if (equal(ext, "md"))
        return "text/markdown; charset=UTF-8";
    if (equal(ext, "txt") || equal(ext, "ini") || equal(ext, "log"))
        return "text/plain; charset=UTF-8";

    /* Images */
    if (equal(ext, "jpg") || equal(ext, "jpeg"))
        return "image/jpeg";
    if (equal(ext, "png"))
        return "image/png";
    if (equal(ext, "gif"))
        return "image/gif";
    if (equal(ext, "webp"))
        return "image/webp";
    if (equal(ext, "svg"))
        return "image/svg+xml";
    if (equal(ext, "bmp"))
        return "image/bmp";
    if (equal(ext, "tiff"))
        return "image/tiff";
    if (equal(ext, "ico"))
        return "image/x-icon";

    /* Audio */
    if (equal(ext, "mp3"))
        return "audio/mpeg";
    if (equal(ext, "ogg"))
        return "audio/ogg";
    if (equal(ext, "wav"))
        return "audio/wav";
    if (equal(ext, "m4a"))
        return "audio/mp4";

    /* Video */
    if (equal(ext, "mp4"))
        return "video/mp4";
    if (equal(ext, "ogg"))
        return "video/ogg";
    if (equal(ext, "avi"))
        return "video/x-msvideo";
    if (equal(ext, "mov"))
        return "video/quicktime";
    if (equal(ext, "mkv"))
        return "video/x-matroska";

    /* Default */
    return "application/octet-stream";
}
static int equal(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

#endif
