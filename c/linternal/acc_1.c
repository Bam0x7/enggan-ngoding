#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void check_access(const char *path) {
    // Check read access
    if (access(path, R_OK) == 0) {
        printf("Read access: YES\n");
    } else {
        perror("Read access");
    }

    // Check write access
    if (access(path, W_OK) == 0) {
        printf("Write access: YES\n");
    } else {
        perror("Write access");
    }

    // Check execute access
    if (access(path, X_OK) == 0) {
        printf("Execute access: YES\n");
    } else {
        perror("Execute access");
    }

    // Check file existence
    if (access(path, F_OK) == 0) {
        printf("File exists: YES\n");
    } else {
        perror("File exists");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_file_or_directory>\n", argv[0]);
        return 1;
    }

    check_access(argv[1]);

    return 0;
}
