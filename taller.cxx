#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include "Graph.h"

// -------------------------------------------------------------------------
struct Point {
  float X, Y, Z;
  float distanceTo(const Point &b) const {
    float x = X - b.X;
    float y = Y - b.Y;
    float z = Z - b.Z;
    return (std::sqrt((x * x) + (y * y) + (z * z)));
  }
};

// -------------------------------------------------------------------------

typedef Graph< Point, float > TGraph;

// -------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << " input_mesh start end" << std::endl;
    return (1);

  } // fi
  long start_id = std::atoi(argv[2]);
  long end_id = std::atoi(argv[3]);

  TGraph g;

  // Load file in a buffer
  std::ifstream in_mesh_stream(argv[1], std::ifstream::binary);
  if (!in_mesh_stream) {
    std::cerr << "Error reading \"" << argv[1] << "\"" << std::endl;
    return (1);

  } // fi
  in_mesh_stream.seekg(0, in_mesh_stream.end);
  unsigned long in_mesh_file_length = in_mesh_stream.tellg();
  in_mesh_stream.seekg(0, in_mesh_stream.beg);
  char *in_mesh_file_buffer = new char[in_mesh_file_length];
  in_mesh_stream.read(in_mesh_file_buffer, in_mesh_file_length);
  in_mesh_stream.close();
  std::istringstream in_mesh(in_mesh_file_buffer);

  // Read vertices
  long nPoints;
  in_mesh >> nPoints;
  for (long pId = 0; pId < nPoints; pId++) {
    Point pnt;
    in_mesh >> pnt.X >> pnt.Y >> pnt.Z;

    g.AddVertex( pnt );

  } // rof
  

  // Read edges
  long nEdges;
  in_mesh >> nEdges;
  for (long eId = 0; eId < nEdges; eId++) {
    long start, end;
    in_mesh >> start >> end;

    float cost = g.GetVertex( start ).distanceTo( g.GetVertex( end ) );
    g.AddEdge( start, end, cost );
    g.AddEdge( end, start, cost );

  } // rof

  std::vector < Vertex < Point, float > > vertices = g.getVertices();
  delete[] in_mesh_file_buffer;

  if (start_id < 0 || start_id >= vertices.size() || end_id < 0 ||
      end_id >= vertices.size()) {
    std::cerr << "Invalid path endpoints." << std::endl;
    return (1);

  } // fi

  std::cout << "TODO 5   :  ";
  
    //TODO 5:
    std::map< long , long > predecesores = g.Dijkstra( start_id, end_id );

    std::stack <long> stack;
    std::vector <long> route;  
    std::map<long, long>::iterator it = predecesores.find(end_id);
  
    while (true){
      if (it->first == it->second){
        stack.push(it->first);
        break;
      }
      stack.push(it->first);
      it = predecesores.find(it->second);
    }
  
    while (!stack.empty()){
      route.push_back(stack.top());
      stack.pop();
    }
  
    std::cout << "Ruta con Dijkstra : " ;
    for (int i = 0; i < route.size(); i ++){
      std::cout << route[i] << " ";
    }
    std::cout << "\n";

  return (0);
}

// eof -
