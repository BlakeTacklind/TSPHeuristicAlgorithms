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
  
  DistanceFileHandler d = DistanceFileHandler(argv[1]);
  cout << "try me2" <<endl;
  Tour t = d.NearestNeighbor();
  cout << t.getlength() << endl;
  t.printTour();
  
  return 0;
}


