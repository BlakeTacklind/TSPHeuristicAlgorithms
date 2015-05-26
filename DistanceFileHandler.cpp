/* 
 * File:   DistanceFileHandler.cpp
 * Author: btacklind
 * 
 * Created on May 21, 2015, 7:42 PM
 */

#include "DistanceFileHandler.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

DistanceFileHandler::DistanceFileHandler(const char* input) {
  
  ifstream file(input);
  
  //In case the file fails to open spits out error and ends program
  if (!file.is_open()){
    cout << "failed to open file" << endl;
    exit(-1);
  }
  
  //get the number of cities (first line is a number)
  string line;
  getline(file, line);
  points = atoi(line.c_str());
  if (points < 3)
  {
    cout << "failed to get a viable number of cities" << endl;
    exit(-1);
  }

  //get a array matrix upper triangle
  distMatrix = new DistanceMatrix(points);
  
  while (getline(file, line)){
    //parse the current line
    list<string> toks = parseString(line);
    if (toks.size() != 3){
      cout << "Line got a bad number of tokens!" << endl;
      exit(-1);
    }
   
    //convert conveet string tokens into ints
    int i = atoi(toks.front().c_str());
    toks.pop_front();
    int j = atoi(toks.front().c_str());
    toks.pop_front();

    //add lines data to data matrix
    distMatrix->set(i,j,atoi(toks.front().c_str()));
  }
  file.close();
}


DistanceFileHandler::DistanceFileHandler(const DistanceFileHandler& orig) {
}

/*
 * parses string into space delimited sections.
 */
list<string> DistanceFileHandler::parseString(string line) {
  
  //parses line into <space> delimited pieces
  int pos;
  string token;
  list<string> tokens;
  while ((pos = line.find(" ")) != -1) {
    token = (string)line.substr(0, pos);
    if (token != "") tokens.push_back(token);
    line.erase(0, pos + 1);
  }
  if (line != "") tokens.push_back(line);
  
  return tokens;
}

DistanceFileHandler::~DistanceFileHandler() {
  delete distMatrix;
}

//create a simple tour: 1-2-...-n-1
Tour DistanceFileHandler::SimpleTour() {
  int tr[points];
  for(int i=0;i<points;i++)
    tr[i]=i+1;
  
  return Tour(tr,distMatrix,points,0);
}

Tour DistanceFileHandler::NearestNeighbor() {
  int tr[points] ;
  
  //find initial smallest
  int si, sj, l=INT_MAX;
  for (int i=1; i < points; i++){
    for (int j=i+1; j <=points; j++){
      int t;
      if((t=distMatrix->get(i,j)) < l){
        l=t;
        si=i;
        sj=j;
      }
    }
  }
  tr[0] = si;
  tr[1] = sj;
  
  int length = l;
  
  //initialize tour to 0
  for (int i = 2; i < points; i++)
    tr[i] = 0;
  
  //greedily complete the tour
  for(int i = 1; i < points-1; i++){
    si=tr[i];
    sj=0;
    l=INT_MAX;
    
    //find next smallest element
    for(int j = 1; j <= points; j++){
      int t;
      if(si!=j && !inTour(j, tr) && l>(t=distMatrix->get(si, j))){
        l=t;
        sj=j;
      }
    }
    
    //add element to tour
    length += l;
    tr[i+1] = sj;
  }
  
  //add length of edge last to front
  length+=distMatrix->get(tr[0],tr[points-1]);

  //create tour
  return Tour(tr, distMatrix, points,length);
}

/*
 * check if element i is in array tr
 */
bool DistanceFileHandler::inTour(int i, int* tr) {
  for(int j=0;j<points;j++){
    if (i==tr[j])
      return true;
    if (tr[j]==0)
      return false;
  }
  return false;
}

/*
 * creaste tour using farthest intersection algorithm
 */
Tour DistanceFileHandler::FarthestInsertion() {
  //find points furthest apart
  int l=0;
  int si,sj=0;
  for(int i =1;i<points;i++)
    for(int j=i+1;j<=points;j++){
      int t;
      if (l<(t=distMatrix->get(i,j))){
        si=i;
        sj=j;
        l=t;
      }
    }
  
  list<int> tr;
  
  tr.push_front(si);
  tr.push_back(sj);
  
  //add n-2 more points to tour
  for(int j=2;j<points;j++){
    double s=-1;
    int sc=0;
    list<int>::iterator sk;
    
    /*
     * For all points, check if it is in the tour
     * If not find the nearest edge.
     * Of all the points add the point furthest from its closest edge
     */
    for(int i=1;i<=points;i++){
      double st=0;
      list<int>::iterator skt;
      if(!inTour(i,tr)){
        list<int>::iterator it=tr.begin();
        
        skt=it;
        st=getInnerDistancePntwise(tr.front(),tr.back(),i);
        
	int last=*it;
	++it;
	//printList(tr);
        while(it!=tr.end()){
          double t = getInnerDistancePntwise(*it,last,i);
          if (t<st){
            skt=it;
            st=t;
	    //cout<<"new high ";
          }
  	  //cout<<"("<<last<<","<<*it<<","<<i<<") "<<t<<endl;
	  last=*it;
	  ++it;
        }
        
        if(st>s){
          s=st;
          sk=skt;
          sc=i;
        }
      }
      
      
    }
    
    tr.insert(sk,sc);
  }
  
  //convert tour list into array
  int tour[points];
  int i=0;
  for (list<int>::iterator it = tr.begin() ; it!=tr.end(); ++it, i++)
    tour[i]=*it;
  
  //Create the tour (make the tour calculate its length)
  return Tour(tour, distMatrix, points, 0);
}

//Check if element i is in list tr
bool DistanceFileHandler::inTour(int i, list<int> &tr){
  for(list<int>::iterator it=tr.begin();it!=tr.end();++it)
    if(i==*it) return true;
  
  return false;
}

//print the list (for debug)
void DistanceFileHandler::printList(list<int> l){
  for(list<int>::iterator it=l.begin(); it!=l.end();++it){
    cout<<*it<<",";
  }
  cout << endl;
}

/*
 * d is the length of the line segment to check distance to
 * a and b are the distances to the third point
 * 
 * Use Heron's Formula to get area of triangle and derive distance to line
 * with that area formula.
 */
double DistanceFileHandler::getInnerDistance(int a, int b, int d){
  double p = (a + b + d) / 2.0;
  return 2 * sqrt(p*(p-a)*(p-b)*(p-d)) / d;
}

double DistanceFileHandler::getInnerDistancePntwise(int i, int j, int c) {
  return getInnerDistance(distMatrix->get(i,c),distMatrix->get(j,c),distMatrix->get(i,j));
}
