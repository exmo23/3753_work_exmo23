#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

int myread(int length, int fd) {
    /*printf("Reading %d\n", length);*/
    /*printf("Opened File %d\n", fd);*/
    char * buffer = malloc(length);
    size_t count = length;
    read(fd, buffer, count);
    printf("%s\n", buffer);
    return 0;
}

int mywrite(int length, int fd) {
    char arr[length];
    printf("Enter the data to enter: \n");
    scanf("%s", arr);
    size_t size = length;
    write(fd, arr, size);
    return 0;
}

int myseek(int offset, int curr_offset, int whence, int fd) {
    lseek(fd, offset, whence);
    return 0;
}

int main(int argc, char *argv[]) {
    bool term = false;
    int curr_offset = 0;
    int fd = open(argv[1], O_RDWR);
    if(fd == -1) {
        printf("Error: file %s does not exist\n", argv[1]);
    }
    while(!term) {
        printf("Option (r for read, w for write, s for seek)\n");
        if(argc > 3) {
            printf("Error: %d is too many arguments\n", argc);
            return -1;
        } else {
            bool isDebugMode = 0;
            /*if(argv[2] == "1") {
                isDebugMode = 1;
            }
            if(isDebugMode == 1) {
                printf("Arguments: %d\n", argc);
                printf("%s\n", argv[1]);
            }*/
            /*printf("Arguments: %d\n", argc);*/
            /*printf("%s\n", argv[1]);*/
            char input;
            int result = scanf(" %c", &input);
            if(result == EOF) {
                close(fd);
                term = true;
            }
            if(input == 'r') {
                printf("Enter the number of bytes to read: \n");
                int slength = 0;
                scanf("%d", &slength);
                myread(slength, fd);
            } else if(input == 'w') {
                printf("Enter the number of bytes to write: \n");
                int wlength = 0;
                scanf("%d", &wlength);
                mywrite(wlength, fd);
            } else if(input == 's') {
                printf("Enter an offset value: \n");
                int soffset = 0;
                scanf("%d", &soffset);
                printf("Enter a value for whence: \n");
                int swhence = 0;
                scanf("%d", &swhence);
                myseek(soffset, curr_offset, swhence, fd);
            }
            if(fd == -1) {
                printf("Error: file %s does not exist\n", argv[1]);
            }
        }
    }
    return 0;
}