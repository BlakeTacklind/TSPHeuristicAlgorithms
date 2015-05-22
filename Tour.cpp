/* 
 * File:   Tour.cpp
 * Author: btacklind
 * 
 * Created on May 21, 2015, 11:11 PM
 */

#include <stdlib.h>

#include "Tour.h"
#include <iostream>
using namespace std;


Tour::Tour(int* tr, DistanceMatrix dMat, int pnts, int l) {
  points = pnts;
  
  distMatrix = DistanceMatrix(points);
  tour = (int*)malloc(sizeof(int)*points);
  
  if(tour == NULL){
    cout << "tour failed to malloc!" << endl;
  }
  
  distMatrix = DistanceMatrix(dMat);
  
  for (int i = 0; i < pnts; i++)
    tour[i] = tr[i];
  
  if (l>0)
    length = l;
  else
    updateLength();
}

Tour::Tour(const Tour& orig) {
}

Tour::~Tour() {  
  if (tour != NULL)
    free(tour);
}

void Tour::updateLength() {
  length = distMatrix.get(tour[0], tour[points-1]);
  
  for (int i = 1; i < points; i++){
    length += distMatrix.get(tour[i-1],tour[i]);
  }
}

void Tour::printTour() {
  for(int i=0; i < points; i++)
    cout << tour[i] << ",";
  
  cout << endl;
}

