/* 
 * File:   main.cpp
 * Author: btacklind
 *
 * Created on May 21, 2015, 7:24 PM
 */

#include <cstdlib>
#include <iostream>

#include "DistanceFileHandler.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  if (argc != 2){
    cout << "Wrong number of arguments!" << endl;
    exit(-1);
  }
  /*
  DistanceMatrix m = DistanceMatrix(14);
 
  for(int i=1;i<m.getPnts();i++){
    for(int j = i+1; j<=m.getPnts();j++){
      m.set(i,j,1);
    }
  }
  m.printMatrix();
  */
  DistanceFileHandler d = DistanceFileHandler(argv[1]);
  Tour t = d.NearestNeighbor();
  cout << t.getlength() << endl;
  t.printTour();
  
  return 0;
}


