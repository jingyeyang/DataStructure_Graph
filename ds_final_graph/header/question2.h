#ifndef __QUESTION__2__
#define __QUESTION__2__


#pragma region solution_1
/**
 * @brief Print the result of question 2 on CRT.
 * @param order_list the best order of node traverse compute by greedyMethod
 * @param step_record the steps record for each traverse
 * @param num_vivit_node number of the node in visit_list
*/
void showResult2(int* order_list, int* step_record, int num_visit_node)
{
    printf("========== .......... QUESTION 2 RESULT (SOLUTION 1) .......... ==========\n");

    int total_step = 0;
    printf("The order of visiting all node with minimum step :: \n");
    printf(" Start from node %2d", order_list[0]);
    for(int node_id = 1 ; node_id < num_visit_node ; node_id++)
    {
        printf("  %2d(with %2d step) ", order_list[node_id], step_record[node_id]);
        total_step += step_record[node_id];
    }
    printf("\n");

    printf("The minimum total step is %2d.\n", total_step);
    printf("==========================================================================\n");
}


/**
 * @brief Find the best order to traverse all the nodes in visit_list using Greedy method.
 * @param graph_csr graph in CSR format
 * @param visit_list list of node you want to traverse
 * @param num_vivit_node number of the node in visit_list
 * @param begin_node node that begin to walk
*/
void greedtMethod(GRAPH_CSR* graph_csr, int* visit_list, int num_visit_node, int begin_node)
{
    bool all_visit_flag = 0;
    bool* visit_flag = (bool*)malloc(num_visit_node * sizeof(bool));
    int* order_list = (int*)malloc((num_visit_node + 1) * sizeof(int));
    int* step_record = (int*)malloc(num_visit_node * sizeof(int));
    for(int node_id = 0 ; node_id < num_visit_node ; node_id++)
    {
        visit_flag[node_id] = 0;
    }
    order_list[0] = begin_node;

    int num_node_have_visited = 1;
    int source_node = begin_node;
    while(!all_visit_flag)
    {

        BFS_INFOS* bfs_info = NULL;
        bfs_info = BFS(graph_csr, source_node);

        int select_node = -1;
        int min_dis = 1000000000;
        int visit_list_offset = 0;
        // printf("The source node %2d :: \n", source_node);
        for(int node_id = 0 ; node_id < num_visit_node ; node_id++)
        {
            // printf("    distance to node %2d = %2d\n", visit_list[node_id], bfs_info -> distance[visit_list[node_id]]);
            if((bfs_info -> distance[visit_list[node_id]] < min_dis) && (!visit_flag[node_id]))
            {
                select_node = visit_list[node_id];
                min_dis = bfs_info -> distance[select_node];
                visit_list_offset = node_id;
            }
        }
        // printf("select ndoe = %2d\n", select_node);
        order_list[num_node_have_visited] = select_node;
        step_record[num_node_have_visited] = min_dis;
        num_node_have_visited++;
        visit_flag[visit_list_offset] = 1;
        source_node = select_node;




        int temp_flag = 1;
        for(int node_id = 0 ; node_id < num_visit_node ; node_id++)
        {
            temp_flag = temp_flag & visit_flag[node_id];
        }
        all_visit_flag = temp_flag;
    }
    showResult2(order_list, step_record, (num_visit_node + 1));

}

#pragma endregion /* solution_1 */ 




#pragma region solution_1

/**
 * @brief Find the best order to traverse all the nodes in visit_list using Dynamic Programming (Result will print in the process).
 * @param graph_csr graph in CSR format
 * @param visit_list list of node you want to traverse
 * @param num_vivit_node number of the node in visit_list
 * @param begin_node node that begin to walk
*/
void dpMethod(GRAPH_CSR* graph_csr, int* visit_list, int num_visit_node, int begin_node)
{
    int** dp_table = (int**)malloc((num_visit_node) * sizeof(int*)); // for storing the result of the minimum cost. :: diagonal for storing the steps between each node and begin node.
    int** step_table = (int**)malloc((num_visit_node) * sizeof(int*)); // for storing the BFS steps between two node from visit_list.
    int** order_table = (int**)malloc((num_visit_node) * sizeof(int*)); // for storing the order of each row of dp_table.

    for(int i = 0 ; i < num_visit_node ; i++)
    {
        dp_table[i] = (int*)malloc(num_visit_node * sizeof(int));
        step_table[i] = (int*)malloc(num_visit_node * sizeof(int));
        order_table[i] = (int*)malloc(num_visit_node * sizeof(int));
    }

    // Initialization
    for(int i = 0 ; i < num_visit_node ; i++)
    {
        for(int j = 0 ; j < num_visit_node ; j++)
        {
            dp_table[i][j] = 0;
            order_table[i][j] = -1;
        }
        order_table[i][i] = 0;
    }


    // Deal with the diagonal of dp table, means the steps between each visit node and source node.
    BFS_INFOS* bfs_info_source_node = (BFS_INFOS*)malloc(1 * sizeof(BFS_INFOS));
    bfs_info_source_node = BFS(graph_csr, begin_node);

    // printf("diagonal of DP table :: \n"); // the steps between source node and each visit node.
    for(int visit_id = 0 ; visit_id < num_visit_node ; visit_id++)
    {
        dp_table[visit_id][visit_id] = bfs_info_source_node -> distance[visit_list[visit_id]];
        // printf("  %2d ",dp_table[visit_id][visit_id]);
    }
    // printf("\n");

    free(bfs_info_source_node);


    // Deal with step table :: record the steps bewteen each two nodes in visit_list. 
    BFS_INFOS** bfs_info_visit_node = (BFS_INFOS**)malloc((num_visit_node) * sizeof(BFS_INFOS*));
    for(int visit_id = 0 ; visit_id < num_visit_node ; visit_id++)
    {
        bfs_info_visit_node[visit_id] = BFS(graph_csr, visit_list[visit_id]);
    }
    for(int visit_id_row = 0 ; visit_id_row < num_visit_node ; visit_id_row++)
    {
        for(int visit_id_col = 0 ; visit_id_col < num_visit_node ; visit_id_col++)
        {
            step_table[visit_id_row][visit_id_col] = bfs_info_visit_node[visit_id_row] -> distance[visit_list[visit_id_col]];
        }
    }
    free(bfs_info_visit_node);


    // Start to doing the algo to find the global optimization
    int num_visit_node_record = 0;
    while(num_visit_node_record < num_visit_node)
    {
        for(int visit_id = 0 ; visit_id < num_visit_node ; visit_id++)
        {
            int previous_cost = -1;
            int previous_node = -1;
            int min_cost = 1000000;
            int select_node_offset = -1;
            STACK* stack = stackInitial(num_visit_node);
            for(int visit_neighbor = 0 ; visit_neighbor < num_visit_node ; visit_neighbor++)
            {
                // consider have't visited node
                if(order_table[visit_id][visit_neighbor] == -1)
                {
                    stackPush(stack, visit_neighbor);
                }
                // consider the previous node
                if(order_table[visit_id][visit_neighbor] == num_visit_node_record)
                {
                    previous_node = visit_neighbor;
                    previous_cost = dp_table[visit_id][visit_neighbor];
                }
            }

            while(!stackEmpty(stack))
            {
                int visit_neighbor = StackGetTop(stack);
                stackPop(stack);
                if(min_cost > (previous_cost + step_table[previous_node][visit_neighbor]))
                {
                    min_cost = previous_cost + step_table[previous_node][visit_neighbor];
                    select_node_offset = visit_neighbor;
                }
            }
            // Update dp_table and order_table
            dp_table[visit_id][select_node_offset] = min_cost;
            order_table[visit_id][select_node_offset] = num_visit_node_record + 1;

        }
        num_visit_node_record++;
    } 

    // printf("===== Final ====\n");
    // printf("dp table :: \n"); 
    // for(int visit_id_row = 0 ; visit_id_row < num_visit_node ; visit_id_row++)
    // {
    //     for(int visit_id_col = 0 ; visit_id_col < num_visit_node ; visit_id_col++)
    //     {
    //         printf("%2d ", dp_table[visit_id_row][visit_id_col]);
    //     }
    //     printf("\n");
    // }

    // printf("order table :: \n"); 
    // for(int visit_id_row = 0 ; visit_id_row < num_visit_node ; visit_id_row++)
    // {
    //     for(int visit_id_col = 0 ; visit_id_col < num_visit_node ; visit_id_col++)
    //     {
    //         printf("%2d ", order_table[visit_id_row][visit_id_col]);
    //     }
    //     printf("\n");
    // }


    // Show the results 
    int min_step = 100000;
    for(int visit_id = 0 ; visit_id < num_visit_node ; visit_id++)
    {
        for(int neighbor_id = 0 ; neighbor_id < num_visit_node ; neighbor_id++)
        {
            if(order_table[visit_id][neighbor_id] == 3)
            {
                if(dp_table[visit_id][neighbor_id] < min_step)
                {
                    min_step = dp_table[visit_id][neighbor_id];
                }
            }
        }
    }
    // printf("min step = %2d\n", min_step);
    STACK* min_path_offset = stackInitial(num_visit_node);
    for(int visit_id = 0 ; visit_id < num_visit_node ; visit_id++)
    {
        for(int neighbor_id = 0 ; neighbor_id < num_visit_node ; neighbor_id++)
        {
            if(order_table[visit_id][neighbor_id] == 3 && dp_table[visit_id][neighbor_id] == min_step)
            {
                stackPush(min_path_offset, visit_id);
            }
        }
    }

    int num_min_path = stackSize(min_path_offset);
    STACK** min_path = (STACK**)malloc(num_min_path * sizeof(STACK*));
    for(int path_id = 0 ; path_id < num_min_path ; path_id++)
    {
        min_path[path_id] = (STACK*)stackInitial(num_visit_node);
    }
    while(!stackEmpty(min_path_offset))
    {
        int min_offset = StackGetTop(min_path_offset);
        stackPop(min_path_offset);
        for(int order_id = num_visit_node - 1 ; order_id >= 0 ; order_id--)
        {
            for(int neighbor_id = 0 ; neighbor_id < num_visit_node ; neighbor_id++)
            {
                if(order_table[min_offset][neighbor_id] == order_id)
                {
                    stackPush(min_path[stackSize(min_path_offset)], visit_list[neighbor_id]);
                }
            }
        }
    }

    printf("========== .......... QUESTION 2 RESULT (SOLUTION 2) .......... ==========\n");

    printf("The order of visiting all node with minimum step :: \n");
    for(int path_id = 0 ; path_id < num_min_path ; path_id++)
    {
        printf("PATH %2d : ", path_id + 1);
        printf(" Start from node %2d", begin_node);
        while(!stackEmpty(min_path[path_id]))
        {
            int node = StackGetTop(min_path[path_id]);
            stackPop(min_path[path_id]);
            printf("  %2d ", node);
        }
        printf("\n");

    }

    printf("The minimum total step is %2d.\n", min_step);
    printf("==========================================================================\n");

}

#pragma endregion /* solution_2 */ 


#endif /* __QUESTION__2__ */