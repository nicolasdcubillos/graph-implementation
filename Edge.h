#ifndef __EDGE__H__
#define __EDGE__H__

template < class C >
class Edge {
  public:
    Edge ( );
    Edge ( long, C );
    long getCost( );
    long getConnect( );
    void setCost ( C );
    void setConnect ( long ); 

  private:
    long connect;
    long cost;
};

#include "Edge.hxx"

#endif