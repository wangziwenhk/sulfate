#ifndef UNISTD_H
#define UNISTD_H

#include "sulfate/asm/processor.h"
#include "stddef.h"
/// 什么也不做
#define nop() __asm__ __volatile__("nop");

#endif //UNISTD_H
