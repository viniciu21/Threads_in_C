#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *thread_return;

struct testes{
    int a;
    int b;
};

struct argsThreads{
    int a;
    int b;
    int h;
    int i;
};

double areasoma = 0;
int soma = 0;

void* hello_world(void *argumentos){

    struct argsThreads *args = (struct argsThreads *)argumentos;

    printf("%d %d %d %d \n", args->a, args->b, args->h, args->i);

    soma += args->i;

    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    
// atoi(argv[1]);
// atoi(argv[2]);
    int numero_threads = 5;
    int numero_trapesios = 4;

    pthread_t threads_trapezios[numero_threads];

    struct testes test1;
    test1.a = 0;
    test1.b = 12;
    int h = (test1.b - test1.a)/numero_trapesios;
    pthread_t threads[numero_threads];

    struct argsThreads args;
    args.a = test1.a;
    args.b = test1.b;
    args.h = h;
    args.i = 0;

    for (int i = 0; i < numero_threads; i++){
        args.i = i;
        printf("%d %d\n", i, args.i);
        pthread_create(&threads[i], NULL, hello_world, (void * ) &args);
    }

    
    for(int i = 0; i < numero_threads; i++){
        pthread_join(threads[i], &thread_return);
    }

    printf("soma %d\n", soma);

    return 0;
}
