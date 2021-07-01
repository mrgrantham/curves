#include <iostream> 
#include <boost/program_options.hpp>
#include <PaddConfigs.hpp>
#include <Workers.hpp>
#include <spdlog/spdlog.h>
#include <signal.h> //  our new library 
#include <ScratchPaddSystem.hpp>
#include <Timer.hpp>
#include <EventTimer.hpp>
#include <chrono>

volatile sig_atomic_t flag = 0;
void signal_handler(int sig);

std::unique_ptr<DisplayPadd> dp;

int main(int argc, char **argv) {
  SCOPED_METHOD_TIMER();
  signal(SIGINT, signal_handler); 
  spdlog::info("Welcome to SCRATCHPADD!");
  spsystem = std::make_unique<SPSystem>();
  spsystem->instantiate();
  std::thread stop_delay_thread([]{
    std::cout << "Starting 10 second countdown" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "countdown over. Stopping" << std::endl;
    spsystem->stop();
  });
  spsystem->start();
}

void signal_handler(int sig){ // can be called asynchronously
  spdlog::info("shutting down");
  flag = 0; // set flag
  spsystem->stop();
}