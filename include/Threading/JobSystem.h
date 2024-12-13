#ifndef JOBSYSTEM_H
#define JOBSYSTEM_H
#include <Threading/Job.h>
#include <queue>
#include<mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>

class JobSystem {
public:
    JobSystem(unsigned int threadCount = std::thread::hardware_concurrency() - 1);
    ~JobSystem();

    void AddJob(JobPtr job);
    void WaitForAllJobs();
private:
    void WorkerThread();
    std::queue<JobPtr> m_jobQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_condition;
    std::vector<std::thread > m_threads;
    std::atomic<bool> m_shouldExit{false};
    std::atomic<int> m_activeJobs{0};
};

#endif //JOBSYSTEM_H
