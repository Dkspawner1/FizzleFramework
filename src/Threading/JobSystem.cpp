#include <Threading/JobSystem.h>

JobSystem::JobSystem(unsigned int threadCount) {
    for (unsigned int i = 0; i < threadCount; ++i) {
        m_threads.emplace_back(&JobSystem::WorkerThread, this);
    }
}

JobSystem::~JobSystem() {
    m_shouldExit = true;
    m_condition.notify_all();
    for (auto &thread: m_threads) {
        thread.join();
    }
}

void JobSystem::AddJob(JobPtr job) { {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_jobQueue.push(std::move(job));
    }
    ++m_activeJobs;
    m_condition.notify_one();
}

void JobSystem::WorkerThread() {
    while (!m_shouldExit) {
        JobPtr job;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_condition.wait(lock, [this] { return !m_jobQueue.empty() || m_shouldExit; });
            if (m_shouldExit && m_jobQueue.empty()) return;
            job = std::move(m_jobQueue.front());
            m_jobQueue.pop();
        }
        job->Execute();
        m_activeJobs--;
    }
}

void JobSystem::WaitForAllJobs() {
    while (m_activeJobs > 0)
        std::this_thread::yield();
}