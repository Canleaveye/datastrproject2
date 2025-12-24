#include "RedBlackTree.h"
#include <string>

struct PCB {
    int id; // 进程ID
    int prior; // 进程优先级
    string name; // 进程功能
    string state; // 运行状态
    int start;  // 进程开始时间
    int end;  // 进程结束时间
    int arrive;  // 进程到达时间
    int wait;  // 进程等待时间
    int turn;  // 进程周转时间
    int serve;  // 进程服务时间
};

// 任务调度器类
class Scheduler {
private:
    // 使用红黑树存储进程信息
    RedBlackTree<int,PCB> task;
public:
    // 添加进程
    bool addProcess(const PCB& pcb);

    // 检查队列是否为空
    bool isEmpty() const;

    // 显示队列中的所有进程
    void showQueue() const;

    // 删除进程
    bool removeProcess(int id);

    // 进行调度
    void runProcess();

};