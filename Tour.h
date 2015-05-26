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
    static Tour Opt2(Tour t);
    static Tour LinKernighan(Tour t);
    
    Tour(int* tr, DistanceMatrix* dMat, int pnts, int l);
    Tour(const Tour& orig);
    virtual ~Tour();
    
    inline int getlength(){return length;};
    void printTour();
    bool opt2();
    void LinKern();
    void opt3swap(int a, int b, int c);
    
private:
    bool opt3();
    void updateLength();
    inline int d(int i, int j){return distMatrix->get(tour[i],tour[j]);};
    void opt2swap(int i, int j);
    bool opt2check(int i, int j);
    bool opt3check(int a, int b, int c);
    
    int points;
    DistanceMatrix* distMatrix;
    int* tour;
    int length;
};

#endif	/* TOUR_H */

