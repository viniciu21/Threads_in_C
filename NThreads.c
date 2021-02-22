#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NTHREADS 5

int soma = 0;

void* hello_world(void *tid){
    printf("Hello World. Esta é a Thread %d\n", (int) (size_t)tid);
    soma += 1;
    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NTHREADS];
    int status, i;
    void *thread_return;

    for (i = 0; i < NTHREADS; i++){
        printf("Processo principal criando thread #%d\n", i);
        status = pthread_create(&threads[i], NULL, hello_world, (void *)(size_t) i);

        if(status!=0){
            printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
            return 1;
        }
    }

    for (i = 0; i < NTHREADS; i++)
    {
        printf("Esperando Thread %d finalizar...\n", i);
        pthread_join(threads[i], &thread_return);
        printf("Thread %d finalizada\n", i);
    }

    printf("Soma: %d\n", soma);
    
    return 0;
}
