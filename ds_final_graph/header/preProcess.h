/**
 * @brief This header file content the process of reading dataset and building it into adjacency list or CSR format.
*/
#ifndef __PREPROCESS__H__
#define __PREPROCESS__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/**
 * @brief Pint the graph in CSR format on CRT.
 * @param graph graph in CSR format
*/
void printCSR(GRAPH_CSR* graph)
{
    printf("========== .......... THE GRAPH CSR FORMAT .......... ==========\n");
    int offset_temp = 0;
    // for(int node_id = graph_info -> start_node ; node_id <= graph_info -> end_node ; node_id++)
    // {
    //     int offset_start = graph -> offset[node_id];
    //     offset_temp = 0;
    //     cout << "NODE " << node_id << " START FROM " << offset_start << " TO " << graph -> offset[node_id + 1] - 1 << " :: " << endl;
    //     for(int edge_id = graph -> offset[node_id] ; edge_id < graph -> offset[node_id + 1] ; edge_id++)
    //     {
    //         cout << graph -> edge[edge_id] << "  ";
    //     }
    //     cout << endl;
    // }
    for(int node_id = graph -> start_node ; node_id <= graph -> end_node ; node_id++)
    {
        int offset_start = graph -> offset[node_id];
        printf("NODE %2d START FROM %2d TO %2d ::\n", node_id, graph -> offset[node_id], graph -> offset[node_id + 1]);
        for(int edge_id = graph -> offset[node_id] ; edge_id < graph -> offset[node_id + 1] ; edge_id++)
        {
            printf("  %2d (%d)  ", graph -> edge[edge_id], graph -> weight[edge_id]);
        }
        printf("\n");
    }
    printf("========== .......................................... ==========\n");
}

/**
 * @brief Pint the graph in adj list on CRT.
 * @param graph graph in adj list
*/
void printGraph(GRAPH* graph)
{
    printf("========== .......... THE GRAPH .......... ==========\n");
    printf("START NODE = %d\n", graph -> start_node);
    printf("END   NODE = %d\n", graph -> end_node);
    for(int node_id = graph -> start_node ; node_id <= graph -> end_node ; node_id++)
    {

        printf("NODE %2d :: ", node_id);
        GRAPH_NODE* ptr = graph -> edge_list[node_id]; 
        while (ptr != NULL)
        {
            printf("%2d -> ", ptr -> node_id);
            ptr = ptr -> next;
        }
        printf("NULL\n");
    }
    printf("========== ................................ ==========\n");
}


/**
 * @brief Build the graph into CSR format.
 * @param graph graph in CSR format
 * @return graph in CSR format
*/
GRAPH_CSR* graphBuildCSR(GRAPH* graph)
{
    GRAPH_CSR* graph_csr = (GRAPH_CSR*)malloc(1 * sizeof(GRAPH_CSR));
    graph_csr -> offset = (int*)malloc((graph -> num_node + 2) * sizeof(int));
    if(graph -> directed)
    {   
        // Directed graph.
        graph_csr -> edge = (int*)malloc((graph -> num_edge) * sizeof(int));
        graph_csr -> weight = (int*)malloc((graph -> num_edge) * sizeof(int));
        graph_csr -> num_edge = graph -> num_edge;
    }
    else
    {
        // Undirected graph.
        graph_csr -> edge = (int*)malloc((2 * graph -> num_edge) * sizeof(int));
        graph_csr -> weight = (int*)malloc((2 * graph -> num_edge) * sizeof(int));
        graph_csr -> num_edge = (2 * graph -> num_edge);
    }

    graph_csr -> start_node = graph -> start_node;
    graph_csr -> end_node = graph -> end_node;
    graph_csr -> num_node = graph -> num_node;

    int offset_count = 0;
    GRAPH_NODE* ptr;
    for(int node_id = graph -> start_node ; node_id <= graph -> end_node ; node_id++)
    {   
        graph_csr -> offset[node_id] = offset_count;
        ptr = graph -> edge_list[node_id];
        while(ptr != NULL)
        {
            graph_csr -> edge[offset_count] = ptr -> node_id;
            graph_csr -> weight[offset_count] = ptr -> weight;
            ptr = ptr -> next;
            offset_count++;
        }
    }
    graph_csr -> edge[offset_count] = -1;
    graph_csr -> weight[offset_count] = -1;
    if(graph -> start_node == 0)
    {
        graph_csr -> offset[graph -> num_node] = graph_csr -> num_edge;
    }
    else
    {
        graph_csr -> offset[graph -> num_node + 1] = graph_csr -> num_edge;
    }

    return(graph_csr);
}


/**
 * @brief Release the adj list.
 * @param graph graph in adj list
 * @param graph_ptr_address the real address of the adj lsit
*/
void freeGraph(GRAPH* graph, GRAPH* *graph_ptr_address)
{
    if(graph != NULL)
    {
        for(int node_id = graph -> start_node ; node_id <= graph -> end_node; node_id++)
        {
            GRAPH_NODE* ptr = graph -> edge_list[node_id];
            while(ptr != NULL)
            {
                GRAPH_NODE* temp = ptr;
                ptr = ptr -> next;
                free(temp);
            }
        }
        free(graph -> edge_list);
        free(graph);
        *graph_ptr_address = NULL;
    }
    else
    {
        writeErrorLog("Error occured : GRAPH* is NULL can't be free");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }
}


/**
 * @brief Add the node as the source node's neighbor in adj list.
 * @param graph graph in adj list
 * @param node structure that stores infomation of neighbors of source node and the wieght between them
 * @param source_node the node you want to insert into
*/
void addEdge(GRAPH* graph, GRAPH_NODE* node, int source_node)
{
    node -> next = graph -> edge_list[source_node];
    graph -> edge_list[source_node] = node;
}


/**
 * @brief Create a node that store in adj list.
 * @param node the node ID
 * @param w the weight
*/
GRAPH_NODE* createGraphNode(int node, int w)
{
    GRAPH_NODE* graph_node = (GRAPH_NODE*)malloc(1 * sizeof(GRAPH_NODE));
    graph_node -> node_id = node;
    graph_node -> weight = w;
    graph_node -> next = NULL;
    return(graph_node);
}


/**
 * @brief Initial the adj list.
 * @param num_node #node
 * @param num_edge #edge
 * @return the empty adl list 
*/
GRAPH* createGraph(int num_node, int num_edge)
{
    GRAPH* graph = (GRAPH*)malloc(1 * sizeof(GRAPH));
    graph -> edge_list = (GRAPH_NODE**)malloc((num_node + 1) * sizeof(GRAPH_NODE*));

    graph -> num_node = num_node;
    graph -> num_edge = num_edge;

    for(int node_id = 0 ; node_id <= num_node ; node_id++)
    {
        graph -> edge_list[node_id] = NULL;
    }
    return(graph);
}


/**
 * @brief Read the dataset and build it into adj list.
 * @param dataset the name of the dataset
 * @return graph in adj list
*/
GRAPH* readGraph(char* dataset)
{
    FILE* input_file = fopen(dataset, "r");
    if(input_file == NULL)
    {
        writeErrorLog("Error occured : GRAPH dataset open failed");
        printf("ERROR : check the error_log\n");
        exit(-1);
    }

    char buffer[10];
    char dataset_info1[10];
    char dataset_info2[10];
    int num_node;
    int num_edge;
    
    fscanf(input_file, "%s", buffer);
    fscanf(input_file, "%s", dataset_info1);
    fscanf(input_file, "%s", dataset_info2);
    fscanf(input_file, "%s", buffer);
    fscanf(input_file, "%d", &num_edge);
    fscanf(input_file, "%d", &num_node);
    fscanf(input_file, "%s", buffer);

    float avg_degree = (float)(2 * num_edge) / (num_node);

    printf("==================================\n");
    printf("       DATASET INFORMATIONS       \n");
    printf("    NAME       = %s\n", dataset);
    printf("    BASIC INFO = %s %s\n", dataset_info1, dataset_info2);
    printf("    #EDGE      = %d\n", num_edge);
    printf("    #NODE      = %d\n", num_node);
    printf("    AvgDegree  = %f\n", avg_degree);
    printf("==================================\n");


    GRAPH* graph = (GRAPH*)createGraph(num_node, num_edge);

    // Symetric unweighted graph
    if(strcmp(dataset_info2, "unweighted") == 0 && strcmp(dataset_info1, "sym") == 0)
    {
        printf("It's a Undirected Unweighted graph\n");
        graph -> weighted = 0;
        graph -> directed = 0;

        int read_node1;
        int read_node2;
        fscanf(input_file, "%d %d", &read_node1, &read_node2);
        if(read_node1 == 0)
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node - 1;
        }
        else
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node;
        }
        GRAPH_NODE* node1 = createGraphNode(read_node1, 1);
        GRAPH_NODE* node2 = createGraphNode(read_node2, 1);
        addEdge(graph, node1, read_node2);
        addEdge(graph, node2, read_node1);

        while(fscanf(input_file, "%d %d", &read_node1, &read_node2) == 2)
        {
            //printf("%d %d\n", read_node1, read_node2);
            
            node1 = createGraphNode(read_node1, 1);
            node2 = createGraphNode(read_node2, 1);
            addEdge(graph, node1, read_node2);
            addEdge(graph, node2, read_node1);
        }
    }
    // Unsymetric unweighted graph
    else if(strcmp(dataset_info2, "unweighted") == 0 && strcmp(dataset_info1, "unsym") == 0)
    {
        printf("It's a Directed Unweighted graph\n");
        graph -> weighted = 0;
        graph -> directed = 1;

        int read_node1;
        int read_node2;
        fscanf(input_file, "%d %d", &read_node1, &read_node2);
        if(read_node1 == 0)
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node - 1;
        }
        else
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node;
        }
        GRAPH_NODE* node2 = createGraphNode(read_node2, 1);
        addEdge(graph, node2, read_node1);

        while(fscanf(input_file, "%d %d", &read_node1, &read_node2) == 2)
        {
            node2 = createGraphNode(read_node2, 1);
            addEdge(graph, node2, read_node1);
        }
        
    }
    // Unsymetric weighted graph
    else if(strcmp(dataset_info2, "weighted") == 0 && strcmp(dataset_info1, "unsym") == 0)
    {
        printf("It's a Directed Weighted graph\n");
        graph -> weighted = 1;
        graph -> directed = 1;

        int read_node1;
        int read_node2;
        int weight;
        fscanf(input_file, "%d %d %d", &read_node1, &read_node2, &weight);
        if(read_node1 == 0)
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node - 1;
        }
        else
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node;
        }
        GRAPH_NODE* node2 = createGraphNode(read_node2, weight);
        addEdge(graph, node2, read_node1);
        
        while(fscanf(input_file, "%d %d %d", &read_node1, &read_node2, &weight) == 3)
        {
            node2 = createGraphNode(read_node2, weight);
            addEdge(graph, node2, read_node1);
        }

    }
    // Symetric weighted graph
    else
    {
        printf("It's a Undirected Weighted graph\n");
        graph -> weighted = 1;
        graph -> directed = 0;

        int read_node1;
        int read_node2;
        int weight;
        fscanf(input_file, "%d %d %d", &read_node1, &read_node2, &weight);
        if(read_node1 == 0)
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node - 1;
        }
        else
        {
            graph -> start_node = read_node1;
            graph -> end_node = graph -> num_node;
        }
        GRAPH_NODE* node1 = createGraphNode(read_node1, weight);
        GRAPH_NODE* node2 = createGraphNode(read_node2, weight);
        addEdge(graph, node1, read_node2);
        addEdge(graph, node2, read_node1);

        while(fscanf(input_file, "%d %d %d", &read_node1, &read_node2, &weight) == 3)
        {
            //printf("%d %d\n", read_node1, read_node2);
            
            node1 = createGraphNode(read_node1, weight);
            node2 = createGraphNode(read_node2, weight);
            addEdge(graph, node1, read_node2);
            addEdge(graph, node2, read_node1);
        }

    }

    fclose( input_file);
    return(graph);
}

#endif /* __PREPROCESS__H__ */