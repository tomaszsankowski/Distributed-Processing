# include <stdio.h>
# include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

int primes[100];
int primes_size = 0;
pthread_mutex_t mx;

struct thread_data {
    int* tab;
    size_t size;
};

void swap(int* a, int* b)
{
    const int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int arr[], const int n)
{
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

bool checkIfPrime(const int x)
{
    if(x<2)
    {
        return false;
    }
    for(int i = 2;i < x; i++)
    {
        if(x%i==0)
        {
            return false;
        }
    }
    return true;
}

void * f ( void * arg )
{
    const struct thread_data* data = (struct thread_data*)arg;
    int* tab = data->tab;
    const size_t size = data->size;
    for(int i = 0; i < size; i++)
    {
        if(!checkIfPrime(tab[i]))
        {
            printf("Checked %d! It is not prime!\n", tab[i]);
            tab[i] = -1;
        }
        else
        {
            pthread_mutex_lock(&mx);
            primes[primes_size++] = tab[i];
            pthread_mutex_unlock(&mx);
            printf("Checked %d! It is prime!\n", tab[i]);

        }
    }
    return NULL ;
}

int main ()
{
    const int thread_number = 10;

    pthread_t threads[10];
    int tab[100];
    for(int i = 1;i <= 100; i++)
    {
        tab[i-1] = i;
    }

    struct thread_data datas[10];

    for(int i = 0;i < thread_number; i++)
    {
        datas[i].tab = &tab[10*i];
        datas[i].size = 10;

        pthread_create(&threads[i], NULL, f, (void*)(&datas[i]));
    }

    for(int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for(int i = 0;i < 100; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    int filtered_out[100];
    unsigned int size = 0;
    for(int i = 0;i < 100; i++)
    {
        if(tab[i]!=-1)
            filtered_out[size++] = tab[i];
    }

    bubbleSort(filtered_out, size);

    for(int i = 0;i < size; i++)
    {
        printf("%d ", filtered_out[i]);
    }

    bubbleSort(primes, primes_size);

    printf("\n");
    for(int i = 0;i < primes_size; i++)
    {
        printf("%d ", primes[i]);
    }

    return 0;
}
