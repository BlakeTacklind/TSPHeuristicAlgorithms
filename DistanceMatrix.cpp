/* 
 * File:   DistanceMatrix.cpp
 * Author: btacklind
 * 
 * Created on May 22, 2015, 1:00 AM
 */

#include "DistanceMatrix.h"
#include <iostream>
using namespace std;

DistanceMatrix::DistanceMatrix() {}

DistanceMatrix::DistanceMatrix(int p) {
  points = p;
  size = (points*points-points)/2;
  
  matrix = (int*)malloc(sizeof(int)*size);
  
  if (matrix == NULL){
    cout << "failed to malloc matrix" <<endl;
    exit(-1);
  }
  
  cout << points << " " << size << endl;
}

DistanceMatrix::DistanceMatrix(const DistanceMatrix& orig) {
  points = orig.points;
  size = orig.size;
  
  for (int i =0; i < size; i++){
    matrix[i] = orig.matrix[i];
  }
}

DistanceMatrix::~DistanceMatrix() {
  if (matrix!=NULL)
    free(matrix);
  
  cout << "FREEDOM" << endl;
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

void DistanceMatrix::set(int i, int j, int num) {
  cout << i << "," << j << "," << num <<endl;
  matrix[getPosDMat(i,j)]=num;
}

int DistanceMatrix::get(int i, int j) {
  if (i==j) return 0;
  return matrix[getPosDMat(i, j)];
}

void DistanceMatrix::printMatrix() {
  for (int i = 1; i< points; i++){
    for (int j = i + 1; j <= points ; j++){
      cout<< get(i,j)<<",";
    }
    cout << endl;
  }
}
