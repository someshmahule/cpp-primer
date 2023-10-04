#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>


class Task {
public:
    Task(int id) : id(id) {}

    void execute() {
        std::cout << "Task " << id << " is executing." << std::endl;
        // Simulate some work here
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Task " << id << " is done." << std::endl;
    }

private:
    int id;
};

class TaskManager {
public:
    TaskManager(int numThreads) : numThreads(numThreads) {
        // Initialize threads
        for (int i = 0; i < numThreads; ++i) {
            threads.push_back(std::thread(&TaskManager::worker, this));
        }
    }

    ~TaskManager() {
        // Join threads on destruction
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    void addTask(Task task) {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.push(std::move(task));
        conditionVariable.notify_one();
    }

private:
    int numThreads;
    std::vector<std::thread> threads;
    std::queue<Task> tasks;
    std::mutex mutex;
    std::condition_variable conditionVariable;

    void worker() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            if (tasks.empty()) {
                conditionVariable.wait(lock);
            }

            if (!tasks.empty()) {
                Task task = std::move(tasks.front());
                tasks.pop();
                lock.unlock();
                task.execute();
            }
        }
    }
};


int main() {
    const int numThreads = 4; // You can change the number of threads as needed
    TaskManager taskManager(numThreads);

    // Add some tasks
    for (int i = 0; i < 10; ++i) {
        Task task(i);
        taskManager.addTask(task);
    }

    // Sleep to allow tasks to complete (in a real application, you'd use proper synchronization)
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}

