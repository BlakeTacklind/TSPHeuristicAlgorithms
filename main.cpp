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
  
  DistanceFileHandler* d = new DistanceFileHandler(argv[1]);
  Tour t = d->NearestNeighbor();
  cout << t.getlength() << endl;
  t.printTour();
  t.LinKern();
  cout << t.getlength() << endl;
  t.printTour();
  Tour f = d->FarthestInsertion();
  //cout<<"testme"<<endl;
  cout << f.getlength() <<endl;
  f.printTour();
  f.opt2();
  cout << f.getlength() << endl;
  f.printTour();
  
  delete d;
 
  return 0;
}


