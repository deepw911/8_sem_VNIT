
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

class LamportMutex {
public:
    LamportMutex(int N) {
        numProcess = N;
        ticketNumbers.resize(numProcess);
        enteringFlags.resize(numProcess, false);
        lastToEnter = 0;
    }

    void lock(int pid) {
        // indicate that the process is entering the critical section. 
        enteringFlags[pid] = true;
        ticketNumbers[pid] = maxTicket() + 1;
        //  indicate that the process has entered the critical section.
        enteringFlags[pid] = false;

        for (int i = 0; i < numProcess; ++i) {
            if (i == pid) {
                continue;
            }

            // waiting till the process has entered the critical section.
            while (enteringFlags[i]) {
                this_thread::yield();
            }

            while (ticketNumbers[i] != 0 && (ticketNumbers[pid] > ticketNumbers[i] || (ticketNumbers[pid] == ticketNumbers[i] && pid > i))) {
                this_thread::yield();
            }
        }
    }

    void unlock(int pid) {
        ticketNumbers[pid] = 0;
    }

private:
    int numProcess;
    vector<int> ticketNumbers;
    vector<bool> enteringFlags;
    atomic<int> lastToEnter;

    int maxTicket() const {
        int max = ticketNumbers[0];
        for (int i = 1; i < numProcess; ++i) {
            if (ticketNumbers[i] > max) {
                max = ticketNumbers[i];
            }
        }
        return max;
    }
};

const int numProcess =2;
const int numIterations = 2;

void processFunction(int pid, LamportMutex& mutex) {
    for (int i = 0; i < numIterations; ++i) {
        mutex.lock(pid);
        cout << "Process " << pid << " locked the mutex, entering critical section" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Process " << pid << " unlocking the mutex, exited critical section" << endl;
        mutex.unlock(pid);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    LamportMutex mutex(numProcess);

    vector<thread> Process;
    Process.reserve(numProcess);
    for (int i = 0; i < numProcess; ++i) {
        Process.emplace_back(processFunction, i, ref(mutex));
    }

    for (int i = 0; i < numProcess; ++i) {
        Process[i].join();
    }

    return 0;
}
