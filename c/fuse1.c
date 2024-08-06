#define FUSE_USE_VERSION 30
#include <fuse/fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static const char *hello_str = "Hello, this is a FUSE filesystem!\n";
static const char *hello_path = "/hello.txt";

static int hello_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0)
    {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if (strcmp(path, hello_path) == 0)
    {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(hello_str);
    }
    else
    {
        res = -ENOENT;
    }

    return res;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path, hello_path) != 0)
    {
        return -ENOENT;
    }

    if ((fi->flags & 3) != O_RDONLY)
    {
        return -EACCES;
    }

    return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    size_t len;
    (void)fi;

    if (strcmp(path, hello_path) != 0)
    {
        return -ENOENT;
    }

    len = strlen(hello_str);
    if (offset < len)
    {
        if (offset + size > len)
        {
            size = len - offset;
        }
        memcpy(buf, hello_str + offset, size);
    }
    else
    {
        size = 0;
    }

    return size;
}

static struct fuse_operations hello_oper = {
    .getattr = hello_getattr,
    .open = hello_open,
    .read = hello_read,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &hello_oper, NULL);
}
