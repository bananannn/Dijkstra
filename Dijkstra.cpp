// Name: Bananannn
// Sources of Help: https://docs.google.com/document/d/1zjgCRHbtzaTpb9gs3XTt
// 50tFW5xXEh_X1_jfdN754ao/edit  // FAQ
// https://piazza-resources.s3.amazonaws.com/jb8pdrlepuy2ga/jd6kqd0nbkv1g5/u
// csdcse101mtsolutions.pdf?AWSAccessKeyId=AKIAIEDNRLJ4AZKBW6HA&Expires=
// 1518326039&Signature=WsKkVJo1GZg2lt7f41HeLll3d5c%3D
// (The midterm solution)
// https://docs.google.com/document/d/11gDhryHYfcQMGPQlQXj65jfKAlEG5KKsd57Xrt
// fj-oM/edit (The Alarm Explanation)
// Due: February 9th, 2018 at 11:59 PM

#ifndef __DIJKSTRA_CPP__
#define __DIJKSTRA_CPP__

#include "Graph.hpp"
// include more libraries as needed
#include <queue>
#include <vector>

template <class T>
float dijkstra(Graph<T>&g, T src) {
  // TODO: Implement Dijkstra's Algorithm
  // the algorithm inspired by the dijksrtra algorithm provided in the 
  // midterm solution
  // According to the Alarm explanation
  Vertex<T> * startv = g.vertices[src];
  startv->distance = 0;
  startv->visited = true;
  std::priority_queue<Alarm<T>, std::vector<Alarm<T>>> pq;
  std::set<T> edges = startv->edges;
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
          curr->distance = preV->distance+g.get_weight(cur.dest, cur.src);
          
          std::set<T> vedges = curr->edges;
          for(auto vit = vedges.begin(); vit!=vedges.end(); vit++ ){
              float time = g.vertices[cur.dest]->distance+
              g.get_weight(cur.dest, *vit);
              Alarm<T> newA = Alarm<T>(cur.dest, (*vit), time);
              pq.push(newA);
          }
      }
  }

  return cost;
}

#endif
