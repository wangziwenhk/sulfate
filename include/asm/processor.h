#ifndef PROCESSOR_H
#define PROCESSOR_H

/// 使 CPU 进入低功耗挂起状态，直到外部中断唤醒
#define hlt() __asm__ __volatile__("hlt");

/// 用于从中断服务例程（ISR）返回
#define iretq() __asm__ __volatile__("iretq");

/// 禁止可屏蔽中断（清除中断标志）：
#define cli() __asm__ __volatile__("cli" ::: "memory");

/// 允许可屏蔽中断（设置中断标志）：
#define sti() __asm__ __volatile__("sti" ::: "memory");

/// 发起系统调用，进入内核态
#define syscall() __asm__ __volatile__("syscall");

/// 用于系统调用返回
#define sysret() __asm__ __volatile__("sysret");

#endif //PROCESSOR_H
