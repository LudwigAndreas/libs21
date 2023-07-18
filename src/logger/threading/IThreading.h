//
// Created by Ludwig Andreas on 18.07.2023.
//

#ifndef S21_SRC_LOGGER_ITHREADING_H_
#define S21_SRC_LOGGER_ITHREADING_H_

namespace s21::threading {
class IThreading {
 public:
  virtual ~IThreading() = 0;

  virtual bool lock() = 0;
  virtual void unlock() = 0;

};
}

#endif //S21_SRC_LOGGER_ITHREADING_H_
