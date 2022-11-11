#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <mutex>
 
std::mutex g_lock;

void Download(std::string arguments, std::ofstream& out)
{
    std::stringstream path;
    path << "./script.sh " << arguments;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    system(path.str().c_str());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    g_lock.lock();

    out << "Downloaded file " << arguments << " in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms.\n";
    
    g_lock.unlock();
}   

int main() 
{
    std::ofstream out("log.txt");
    std::cout << "Enter arguments\n:";
    while (true)
    {
        std::string arguments;
        std::cin >> arguments;
        if (arguments == "q")
            break;

        std::thread thr(Download, arguments, std::ref(out));
        thr.detach();
    }
    
    out.close();
    return 0;
}
