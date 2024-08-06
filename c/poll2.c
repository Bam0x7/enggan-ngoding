#include<asm-generic/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<poll.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080

int main() {
    // Membuat socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Membuat struktur pollfd untuk memantau stdin dan socket
    struct pollfd fds[2];
    int timeout_ms = -1; // Menunggu tanpa batas waktu

    // Memantau stdin (file descriptor 0)
    fds[0].fd = 0; // stdin
    fds[0].events = POLLIN;

    // Memantau socket
    fds[1].fd = server_fd;
    fds[1].events = POLLIN;

    while (1) {
        // Memantau peristiwa dengan poll
        int result = poll(fds, 2, timeout_ms);

        if (result == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        // Peristiwa terjadi pada stdin
        if (fds[0].revents & POLLIN) {
            char buffer[100];
            ssize_t bytesRead = read(0, buffer, sizeof(buffer));

            if (bytesRead == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            printf("Data dari stdin: %.*s\n", (int)bytesRead, buffer);
        }

        // Peristiwa terjadi pada socket
        if (fds[1].revents & POLLIN) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            char buffer[100];
            ssize_t bytesRead = read(new_socket, buffer, sizeof(buffer));

            if (bytesRead == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            printf("Data dari socket: %.*s\n", (int)bytesRead, buffer);
            close(new_socket);
        }
    }

    return 0;
}
