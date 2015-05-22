/* 
 * File:   Tour.h
 * Author: btacklind
 *
 * Created on May 21, 2015, 11:11 PM
 */

#ifndef TOUR_H
#define	TOUR_H

#include "DistanceMatrix.h"

using namespace std;

class Tour {
public:
    Tour(int* tr, DistanceMatrix* dMat, int pnts, int l);
    Tour(const Tour& orig);
    virtual ~Tour();
    
    inline int getlength(){return length;};
    void printTour();
private:
    void updateLength();
    
    int points;
    DistanceMatrix distMatrix;
    int* tour;
    int length;
};

#endif	/* TOUR_H */

