#define FUSE_USE_VERSION 30
#include <fuse/fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static const char *file_content = "Hello, this is a Fuse filesystem!\n";

static int fuse_getattr(const char *path, struct stat *stbuf) {
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, "/hello.txt") == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(file_content);
    } else {
        res = -ENOENT;
    }

    return res;
}

static int fuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, "hello.txt", NULL, 0);

    return 0;
}

static int fuse_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, "/hello.txt") != 0) {
        return -ENOENT;
    }

    if ((fi->flags & 3) != O_RDONLY) {
        return -EACCES;
    }

    return 0;
}

static int fuse_read(const char *path, char *buf, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
    size_t len;
    (void) fi;

    if (strcmp(path, "/hello.txt") != 0) {
        return -ENOENT;
    }

    len = strlen(file_content);
    if (offset < len) {
        if (offset + size > len) {
            size = len - offset;
        }
        memcpy(buf, file_content + offset, size);
    } else {
        size = 0;
    }

    return size;
}

static struct fuse_operations fuse_oper = {
    .getattr = fuse_getattr,
    .readdir = fuse_readdir,
    .open = fuse_open,
    .read = fuse_read,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &fuse_oper, NULL);
}
