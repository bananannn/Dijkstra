// Name: Bananannn
// Sources of Help:
// https://docs.google.com/presentation/d/1xbOowaM2nJqfefgimFnZisJGjInLjK
// IGWdqhjpwoxF0/edit#slide=id.g1088ef3f8b_0_0 (Review Discussion)
// The file TestGraph.cpp
// https://piazza.com/class/jb8pdrlepuy2ga?cid=618
// https://piazza.com/class/jb8pdrlepuy2ga?cid=609 // Bellman-Ford
// https://piazza.com/class/jb8pdrlepuy2ga?cid=623 // negative cycles
// Due: February 9th, 2018 at 11:59 PM

#ifndef __BITVEST_CPP__
#define __BITVEST_CPP__

#include <list>
#include <string>
#include <set>
#include <map>
#include <stdio.h>
#include <math.h>

#include "Graph.hpp"
#include "Bitvest.hpp"
// include more libraries as needed

bool bitvest(std::list<Exchange> exchanges, std::map<std::string, float> fees) {
  //TODO: Implement an algorithm to determine if a profitable trade is possible
  // Algorithm based on buildgraph function in testGraph.cpp
  Graph<std::string> myg;
  for( auto it = exchanges.begin(); it!=exchanges.end() ; ++it){
      if(myg.vertices.count((*it).in) == 0 ){
          myg.vertices[(*it).in] = new Vertex<std::string>((*it).in);
      }
      if(myg.vertices.count((*it).out) == 0 ){
          myg.vertices[(*it).out] = new Vertex<std::string>((*it).out);
      }
      myg.vertices[(*it).in]->edges.insert((*it).out);
      myg.set_weight((*it).in,(*it).out,-1*log((*it).rate*(1-fees[(*it).in])
      *(1-fees[(*it).out])));
  }
//  std::cout<<"# of edges "<< exchanges.size()  <<std::endl;
//  std::cout<<"# of vertices "<< myg.vertices.size() <<std::endl;

  // aldorithm inspired by the  bellman-ford provided in the link 
  // given above
  std::string src = (*exchanges.begin()).in;
  myg.vertices[src]->distance = 0;
  Vertex<std::string> * source = myg.vertices[src];
  for(int k = 1; k<myg.vertices.size(); k++ ){
      for(auto eit = exchanges.begin(); eit!=exchanges.end(); ++eit){
          Vertex<std::string> * u = myg.vertices[(*eit).in];
          Vertex<std::string> * v = myg.vertices[(*eit).out];

          if(v->distance > u->distance+myg.get_weight((*eit).in, (*eit).out)){
              v->distance = u->distance+myg.get_weight((*eit).in, (*eit).out);
              v->prev = (*eit).in;
          }
      }
  }

  
  // find whether it has negative cycles
  for(auto vit = exchanges.begin(); vit!=exchanges.end(); ++vit){
      Vertex<std::string> * u = myg.vertices[(*vit).in];
      Vertex<std::string> * v = myg.vertices[(*vit).out];
      //float currweight = myg.get_weight(u->id, v->id);
      //myg.set_weight(u->id, v->id, -1*currweight);
      //if( v->distance > u->distance + myg.get_weight((*vit).in, (*vit).out)){
      if( 0 > u->distance+myg.get_weight((*vit).in, (*vit).out)){
          return true;
      }
  }
  return false;
}
#endif
