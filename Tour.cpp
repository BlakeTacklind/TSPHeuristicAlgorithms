/* 
 * File:   Tour.cpp
 * Author: btacklind
 * 
 * Created on May 21, 2015, 11:11 PM
 * 
 * Has a tour as well as all distances between points
 */

#include <stdlib.h>

#include "Tour.h"
#include <iostream>
using namespace std;


Tour::Tour(int* tr, DistanceMatrix* dMat, int pnts, int l) {
  points = pnts;
  
  tour = (int*)malloc(sizeof(int)*points);
  
  if(tour == NULL){
    cout << "tour failed to malloc!" << endl;
    exit(-1);
  }
 
  distMatrix = new DistanceMatrix(*dMat);
  
  for (int i = 0; i < pnts; i++)
    tour[i] = tr[i];
  
  if (l>0)
    length = l;
  else
    updateLength();
}

Tour::Tour(const Tour& orig) {
  points=orig.points;
  
  tour = (int*) malloc(sizeof(int)*points);
  
  if(tour == NULL){
    cout << "tour failed to malloc!" << endl;
    exit(-1);
  }
 
  for(int i=0;i<points;i++)
    tour[i]=orig.tour[i];
  
  
  distMatrix = new DistanceMatrix(*(orig.distMatrix));
  
  updateLength();
}

Tour::~Tour() {  
  if (tour != NULL)
    free(tour);

  delete distMatrix;
}

void Tour::updateLength() {
  length = distMatrix->get(tour[0], tour[points-1]);
  
  for (int i = 1; i < points; i++){
    length += distMatrix->get(tour[i-1],tour[i]);
  }
}

void Tour::printTour() {
  for(int i=0; i < points; i++)
    cout << tour[i] << ",";
  
  cout << endl;
}

//Perform an opt-2 swap
void Tour::opt2swap(int i, int j) {
  int k;
  if (j<i){
    k=j;
    j=i;
    i=k;
  }
  
  k=j-i;
  int sub[k];
  for(int a=i+1,b=0;a<=j;a++)
    sub[b++]=tour[a];
  
  for(int a=i+1,b=k;b!=0;a++)
    tour[a]=sub[--b];
}

//check if opt-2 swap would improve tour
bool Tour::opt2check(int i, int j) {
  return (d(i,i+1)+d(j,j+1) > d(i,j)+d(i+1,j+1));
}

//run the opt2 algorithm on this tour
bool Tour::opt2() {
  bool swap = false;
  
  //Run until no more swaps will improve tour
  bool madeSwap;
  do{
    madeSwap=false;
    
    //choose an edge (i,i+1)
    for(int i=0;i<points-2;i++){
      
      //special case of edge (points,0)
      if(d(i,i+1)+d(0,points-1) > d(i,points-1)+d(0,i+1)){
        swap=madeSwap=true;
        opt2swap(i,points-1);
      }
      
      //check if edge (j,j+1)
      for(int j=i+2;j<points-1;j++){
        if(opt2check(i,j)){
          swap=madeSwap=true;
          opt2swap(i,j);
        }
      }
    }
    
  }while(madeSwap);
  
  updateLength();
  
  return swap;
}

//check if an opt-3 swap is worth it
bool Tour::opt3check(int a, int b, int c) {
  return d(a,a+1)+d(b,b+1)+d(c,c+1)>d(a,b+1)+d(b,c+1)+d(c,a+1);
}

/* Swap 3 edges
 * 
 * [0...a][a+1...b][b+1...c][c+1...]
 * becomes
 * [0...a][b+1...c][a+1...b][c+1...]
 */
void Tour::opt3swap(int a, int b, int c) {
  if(c<b){
    int k=c;
    c=b;
    b=k;
  }
  if(b<a){
    int k=a;
    a=b;
    b=k;
  }
  if(c<b){
    int k=c;
    c=b;
    b=k;
  }
  int k1=b-a,k2=c-b;
  int sub1[k1],sub2[k2];
  
  int i=a+1;
  for(int j=0;i<=b;i++,j++)
    sub1[j]=tour[i];
  
  for(int j=0;i<=c;i++,j++)
    sub2[j]=tour[i];
  
  i=a+1;
  for(int j=0;j<k2;j++,i++)
    tour[i]=sub2[j];
  
  for(int j=0;j<k1;j++,i++)
    tour[i]=sub1[j];
}

/*
 * Check for and perform any opt-3 swaps that will improve the tour
 */
bool Tour::opt3() {
  bool madeSwap;
  bool swap;
  
  do{
    madeSwap=false;
    
    for(int i=0;i<points-5;i++){
      for(int j=i+2;j<points-3;j++){
        if(d(i,i+1)+d(j,j+1)+d(0,points-1)>d(i,j+1)+d(0,j)+d(points-1,i+1)){
          swap=madeSwap=true;
          opt3swap(i,j,points-1);
        }
        
        for(int k=j+2;k<points-1;k++){
          //cout<<"check "<<i<<","<<j<<","<<k<<endl;
          if(opt3check(i,j,k)){
            //cout<<"Swap!"<<endl;
            swap=madeSwap=true;
            opt3swap(i,j,k);
          }
        }
      }
    }
  }while(madeSwap);
  
  updateLength();
  
  return swap;
}

/*
 * Run the Lin-Kernighan algorithm on this tour
 * perform opt-3 and opt-2 swaps until no improvements can be done
 */
void Tour::LinKern() {
  bool madeSwap;
  
  do{
    madeSwap=false;
    if(opt3()||opt2()) madeSwap=true;
  }while(madeSwap);
}

//copy tour and run Lin-Kernighan algorithm on the copy
Tour Tour::LinKernighan(Tour t) {
  Tour out = Tour(t);
  out.opt2();
  return out;
}

//copy tour and run opt-2 algorithm on the copy
Tour Tour::Opt2(Tour t) {
  Tour out = Tour(t);
  out.opt2();
  return out;
}
