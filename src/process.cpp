#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;

Process::Process() {
}

Process::Process(int pid) {
	pid_ = pid;
	cpu_ = LinuxParser::CpuUtilization(pid);
	cmd_ = LinuxParser::Command(pid);
	ram_ = LinuxParser::Ram(pid);
	user_ = LinuxParser::User(pid);
	uptime_ = LinuxParser::UpTime(pid);
}

// TODO: Return this process's ID
int Process::Pid() const {
	return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
	return cpu_;
}

void Process::setCpuUtilization() {
	cpu_ = LinuxParser::CpuUtilization(Process::Pid());
}

// TODO: Return the command that generated this process
string Process::Command() const {
	return cmd_;
}

// TODO: Return this process's memory utilization
string Process::Ram() const {
	return ram_;
}

// TODO: Return the user (name) that generated this process
string Process::User() const {
	return user_;
}

// TODO: Return the age of this process (in seconds)
long Process::UpTime() const {
	return uptime_;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const
{
	// return this->CpuUtilization() > a.CpuUtilization();
	return this->cpu_ > a.cpu_;
}
