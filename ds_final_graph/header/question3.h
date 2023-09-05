#ifndef __QUESTION__3__
#define __QUESTION__3__


/**
 * @brief Print the result on CRT of question 3.
 * @param dijkstra_info a structure that store the infomations of dijkstra algorithm
 * @param visit_list the list of nodes that you want to trace
 * @param vivist_num the number of nodes that you want to trace
*/
void PrintResult3(DIJKSTRA_INFOS* dijkstra_info, int* visit_list, int visit_num)
{
    printf("========== .......... QUESTION 3 RESULT .......... ==========\n");
    printf("Start from node %2d :: \n", dijkstra_info -> source_node);
    STACK* stack = stackInitial(10);
    for(int visit_id = 0 ; visit_id < visit_num ; visit_id++)
    {
        int visit_node = visit_list[visit_id];
        stackPush(stack, visit_node);
        int parent_temp = dijkstra_info -> parents[visit_node];
        while(parent_temp != -1)
        {
            stackPush(stack, parent_temp);
            parent_temp = dijkstra_info -> parents[parent_temp];
        }
        printf("  Path of destination = %2d :\n", visit_node);
        while(!stackEmpty(stack))
        {
            printf("    %2d", StackGetTop(stack));
            stackPop(stack);
        }
        printf("\n");
        printf("    # Minimum cost of this path = %2d\n", dijkstra_info -> distance[visit_node]);

        
    }

    printf("=============================================================\n");
}


/**
 * @brief Consider whether there is a shorter path from source node t0 node u.
 * @param dijkstra_info a structure that store the infomations of dijkstra algorithm
 * @param u the node that we consider to find the shorter path
 * @param v the node that exist a path between source node and node u
 * @param weight weight between node u and node v
*/
void relax(DIJKSTRA_INFOS* dijkstra_info, int u, int v, int weight)
{
    // printf("%d ..... %d\n", dijkstra_info -> distance[v], (dijkstra_info -> distance[u] + weight));
    if((dijkstra_info -> distance[v]) > (dijkstra_info -> distance[u] + weight))
    {
        dijkstra_info -> distance[v] = dijkstra_info -> distance[u] + weight;
        dijkstra_info -> parents[v] = u;
    }
    // printf("after change : %d\n", dijkstra_info -> distance[v]);
}




#pragma region solution_1

/**
 * @brief Swap two item in  the sorting array.
 * @param node_list sorting array
 * @param a first swap item
 * @param b second swap item
*/
void quickSortSwap(int* node_list, int a, int b)
{
    int temp = 0;
    temp = node_list[a];
    node_list[a] = node_list[b];
    node_list[b] = temp;
}


/**
 * @brief To devide the sorting array.
 * @param node_list sorting array
 * @param dijkstra_info a structure that store the infomations of dijkstra algorithm
 * @param front begin offset of the sorthing array
 * @param end end offset of the sorthing array
*/
int quickSortPartition(int* node_list, DIJKSTRA_INFOS* dijkstra_info, int front, int end)
{
    int distance_temp = dijkstra_info -> distance[node_list[end]];
    int i = front - 1;

    for(int location = front ; location < end ; location++)
    {
        if(dijkstra_info -> distance[node_list[location]] >= distance_temp)
        {
            i++;
            quickSortSwap(node_list, i, location);
        }
    }
    quickSortSwap(node_list,i + 1, end);
    i++;
    return(i);
}


/**
 * @brief Qiuck sort.
 * @param dijkstra_info a structure that store the infomations of dijkstra algorithm
 * @param front begin offset of the sorthing array
 * @param end end offset of the sorthing array
*/
void quickSort(int* node_list, DIJKSTRA_INFOS* dijkstra_info, int front, int end)
{
    if(front < end)
    {
        int pivot = quickSortPartition(node_list, dijkstra_info, front, end);
        quickSort(node_list, dijkstra_info, front, pivot - 1);
        quickSort(node_list, dijkstra_info, pivot + 1, end);
    }

}


/**
 * @brief Dijkstra algorithm using stack and sorting.
 * @param graph_csr graph in CSR format
 * @param source_node the node you want to compute all shortest path of other nodes
*/
DIJKSTRA_INFOS* dijkstra(GRAPH_CSR* graph_csr, int source_node)
{
    DIJKSTRA_INFOS* dijkstra_info = (DIJKSTRA_INFOS*)malloc(1 * sizeof(DIJKSTRA_INFOS));
    dijkstra_info -> parents = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));
    dijkstra_info -> distance = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));

    STACK* non_visit_node = stackInitial((graph_csr -> num_node));   
    // STACK* Q = stackInitial(100); 
    for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
    {
        dijkstra_info -> parents[node_id] = -1;
        dijkstra_info -> distance[node_id] = 1000000;
        stackPush(non_visit_node, node_id);
    }
    dijkstra_info -> source_node = source_node;
    dijkstra_info -> distance[source_node] = 0;


    while((stackSize(non_visit_node)) != 0)
    {

        quickSort(non_visit_node -> stack_array, dijkstra_info, 0, stackSize(non_visit_node) - 1);

        // printStack(non_visit_node);


        int select_node = non_visit_node -> stack_array[(stackSize(non_visit_node) - 1)];
        stackPop(non_visit_node);
        // stackPush(Q, select_node);

        for(int neighbor_id = graph_csr -> offset[select_node] ; neighbor_id < graph_csr -> offset[select_node + 1] ; neighbor_id++)
        {
            relax(dijkstra_info, select_node, graph_csr -> edge[neighbor_id], graph_csr -> weight[neighbor_id]);
        }
    }



    // int test = dijkstra_info -> parents[18];
    // printf(" %2d \n", test);
    // while(test != -1)
    // {
    //     test = dijkstra_info -> parents[test];
    //     printf(" %2d \n", test);
    // }
    // printf("The minimum cost is %2d\n", dijkstra_info -> distance[18]);


    return(dijkstra_info);
}

#pragma endregion /* solution_1 */




#pragma region solution_2

/**
 * @brief Adjust the Minimum heap after modify the weight in minimum heap.
 * @param min_heap Minimum heap
 * @param target_item the item in Minimum heap you want to modify
 * @param update_weight the update weight of target node in minimum heap
*/
void adjustMinHeap(MIN_HEAP* min_heap, int target_item, int update_weight)
{
    int target_location = 0;
    for(int location = 0 ; location < MinHeapSize(min_heap) ; location++)
    {
        if(min_heap -> heap_array[location] == target_item)
        {
            target_location = location;
            break;
        }
    }
    min_heap -> heap_weight[target_location] = update_weight;

    swap(&(min_heap -> heap_array[target_location]), &(min_heap -> heap_array[1]));
    swap(&(min_heap -> heap_weight[target_location]), &(min_heap -> heap_weight[1]));
    MinHeapify(min_heap, 1); // BUG !!!
}


/**
 * @brief Dijkstra algorithm using Minimum heap.
 * @param graph_csr graph in CSR format
 * @param source_node the node you want to compute all shortest path of other nodes
*/
DIJKSTRA_INFOS* dijkstraMinHeap(GRAPH_CSR* graph_csr, int source_node)
{

    DIJKSTRA_INFOS* dijkstra_info = (DIJKSTRA_INFOS*)malloc(1 * sizeof(DIJKSTRA_INFOS));
    dijkstra_info -> parents = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));
    dijkstra_info -> distance = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));

    // Building min_heap
    MIN_HEAP* min_heap = MinHeapInitial(graph_csr -> num_node + 1);
    for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
    {
        dijkstra_info -> parents[node_id] = -1;
        dijkstra_info -> distance[node_id] = 1000000;
        // stackPush(non_visit_node, node_id);
        if(node_id != source_node)
        {
            dijkstra_info -> parents[node_id] = -1;
            dijkstra_info -> distance[node_id] = 1000000;
        }
        else
        {
            dijkstra_info -> source_node = source_node;
            dijkstra_info -> parents[node_id] = -1;
            dijkstra_info -> distance[source_node] = 0;
        }
        MinHeapInsert(min_heap, node_id, dijkstra_info -> distance[node_id]);
    }
    // PrintHeap(min_heap);

    while(!MinHeapEmpty(min_heap))
    {
        int select_node = MinHeapGetTop(min_heap);
        MinHeapdelete(min_heap);

        for(int neighbor_id = graph_csr -> offset[select_node] ; neighbor_id < graph_csr -> offset[select_node + 1] ; neighbor_id++)
        {
            relax(dijkstra_info, select_node, graph_csr -> edge[neighbor_id], graph_csr -> weight[neighbor_id]);
            adjustMinHeap(min_heap, graph_csr -> edge[neighbor_id], dijkstra_info -> distance[graph_csr -> edge[neighbor_id]]);

        }
    }

    return(dijkstra_info);
}

#pragma endregion /* solution_2 */





















#endif /* __QUESTION__3__ */