//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"

struct _GraphTopoSort {
  int* marked;                     // Aux array
  unsigned int* numIncomingEdges;  // Aux array
  unsigned int* vertexSequence;    // The result
  int validResult;                 // 0 or 1
  unsigned int numVertices;        // From the graph
  Graph* graph;
};

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort* _create(Graph* g) {
  assert(g != NULL);

  GraphTopoSort* p = NULL;

    p = (GraphTopoSort*)malloc(sizeof(GraphTopoSort));
    if (p == NULL) {
        printf("Error in _create(): memory allocation of GraphTopoSort failed!\n");
        exit(EXIT_FAILURE);
    }

    p->marked = (int*)malloc(GraphGetNumVertices(g) * sizeof(int));
    if (p->marked == NULL) {
      printf("Error in _create(): memory allocation of marked failed!\n");
      exit(0);
    }

    p->numIncomingEdges = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
    if (p->numIncomingEdges == NULL) {
      printf("Error in _create(): memory allocation of numIncomingEdges failed!\n");
      exit(0);
    }

    p->vertexSequence = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
    if (p->vertexSequence == NULL) {
      printf("Error in _create(): memory allocation of vertexSequence failed!\n");
      exit(0);
    }

    p->validResult = 0;
    p->numVertices = GraphGetNumVertices(g);
    p->graph = g;

    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
      p->marked[i] = 0;
      p->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
      p->vertexSequence[i] = 0;
    }

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
    assert(g != NULL && GraphIsDigraph(g) == 1);

    GraphTopoSort* topoSort = _create(g);

    // Build the topological sorting using Algorithm 1

    // Process each vertex
    for (unsigned int i = 0; i < topoSort->numVertices; i++) {
        int vertexWithoutIncomingEdges = -1;

        // Find a vertex with no incoming edges
        for (unsigned int v = 0; v < topoSort->numVertices; v++) {
            if (topoSort->marked[v] == 0 && topoSort->numIncomingEdges[v] == 0) {
                vertexWithoutIncomingEdges = v;
                break;
            }
        }

        if (vertexWithoutIncomingEdges == -1) {
            // There is a cycle in the graph, topological sorting is not possible
            topoSort->validResult = 0;
            return topoSort;
        }

        // Mark the vertex as visited
        topoSort->marked[vertexWithoutIncomingEdges] = 1;

        // Store the vertex in the result sequence
        topoSort->vertexSequence[i] = vertexWithoutIncomingEdges;

        // Update the number of incoming edges for adjacent vertices
        for (unsigned int e = 0; e < GraphGetVertexOutDegree(g, vertexWithoutIncomingEdges); e++) {
            unsigned int adjacentVertex = GraphGetAdjacentsTo(g, vertexWithoutIncomingEdges)[e];
            topoSort->numIncomingEdges[adjacentVertex]--;
        }
    }

    // Check if a valid sorting was computed
    topoSort->validResult = 1;

    return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV2(Graph* g) {
    assert(g != NULL && GraphIsDigraph(g) == 1);

    // Create and initialize the struct
    GraphTopoSort* topoSort = _create(g);

    // Initialize an array to store in-degrees of vertices
    unsigned int* inDegrees = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
    if (inDegrees == NULL) {
        printf("Error in GraphTopoSortComputeV2: Memory allocation failed!\n");
        GraphTopoSortDestroy(&topoSort);
        return NULL;
    }

    // Initialize the in-degrees array
    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
        inDegrees[i] = GraphGetVertexInDegree(g, i);
        if (inDegrees[i] == 0) {
            topoSort->vertexSequence[topoSort->validResult++] = i;
            topoSort->marked[i] = 1;
        }
    }

    // Build the topological sorting
    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
        if (topoSort->validResult == (int)(GraphGetNumVertices(g))) {
            // All vertices were processed
            break;
        }

        if (topoSort->validResult == (int)(i)) {
            // There is a cycle in the graph, topological sorting is not possible
            topoSort->validResult = 0;
            break;
        }

        // Get the next vertex to process
        unsigned int vertex = topoSort->vertexSequence[i];

        // Update the number of incoming edges for adjacent vertices
        for (unsigned int e = 0; e < GraphGetVertexOutDegree(g, vertex); e++) {
            unsigned int adjacentVertex = GraphGetAdjacentsTo(g, vertex)[e];
            inDegrees[adjacentVertex]--;
            if (inDegrees[adjacentVertex] == 0) {
                topoSort->vertexSequence[topoSort->validResult++] = adjacentVertex;
                topoSort->marked[adjacentVertex] = 1;
            }
        }
    }

    free(inDegrees);
    return topoSort;
}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
    assert(g != NULL && GraphIsDigraph(g) == 1);

    // Create and initialize the struct
    GraphTopoSort* topoSort = _create(g);

    // Allocate and initialize an array to store the in-degree of each vertex
    unsigned int* numEdgesPerVertex = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
    if (numEdgesPerVertex == NULL) {
        printf("Error in GraphTopoSortComputeV3(): memory allocation failed!\n");
        GraphTopoSortDestroy(&topoSort);
        return NULL;
    }

    // Initialize the in-degree array
    for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
        numEdgesPerVertex[i] = GraphGetVertexInDegree(g, i);
        if (numEdgesPerVertex[i] == 0) {
            // If in-degree is 0, add the vertex to the result
            topoSort->vertexSequence[topoSort->validResult++] = i;
        }
    }

    // Perform topological sorting
    for (int i = 0; i < topoSort->validResult; i++) {
        unsigned int v = topoSort->vertexSequence[i];

        // Iterate through adjacent vertices
        for (unsigned int w = 0; w < GraphGetNumVertices(g); w++) {
            if (GraphGetAdjacentsTo(g, v)[w] != (unsigned int)(-1)) {
                // Reduce in-degree of the adjacent vertex
                numEdgesPerVertex[w]--;

                // If in-degree becomes 0, add the vertex to the result
                if (numEdgesPerVertex[w] == 0) {
                    topoSort->vertexSequence[topoSort->validResult++] = w;
                }
            }
        }
    }

    free(numEdgesPerVertex);

    // Check if a valid sorting was computed
    topoSort->validResult = (topoSort->validResult == (int)(GraphGetNumVertices(g))) ? 1 : 0;

    return topoSort;
}

void GraphTopoSortDestroy(GraphTopoSort** p) {
  assert(*p != NULL);

  GraphTopoSort* aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort* p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int* GraphTopoSortGetSequence(const GraphTopoSort* p) {
  assert(p != NULL);

    if (p->validResult == 1) {
        unsigned int* result = (unsigned int*)malloc(GraphGetNumVertices(p->graph) * sizeof(unsigned int));
        if (result == NULL) {
        printf("Error in GraphTopoSortGetSequence(): memory allocation failed!\n");
        return NULL;
        }

        for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
        result[i] = p->vertexSequence[i];
        }

        return result;
    }
    else {
        return NULL;
    }
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort* p) {
  assert(p != NULL);

  if (p->validResult == 0) {
    printf("The topological sorting could not be computed!!\n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort* p) {
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0) {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
