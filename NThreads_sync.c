#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 5

pthread_t threads[NTHREADS];
int status, i;
void *thread_return;

int soma = 0;

void* hello_world(void *tid){
    if((int)(size_t)tid > 0){
        pthread_join(threads[(size_t)tid-1], &thread_return);
        printf("Esta é a Thread %d. A Thread %d terminou. ", (int) (size_t)tid, (int) (size_t)tid-1);
    }
    else
        printf("Esta é a primeira Thread.");     
    
    soma += 1;
    printf("O valor de soma eh: %d\n", soma);
    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    
    
    for (i = 0; i < NTHREADS; i++){
        printf("Processo principal criando thread #%d\n", i);
        status = pthread_create(&threads[i], NULL, hello_world, (void *)(size_t) i);

        if(status!=0){
            printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
            return 1;
        }
    }

    printf("Esperando Thread %d finalizar...\n", i-1);
    pthread_join(threads[i-1], &thread_return);
    printf("Thread %d finalizada\n", i-1);

    printf("Processo pai vai finalizar e soma = %d\n", soma);

    
    return 0;
}
