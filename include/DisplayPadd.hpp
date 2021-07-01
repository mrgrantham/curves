#pragma once
#include <spdlog/spdlog.h>

#include <Base.hpp>
#include <Passables.hpp>
#include <Timer.hpp>

namespace Curves {

class DisplayPadd {
 private:
  ScratchPadd::Timer performanceTimer_;
  std::unique_ptr<Graphics> graphics_;

 public:
  void prepare() {
    spdlog::info("Preparing: {}", __CLASS_NAME__);
    setRepeatInterval(100);
    performanceTimer_.setTimerName(paddName_);
    performanceTimer_.start();
  }
  DisplayPadd(ScratchPadd::Sender *sender) : Base(sender) {
    spdlog::info("Constructing: {}", __CLASS_NAME__);
    paddName_ = __CLASS_NAME__;
    graphics_ = std::make_unique<GL4>();
    // We dont want the work loop to sleep
    // TODO make this sleep/wake from semaphore
    work_thread_sleep_interval_ = 0;
  }
  void starting() {
    spdlog::info("Starting Window Setup");
    graphics_->setupWindow();
  }
  void finishing() {
    spdlog::info("[{}] Avg Repeating Interval: {}", paddName_,
                 performanceTimer_.getAverageIntervalString());
    performanceTimer_.markTimeAndPrint();
    graphics_->tearDown();
  }

  ~DisplayPadd() { spdlog::info("Destroying: {}", __CLASS_NAME__); }

  void repeat() {
    spdlog::info("DisplayPadd drawing at {:.3f}s interval",
                 performanceTimer_.markAndGetInterval());
    if (!graphics_->draw()) {
      spdlog::info("Stop drawing");
    }
  }

  bool runOnMainThread() { return true; }

  void receive(Passable::Triangle triangle) {
    std::cout << "receieved triangle: " << triangle << std::endl;
  }
};

}  // namespace Curves