#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    std::cout << "worker process started\n";

    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    std::cout << "worker process is processing data\n";
    data += " after process";

    processed = true;

    lk.unlock();
    cv.notify_one();

    std::cout << "worker process finished\n";
}

int main()
{
    std::thread worker(worker_thread);

    data = "Example data";

    {
        std::lock_guard<std::mutex> lk(m);

        ready = true;
        
        std::cout << "main() singals data ready for processing\n";
    }

    cv.notify_one();

    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }

    std::cout << "back in main(), data = " << data << std::endl;

    worker.join();

    return 0;
}




