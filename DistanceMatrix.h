/* 
 * File:   DistanceMatrix.h
 * Author: btacklind
 *
 * Created on May 22, 2015, 1:00 AM
 * 
 * Handles the distance matrix used in defining a symmetric graph
 */

#ifndef DISTANCEMATRIX_H
#define	DISTANCEMATRIX_H

class DistanceMatrix {
public:
    //DistanceMatrix();
    DistanceMatrix(int p);
    DistanceMatrix(const DistanceMatrix& orig);
    virtual ~DistanceMatrix();
    
    void set(int i, int j, int num);
    int get(int i, int j);
    
    inline int getPnts(){return points;};
    
    void printMatrix();
private:
    int points;
    int* matrix;
    int size;
    
    int getPosDMat(int i, int j);
};

#endif	/* DISTANCEMATRIX_H */

