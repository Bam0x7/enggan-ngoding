#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<poll.h>
#include<sys/xattr.h>
#include<sys/types.h>

#define XATTR_NAME "user.attribute"
#define MSG_QUEUE_KEY 1234

struct msg_buffer{
    long msg_type;
    char msg_text[256];
};

void set_attribute(const char *path, const char *value)
{
    if(setxattr(path,XATTR_NAME,value,strlen(value),0)==-1){
        perror("setxattr");
        exit(EXIT_FAILURE);
    }
    printf("attribute file berhasil di buat\n");
}

void poll_for_change(const char *path)
{
    int fd = open(path,O_RDONLY);
    if(fd==-1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    int ret = poll(fds,1,-1);
    if(ret==-1){
        perror("poll");
        exit(EXIT_FAILURE);
    }

    if(fds[0].revents & POLLIN){
        printf("file berubah, nilai attributenya: ");

        char value[256];
        ssize_t xattr_size = getxattr(path,XATTR_NAME,value,sizeof(value));
        if(xattr_size==-1){
        perror("getxattr:");
        exit(EXIT_FAILURE);
        }

        value[xattr_size] = '\0';
        printf("%s\n" ,value); 
    }
}

void send_message(const char *message)
{
    int msgid = msgget(MSG_QUEUE_KEY,IPC_CREAT|0666);
    if(msgid==-1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer msg;
    msg.msg_type=1;
    strncpy(msg.msg_text,message,strlen(message));

    if(msgsnd(msgid,&msg,sizeof(msg.msg_text),0)==-1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("pesan terkirim: %s\n" ,message);
}

void message_receive()
{
    int msgid = msgget(MSG_QUEUE_KEY,IPC_CREAT|0666);
    if(msgid==-1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer msg;
    if(msgrcv(msgid,&msg,sizeof(msg.msg_text),1,0)==-1){
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("pesan di terima: %s\n" ,msg.msg_text);
}

int main()
{
    const char *file_path = "file_contoh.txt";
    const char *attr_value = "contoh_attribute";
    const char *message = "hallo, antrian pesan";

    set_attribute(file_path,attr_value);

    poll_for_change(file_path);

    send_message(message);

    message_receive();

    return EXIT_SUCCESS;
}