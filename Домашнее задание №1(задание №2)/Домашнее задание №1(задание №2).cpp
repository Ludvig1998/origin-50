// Домашнее задание №1(задание №2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std::chrono;

void Element_wise_addition(const std::vector<int>& vec1, const std::vector<int>& vec2,std::vector<int>& vec3, std::size_t start, std::size_t end)
{
    for (std::size_t i = start; i < end; ++i)
    {
        vec3[i] = vec1[i] + vec2[i];
    }
}

void run_parallel_sum(int sizet, const std::vector<int>& vec1, const std::vector<int>& vec2, std::vector<int>& vec3)
{
    std::size_t n = vec1.size();
    if (n == 0) return;

 
    std::vector<std::thread> VT(sizet);

   
    std::size_t chunk_size = (n + sizet - 1) / sizet;


    for (int i = 0; i < sizet; ++i)
    {
        std::size_t start = i * chunk_size;
        std::size_t end = std::min(start + chunk_size, n);

        if (start >= n) break; 

        
        VT[i] = std::thread(Element_wise_addition, std::cref(vec1), std::cref(vec2), std::ref(vec3), start, end);
    }

    for (int i = 0; i < sizet; i++)
    {
        if (VT[i].joinable())
            VT[i].join();
    }
}

int main()
{
    int n = std::thread::hardware_concurrency();
    std::cout << "Number_MAX of threads = " << n << std::endl;
    const std::vector<std::size_t> sizes = { 1'000, 10'000, 100'000, 1'000'000 };
    const std::vector<int> thread_counts = { 1, 2, 4, 8, 16 };


    for (std::size_t n : sizes)
    {
        std::cout << "\n----------------------------------------\n";
        std::cout << "  Array Size : " << n << " elements\n";
        std::cout << "----------------------------------------\n";

      
        std::vector<int> a(n, 1);
        std::vector<int> b(n, 2);
        std::vector<int> c(n, 0);

        for (int t : thread_counts)
        {
           
            auto start_time = std::chrono::steady_clock::now();
           
            run_parallel_sum(t, a, b, c);

            auto end_time = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> ms = end_time - start_time;

            std::cout << "  Streams: "  << t
                << " \t-> Time: " << ms.count() << " ms\n";
        }
    }

    return 0;
}


