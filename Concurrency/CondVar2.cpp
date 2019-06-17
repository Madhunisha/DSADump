#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

mutex mut;
condition_variable condVar;
enum class Laundry {DIRTY, CLEAN};
Laundry SONS_LAUNDRY = Laundry::CLEAN;
bool isLaundryDirty () {
    return SONS_LAUNDRY == Laundry::DIRTY;
}
bool isLaundryClean () {
    return SONS_LAUNDRY == Laundry::CLEAN;
}
void doLaundry() {
    std::unique_lock<std::mutex> lock(mut);
    condVar.wait(lock, isLaundryDirty);
    std::cout << "Doing the son's laundry." << std::endl;
    SONS_LAUNDRY = Laundry::CLEAN;
    std::cout << "The laundry is clean." << std::endl;
    lock.unlock();
    condVar.notify_one();
}

void playAround() {
    std::cout << "Playing basketball and sweating." << std::endl;
    {
        std::lock_guard<std::mutex> lock(mut);
        SONS_LAUNDRY = Laundry::DIRTY;
    }
    std::cout << "Asking mother to do the laundry." << std::endl;
    condVar.notify_one();
    {
        std::unique_lock<std::mutex> lock(mut);
        condVar.wait(lock, isLaundryClean);
    }
    std::cout << "I have a clean laundry! Thank you mum!" << std::endl;
}


int main() {
    std::thread mother(doLaundry);
    std::thread son(playAround);

    mother.join();
    son.join();
}