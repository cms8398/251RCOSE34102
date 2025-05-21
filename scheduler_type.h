#ifndef SCHEDULER_TYPE_H
#define SCHEDULER_TYPE_H

typedef enum {
    fcfs,
    sjf,
    priority,
    round_robin,
    pre_sjf,
    pre_priority,
} SchedulerType;

#endif