#include<stdio.h>
#include<stdlib.h>
#include<sys/xattr.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stderr,"masukan path file\n");
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    const char *attribute_value = argv[2];
    const char *attribute_name = "user.custom_attribute";

    int result = setxattr(path,attribute_name,attribute_value,strlen(attribute_value),0);
    if(result==0){
        printf("attribut file berhasil di buat\n");
    }else{
        perror("setxattr");
    }

    return EXIT_SUCCESS;
}