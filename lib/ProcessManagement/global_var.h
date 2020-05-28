#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include "ProcessesList.h"
#include "allocator.h"

extern ProcessesList global_pl = ProcessesList();


extern FSB_allocator global_allocator = FSB_allocator();

#endif // GLOBAL_VAR_H
