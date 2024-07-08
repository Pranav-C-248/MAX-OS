#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct dynamic_mem_node      //DLL node
{
    bool used;
    uint32_t size;
    struct mem_node* next;
    struct mem_node* prev;
}mem_node;

#define NODE_SIZE sizeof(mem_node)
#define NULL_POINTER ((void*)0)
#define MAX_DYNAMIC_MEMORY 4*1024

extern void init_dynamic_memory();
// extern mem_node* find_best_block(struct mem_node *t,size_t size);
extern void *mallok(uint32_t size);
extern void freek(void* p);