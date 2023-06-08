/* author: fpayan*/

#include "dslib.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(stack_t *s, int capacity)
{
    s->count = 0;
    s->data = malloc(sizeof(int) * capacity);
    s->max = capacity;
}

int size_stack(stack_t *s)
{
    return s->count;
}

int pop_stack(stack_t *s)
{
    /* Pop the value from the stack */
    if ( (s->count - 1) >= 0)
    {
        int temp = s->data[s->count - 1];
        s->count--;

        return temp;
    } else
    
    return -9999;
    
}

int push_stack(stack_t *s, int e)
{
    if ( (s->count) != s->max)
    {
        s->data[s->count] = e;
        s->count++;
    } 
    
    return -9999;
}

void deallocate_stack(stack_t *s)
{
    free(s->data);
}