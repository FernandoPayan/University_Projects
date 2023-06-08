/* author: fpayan*/

#ifndef STACK_H_
#define STACK_H_

struct stack
{
    int count; // number of int values currently stored in stack
    int *data; /* pointer will be initalized inside stack_init(). Also, the actual size
                  of the allocated memory will be determined by "capacity" value that is
                  given as one of the parameters to stack_init() */
    int max; // total number of int values that can be stored in this stack
};

typedef struct stack stack_t;

void init_stack(stack_t *s, int capacity); // Initalizies the stack that stores integers with maximum size capacity

int size_stack(stack_t *s); // Returns the size of the stack

int pop_stack(stack_t *s); // Returns the integer element on top of the stack. If empty, return undefined

int push_stack(stack_t *s, int e); // If stack is not full, push the item on top of the stack.

void deallocate_stack(stack_t *s); // Frees this stack

#endif