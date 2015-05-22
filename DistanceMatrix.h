/* 
 * File:   DistanceMatrix.h
 * Author: btacklind
 *
 * Created on May 22, 2015, 1:00 AM
 */

#ifndef DISTANCEMATRIX_H
#define	DISTANCEMATRIX_H

class DistanceMatrix {
public:
    DistanceMatrix(int p);
    DistanceMatrix(const DistanceMatrix& orig);
    virtual ~DistanceMatrix();
    
    inline void set(int i, int j, int num){matrix[getPosDMat(i,j)]=num;};
    inline int get(int i, int j){return matrix[getPosDMat(i,j)];};
private:
    int points;
    int* matrix;
    int size;
    
    int getPosDMat(int i, int j);
};

#endif	/* DISTANCEMATRIX_H */

