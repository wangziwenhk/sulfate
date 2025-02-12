#include <stdint.h>
#include "memory/alloca.h"
/* 定义堆的大小，比如 16MB */
#define HEAP_SIZE (1 * 1024 * 1024)

/* 定义一个大数组作为内核堆 */
static uint8_t kernel_heap[HEAP_SIZE] __attribute__((aligned(8)));

/* 内存块管理结构 */
typedef struct heap_block {
    size_t size; // 本块数据区大小，不包括管理头
    int free; // 1 表示空闲，0 表示已分配
    struct heap_block *next; // 指向下一个内存块
} heap_block_t;

/* 堆的空闲链表起始地址 */
static heap_block_t *heap_free_list = nullptr;

/* 初始化堆，在内核启动时调用一次 */
void kernel::heap_init() {
    heap_free_list = reinterpret_cast<heap_block_t *>(kernel_heap);
    kernel_heap[0] = 1;
    heap_free_list->size = HEAP_SIZE - sizeof(heap_block_t);
    heap_free_list->free = 1;
    heap_free_list->next = nullptr;
}

/* 内核内存分配函数，类似 malloc */
void *kernel::kalloc(size_t size) {
    /* 简单的 8 字节对齐 */
    size = (size + 7) & ~7;
    heap_block_t *current = heap_free_list;

    while (current) {
        if (current->free && current->size >= size) {
            /* 如果空间足够大则进行分割 */
            if (current->size >= size + sizeof(heap_block_t) + 8) {
                const auto new_block = reinterpret_cast<heap_block_t *>(
                    reinterpret_cast<char *>(current) + sizeof(heap_block_t) + size);
                new_block->size = current->size - size - sizeof(heap_block_t);
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            return reinterpret_cast<char *>(current) + sizeof(heap_block_t);
        }
        current = current->next;
    }
    /* 如果没有合适的内存块，则返回 NULL */
    return nullptr;
}

/* 内核内存释放函数，类似 free */
void kernel::kfree(void *ptr) {
    if (!ptr)
        return;

    heap_block_t *block = reinterpret_cast<heap_block_t *>(static_cast<char *>(ptr) - sizeof(heap_block_t));
    block->free = 1;

    /* 简单合并相邻空闲块，减少碎片 */
    heap_block_t *current = heap_free_list;
    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += sizeof(heap_block_t) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}
