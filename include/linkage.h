#ifndef LINKAGE_H
#define LINKAGE_H

/// 定义一级缓存行的字节数为 32
#define L1_CACHE_BYTES 32

/// 调用该函数时不要使用寄存器传参
#define asmlinkage __attribute__((regparm(0)))	

/// 将数据对齐到 L1 缓存行 ( 32 字节 )边界
#define ____cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))

/// 符号名称相关宏
#define SYMBOL_NAME(X)	X
#define SYMBOL_NAME_STR(X)	#X
#define SYMBOL_NAME_LABEL(X) X##:

// 全局汇编符号
#define ENTRY(name)		\
.global	SYMBOL_NAME(name);	\
SYMBOL_NAME_LABEL(name)

#endif
