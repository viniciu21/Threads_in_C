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
    int local_a;
    int local_b;
    int i;
};
void* hello_world(void *argumentos){

    struct argsThreads *args = (struct argsThreads *)argumentos;

    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    
// atoi(argv[1]);
// atoi(argv[2]);
    int numero_threads = 2;
    int numero_trapesios = 4;

    int a = 0;
    int b = 12;

    struct testes test1;
    test1.a = 0;
    test1.b = 12;
    int h = (test1.b - test1.a)/numero_trapesios;
    pthread_t threads_trapezios[numero_threads];

    struct argsThreads args;
    args.local_a = a;
    args.local_b = b;
    args.i = 0;

    for (int i = 0; i < numero_threads; i++){
        args.i = i;
        pthread_create(&threads_trapezios[i], NULL, hello_world, (void * )(size_t) &args);
        pthread_join(threads_trapezios[i], &thread_return);
    }

    return 0;
}
