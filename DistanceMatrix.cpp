/* 
 * File:   DistanceMatrix.cpp
 * Author: btacklind
 * 
 * Created on May 22, 2015, 1:00 AM
 */

#include "DistanceMatrix.h"
#include <iostream>
using namespace std;

DistanceMatrix::DistanceMatrix(int p) {
  points=p;
  size=(points*points-points)/2;
  
  matrix = (int*)malloc(sizeof(int)*size);
  
  if (matrix == NULL){
    cout << "failed to malloc matrix" <<endl;
    exit(-1);
  }
}

DistanceMatrix::DistanceMatrix(const DistanceMatrix& orig) {
  points = orig->points;
  size = orig->size;
  
  for (int i =0; i < size; i++){
    matrix[i] = orig->matrix[i];
  }
}

DistanceMatrix::~DistanceMatrix() {
  if (matrix!=NULL)
    free(matrix);
}

/*
 * Gets the placement of the distance of a element in the triangle matrix 
 * compacts the matrix into a linear output. (smaller number always first)
 */
int DistanceMatrix::getPosDMat(int i, int j) {
  if (j < i){
    int k = j;
    j = i;
    i = k;
  }
  
  return points*(i-1) - (i*i+i)/2 + j;
}