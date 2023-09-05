/**
 * @brief This header file content the functions of queue.
*/
#ifndef __QUEUE__H__
#define __QUEUE__H__




//////////////////// .................... DATA STRUCTURE :: QUEUE .................... ////////////////////
/**
 * @brief Here is a simple implementation of circular queue, and we will intro the operation finction down.
 * 
 *  1. queueInitial(int initial_size) :: to create a new queue.
 *      e.g. QUEUE* queue = queueInitial(10); 10 = the size you want to intial.
 * 
 *  2. queueEmpty(QUEUE* queue) :: check whether the queue is empty or not, if is empty return 1, else return 0.
 * 
 *  3. queueFull(QUEUE* queue) :: check whether the queue is full or not, if is empty return 1, else return 0.
 * 
 *  4. queueCurrentSize(QUEUE* queue) :: retrun the number of item in the queue now.
 * 
 *  5. queueMaxSize(QUEUE* queue) :: return the queue size recently.
 * 
 *  6. queuePush(QUEUE* queue, int item) :: push the item into queue, if queue is full then will append the size of queue and push it again.
 * 
 *  7. queueAppend(QUEUE* queue) :: append the queue size into two times larger.
 * 
 *  8. queueGetTop(QUEUE* queue) :: return the top item in tha queue but won't delete it. (queue is a FIFO, so return the item that front pointer point at)
 * 
 *  9. queuePop(QUEUE* queue) :: delete the top item in the queue.
*/

#pragma region QUEUE

/**
 * @brief Append the queue if queue is full.
*/
void queueAppend(QUEUE* queue)
{
    int new_size = (2 * (queue -> current_size));
    int* new_queue_array = (int*)malloc(new_size * sizeof(int));


    int count = 0;
    int front = ((queue -> front_ptr) % (queue -> max_size));
    int end = ((queue -> end_ptr) % (queue -> max_size));
    while(front != end)
    {
        new_queue_array[count] = queue -> queue_array[front];
        count++;
        front = (front + 1) % (queue -> max_size);
    }
    new_queue_array[count] = queue -> queue_array[front];
    count++;

    free(queue -> queue_array);
    queue -> queue_array = (int*)new_queue_array;
    queue -> max_size = new_size;
    queue -> front_ptr = 0;
    queue -> end_ptr = count - 1;
}

/**
 * @brief Show the queue.
*/
void queuePrint(QUEUE* queue)
{
    printf("========== .......... THE STATE IN THE QUEUE .......... ==========\n\n");
    int front = queue -> front_ptr % (queue -> max_size);
    int end = queue -> end_ptr % (queue -> max_size);
    printf("(front) ::    ");
    while(front != end)
    {
        printf("%d -> ", queue -> queue_array[front]);
        front = (front + 1) % (queue -> max_size);
    }
    printf("%d ", queue -> queue_array[front]);
    printf("    :: (end)\n");
    printf("\n");

    printf("#item  in   QUEUE = %d\n", queue -> current_size);
    printf("Max_size of QUEUE = %d\n\n", queue -> max_size);
    printf("========== ............................................ ==========\n");
}

/**
 * @brief Return the #item in the queue.
*/
int queueCurrentSize(QUEUE* queue)
{
    return(queue -> current_size);
}

/**
 * @brief Return the maximum storage size of the queue.
*/
int queueMaxSize(QUEUE* queue)
{
    return(queue -> max_size);
}

/**
 * @brief If queue is empty return 1, else return 0.
*/
bool queueEmpty(QUEUE* queue)
{
    if(queue -> current_size == 0)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

/**
 * @brief If queue is full return 1, else return 0.
*/
bool queueFull(QUEUE* queue)
{
    if(queue -> current_size == queue -> max_size)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

/**
 * @brief Insert the an element into the end(Rear) of the queue.
*/
void queuePush(QUEUE* queue, int item)
{
    if(queueFull(queue))
    {
        queueAppend(queue); // append queue.
        queuePush(queue, item); // recall queuePush.
    }
    else
    {
        queue -> end_ptr++;
        queue -> queue_array[(queue -> end_ptr) % (queue -> max_size)] = item; 
        queue -> current_size++;
    }
    if(queue -> front_ptr == -1)
    {
        queue -> front_ptr = queue -> end_ptr;
    }
}

/**
 * @brief Return the front element of the queue.
*/
int queueGetTop(QUEUE* queue)
{
    if(queueEmpty(queue))
    {
        //writeErrorLog("Error occured : QUEUE is empty");
        printf("queue is empty no top value.\n");
        return(-1);
    }
    else
    {
        int item = queue -> queue_array[(queue -> front_ptr) % (queue -> max_size)];
        return(item);
    }
}

/**
 * @brief Remove the element from the front of the queue.
*/
void queuePop(QUEUE* queue)
{
    if(queueEmpty(queue))
    {
        writeErrorLog("Error occured : QUEUE is empty");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }
    else
    {
        if(queue -> front_ptr == queue -> end_ptr)
        {
            queue -> front_ptr = queue -> end_ptr = -1;   
        }
        else
        {
            queue -> front_ptr = ((queue -> front_ptr + 1) % (queue -> max_size));
        }
        queue -> current_size--;
    }
}

/**
 * @brief Create a circular queue and initila it.
*/
QUEUE* queueInitial(int inital_size)
{
    QUEUE* queue = (QUEUE*)malloc(1 * sizeof(QUEUE));
    queue -> queue_array = (int*)malloc(inital_size * sizeof(int));
    if(queue -> queue_array == NULL || queue == NULL)
    {
        writeErrorLog("Error occured : QUEUE malloc fail");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }

    queue -> front_ptr = -1;
    queue -> end_ptr = -1;
    queue -> max_size = inital_size;
    queue -> current_size = 0;

    return(queue);
}

#pragma endregion QUEUE
















#endif