#pragma once

#define close_interrupt __asm__ volatile("cli" ::: "memory")
#define open_interrupt __asm__ volatile("sti" ::: "memory")


/**
 * Reads an 8-bit data from the specified IO port.
 * @param port IO port number
 * @return The 8-bit data read from the specified port.
 */
static uint8_t io_in8(uint16_t port) {
    uint8_t data;
    __asm__ volatile("inb %w1, %b0" : "=a"(data) : "Nd"(port));
    return data;
}

/**
 * Writes an 8-bit data to the specified IO port.
 * @param port IO port number
 * @param data Data to write to the port
 */
static void io_out8(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %b0, %w1" : : "a"(data), "Nd"(port));
}

/**
 * Reads an 16-bit data from the specified IO port.
 * @param port IO port number
 * @return The 16-bit data read from the specified port.
 */
static uint16_t io_in16(uint16_t port) {
    uint16_t data;
    __asm__ volatile("inw %w1, %w0" : "=a"(data) : "Nd"(port));
    return data;
}

/**
 * Writes an 16-bit data to the specified IO port.
 * @param port IO port number
 * @param data Data to write to the port
 */
static void io_out16(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

/**
 * Reads an 32-bit data from the specified IO port.
 * @param port IO port number
 * @return The 32-bit data read from the specified port.
 */
static uint32_t io_in32(uint16_t port) {
    uint32_t data;
    __asm__ volatile("inl %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

/**
 * Writes an 32-bit data to the specified IO port.
 * @param port IO port number
 * @param data Data to write to the port
 */
static void io_out32(uint16_t port, uint32_t data) {
    __asm__ volatile("outl %0, %1" : : "a"(data), "Nd"(port));
}

/**
 * Flash TLB (Translation Lookaside Buffer),
 * usually used to update the mapping of virtual memory to physical memory
 * @param addr Address to refresh
 */
static void flush_tlb(uint64_t addr) {
    __asm__ volatile("invlpg (%0)" ::"r"(addr) : "memory");
}

/**
 * Gets the value of the CR3 register of the current CPU.
 * The CR3 register is typically used to store page table base addresses for mapping virtual addresses to physical
 * addresses.
 * @return Current CR3 register value
 */
static uint64_t get_cr3() {
    uint64_t cr0;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cr0));
    return cr0;
}

/**
 * Get the current stack pointer The value of (rsp register).
 * @return Value of current stack pointer
 */
static uint64_t get_rsp() {
    uint64_t rsp;
    __asm__ volatile("mov %%rsp, %0" : "=r"(rsp));
    return rsp;
}

/**
 * Gets the value of the current flag register (RFLAGS).
 * @return Value of current RFLAGS register
 */
static uint64_t get_rflags() {
    uint64_t rflags;
    __asm__ volatile("pushfq\n"
                     "pop %0\n"
                     : "=r"(rflags)
                     :
                     : "memory");
    return rflags;
}

/**
 * Reads 32-bit data from a memory-mapped IO address.
 * @param addr Memory mapped address
 * @return 32-bit data read from the specified address
 */
static uint32_t mmio_read32(void *addr) {
    return *static_cast<volatile uint32_t *>(addr);
}


/**
 * Writes 32-bit data to a memory-mapped IO address.
 * @param addr Memory mapped address
 * @param data Data to write
 */
static void mmio_write32(uint32_t *addr, uint32_t data) {
    *static_cast<volatile uint32_t *>(addr) = data;
}

/**
 * Reads 64-bit data from memory-mapped I/O addresses.
 * @param addr Memory mapped address
 * @return 64-bit data read from the specified address
 */
static uint64_t mmio_read64(void *addr) {
    return *static_cast<volatile uint64_t *>(addr);
}

static void mmio_write64(void *addr, uint64_t data) {
    *static_cast<volatile uint64_t *>(addr) = data;
}

static uint64_t rdmsr(uint32_t msr) {
    uint32_t eax, edx;
    __asm__ volatile("rdmsr" : "=a"(eax), "=d"(edx) : "c"(msr));
    return (static_cast<uint64_t>(edx) << 32) | eax;
}

static void wrmsr(uint32_t msr, uint64_t value) {
    uint32_t eax = static_cast<uint32_t>(value);
    uint32_t edx = value >> 32;
    __asm__ volatile("wrmsr" : : "c"(msr), "a"(eax), "d"(edx));
}

static uint64_t load(uint64_t *addr) {
    uint64_t ret = 0;
    __asm__ volatile("lock xadd %[ret], %[addr];" : [addr] "+m"(*addr), [ret] "+r"(ret) : : "memory");
    return ret;
}

static void store(uint64_t *addr, uint32_t value) {
    __asm__ volatile("lock xchg %[value], %[addr];" : [addr] "+m"(*addr), [value] "+r"(value) : : "memory");
}
