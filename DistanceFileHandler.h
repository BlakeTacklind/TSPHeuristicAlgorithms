/* 
 * File:   DistanceFileHandler.h
 * Author: btacklind
 *
 * Created on May 21, 2015, 7:42 PM
 */

#ifndef DISTANCEFILEHANDLER_H
#define	DISTANCEFILEHANDLER_H
#include "Tour.h"
#include <list>
#include <string>

using namespace std;

class DistanceFileHandler {
public:
    DistanceFileHandler(char* input);
    DistanceFileHandler(const DistanceFileHandler& orig);
    virtual ~DistanceFileHandler();
    
    Tour NearestNeighbor();
    Tour FarthestInsertion();
private:
    
    double getInnerDistance(int a, int b, int d);
    list<string> parseString(string line);
    bool inTour(int i, int* tr);
    
    DistanceMatrix distMatrix;
    int points;
};

#endif	/* DISTANCEFILEHANDLER_H */
