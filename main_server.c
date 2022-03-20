#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include "message.h"

#define MSGKEY_RCV 11
#define MSGKEY_SND 26

int get_msg(int shmid, int semid, char *shm_address, int client);
int snd_msg(int shmid, int semid, char *shm_address, int client);
void send_compiled_file(int sock);
int receive_file(int client);

typedef struct
{
    long mtype;
    int is_file_over;
    char msg_text[BUFSIZ];
}qmsg;


//#define SEMKEYPATH "/dev/null"
#define SEMKEYID 1
//#define SHMKEYPATH "/dev/null"
#define SHMKEYID 1
#define NUMSEMS 2

int calculating(int client);
int compile(int client);

int main(int argc, char* argv[])
{
    int sock, client;
    char ip[16] = "127.0.0.1";
    int port = 1111;
    char choose[10];
    char buf[BUFSIZ];


    int res = semget(18874758, 2, 0666);
    printf("semid here is %d\n", res);



    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("can't create socket\n");
        exit(-1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(sock, 3);

    while (1)
    {
        int flag = 0;
        client = accept(sock, NULL, NULL);
        printf("client accepted! PID: %d\n", getpid());
        if (client < 0)
        {
            perror("client can't be accepted");
            close(sock);
        }
        switch (fork())
        {
        case 0:
            break;

        default:
            flag = 1;
            break;
        }
        if (flag)
            break;
    }
    sprintf(buf, "1) Remote compile\n2) Calculating of long numbers\nChoose the service: ");
    send(client, buf, BUFSIZ, 0);
    recv(client, choose, 10, 0);
    if(choose[0] == '1')
    {
        compile(client);
    }
    else if(choose[0] == '2')
    {
        calculating(client);
    }
    else
        perror("wrong between 1 and 2!\n");
    shutdown(client, SHUT_RDWR);

    return 0;
}

int compile(int client)
{
    printf("compile func\n");
    if(receive_file(client))
        return -1;
    send_compiled_file(client);
    return 0;
}

int calculating(int client)
{
    printf("calc func\n");
    struct sembuf ops[2];
    msg* message;
    int semID, shmid, rc;
    key_t semkey, shmkey;
    char buf[BUFSIZ];
    int id = getpid();

    semkey = ftok("./", 1);
    printf("semkey is %d\n", semkey);
    if (semkey == (key_t)-1)
    {
        perror("client: ftok() for sem failed");
        return -1;
    }
    shmkey = ftok("./", 1);
    if (shmkey == (key_t)-1)
    {
        perror("client: ftok() for shm failed");
        return -1;
    }
    // Получаем уже существующий ID семафоров, свзанный с ключом.
    semID = semget(semkey, 2, 0666);
    printf("SEMIDDDD is %d\n", semID);
    if (semID == -1)
    {
        perror("client: semget() failed");
        return -1;
    }
    // Получаем уже существующий ID сегмента разделяемой памяти, свзанный с ключом.
    shmid = shmget(shmkey, sizeof(message), 0666);
    if (shmid == -1)
    {
        perror("client: shmget() failed");
        return -1;
    }

    sprintf(buf, "write nums for calculation\n");
    while (1)
    {
        send(client, buf, BUFSIZ, 0);
        rc = recv(client, buf, BUFSIZ, 0);
        printf("rc is %d\n", rc);
        printf("buf is %s", buf);
        ops[0].sem_num = 0;
        ops[0].sem_op = 0;
        ops[0].sem_flg = 0;

        ops[1].sem_num = 1;
        ops[1].sem_op = -1;
        ops[1].sem_flg = 0;
        rc = semop(semID, ops, 2);
        if (rc == -1)
        {
            perror("SEMOP 1 ");
            return -1;
        }

        message = (msg*)shmat(shmid, NULL, 0);
        if (message == NULL)
        {
            perror("SHMAT ");
            return -1;
        }
        strcpy(message->string, buf);
        printf("server send message : %s\n", message->string);
        message->id = id;
        ops[0].sem_num = 0;
        ops[0].sem_op = 1;
        ops[0].sem_flg = 0;

        ops[1].sem_num = 1;
        ops[1].sem_op = 0;
        ops[1].sem_flg = 0;
        rc = semop(semID, ops, 2);
        if (rc == -1)
        {
            perror("SEMOP 2");
            return -1;
        }

        ops[0].sem_num = 0;
        ops[0].sem_op = -1;
        ops[0].sem_flg = 0;

        ops[1].sem_num = 1;
        ops[1].sem_op = -1;
        ops[1].sem_flg = 0;
        rc = semop(semID, ops, 2);
        if (rc == -1)
        {
            perror("SEMOP 3");
            return -1;
        }
        strcpy(buf, message->string);
        printf("server get message : %s\n", buf);

        ops[0].sem_num = 0;
        ops[0].sem_op = 0;
        ops[0].sem_flg = IPC_NOWAIT;

        ops[1].sem_num = 1;
        ops[1].sem_op = 1;
        ops[1].sem_flg = IPC_NOWAIT;
        rc = semop(semID, ops, 2);
        if (rc == -1)
        {
            perror("SEMOP 4");
            return -1;
        }
        rc = shmdt(message);
        if (rc == -1)
        {
            perror("client: shmdt() failed");
            return -1;
        }
        if (buf[0] == 'k' && buf[1] == 'l')
        {
            shutdown(client, SHUT_RDWR);
            return 0;
        }
    }
}

int receive_file(int client)
{
    int key = MSGKEY_RCV;
    int msgid;
    qmsg my_msg;
    int er;
    char buf[BUFSIZ];
    msgid = msgget(key, 0666);
    if(msgid == -1)
    {
        perror("msgget error\n");
        return -1;
    }
    my_msg.is_file_over = 0;
    my_msg.mtype = getpid();
    while (1)
    {
        er = recv(client, buf, BUFSIZ, 0);
        if (er < 0)
            break;
        if (er == 0)
            break;
        printf("%s", buf);
        strcpy(my_msg.msg_text, buf);
        if (msgsnd(msgid, &my_msg, BUFSIZ, 0) < 0)
        {
            perror("message can't be sent to compile server!!!");
            shutdown(client, SHUT_RDWR);
            exit(-1);
        }
    }
    my_msg.is_file_over = 1;
    msgsnd(msgid, &my_msg, BUFSIZ, 0);
    return 0;
}

void send_compiled_file(int sock)
{
    int msgid;
    int key = MSGKEY_SND;
    qmsg my_msg;
    //char buf[BUFSIZ];
    //int read_num;
    msgid = msgget(key, 0666);
    if (msgid == -1)
    {
        perror("msgget error\n");
        return;
    }
    while (1)
    {
        msgrcv(msgid, &my_msg, BUFSIZ + sizeof(int), getpid(), 0);
        printf("msg of compiled part received\n");
        if(my_msg.is_file_over)
            break;
        send(sock, my_msg.msg_text, BUFSIZ, 0);
    }
    // strcpy(buf, "fin!");
    // send(sock, buf, 5, 0);
    shutdown(sock, SHUT_RDWR);
    system("sleep 2");
    
}