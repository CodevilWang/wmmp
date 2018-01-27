// Copyright 2017 codevil All Rights Reserved.
// Author: codevil.w.m@gmail.com (M. W.)
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
int cnt_up() {
    static __thread int cnt = 0;
    ++cnt;
    return cnt;
}
void* work(void* args) {
    int* ret = new int(0);
    while (1) {
        *ret = cnt_up(); 
        if (*ret >= 500) {
            return ret;
        }
    }
}

int main() {
    std::vector<pthread_t> p_v;
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("main pid %u tid %u (0x%x)\n", pid,
                                       tid,
                                       tid);
    int total_p_num = 10;
    p_v.resize(total_p_num);
    for (int i = 0; i < total_p_num; ++i) {
        pthread_create(&p_v[i], NULL, work, NULL);
    }
    int total_ret = 0;
    int* ret = NULL;
    for (int i = 0; i < total_p_num; ++i) {
        pthread_join(p_v[i], (void**)(&ret));
        total_ret += *ret;
        printf("here %p\n", ret);
        if (ret != NULL) {
            delete ret;
            ret = NULL;
        }
    }
    printf("total_ret[%d]\n", total_ret);
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
