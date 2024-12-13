#ifndef JOB_H
#define JOB_H
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

class Job {
public:
    using JobFunction = std::function<void()>;

    Job(JobFunction function, std::string description)
        : m_function(std::move(function)), m_description(std::move(description)) {}

    virtual ~Job() = default;

    virtual void Execute() {
        std::cout << "Thread " << std::this_thread::get_id() << " executing job: " << m_description << std::endl;
        m_function();
    }

    const std::string& GetDescription() const { return m_description; }

private:
    JobFunction m_function;
    std::string m_description;  // Remove the reference (&)
};

using JobPtr = std::shared_ptr<Job>;

#endif //JOB_H
