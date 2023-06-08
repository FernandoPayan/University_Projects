/* author: fpayan*/

#include "dslib.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    stack_t my_stack;

    /* Initialize stack */
    init_stack(&my_stack, 10);

    /* Push elements into the stack*/
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            push_stack(&my_stack, (i * 2));
            printf("Adding %d to stack\n", (i * 2));
        }
        else
        {
            push_stack(&my_stack, i);
            printf("Adding %d to stack\n", (i));
        }
    }
    
    /* Condition if stack is full */
    printf("Is stack full? %d\n", push_stack(&my_stack, 99999));
    

    /* Pop the values of the stack*/
    printf("The stack has %d values\n", size_stack(&my_stack));

    /* Print the values of the stack */

    while (size_stack(&my_stack) > 0)
    {
        printf("Popping the value %d from the stack\n", pop_stack(&my_stack));
    }

    /* Condition if stack is empty */
    printf("Is stack empty? %d\n", pop_stack(&my_stack));

    /* Free the stack */
    deallocate_stack(&my_stack);
}