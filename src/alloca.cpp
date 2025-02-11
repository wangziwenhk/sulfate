#include "alloca/alloca.h"

struct block {
    size_t size;
    bool free;
    block *next;
};

// 全局调用链表头
block *free_list = nullptr;

// 在链表中查找空闲且足够大的块
block *get_free_block(block **last, const size_t size) {
    block *current = free_list;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        *last = current;
        current = current->next;
    }
    return nullptr;
}

void *alloca::malloc(size_t size) {
    return nullptr;
}
