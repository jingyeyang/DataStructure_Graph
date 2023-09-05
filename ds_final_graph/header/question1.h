#ifndef __QUESTION__1__
#define __QUESTION__1__


#pragma region solution_1

/**
 * @brief The algorithm for constructing minimum spanning tree.
 * @param graph_csr graph in CSR format
 * @param source_node node that start constructing minimum spanning tree
*/
int pirms(GRAPH_CSR* graph_csr, int source_node)
{
    int num_spanning_tree_edge = graph_csr -> num_node - 1;
    int num_edge_recent = 0;
    int total_cost = 0;



    // Check wether the node or edge has been selected
    bool* node_select_flag = (bool*)calloc((graph_csr -> num_node), sizeof(bool));
    bool* edge_select_flag = (bool*)calloc((graph_csr -> num_edge), sizeof(bool));

    // Show the candidate edges
    bool* edge_candidate = (bool*)calloc((graph_csr -> num_edge), sizeof(bool));


    int select_node = source_node;
    while(num_edge_recent < num_spanning_tree_edge)
    {
        node_select_flag[select_node] = 1;
        for(int edge_id = graph_csr -> offset[select_node] ; edge_id < graph_csr -> offset[select_node + 1] ; edge_id++)
        {
            edge_candidate[edge_id] = 1;
        }

        int min_cost = 1000000;
        int min_offset = -1;
        int min_node = -1;
        for(int edge_id = 0 ; edge_id < graph_csr -> num_edge ; edge_id++)
        {
            if((edge_candidate[edge_id]) && (!edge_select_flag[edge_id]) && (!node_select_flag[graph_csr -> edge[edge_id]]))
            {
                if(graph_csr -> weight[edge_id] < min_cost)
                {
                    min_cost = graph_csr -> weight[edge_id];
                    min_offset = edge_id;
                    min_node = graph_csr -> edge[edge_id];
                }
            }
        }

        edge_select_flag[min_offset] = 1;
        select_node = min_node;

        total_cost += min_cost;

        num_edge_recent++;
    }

    return(total_cost);
}


/**
 * @brief Print the result on CRT of question 1.
 * @param total_cost the total cost of the weight of minimum spanning tree
*/
void printResult1_1(int total_cost)
{
    printf("========== .......... QUESTION 1 RESULT (SOLUTION 1) .......... ==========\n");
    printf("The minimum cost of building metro in the beginning is $%3d\n", total_cost);
    printf("==========================================================================\n");
}

#pragma endregion /* solution_1 */




#pragma region solution_2

/**
 * @brief Compute sum of weight of building the spanning tree.
 * @param bfs_info a structure that store the infomations of BFS
 * @param graph_csr graph in CSR format
 * @return sum of the weight of spanning tree
*/
int minCost(BFS_INFOS* bfs_info, GRAPH_CSR* graph_csr)
{
    int min_cost = 0;
    for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
    {
        min_cost += bfs_info -> distance[node_id];
    }
    return(min_cost);
}


/**
 * @brief Print the result on CRT of question 1.
 * @param bfs_info a structure that store the infomations of BFS
 * @param graph_csr graph in CSR format
*/
void printResult1_2(BFS_INFOS* bfs_info, GRAPH_CSR* graph_csr)
{
    printf("========== .......... QUESTION 1 RESULT (SOLUTION 2) .......... ==========\n");

    int level = 0;
    int max_level = 0;
    for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
    {
        if(bfs_info -> distance[node_id] > max_level)
        {
            max_level = bfs_info -> distance[node_id];
        }
    }
    while(max_level != level)
    {   
        level++;
        printf(" THE %2d LEVEL ::\n", level);
        for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
        {
            if(bfs_info -> distance[node_id] == level)
            {
                printf("  %2d ", node_id);
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("The minimum cost of building metro in the beginning is $%3d\n", minCost(bfs_info, graph_csr));
    printf("=========================================================================\n");
}


/**
 * @brief Initial the BFS_INFOS structure.
 * @param graph_csr graph in CSR format
 * @return a pointer points at BFS_INFOS structure
*/
BFS_INFOS* bfsInfoInitial(GRAPH_CSR* graph_csr)
{
    BFS_INFOS* bfs_info = (BFS_INFOS*)malloc(1 * sizeof(BFS_INFOS));

    bfs_info -> distance = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));
    bfs_info -> parents = (int*)malloc((graph_csr -> num_node + 1) * sizeof(int));

    for(int node_id = graph_csr -> start_node ; node_id <= graph_csr -> end_node ; node_id++)
    {
        bfs_info -> distance[node_id] = -1;
        bfs_info -> parents[node_id] = -1;
    }
    
    return(bfs_info);
}


/**
 * @brief Doing BFS start at source node.
 * @param graph_csr graph in CSR format
 * @param source_node the node that we start doing BFS
 * @return a pointer points at BFS result store in BFS_INFOS structure
*/
BFS_INFOS* BFS(GRAPH_CSR* graph_csr, int source_node)
{
    BFS_INFOS* bfs_info = bfsInfoInitial(graph_csr); 

    QUEUE* queue = queueInitial(1);
    queuePush(queue, source_node);
    bfs_info -> source_node = source_node;
    bfs_info -> distance[source_node] = 0;

    while(!queueEmpty(queue))
    {
        //queuePrint(queue);
        int current_node = queueGetTop(queue);
        queuePop(queue);

        for(int neighbor_id = graph_csr -> offset[current_node] ; neighbor_id < graph_csr -> offset[current_node + 1] ; neighbor_id++)
        {
            if(bfs_info -> distance[graph_csr -> edge[neighbor_id]] < 0)
            {
                queuePush(queue, graph_csr -> edge[neighbor_id]);
                bfs_info -> distance[graph_csr -> edge[neighbor_id]] = bfs_info -> distance[current_node] + 1;
                bfs_info -> parents[graph_csr -> edge[neighbor_id]] = current_node;
            }
        }
    }

    return(bfs_info);
}

#pragma endregion /* solution_2 */


#endif /* __QUESTION__1__ */