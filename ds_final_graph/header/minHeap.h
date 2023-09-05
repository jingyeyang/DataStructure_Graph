#ifndef __MIN__HEAP__H__
#define __MIN__HEAP__H__

//////////////////// .................... DATA STRUCTURE :: HEAP .................... ////////////////////
/**
 * @brief Here is a simple implementation of minimum heap, and we will intro the operation finction down.
 * 
 *  1. MinHeapInitial(int initial_size) :: to create a new minimum heap.
 *      e.g. MIN_HEAP* min_heap = MinHeapInitial(10); 10 = the size you want to intial.
 * 
 *  2. MinHeapFull(MIN_HEAP* heap) :: check whether the minimum heap is full or not, if is empty return 1, else return 0.
 * 
 *  3. MinHeapEmpty(MIN_HEAP* heap) :: check whether the minimum heap is empty or not, if is empty return 1, else return 0.
 * 
 *  4. MinHeapInsert(MIN_HEAP* heap, int item) :: insert the item into minimum heap, and it will get to the top of heap.
 * 
 *  5. MinHeapGetTop(MIN_HEAP* heap) :: return the minimum key of the heap, means the top key of the heap.
 * 
 *  6. MinHeapdelete(MIN_HEAP* heap) :: delete the minimum key in the heap, and start to adjust the minimum heap.
 * 
 *  7. MinHeapify(MIN_HEAP* heap, int location) :: to adjust the heap become minimum heap.
 * 
 *  8. MinHeapSize(MIN_HEAP* heap) :: retrun the current #item in the  heap.
 * 
 *  9. MinHeapMaxSize(MIN_HEAP* heap) :: retrun the maximum #item that minimum heap can store reccently.
 * 
 *  10. MinHeapAppend(MIN_HEAP* heap) :: append the maximum size of heap.
 * 
 *  11. PrintHeap(MIN_HEAP* heap) :: show the heap state.
*/


#pragma region MIN_HEAP

/**
 * @brief Swap two item.
*/
void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}


/**
 * @brief Show the heap state.
*/
void PrintHeap(MIN_HEAP* heap)
{
    printf("========== .......... THE STATE IN THE HEAP .......... ==========\n");

    int location = 1;
    while(location <= heap -> heap_ptr)
    {   
        printf("%2d (%d)\n", heap -> heap_array[location], heap -> heap_weight[location]);
        location++;
    }
    


    printf("#item  in   HEAP = %d\n", heap -> heap_ptr);
    printf("Max_size of HEAP = %d\n", heap -> max_size);
    //printf("HEIGHT  OF  HEAP = %f\n\n", heap_height);
    printf("========== ............................................ ==========\n");


}


/**
 * @brief Append the maximum size of heap.
*/
void MinHeapAppend(MIN_HEAP* heap)
{
    int append_size = (2 * (heap -> max_size));
    int* new_heap_array = (int*)malloc((append_size) * sizeof(int));
    int* new_heap_weight = (int*)malloc((append_size) * sizeof(int));
    int temp_ptr = 1;
    while (temp_ptr <= heap -> heap_ptr)
    {
        new_heap_array[temp_ptr] = heap -> heap_array[temp_ptr];
        new_heap_weight[temp_ptr] = heap -> heap_weight[temp_ptr];
        temp_ptr++;
    }
    free(heap -> heap_array);
    free(heap -> heap_weight);
    heap -> heap_array = (int*)new_heap_array;
    heap -> heap_weight = (int*)new_heap_weight;
    heap -> max_size = append_size;
}


/**
 * @brief Return maximum #item that can store in the heap now.
*/
int MinHeapMaxSize(MIN_HEAP* heap)
{
    return(heap -> max_size);
}


/**
 * @brief Return #item in the minimum heap.
*/
int MinHeapSize(MIN_HEAP* heap)
{
    return(heap -> heap_ptr);
}


/**
 * @brief If minimum heap is full return 1, else return 0.
*/
bool MinHeapFull(MIN_HEAP* heap)
{
    if(heap -> heap_ptr == heap -> max_size)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}


/**
 * @brief If minimum heap is empty return 1, else return 0.
*/
bool MinHeapEmpty(MIN_HEAP* heap)
{
    if(heap -> heap_ptr == 0)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}


/**
 * @brief Return the minimum key of the heap.
*/
int MinHeapGetTop(MIN_HEAP* heap)
{
    //int item = heap -> heap_array[1];
    return(heap -> heap_array[1]);
}


/**
 * @brief Adjust the heap become minimum heap.
*/
void MinHeapify(MIN_HEAP* heap, int location)
{
    int largest = location;
    int left = (2 * location);
    int right = left + 1;
    if((left <= heap -> heap_ptr) && (heap -> heap_weight[left] < heap -> heap_weight[location]))
    {
        largest = left;
    }

    if((right <= heap -> heap_ptr) && (heap -> heap_weight[right] < heap -> heap_weight[largest]))
    {
        largest = right;
    }

    if(largest != location)
    {
        swap(&(heap -> heap_array[largest]), &(heap -> heap_array[location]));
        swap(&(heap -> heap_weight[largest]), &(heap -> heap_weight[location]));
        MinHeapify(heap, largest);
    }
}


/**
 * @brief Delete the minimum key of the heap.
*/
void MinHeapdelete(MIN_HEAP* heap)
{
    swap(&(heap -> heap_array[heap -> heap_ptr]), &(heap -> heap_array[1]));
    swap(&(heap -> heap_weight[heap -> heap_ptr]), &(heap -> heap_weight[1]));
    heap -> heap_ptr--;
    MinHeapify(heap, 1);
}


/**
 * @brief Insert the item into minimum heap.
*/
void MinHeapInsert(MIN_HEAP* heap, int item, int weight)
{
    if(MinHeapFull(heap))
    {
        // heap is full, must append the heap.
        MinHeapAppend(heap);
        MinHeapInsert(heap, item, weight);
    }
    else
    {
        // heap is not full
            // insert item into the last location of the heap.
        heap -> heap_ptr++;
        heap -> heap_array[heap -> heap_ptr] = item;
        heap -> heap_weight[heap -> heap_ptr] = weight;
            // consider the heap will swap location or not.
        int location = (heap -> heap_ptr);
        // while (heap -> heap_array[location] < heap -> heap_array[(location / 2)] && location > 0)
        // {
        //     swap(&(heap -> heap_array[location]), &(heap -> heap_array[(location / 2)]));
        //     location = (location / 2);
        // }

        while(heap -> heap_weight[location] < heap -> heap_weight[(location / 2)] && location > 0)
        {
            swap(&(heap -> heap_array[location]), &(heap -> heap_array[(location / 2)]));
            swap(&(heap -> heap_weight[location]), &(heap -> heap_weight[(location / 2)]));
            location = (location / 2);
        }

    }


}


/**
 * @brief Create and Initial a minimum heap with the input intital_size.
*/
MIN_HEAP* MinHeapInitial(int initial_size)
{
    MIN_HEAP* heap = (MIN_HEAP*)malloc(1 * sizeof(MIN_HEAP));
    heap -> heap_array = (int*)malloc((initial_size + 1) * sizeof(int));
    heap -> heap_weight = (int*)malloc((initial_size + 1) * sizeof(int));
    heap -> heap_ptr = 0;
    heap -> max_size = initial_size;
    if(heap -> heap_array == NULL || heap == NULL)
    {
        writeErrorLog("Error occured : HEAP malloc fail");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }

    return(heap);
}

#pragma endregion MIN_HEAP

#endif /* __MIN__HEAP__H__ */
