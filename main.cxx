#include <iostream>
#include "Graph.h"

using namespace std;

void print_mat(std::vector < std::vector < float > > dist) {
    for (int i = 0; i < dist.size( ); i++) {
        for (int j = 0; j < dist[i].size( ); j++) {
            std::cout << dist[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}

int main (int argc, char** argv) {
    Graph < string, float > graph;
    graph.AddVertex("Abrir imagen 1"); // 0
    graph.AddVertex("Sumar imagenes 1"); // 1
    graph.AddVertex("Ajustar intensidad 1"); // 2
    graph.AddVertex("Promediar imagenes"); // 3
    graph.AddVertex("Guardar imagen 1"); // 4
    graph.AddVertex("Abrir imagen 2"); // 5
    graph.AddVertex("Restar imagenes"); // 6
    graph.AddVertex("Ajustar intensidad 2"); // 7
    graph.AddVertex("Ajustar intensidad 3"); // 8
    graph.AddVertex("Suavizar"); // 9
    graph.AddVertex("Guardar imagen 3"); // 10
    graph.AddVertex("Sumar imagenes 2"); // 11
    graph.AddVertex("Guardar imagen 2"); // 12

    graph.AddEdge(0, 1, 12);
    graph.AddEdge(1, 2, 14);
    graph.AddEdge(2, 3, 10);
    graph.AddEdge(3, 4, 20);
    graph.AddEdge(3, 11, 20);
    graph.AddEdge(11, 12, 14);
    graph.AddEdge(0, 6, 12);
    graph.AddEdge(6, 7, 14);
    graph.AddEdge(7, 3, 10);
    graph.print();

    std::cout << "Cost from A to B: " << graph.Dijkstra(0, 12) << std::endl;
    for (long l : graph.DijkstraWithPath(0, 12)) 
        std::cout << graph.getVertices( )[l].getPoint( ) << "->";
    
    std::cout << std::endl << "Adj matrix: \n";

    print_mat(graph.AdjMatrix( ));

    std::cout << std::endl << "Floyd warshall: \n";

    print_mat(graph.FloydWarshall( ));

    return 0;
}

int main2 (int argc, char** argv) {
    Graph < string, float > graph;
    graph.AddVertex("1");
    graph.AddVertex("2");
    graph.AddVertex("3");
    graph.AddVertex("4");
    graph.AddVertex("5");

    graph.AddEdge(1, 0, 3);
    graph.AddEdge(2, 1, 1);
    graph.AddEdge(0, 2, -2);
    graph.AddEdge(1, 3, -3);
    graph.AddEdge(1, 4, -2);
    graph.AddEdge(3, 2, 3);  
    
    print_mat(graph.FloydWarshall( ));
}