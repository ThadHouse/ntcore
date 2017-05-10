#include "support/SafeThread.h"
#include "support/timestamp.h"
#include <stdint.h>

#define HAL_kInvalidHandle 0

typedef int32_t HAL_Handle;

typedef HAL_Handle HAL_NotifierHandle;

typedef void (*HAL_NotifierProcessFunction)(uint64_t currentTime,
                                            HAL_NotifierHandle handle);

class NotifierThread : public wpi::SafeThread {
 public:
  void Main() {
    std::unique_lock<std::mutex> lock (m_mutex);
    while (m_active) {
      startNotifierLoop:
      double waitTime = m_waitTime * 1e-6;
      if (!m_running) {
        // If not running, wait 1000 seconds
        waitTime = 1000.0;
      }
      
      // TODO: Switch to use fpgatime
      auto timeoutTime = std::chrono::seconds<double>(waitTime);

      while (m_active && !m_notify) {
        m_cond.wait_until(lock, timeoutTime);
        if (m_updatedAlarm) {
          m_updatedAlarm = false;
          goto startNotifierLoop;
        }
      }
      if (!m_running) continue;
      if (!m_active) break;
      m_notify = false;
      m_running = false;
      uint64_t currentTime = WPI_Now();
      HAL_NotifierHandle handle = m_handle;
      HAL_NotifierProcessFunction process = m_process;
      lock.unlock();  // don't hold mutex during callback execution
      process(currentTime, handle);
      lock.lock();
    }
  }

  bool m_notify = false;
  HAL_NotifierHandle m_handle = HAL_kInvalidHandle;
  HAL_NotifierProcessFunction m_process;
  uint64_t m_waitTime;
  bool m_updatedAlarm = false;
  bool m_running = false;
};

class NotifierThreadOwner : public wpi::SafeThreadOwner<NotifierThread> {
  void SetFunc(HAL_NotifierProcessFunction process, HAL_NotifierHandle handle, void* param) {
    auto thr = GetThread();
    if (!thr) return;
    thr->m_process = process;
    thr->m_handle = handle;
    m_param = param;
  }

  void UpdateAlarm(uint64_t triggerTime) {
    auto thr = GetThread();
    if (!thr) return;
    thr->m_waitTime = triggerTime;
    thr->m_running = true;
    thr->m_updatedAlarm = true;
    thr->m_cond.notify_one();
  }

  void StopAlarm() {
    auto thr = GetThread();
    if (!thr) return;
    thr->m_running = false;
  }

  void* m_param;
};

HAL_NotifierHandle HAL_InitializeNotifier(HAL_NotifierProcessFunction process,
                                          void* param, int32_t* status) {
  return 0;
}
void HAL_CleanNotifier(HAL_NotifierHandle notifierHandle, int32_t* status) {

}
void* HAL_GetNotifierParam(HAL_NotifierHandle notifierHandle, int32_t* status) {
  return nullptr;
}
void HAL_UpdateNotifierAlarm(HAL_NotifierHandle notifierHandle,
                             uint64_t triggerTime, int32_t* status) {
  
}
void HAL_StopNotifierAlarm(HAL_NotifierHandle notifierHandle, int32_t* status) {

}