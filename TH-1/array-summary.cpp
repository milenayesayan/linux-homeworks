#include <iostream>
#include <string>
#include <pthread.h>
#include <algorithm>
#include <string.h>
#include <chrono>

struct local_sum_arg
{
    int* array;
    int start;
    int end;
};

void* local_sum(void* arg)
{
    local_sum_arg* part = (local_sum_arg*) arg;
    int sum = 0;
    for(int i = part->start; i < part->end; ++i)
    {
        sum += part->array[i];
    }

    return new int(sum);
}





int main(int argc, char **argv)
{

    int N;
    std::cin >> N;

    int* array = new int[N];

    for (int i = 0; i < N; ++i) {
        array[i] = 3;
    }

    int sum = 0;

    auto start_without_th = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sum += array[i];
    }

    auto end_without_th = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_without_th - start_without_th;




    int size = N;
    int M;
    std::cin >> M;
    int threads_count = M;
    int global_sum = 0;
    for(int i = 0; i < size; ++i)
    {
        array[i] = 1;
    }

    auto start_with_th = std::chrono::high_resolution_clock::now();


    pthread_t* threads = new pthread_t[threads_count];
    local_sum_arg** array_of_args = new local_sum_arg*[threads_count];
    for(int i = 0; i < threads_count; ++i)
    {
        array_of_args[i] = new local_sum_arg;
        array_of_args[i]->array = array;
        array_of_args[i]->start = i * (size / threads_count);
        array_of_args[i]->end = std::min(array_of_args[i]->start + (size / threads_count), size);
        int result = pthread_create(&threads[i], NULL, local_sum, array_of_args[i]);
        if(result != 0)
        {
            std::cerr << strerror(result) << std::endl;
            exit(result);
        }
    }


    for(int i = 0; i < threads_count; ++i)
    {
        void* return_value;
        int result = pthread_join(threads[i], &return_value);
        int* local_sum_result = (int*)return_value;
        global_sum += *local_sum_result;
        delete local_sum_result;
        delete array_of_args[i];
    }

    auto end_with_th = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end_with_th - start_with_th;
    
    std::cout << "Time spent without threads " << duration.count() << std::endl;

    std::cout << "Time spent with " << M <<" threads: " << duration1.count() << std::endl;


    delete[] array_of_args;
    delete[] array;


    return 0;
}

