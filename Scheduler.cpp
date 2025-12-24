#include "Scheduler.h"

// 添加进程
bool Scheduler::addProcess(const PCB& p) {
    task.insert(p.prior,p);
    // 检查是否成功添加
    bool res = task.modify(p.prior,p); 
}