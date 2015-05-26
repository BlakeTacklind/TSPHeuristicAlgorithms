/* 
 * File:   main.cpp
 * Author: btacklind
 *
 * Created on May 21, 2015, 7:24 PM
 */

#include <cstdlib>
#include <iostream>
#include <dirent.h>
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
  
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (argv[1])) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      //printf ("%s\n", ent->d_name);
      string s=string(argv[1])+ent->d_name;
      if(s.find(".txt")!=-1){
        cout<<ent->d_name;
        DistanceFileHandler* d = new DistanceFileHandler(s.c_str());
          cout<<","<<d->SimpleTour().getlength();
          Tour NN = d->NearestNeighbor();
          cout<<","<<NN.getlength();
          cout<<","<<Tour::Opt2(NN).getlength();
          cout<<","<<Tour::LinKernighan(NN).getlength();
          Tour FI = d->FarthestInsertion();
          cout<<","<<FI.getlength();
          cout<<","<<Tour::Opt2(FI).getlength();
          cout<<","<<Tour::LinKernighan(FI).getlength();
          cout<<endl;
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
  
/*
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
 */
  return 0;
}


