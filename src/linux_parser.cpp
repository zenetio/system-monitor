#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

// using std::stoi;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
	string line;
	string key;
	string value;
	std::ifstream filestream(kOSPath);
	if (filestream.is_open()) {
		while (std::getline(filestream, line)) {
			std::replace(line.begin(), line.end(), ' ', '_');
			std::replace(line.begin(), line.end(), '=', ' ');
			std::replace(line.begin(), line.end(), '"', ' ');
			std::istringstream linestream(line);
			while (linestream >> key >> value) {
				if (key == "PRETTY_NAME") {
					std::replace(value.begin(), value.end(), '_', ' ');
					return value;
				}
			}
		}
	}
	return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
	string os, version, kernel;
	string line;
	std::ifstream stream(kProcDirectory + kVersionFilename);
	if (stream.is_open()) {
		std::getline(stream, line);
		std::istringstream linestream(line);
		linestream >> os >> version >> kernel;
	}
	return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
	vector<int> pids;
	DIR* directory = opendir(kProcDirectory.c_str());
	struct dirent* file;
	while ((file = readdir(directory)) != nullptr) {
		// Is this a directory?
		if (file->d_type == DT_DIR) {
			// Is every character of the name a digit?
			string filename(file->d_name);
			if (std::all_of(filename.begin(), filename.end(), isdigit)) {
				int pid = stoi(filename);
				pids.push_back(pid);
			}
		}
	}
	closedir(directory);
	return pids;
}


// TODO(C): Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
	string StrMemTotal = "MemTotal:";
	string StrMemFree = "MemFree:";

	vector<string> values;
	string line;

	float MemTotalValue, MemFreeValue;
	float result;

	std::ifstream stream(kProcDirectory + kMeminfoFilename);
	while (getline(stream, line)) {
		if (line.compare(0, StrMemTotal.size(), StrMemTotal) == 0) {
			std::istringstream MemInfoStr(line);
			std::istream_iterator<string> beg(MemInfoStr), end;
			values = vector<string>(beg, end);

			MemTotalValue = stof(values[1]);
		}
		if (line.compare(0, StrMemFree.size(), StrMemFree) == 0) {
			std::istringstream MemInfoStr(line);
			std::istream_iterator<string> beg(MemInfoStr), end;
			values = vector<string>(beg, end);

			MemFreeValue = stof(values[1]);
		}
	}
	float UsedMemValue = MemTotalValue - MemFreeValue;
	result = UsedMemValue / MemTotalValue;
	return result;
}

// TODO(C): Read and return the system uptime
long LinuxParser::UpTime() {
	std::ifstream stream(kProcDirectory + kUptimeFilename);
	vector<string> values = getValue(stream);
	long int result = stoi(values[0]);
	return result;
}

// TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid) {}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
	std::ifstream stream(kProcDirectory + kStatFilename);
	vector<string> values = getValue(stream);
	long userVal = stoi(values[CPUStates::kUser_]);
	long niceVal = stoi(values[CPUStates::kNice_]);
	long systemVal = stoi(values[CPUStates::kSystem_]);
	long irqVal = stoi(values[CPUStates::kIRQ_]);
	long softirqVal = stoi(values[CPUStates::kSoftIRQ_]);
	long stealVal = stoi(values[CPUStates::kSteal_]);
	long guestVal = stoi(values[CPUStates::kGuest_]);
	long guestniceVal = stoi(values[CPUStates::kGuestNice_]);

	long result = userVal + niceVal + systemVal + irqVal + softirqVal + stealVal + guestVal + guestniceVal;
	return result;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
	std::ifstream stream(kProcDirectory + kStatFilename);
	vector<string> values = getValue(stream);
	long idle = stoi(values[CPUStates::kIdle_]);
	long iowait = stoi(values[CPUStates::kIOwait_]);
	long result = idle + iowait;

	return result;
}

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() { return {}; }

float LinuxParser::CpuUtilization(int pid) {
	std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
	vector<string> values = getValue(stream);

	long utime = stof(values[13]);    // CPU time spent in user code, measured [clock ticks]
	float stime = stof(values[14]);   // CPU time spent in kernel code, measured [clock ticks]
	float cutime = stof(values[15]);  // Waited-for children's CPU time spent in user code [clock ticks]
	float cstime = stof(values[16]);  // Waited-for children's CPU time spent in kernel code [clock ticks]
	// float starttime = UpTime(pid);    // The time the process started after system boot. [sec]
	float starttime = stof(values[21]);    // The time the process started after system boot. [sec]
	float uptime = LinuxParser::UpTime(); // Time when the process started (the first parameter of /proc/uptime) [sec]

	float totaltime = utime + stime + cutime + cstime;

	float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
	return ((totaltime / sysconf(_SC_CLK_TCK)) / seconds);
}

// TODO(C): Read and return the total number of processes
int LinuxParser::TotalProcesses() {
	std::ifstream stream(kProcDirectory + kStatFilename);
	vector<string> values = getValue(stream, "processes");
	return stoi(values[1]);
}

// TODO(C): Read and return the number of running processes
int LinuxParser::RunningProcesses() {
	std::ifstream stream(kProcDirectory + kStatFilename);
	vector<string> values = getValue(stream, "procs_running");
	return stoi(values[1]);
}

// TODO(C0): Read and return the command associated with a process
string LinuxParser::Command(int pid) {
	vector<string> cmdline;
	string line;
	std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

	if (stream.is_open()) {
		std::getline(stream, line);
	}

	return line;
}

// TODO(C): Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
	std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
	string str;
	while (stream >> str) {
		if (str.substr(0, 7) == "VmSize:") {
			stream >> str;
			return to_string(static_cast<int>(stof(str) / float(1000)));
		}
	}

	return "";
}

// TODO(C0): Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
	std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
	vector<string> uid = LinuxParser::getValue(stream, "Uid:");

	return uid[1];
}

// TODO(C): Read and return the user associated with a process
string LinuxParser::User(int pid) {
	std::ifstream stream(kPasswordPath);
	vector<string> values = LinuxParser::getValue(stream, "x:" + LinuxParser::Uid(pid));
	string result = values[0].substr(0, values[0].find(':'));

	return result;
}


// TODO(C): Read and return the system uptime
long LinuxParser::UpTime(int pid) {
	std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
	vector<string> values = LinuxParser::getValue(stream);
	long result = stoi(values[21]) / sysconf(_SC_CLK_TCK);

	return result;
}
  
// added for convenience
vector<string> LinuxParser::getValue(std::ifstream& stream, string valueToFind) {
	vector<string> value;
	string line;
	while (getline(stream, line)) {
		if (valueToFind == "" || line.find(valueToFind) != std::string::npos) {
			std::stringstream ss(line);
			std::istream_iterator<std::string> beg(ss), end;
			value = vector<string>(beg, end);

			return value;
		}
	}
	return value;
}