#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <math.h>

double fTest1(double x)
{
    return 5;
}

double fTest2(double x)
{
    return sin(2 * x) + cos(5 * x);
}

double calcTrapezio(double inicio, double fim)
{
    double h = fim - inicio;
    // double hInicio = fTest1(inicio);
    // double hFim = fTest1(fim);
    double hInicio = fTest2(inicio);
    double hFim = fTest2(fim);

    return (h * (hInicio + hFim) / 2);
}

void *thread_return;

int numThreads = 2;
int numTrapezios = 4;

std::vector<double> somaTrapezios;

float a = 0;
float b = 10;

double trapeziosPorThread = (int)numTrapezios / numThreads;
float crescimento = (b - a) / numTrapezios;

void *mainThreads(void *tid)
{
    int maxTrapezios;
    double localA, localB;
    int positionTid = (int)(size_t)tid;

    if (positionTid == numThreads - 1)
        maxTrapezios = numTrapezios - (positionTid * trapeziosPorThread);
    else
        maxTrapezios = trapeziosPorThread;

    localA = a + (positionTid * crescimento * trapeziosPorThread);

    for (int i = 0; i < maxTrapezios; i++)
    {
        localB = localA + crescimento;

        somaTrapezios[(positionTid * trapeziosPorThread) + i] = calcTrapezio(localA, localB);

        localA = localB;
    }
}

int main(int argc, char const *argv[])
{
    int status;
    pthread_t threads[numThreads];

    somaTrapezios.resize(numTrapezios);

    for (int i = 0; i < numThreads; i++)
    {
        status = pthread_create(&threads[i], NULL, mainThreads, (void *)(size_t)i);

        if (status != 0)
        {
            printf("Erro na criação da thread. Codigo de Erro: %d\n", status);
            return 1;
        }
    }

    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], &thread_return);
    }

    double area = 0;
    for (int i = 0; i < somaTrapezios.size(); i++)
    {
        area += somaTrapezios.at(i);
    }

    if (area < 0)
        printf("Área Total = %.2e\n", area);
    else
        printf("Área Total = %.lf\n", area);

    return 0;
}
