#define _GNU_SOURCE
#include <fuse/fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/userfaultfd.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void handle_userfault(int uffd, struct uffdio_copy* uffdio_copy) {
    ssize_t n;
    n = read(uffd, uffdio_copy, sizeof(*uffdio_copy));
    if (n == -1) {
        handle_error("read");
    }
}

int main() {
    // Membuat userfaultfd
    int uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
    if (uffd == -1) {
        handle_error("userfaultfd");
    }

    // Membuat wilayah memori
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    void* buffer = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        handle_error("mmap");
    }

    // Mendaftarkan wilayah memori ke userfaultfd
    struct uffdio_register uffdio_register = {
        .range = {
            .start = (uintptr_t)buffer,
            .len = page_size
        },
        .mode = UFFDIO_REGISTER_MODE_MISSING
    };

    if (ioctl(uffd, UFFDIO_REGISTER_MODE_MISSING, &uffdio_register) == -1) {
        handle_error("ioctl: UFFDIO_REGISTER");
    }

    printf("Registered region for userfaultfd.\n");

    // Membuat array struct pollfd untuk memantau userfaultfd
    struct pollfd poll_fds[1];
    poll_fds[0].fd = uffd;
    poll_fds[0].events = POLLIN;

    // Menggunakan buffer untuk memicu kesalahan halaman
    buffer = 'A';

    // Mengatur penangan kesalahan halaman
    struct uffdio_copy uffdio_copy = {
        .dst = (uintptr_t)buffer,
        .src = (uintptr_t)"B",
        .len = page_size,
        .mode = 0 // Normal copy mode
    };

    while (1) {
        // Memantau userfaultfd menggunakan poll
        int ret = poll(poll_fds, 1, -1);
        if (ret == -1) {
            handle_error("poll");
        }

        // Menangani userfault event
        if (poll_fds[0].revents & POLLIN) {
            handle_userfault(uffd, &uffdio_copy);
            printf("Handling userfault, copied: %s, addr: 0x%lx\n", (char*)buffer,(unsigned long)buffer);
        }
    }

    // Unreachable code, just for completion
    close(uffd);
    munmap(buffer, page_size);
    return 0;
}
