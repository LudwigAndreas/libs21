//
// Created by Ludwig Andreas on 18.07.2023.
//

#ifndef S21_SRC_LOGGERTHREADING_H_
#define S21_SRC_LOGGERTHREADING_H_

#include <mutex>

#include "IThreading.h"

namespace s21::threading {
 class LoggerProcessLock {
  public:
   ~LoggerProcessLock() = default;
   LoggerProcessLock() = default;
   inline bool lock() {
     return mtx_.try_lock();
   }
   void unlock() {
     mtx_.unlock();
   }

 private:
  std::mutex mtx_;
};

class LoggerProcessNoLock {
 public:
  ~LoggerProcessNoLock() = default;
  LoggerProcessNoLock() = default;

  inline bool lock() {
    return true;
  }

  inline void unlock() {}
};
}

#endif //S21_SRC_LOGGERTHREADING_H_
