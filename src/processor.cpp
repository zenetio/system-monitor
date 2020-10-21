#include <string>
#include <vector>
#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  float utilization{0};

  long active_ticks = LinuxParser::ActiveJiffies();
  long idle_ticks = LinuxParser::IdleJiffies();
  
  // diff : active value - the previous one
  long duration_active{active_ticks - cached_active_ticks_};
  long duration_idle{idle_ticks - cached_idle_ticks_};  

  long duration{duration_active + duration_idle};
  utilization = static_cast<float>(duration_active)/duration;

  // Update the cached ticks
  cached_active_ticks_ = active_ticks;
  cached_idle_ticks_ = idle_ticks;
  // return utilization;
  return static_cast<float>(utilization);
}