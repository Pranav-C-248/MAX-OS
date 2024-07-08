#include "memory.h"

/*So heres what well do:
1)Get one big chunk of memory and assign all dynamic mem chunks from that chunk.
2) To handle each chunks info , like size and wheter its being used , and pointer to its prev 
and next chunks well use doubly linked lists.
3)Now where to store each node. cause number of nodes will go on increasing.
  we store it just behind each chunks, like if the chunk is of 500b, we store the node in the first 16b or 8b
4)when we need to allocate a fixed size of memory, we have to go trough the entire list of 
unused memory and find the smallest free node.
5)When freeing the nodes , well just change the status to unused. And if there are other free memory beside it
combine the chunks into one big chunk
 */


static uint8_t complete_memory[MAX_DYNAMIC_MEMORY]; //big chunk

static mem_node *dynamic_mem_start;

void init_dynamic_memory() {
    dynamic_mem_start=(struct mem_node*)complete_memory;
    dynamic_mem_start->size=MAX_DYNAMIC_MEMORY-NODE_SIZE;
    dynamic_mem_start->next=NULL_POINTER;
    dynamic_mem_start->prev=NULL_POINTER;
}

void *find_best_block(struct mem_node *t,size_t size){

    mem_node* curr_block=t;
    mem_node* best_block=(mem_node*) NULL_POINTER;
    uint32_t smallest_possible_size=MAX_DYNAMIC_MEMORY+1;

    while (curr_block)
    {
        if(!curr_block->used && curr_block->size>=size+NODE_SIZE && curr_block->size<=MAX_DYNAMIC_MEMORY && curr_block->size<=smallest_possible_size){
                best_block=curr_block;
                smallest_possible_size=best_block->size;
        }
        curr_block=curr_block->next;
    }

    return best_block;
}

void *mallok(uint32_t size){

    //get the block address
    mem_node* best_block=(mem_node*)find_best_block(dynamic_mem_start,size);

    //check if its valid
    if(best_block!=NULL_POINTER){
        //we have a big chunk, now we need to take only as much as need, size+Node_size
        best_block->size=best_block->size-size-NODE_SIZE;

        //creating the needed block. Needed block address=best_block address+reqSize+node_size
        mem_node* dynamic_block=(mem_node*)((uint8_t*)best_block+size+NODE_SIZE);

        dynamic_block->size=size;
        dynamic_block->used=true;
        dynamic_block->prev=best_block;
        dynamic_block->next=best_block->next;

        //reconnect
        if(best_block->next!=NULL_POINTER){
            mem_node* next=best_block->next;
            next->prev=dynamic_block;
        }
        return (void*)((uint8_t*)best_block+NODE_SIZE);
    }
    return NULL_POINTER;
}


void *merge_to_current(mem_node* p){

    mem_node* next_node=p->next;

    if(next_node!=NULL_POINTER && !next_node->used){
        p->size=p->size+next_node->size+NODE_SIZE;

        //remove next block from list

        p->next=next_node->next;
        if(p->next!=NULL_POINTER){
            mem_node* nnode=next_node->next;
            nnode->prev=p;
        }
    }
    return p;
}

void merge_to_prev(mem_node* p){

    mem_node* prev_node=p->prev;
    if(prev_node!=NULL_POINTER && !prev_node->used){
        prev_node->size=prev_node->size+p->size+NODE_SIZE;

        prev_node->next=p->next;
        if(prev_node->next!=NULL_POINTER){
            mem_node* nnode=p->next;
            nnode->prev=prev_node;
        }
    }
}


void freek(void* p){

    if(p==NULL_POINTER){
        return;
    }
    //get the node assosciated with this block
    mem_node* node=(mem_node*)((uint8_t*)p-NODE_SIZE);
    if(node==NULL_POINTER)return;

    node->used=false;

    //merge unused nodes
    node=merge_to_current(node);
    merge_to_prev(node);
}
