/* 
 * File:   DistanceFileHandler.h
 * Author: btacklind
 *
 * Created on May 21, 2015, 7:42 PM
 * 
 * Reads a distance file and creates a Object that contains data from that
 * file
 */

#ifndef DISTANCEFILEHANDLER_H
#define	DISTANCEFILEHANDLER_H
#include "Tour.h"
#include <list>
#include <string>

using namespace std;

class DistanceFileHandler {
public:
    DistanceFileHandler(const char* input);
    DistanceFileHandler(const DistanceFileHandler& orig);
    virtual ~DistanceFileHandler();
    
    Tour NearestNeighbor();
    Tour FarthestInsertion();
    Tour SimpleTour();
private:
    
    double getInnerDistancePntwise(int i, int j, int c);
    double getInnerDistance(int a, int b, int d);
    list<string> parseString(string line);
    bool inTour(int i, int* tr);
    bool inTour(int i, list<int> &tr);
    void printList(list<int> l);

    DistanceMatrix* distMatrix;
    int points;
};

#endif	/* DISTANCEFILEHANDLER_H */

