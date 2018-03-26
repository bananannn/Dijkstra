// Name: Bananannn
// Sources of
// Help:https://docs.google.com/document/d/11gDhryHYfcQMGPQlQXj65jfKAlEG5KKsd57
// Xrtfj-oM/edit?usp=sharing (Alarm Explanation)
// The file Dijkstra.cpp
// Due: February 9th, 2018 at 11:59 PM

#ifndef __PRIM_CPP__
#define __PRIM_CPP__

#include <queue>
#include <vector>

#include "Graph.hpp"
// include more libraries as needed

template <class T>
float prim(Graph<T>& g, T src) {
  // TODO: Implement Prim's algorithm

  Vertex<T> * startv = g.vertices[src];
  startv->distance = 0;
  std::priority_queue<Alarm<T>, std::vector<Alarm<T>>> pq;
  std::set<T> edges = startv->edges;
  startv->visited = true;
  float cost = 0;
  for( auto it = edges.begin(); it != edges.end(); it++ ){
      pq.push(Alarm<T>(src, (*it), 
      g.get_weight(src, (*it)))); 
  }
  while(pq.size()!=0){
      Alarm<T> cur = pq.top();
      Vertex<T> * curr = g.vertices[cur.dest];
      pq.pop();
      if( curr->visited == false ){
          curr->visited = true;
          //update the cost
          //if( curr->id != src ){
              cost = cost+g.get_weight(cur.dest, cur.src);
          //}
          curr->prev = cur.src;
          Vertex<T> * preV = g.vertices[cur.src];
          curr->distance = g.get_weight(cur.dest, cur.src);
          
          std::set<T> vedges = curr->edges;
          for(auto vit = vedges.begin(); vit!=vedges.end(); vit++ ){
              float time = g.get_weight(cur.dest, *vit);
              Alarm<T> newA = Alarm<T>(cur.dest, (*vit), time);
              pq.push(newA);
          }
      }
  }

  return cost;
}
#endif
