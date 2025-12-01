#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int nThreads = 5;
int nEtapas = 4;

typedef struct {
    int count;
    int N;
    int etapa;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrier;

barrier b; // Variable global para la barrera

void barrierInit(barrier* b, int N) {
    b->count = 0;
    b->N = N;
    b->etapa = 0;

    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
}

void barrierWait(barrier* b){
    int etapa;
    pthread_mutex_lock(&b->mutex);

    etapa = b->etapa;
    b->count++;

    if(b->count == b->N){
        b->count = 0;
        b->etapa++;
        pthread_cond_broadcast(&b->cond);
    }
    else{
        while(b->etapa == etapa){
            pthread_cond_wait(&b->cond, &b->mutex);
        }
    }

    pthread_mutex_unlock(&b->mutex);
}

void barrierDestroy(barrier* b){
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->cond);
}

void *thread_work(void *arg) {
    long tid = (long)arg;

    for (int e = 1; e <= nEtapas; e++) {
        usleep(rand() % 100000);

        printf("[TID %ld] esperando en etapa %d.\n", tid, e);

        barrierWait(&b);

        printf("[TID %ld] paso barrera en etapa %d.\n", tid, e);
    }

    return NULL;
}

int main(int argc, char* argv[]){

    if(argc > 2){
        nThreads = atoi(argv[1]);
        nEtapas = atoi(argv[2]);
    }

    srand(time(NULL));

    barrierInit(&b, nThreads);

    pthread_t threads[nThreads];

    for(long i = 0; i < nThreads; i++) pthread_create(&threads[i], NULL, thread_work, (void *)i);

    for(int i = 0; i< nThreads; i++) pthread_join(threads[i], NULL);

    barrierDestroy(&b);

    return 0;
}
