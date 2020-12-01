#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::map;
using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() {
}

Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  
    vector<int> pids{LinuxParser::Pids()};
    set<int> extant_pids;
  
    for (Process& process : processes_) {
        extant_pids.insert(process.Pid());
    }
  
    // Emplace(push) all new processes
    for (int pid : pids) {
        if (extant_pids.find(pid) == extant_pids.end()) {
            Process proc(pid);
            processes_.emplace_back(proc);
        }
    }
  
    // update CPU utilization
    for (auto& process : processes_) {
        process.setCpuUtilization();
    }

    std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
  
    return processes_;
}

// TODO(C): Return the system's kernel identifier (string)
std::string System::Kernel() const { return LinuxParser::Kernel(); }

// TODO(C): Return the system's memory utilization
float System::MemoryUtilization() const { return LinuxParser::MemoryUtilization(); }

// TODO(C): Return the operating system name
std::string System::OperatingSystem() const { return LinuxParser::OperatingSystem(); }

// TODO(C): Return the number of processes actively running on the system
int System::RunningProcesses() const { return LinuxParser::RunningProcesses(); }

// TODO(C): Return the total number of processes on the system
int System::TotalProcesses() const { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long System::UpTime() const { return LinuxParser::UpTime(); }
