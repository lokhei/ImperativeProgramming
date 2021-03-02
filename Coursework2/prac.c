#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 


//struct for adjacency list node
typedef struct listnode 
{ 
    int dest; 
    struct listnode* next; 
}listnode; 
  
// struct for an adjacency list 
typedef struct AdjList 
{ 
    struct listnode *head;  
}Adjlist; 
  
// struct for network - array of adjacency lists; size = no of vertices
typedef struct Network 
{ 
    int Vertices; 
    struct AdjList* array; 
}Network; 
  
//creates a new adjacency list node 
struct listnode* newlistnode(int dest) 
{ 
    struct listnode* newNode = (struct listnode*) malloc(sizeof(struct listnode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
} 
  
// creates a network of V vertices 
Network* createNetwork(int Vertices) 
{ 
    Network* network =  
        (Network*) malloc(sizeof(Network)); 
    network->Vertices = Vertices; 
  
    // Create an array of adjacency lists. array size = V
    network->array =  (struct AdjList*) malloc(Vertices * sizeof(struct AdjList)); 
  
    // Initialize each adjacency list as empty by making head as NULL 
    int i; 
    for (i = 0; i < Vertices; ++i) 
        network->array[i].head = NULL; 
  
    return network; 
} 
  
// Adds an edge to an undirected graph 
void addEdge(Network* network, int src, int dest) 
{ 
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    struct listnode* newNode = newlistnode(dest); 
    newNode->next = network->array[src].head; 
    network->array[src].head = newNode; 
  
    // Since graph is undirected, add an edge from 
    // dest to src also 
    newNode = newlistnode(src); 
    newNode->next = network->array[dest].head; 
    network->array[dest].head = newNode; 
} 
  
// A utility function to print the adjacency list  
// representation of graph 
void printNetwork(Network* network) 
{ 
    int Vertices; 
    for (Vertices = 0; Vertices < network->Vertices; Vertices ++) 
    { 
        struct listnode* pCrawl = network->array[Vertices].head; 
        printf("\n Adjacency list of vertex %d\n head ", Vertices); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 
  
// Driver program to test above functions 
int main() 
{ 
    // create the graph given in above fugure 
    int Vertices = 5; 
    Network* network = createNetwork(Vertices); 
    addEdge(network, 0, 1); 
    addEdge(network, 0, 4); 
    addEdge(network, 1, 2); 
    addEdge(network, 1, 3); 
    addEdge(network, 1, 4); 
    addEdge(network, 2, 3); 
    addEdge(network, 3, 4); 
  
    // print the adjacency list representation of the above graph 
    printNetwork(network); 
  
    return 0; 
} 
