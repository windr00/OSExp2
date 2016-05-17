//
// Created by 冉惟之 on 16/5/17.
//

#ifndef OSEXP2_TYPEDEFINES_H
#define OSEXP2_TYPEDEFINES_H

#include <sys/semaphore.h>
#include <pthread.h>

#define BUFFER_LEN 5 /* 缓冲区的长度 */
int buffer[BUFFER_LEN];
/* 缓冲区 */
int in, out;
/* 产品进、出缓冲区的指针 */
sem_t FullSemaphore;
/* 缓冲区满的信号量（已在缓冲区中的产品数） */
sem_t EmptySemaphore;
/* 缓冲区空的信号量（空闲缓冲区数） */
sem_t Mutex; /*互斥信号量 */

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
/* 线程信息数组 */

int tot = 0; /* 当前产品总数目 */


#endif //OSEXP2_TYPEDEFINES_H
