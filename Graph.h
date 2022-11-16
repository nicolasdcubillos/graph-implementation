#ifndef __GRAPH__H__
#define __GRAPH__H__

#include <list>
#include <vector>
#include <map>
#include "Vertex.h"

template < class V, class C >
class Graph {
  public:
    Graph( );
    Graph( int );
    void AddVertex( V );
    V GetVertex( long );
    void AddEdge( long, long, C );
    std::vector< Vertex < V, C > > getVertices( );
    long Dijkstra( long, long );
    std::vector < long > DijkstraWithPath( long, long );
    void print ( );
    std::vector < std::vector < C > > AdjMatrix();
    std::vector < std::vector < C > > FloydWarshall();
  
  private:
    std::vector < Vertex < V, C > > vertices;
};

#include "Graph.hxx"

#endif