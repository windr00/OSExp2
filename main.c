#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>


int tot = 0; /* 当前产品总数目 */
#define BUFFER_LEN 5 /* 缓冲区的长度 */
int buffer[BUFFER_LEN];
/* 缓冲区 */
int in, out;
/* 产品进、出缓冲区的指针 */
sem_t FullSemaphore;
/* 缓冲区满的信号量（已在缓冲区中的产品数） */
sem_t EmptySemaphore;
/* 缓冲区空的信号量（空闲缓冲区数） */
sem_t PMutex, CMutex; /*互斥信号量 */

#define MAX_THREAD_NUM 100 /* 最大线程数目 */
pthread_t Thread[MAX_THREAD_NUM];
/* 线程数组 */
typedef struct _ThreadInfo {
    /* 线程信息结构 */
    char entity;
    /* 生产者还是消费者 */
    int ID;
    /* 线程标示 */
    int sleeptime;
    /* 休息时间 */
    int num; /* 生产产品编号 */
} ThreadInfo;
ThreadInfo Thread_Info[MAX_THREAD_NUM];


void threads_init(int pnum, int cnum) {
    for (int i = 0; i < pnum; i++) {
        Thread_Info[i].entity = 'P';
        Thread_Info[i].sleeptime = (rand() % 3);
    }

    for (int j = pnum; j < pnum + cnum; j++) {
        Thread_Info[j].entity = 'C';
        Thread_Info[j].sleeptime = rand() % 4;
    }
}

void *consume(void *s) {
    tot--;
    printf("out index: %d\n", out);
    int prod = buffer[out];
    printf("consumed product id : %d\n", prod);
    out++;
    out %= 5;

    printf("product count : %d\n\n", tot);
}


void *Consumer(void *p) {
    unsigned sleep_time = (unsigned) ((ThreadInfo *) p)->sleeptime;
    int thread_num = ((ThreadInfo *) p)->ID;
    while (1) {

            sleep(sleep_time);
            sem_wait(&FullSemaphore);
            sem_wait(&CMutex);
            printf("CONSUMER %d consuming product\n", thread_num);
            consume(NULL);
            sem_post(&CMutex);
            sem_post(&EmptySemaphore);
    }
}


void *produce(void *s) /* 生产者执行的函数，将产品放入缓冲区 */
{
    tot++;
    printf("product num: %d\n", *((int *) s));
    buffer[in] = *(int *) s;
    in++;
    in = in % BUFFER_LEN;
    printf("total product count: %d\n\n", tot);
//    获取线程标示、产品编号；
//    当前产品总数加1；
//    打印生产者标示、产品ID;
//    将生产的产品放入缓冲区；
//    移动产品进入缓冲区的指针；
//    打印当前产品总数；
}

void *Product(void *p) /* 生产者线程 */
{
    int product_num = 0;
    unsigned sleep_time = (unsigned) (((ThreadInfo *) p)->sleeptime);
    int thread_num = ((ThreadInfo *) p)->ID;
    while (1) {
        if (tot < 5) {
            sleep(sleep_time);
            sem_wait(&EmptySemaphore);
            sem_wait(&PMutex);
            printf("PRODUCER %d producing product\n", thread_num);
            produce(&product_num);
            sem_post(&PMutex);
            sem_post(&FullSemaphore);
            product_num++;
        }
    }
//    获取线程的休眠时间并休眠；
//    空闲缓冲区信号量操作；
//    互斥信号量操作；
//    调用生产函数；
//    互斥信号量操作；
//    满缓冲区信号量操作；
}

void *status;

int main(int argc, char *argv[]) {
    int pnum = 2, cnum = 20;
    threads_init(pnum, cnum); /* 初始化各个线程数据，线程类型、标示等 */
    printf("this project is done by 冉惟之, stu. id : 2013060105023\n");
    sem_init(&FullSemaphore, 0, 0);
    sem_init(&EmptySemaphore, 0, BUFFER_LEN);
    sem_init(&PMutex, 0, 1);
    sem_init(&CMutex, 0, 1);
    for (int i = 0; i < pnum; i++) {
        pthread_create(&Thread[i], NULL, Product, &Thread_Info[i]);
        Thread_Info[i].ID = i;
    }
    for (int i = pnum; i < pnum + cnum; i++) {
        Thread_Info[i].ID = i;
        pthread_create(&Thread[i], NULL, Consumer, &Thread_Info[i]);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(Thread[i], &status);
    }


//    初始化信号量；
//
//    初始化产品进、出缓冲区的指针；
//
//    创建生产者、消费者线程；
//
//    等待子线程结束；
}
