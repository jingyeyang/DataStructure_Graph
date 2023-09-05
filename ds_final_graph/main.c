#include "header/dataStructure.h"
#include "header/error.h"
#include "header/preProcess.h"
#include "header/stack.h"
#include "header/queue.h"
#include "header/minHeap.h"

#include "header/question1.h"
#include "header/question2.h"
#include "header/question3.h"








int main(int argc, char* argv[], char* env[])
{

    // Preprocessing :: reading the dataset and storing the dataset using adj list or CSR format.

    GRAPH* graph_adj = readGraph(argv[1]);
    // printGraph(graph_adj);

    GRAPH_CSR* graph_csr = graphBuildCSR(graph_adj);
    // printCSR(graph_csr);


    // Question 1 :: Finding the least cost for building the metro by connecting all stations.

        // Q1. Solution 1 :: using pirms algorithm constructing minimum spanning tree, start from any node you want.
    int min_cost = pirms(graph_csr, 17);
    printResult1_1(min_cost);
    printf("\n\n");


        // Q1. Solution 2 :: using BFS start from node 4 cause the weight is propotional to the distance from node 4.
    BFS_INFOS* bfs_info = NULL;
    bfs_info = (BFS_INFOS*)malloc(1 * sizeof(BFS_INFOS));
    bfs_info = BFS(graph_csr, 4);
    printResult1_2(bfs_info, graph_csr);
    free(bfs_info);
    printf("\n\n");



    // Question 2 :: Gevin some station you would like to visit, compute the best order to visit with minimum steps.

        // Q2. Solution 1 :: using greedy method 
    int source_node = 4;
    int num_visit_node = 4;
    int visit_list[4] = {29, 15, 2, 6};
    greedtMethod(graph_csr, visit_list, num_visit_node, source_node);
    printf("\n\n");
 
        // Q2. Solution 2 :: using dynamic programming
    dpMethod(graph_csr, visit_list, num_visit_node, source_node);
    printf("\n\n");




    // Question 3 :: Finding the minimum sum of weight that the path begin from source node to nodes in visit_lsit.

        // Q3. solution 1 :: Using sorting
    source_node = 37;
    int num_visit_node_Q3 = 3;
    int visit_list_Q3[3] = {2, 5, 26};
    DIJKSTRA_INFOS* dijkstra_info_1 = dijkstra(graph_csr, source_node);
    PrintResult3(dijkstra_info_1, visit_list_Q3, num_visit_node_Q3);
    printf("\n\n");

        // Q3. solution 2 :: Using minimum heap
    DIJKSTRA_INFOS* dijkstra_info_2 = dijkstraMinHeap(graph_csr, source_node);
    PrintResult3(dijkstra_info_2, visit_list_Q3, num_visit_node_Q3);
    printf("\n\n");

}