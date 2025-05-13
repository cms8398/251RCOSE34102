#ifndef EVALUATION_H
#define EVALUATION_H

#include "process.h"
#include <stdio.h>
#include <stdlib.h>

void print_average_performance(Process* processes, int num_processes);
void print_each_performance(Process* processes, int num_processes);

#endif // EVALUATION_H