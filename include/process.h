#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
  public:
  Process();
  Process(int pid);
  int Pid() const;                            // TODO: See src/process.cpp
  std::string User() const;                   // TODO: See src/process.cpp
  std::string Command() const;                // TODO: See src/process.cpp
  float CpuUtilization() const ;               // TODO: See src/process.cpp
  void setCpuUtilization();
  std::string Ram() const;                    // TODO: See src/process.cpp
  long UpTime() const;                    // TODO: See src/process.cpp
  bool operator>(Process const& a) const;

  
// TODO: Dece any necessary privamembers
 private:
  int pid_;
  std::string user_;
  std::string cmd_;
  float cpu_;
  std::string ram_;
  long uptime_;
};

#endif