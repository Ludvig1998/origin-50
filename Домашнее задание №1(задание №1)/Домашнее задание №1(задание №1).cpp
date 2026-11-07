#include <iostream>
#include <thread>
#include <chrono>

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

const int Max_number_Clients = 20;

void Increase_Clients(int* log, int step, int current)
{
    if (step >= Max_number_Clients)
        return;

    std::this_thread::sleep_for(100ms);

    current += 1;                            
    log[step] = current;
    std::cout << "connect+" << current << " ";

    Increase_Clients(log, step + 1, current);
}

void Decrease_Clients(int* log, int step, int current)
{
    if (step >= Max_number_Clients)
        return;

    std::this_thread::sleep_for(200ms);

    current -= 1;                            
    log[step] = current;
    std::cout << "disconnect-" << current << " ";

    Decrease_Clients(log, step + 1, current);
}

int main()
{
    int connect_log[Max_number_Clients] = { 0 };
    int disconnect_log[Max_number_Clients] = { 0 };

   
    std::thread t1(Increase_Clients, connect_log, 0, 0);
    std::thread t2(Decrease_Clients, disconnect_log, 0, Max_number_Clients);

    t1.join();
    t2.join();

    std::cout << "connect_log:"<<std::endl;
    for (int x : connect_log) 
    std::cout << x << " ";       
    std::cout<< std::endl;
    std::cout << "disconnect_log: " << std::endl;
    for (int x : disconnect_log) 
    std::cout << x << " ";     
    std::cout << std::endl;

    return 0;
}