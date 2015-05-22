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
using namespace std;

DistanceFileHandler::DistanceFileHandler(char* input) {
  cout << "reading from \"" << input << "\"" << endl;
  
  ifstream file(input);
  
  //In case the file fails to open spits out error and ends program
  if (!file.is_open()){
    cout << "failed to open file" << endl;
    exit(-1);
  }
  
  string line;
  getline(file, line);
  
  points = atoi(line.c_str());
  
  if (points < 3)
  {
    cout << "failed to get a viable number of cities" << endl;
    exit(-1);
  }
  
  //get a array matrix upper triangle
  distMatrix = DistanceMatrix(points);
  
  while (getline(file, line)){
    cout << line <<endl;
    list<string> toks = parseString(line);
    cout << "yeah" <<endl;
    if (toks.size() != 3){
      cout << "Line got a bad number of tokens!" << endl;
      exit(-1);
    }
    cout << "ya" <<endl;
    int i = atoi(toks.front().c_str());
    cout << i <<endl;
    toks.pop_front();
    int j = atoi(toks.front().c_str());
    cout << j <<endl;
    toks.pop_front();
    cout << "ok" <<endl;
    //cout << i << "," << j << "," << toks.front().c_str() << endl;
    distMatrix.set(i,j,atoi(toks.front().c_str()));
    distMatrix.printMatrix();
    cout << "ummm" <<endl;
    //cout << "i:" << i << " j:" << j << " d:" << getPosDMat(i,j) << endl;
  }
  cout << "umm" <<endl;
  file.close();
}


DistanceFileHandler::DistanceFileHandler(const DistanceFileHandler& orig) {
}

/*
 * parses string into space delimited sections.
 */
list<string> DistanceFileHandler::parseString(string line) {
  
  //parses line into <space> delimited pieces
  cout << "first" <<endl;
  int pos;
  string token;
  list<string> tokens;
  while ((pos = line.find(" ")) != -1) {
    cout << "pos " << pos << " l " << line.length() << endl;
    token = (string)line.substr(0, pos);
    cout << "token " << token << endl;
    if (token != "") tokens.push_back(token);
    cout << "# "<< tokens.size() << " pos " << pos << " l " << line.length() <<endl;
    line.erase(0, pos + 1);
    cout << "e: " << line << endl;
  }
  if (line != "") tokens.push_back(line);
  cout << "3 " << line << endl;
  
  return tokens;
}

DistanceFileHandler::~DistanceFileHandler() {
}

Tour DistanceFileHandler::NearestNeighbor() {
  int* tr = (int*) malloc(sizeof(int) * points);
  if (tr == NULL){
    cout << "failed to malloc for nearest neighbor" << endl;
    exit(-1);
  }
  
  
  //find initial smallest
  int si, sj, l=INT_MAX;
  for (int i=1; i < points; i++){
    for (int j=i+1; j <=points; j++){
      int t;
      if((t=distMatrix.get(i,j)) < l){
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
  
  for(int i = 1; i < points-1; i++){
    si=tr[i];
    sj=0;
    l=INT_MAX;
    
    for(int j = 1; j <= points; j++){
      int t;
      if(si!=j && !inTour(j, tr) && l>(t=distMatrix.get(si, j))){
        l=t;
        sj=j;
      }
    }
    
    length += l;
    tr[i+1] = sj;
  }
  
  length += distMatrix.get(tr[0], tr[points-1]);
  return Tour(tr, distMatrix, points,-1);
}

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
 * d is the length of the line segment to check distance to
 * a and b are the distances to the third point
 * 
 * Use Heron's Formula to get area of triangle and derive distance to line
 * with that area formula.
 */
double getInnerDistance(int a, int b, int d){
  double p = (a + b + d) / 2;
  return 2 * sqrt(p*(p-a)*(p-b)*(p-d)) / d;
}