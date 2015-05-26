/* 
 * File:   main.cpp
 * Author: btacklind
 *
 * Created on May 21, 2015, 7:24 PM
 * 
 * Give this program a directory to read Distance files from
 */

#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <sys/timeb.h>

#include "DistanceFileHandler.h"

using namespace std;

int clk;
int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

void start(){
  clk=getMilliCount();
}

void split(){
  cout<<","<<getMilliSpan(clk);
  clk=getMilliCount();
  
}

int main(int argc, char** argv) {
  //check if argument was given
  if (argc != 2){
    cout << "Wrong number of arguments!" << endl;
    exit(-1);
  }
  
  //open the directory cointaining data filkes
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (argv[1])) != NULL) {
    
    while ((ent = readdir (dir)) != NULL) {
      
      string s=string(argv[1])+ent->d_name;
      if(s.find(".txt")!=-1){
        //perform analysis and print on each data file
        cout<<ent->d_name;
        DistanceFileHandler* d = new DistanceFileHandler(s.c_str());
        start();
        cout<<","<<d->SimpleTour().getlength();
        split();
        Tour NN = d->NearestNeighbor();
        cout<<","<<NN.getlength();
        split();
        cout<<","<<Tour::Opt2(NN).getlength();
        split();
        cout<<","<<Tour::LinKernighan(NN).getlength();
        split();
        Tour FI = d->FarthestInsertion();
        cout<<","<<FI.getlength();
        split();
        cout<<","<<Tour::Opt2(FI).getlength();
        split();
        cout<<","<<Tour::LinKernighan(FI).getlength();
        split();
        cout<<endl;
      }
    }
    closedir (dir);
  } else {
    perror ("Could not open directory");
    return EXIT_FAILURE;
  }
  
  return 0;
}


