/**
 * @brief This header file content the data structure used in assignment.
*/
#ifndef __DATASTRUCTURE__H__
#define __DATASTRUCTURE__H__

#include<stdbool.h>


//////////////////// .................... DATA STRUCTURE :: HEAP .................... ////////////////////

/**
 * @brief  Contain :: heap_array(minimum heap), heap_ptr, max_size.
*/
typedef struct MIN_HEAP
{
    int* heap_array;
    int* heap_weight;
    int heap_ptr;       // heap_ptr == 0 :: heap is empty.
    int max_size;
}MIN_HEAP;


//////////////////// .................... DATA STRUCTURE :: STACK .................... ////////////////////

/**
 * @brief Contain :: stack_array(stack), stack_ptr, max_size.
*/
typedef struct STACK
{
    int* stack_array;
    int stack_ptr;
    int max_size;

}STACK;


//////////////////// .................... DATA STRUCTURE :: QUEUE .................... ////////////////////

/**
 * @brief Contain :: queue_array(queue), front_ptr, end_ptr, current_size, max_size.
*/
typedef struct QUEUE
{
    int* queue_array;
    int front_ptr;
    int end_ptr;
    int current_size;
    int max_size;
}QUEUE;


//////////////////// .................... DATA STRUCTURE :: GRAPH .................... ////////////////////

/**
 * @brief the node stores in the adj list.
*/
typedef struct GRAPH_NODE
{

    int node_id;
    int weight;
    struct GRAPH_NODE* next;

}GRAPH_NODE;

/**
 * @brief Graph store in adj list.
*/
typedef struct GRAPH
{
    GRAPH_NODE** edge_list;
    int num_node;
    int num_edge;
    int start_node;
    int end_node;
    bool weighted; // weighted = 1, unweighted = 0
    bool directed; // directed = 1, undirected = 0
    
}GRAPH;

/**
 * @brief Graph store in CSR format.
*/
typedef struct GRAPH_CSR
{
    int* offset;
    int* edge;
    int* weight;
    int start_node;
    int end_node;
    int num_edge;
    int num_node;

}GRAPH_CSR;


//////////////////// .................... DATA STRUCTURE :: ALOG INFO .................... ////////////////////

/**
 * @brief The data structure that store the result of BFS.
 * @param source_node the node that we start doing BFS
 * @param parents to record each node's parent when doing BFS
 * @param distance to record distance of each node from the source node
*/
typedef struct BFS_INFOS
{
    int source_node;
    int* parents;
    int* distance;  // It means the hops from the source node.
}BFS_INFOS;

/**
 * @brief The data structure that store the result of dijkstra algorithm with Single Source Shortest Path(SSSP) tree.
 * @param source_node the beginning node
 * @param parents the parent for each node in SSSP tree
 * @param distance the shortest distance from source node to each node
*/
typedef struct  DIJKSTRA_INFOS
{
    int source_node;
    int* parents;
    int* distance;
}DIJKSTRA_INFOS;

#endif /* __DATASTRUCTURE__H__ */