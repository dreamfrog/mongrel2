#ifndef _dir_h
#define _dir_h

#include <stdlib.h>

#ifdef __APPLE__
#include "mac_specific.h"
#else
#include <sys/sendfile.h>
#endif
#include <bstring.h>

enum {
    MAX_SEND_BUFFER = 16 * 1024,
    MAX_DIR_PATH = 256
};


typedef struct Dir {
    bstring base;
} Dir;

Dir *Dir_create(const char *base);

void Dir_destroy(Dir *dir);

int Dir_find_file(bstring path, size_t *out_size);

int Dir_stream_file(int file_fd, size_t flen, int sock_fd);

int Dir_serve_file(Dir *dir, bstring, int fd);

#ifdef __APPLE__
#define Dir_send mac_sendfile
#else
#define Dir_send sendfile
#endif

#endif