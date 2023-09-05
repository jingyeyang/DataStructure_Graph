/**
 * @brief This header file content the functions of stack.
*/
#ifndef __STACK__H__
#define __STACK__H__

//////////////////// .................... DATA STRUCTURE :: STACK .................... ////////////////////
/**
 * @brief Here is a simple implementation of stack, and we will intro the operation functions down.
 * 
 *  1. stackInitial(int initial_size) :: to create a new stack. 
 *      e.g. STACK* stack = stackInitial(10); 10 = the size you want to initial.
 * 
 *  2. stackEmpty(STACK* stack) :: check whether the stack is empty or not, if is empty return 1, else return 0.
 * 
 *  3. stackFULL(STACK* stack) :: check whether the stack is full or not, if is empty return 1, else return 0.
 * 
 *  4. stackSize(STACK* stack) :: return the stack size recently.
 * 
 *  5. stackPush(STACK* stack, int item) :: push the item into stack, if stack is full then will append the size of stack and push it again.
 * 
 *  6. stackAppend(STACK* stack) :: append the stack size into two times larger.
 * 
 *  7. stackGetTop(STACK* stack) :: return the top item in tha stack but won't delete it.
 * 
 *  8. stackPop(STACK* stack) :: delete the top item in the stack.
 * 
 *  9. printStack(STACK* stack) :: show all the item and it's address in the stack.
 * 
*/

#pragma region STACK



/**
 * @brief Make it to append the stack, similar to vector in C++.
*/
void stackAppend(STACK* stack)
{
    int current_size = stack -> max_size;
    int new_size = (2 * current_size);
    int* new_stack_array = (int*)malloc(new_size * sizeof(int));

    for(int sp = 0 ; sp <= stack -> stack_ptr ; sp++)
    {
        new_stack_array[sp] = stack -> stack_array[sp];
    }

    free(stack -> stack_array);
    stack -> stack_array = (int*)new_stack_array;
    stack -> max_size = new_size;
}

/**
 * @brief Return #item in the stack.
*/
int stackSize(STACK* stack)
{
    return(stack -> stack_ptr + 1);
}

/**
 * @brief Show the item in the stack.
*/
void printStack(STACK* stack)
{
    printf("========== .......... THE STATE IN THE STACK .......... ==========\n");

    //int size = stackSize(stack);
    int temp_ptr = stack -> stack_ptr;

    printf("\n");
    printf("                |   | \n");
    while(temp_ptr >= 0)
    {
        printf(" %p | %d | \n",&(stack -> stack_array[temp_ptr + 1]),  stack -> stack_array[temp_ptr]);
        temp_ptr--;
    }
    printf("                -----\n\n");

    printf("#item  in   STACK = %d\n", (stack -> stack_ptr + 1));
    printf("Max_size of STACK = %d\n\n", stack -> max_size);
    printf("========== ............................................ ==========\n");
}

/**
 * @brief If stack is full return 1, else return 0.
*/
bool stackFull(STACK* stack)
{
    if((stack -> stack_ptr) == (stack -> max_size - 1))
    {
        return(1);
    }
    else
    {
        return(0);
    }

}

/**
 * @brief If stack is empty return 1, else return 0.
*/
bool stackEmpty(STACK* stack)
{
    if(stack -> stack_ptr == -1)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

/**
 * @brief Return the top value of the stack. 
*/
int StackGetTop(STACK* stack)
{
    if(stackEmpty(stack))
    {
        //writeErrorLog("Error occured : STACK is empty");
        printf("stack is empty no top value.\n");
        return(-1);
    }
    else
    {
        int item = stack -> stack_array[stack -> stack_ptr];
        return(item);
    }
}

/**
 * @brief Delete the top item of the stack.
*/
void stackPop(STACK* stack)
{
    if(stackEmpty(stack))
    {
        writeErrorLog("Error occured : STACK is empty");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }
    else
    {
        stack -> stack_ptr--;
    }
}

/**
 * @brief Insert the item into top of the stack.
*/
void stackPush(STACK* stack, int item)
{
    if(stackFull(stack))
    {
        stackAppend(stack); // append stack.
        stackPush(stack,item); // recall stackPush.
    }
    else
    {
        stack -> stack_ptr++;
        stack -> stack_array[stack -> stack_ptr] = item;
    }
}


/**
 * @brief Create a stack and initial it.
*/
STACK* stackInitial(int initial_size)
{
    //stack = (STACK*)malloc(initial_size * sizeof(int));
    STACK* stack = (STACK*)malloc(1 * sizeof(STACK));
    stack -> stack_array = (int*)malloc(initial_size * sizeof(int));
    if(stack -> stack_array == NULL || stack == NULL)
    {
        writeErrorLog("Error occured : STACK malloc fail");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }
    stack -> stack_ptr = -1;
    stack -> max_size = initial_size;
    return(stack);
}

#pragma endregion STACK























#endif