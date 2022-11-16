#ifndef __GRAPH__HXX__
#define __GRAPH__HXX__

#include "Graph.h"
#include "Edge.h"
#include <map>
#include <numeric>
#include <queue>
#include <algorithm>

template < class V, class C >
Graph<V, C>::Graph( ) {
  
}

template < class V, class C >
Graph<V, C>::Graph( int num_vertices ) {
  this->adj = new std::vector< int > [ num_vertices ];
}

template < class V, class C > void
Graph<V, C>::AddVertex( V point ) {
  Vertex < V, C > vertex;
  vertex.setPoint( point );
  this->vertices.push_back( vertex );
}

template < class V, class C > V
Graph<V, C>::GetVertex(long pos) {
  return this->vertices[pos].getPoint( );
}

template < class V, class C > void
Graph<V, C>::AddEdge(long start, long end, C cost) {

  this->vertices[start].getConnections().push_back(new Edge < C > (end, cost));
  //this->vertices[end].getConnections().push_back(new Edge < C > (start, cost));

}

template < class V, class C > std::vector < Vertex < V, C > >
Graph<V, C>::getVertices() {
    return this->vertices;
}

template < class V, class C > long
Graph<V, C>::Dijkstra( long start, long end ) {
  typedef std::pair < C, long > pair;

  std::vector < bool > visited ( this->vertices.size( ), false ); //nodos visitados, inicialmente ninguno

  std::priority_queue < pair > Q; //cola de prioridad
  
  Q.push({ 0, start }); //introducimos el nodo origen (a distancia 0 de él mismo)

  while (!Q.empty()){
    pair arc = Q.top( ); //arco con menor peso desde F hasta G\F 
    
    Q.pop( ); //lo quitamos de la cola

    C cost = arc.first; //distancia entre el nodo origen y v
    long v = arc.second; //vértice de Q a menor distancia del nodo origen

    if (v == end) return -cost;

    if (!visited[v]) { 
        visited[v] = true;
        for (Edge < C >* edge : this->vertices[v].getConnections( )) 
            Q.push({cost - edge->getCost( ), edge->getConnect( )}); 
    }
  }

  return 9999999;
}


template < class V, class C > std::vector < long >
Graph<V, C>::DijkstraWithPath( long start, long end ) {
  typedef std::pair < C, long > pair;
  
  std::vector < long > path ( this->vertices.size( ) );

  std::vector < bool > visited ( this->vertices.size( ), false ); //nodos visitados, inicialmente ninguno

  std::priority_queue < pair > Q; //cola de prioridad
  
  Q.push({ 0, start }); //introducimos el nodo origen (a distancia 0 de él mismo)

  while (!Q.empty()){
    pair arc = Q.top( ); //arco con menor peso desde F hasta G\F 
    
    Q.pop( ); //lo quitamos de la cola

    C cost = arc.first; //distancia entre el nodo origen y v
    long v = arc.second; //vértice de Q a menor distancia del nodo origen

    if (v == end) {
      std::vector < long > shortestPath;
      shortestPath.push_back(end);
      while (path[v] != start) {
          shortestPath.push_back(path[v]);
          v = path[v];
      }
      shortestPath.push_back(start);
      std::reverse(shortestPath.begin(), shortestPath.end());
      return shortestPath;
    }

    if (!visited[v]) { 
        visited[v] = true;
        for (Edge < C >* edge : this->vertices[v].getConnections( )) {
            Q.push({cost - edge->getCost( ), edge->getConnect( )}); 
            path[edge->getConnect( )] = v;
        }
    }
  }

  return path;
}

template < class V, class C > void
Graph<V, C>::print( ) {
  std::cout << this->vertices.size( ) << " vertex." << std::endl;
  for (int i = 0; i < this->vertices.size( ); i++)
    for (Edge < C >* edge : vertices[i].getConnections( ))
      std::cout << "From " << vertices[i].getPoint( ) << " [" << i << "] to " 
      << vertices[edge->getConnect( )].getPoint( ) << " [" << edge->getConnect( ) 
      << "] with cost " << edge->getCost( ) << std::endl;
}

template < class V, class C > std::vector < std::vector < C > > 
Graph< V, C >::AdjMatrix( ) {
  std::vector < std::vector < C > > dist (this->vertices.size( ), std::vector < C > ( this->vertices.size( ) ));
  for (int i = 0; i < vertices.size( ); i++) 
    for (int j = 0; j < vertices[i].getConnections( ).size( ); j++) 
      dist[i][vertices[i].getConnections( )[j]->getConnect( )] = vertices[i].getConnections( )[j]->getCost( );
  return dist;
}

template < class V, class C > std::vector < std::vector < C > > 
Graph< V, C >::FloydWarshall( ) {
  std::vector < std::vector < C > > dist = this->AdjMatrix( );
  for (int i = 0; i < dist.size( ); i++) {
        for (int j = 0; j < dist.size( ); j++) {
            if (i != j && dist[i][j] == 0) dist[i][j] = 9999999; 
        }
    }

         
  for (int k = 0; k < dist.size( ); k++) 
    for (int i = 0; i < dist.size( ); i++) 
        for (int j = 0; j < dist.size( ); j++)
            dist[i][j] = dist[i][j] < dist[i][k] + dist[k][j] ? dist[i][j] : dist[i][k] + dist[k][j];
      
     return dist;
}



#endif