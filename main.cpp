#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#define MAX_CLIENTS 5
std::mutex mut;

void client(int& count)
{
    while (count != MAX_CLIENTS)
    {
        mut.lock();
        count++;
        std::cout << "(Queue) Clients in queue: " << count << std::endl;
        mut.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void oper(int& count)
{
    while (count != 0)
    {
        mut.lock();
        count--;
        std::cout << "(oper) Clients in queue: " << count << std::endl;
        mut.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{

    int countClients = 0;
    std::thread clients(client, std::ref(countClients));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread opers(oper, std::ref(countClients));
    opers.join();
    clients.join();
}