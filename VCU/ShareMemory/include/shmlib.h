#ifndef SHMLIB_H
#define SHMLIB_H

#include <pthread.h>

//struct shared memeory using mutex
typedef struct shm_struct_for_test {
    pthread_mutex_t mtx;
    int r;
    int data;
} shm_t;

//shared memory init
shm_t* shm_initialize(int shmkey);
//shared memory finalize
void shm_finalize(int shmid, shm_t* shm);
//write data to shm
void update_data(shm_t* shm, int value);
//read data from shm
int read_data(shm_t* shm, int* r);

#endif