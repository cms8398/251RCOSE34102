#ifndef gantt_h
#define gantt_h
#include "process.h"

void simple_gantt(Process* processes, int num_processes); //sjf랑 fcfs에서 사용할 간트차트 출력방식식
void new_gantt(int* log); //round robin에서 사용할 간트차트 출력방식
#endif // gantt_h