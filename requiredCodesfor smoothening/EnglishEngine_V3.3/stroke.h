#ifndef STROKE_H
#define STROKE_H
#pragma once

//#include "matrix.h"
#include "stdafx.h"

class Stroke
{

private:
    int basetype;
    Matrix<double> points;
    int originflag;
    double origin[2];
    double linespace;
    int strkClass;
    int npointsToInterpolateTo;
    int numClass[4];

public:
    Stroke();
	~Stroke();
    string label;
    int attachedTo;//stroke to which it is attched, usually main, sometimes other baseline strokes
    int nonTouching;//bottom stroke totally below, top stroke totally above...
    int enclosed;//inside main stroke - dot, ta_arc...
    bool recognized;//determine dot, hbar, vbar and label accordingly

    Stroke(Matrix<double> a);
    void ChangeStrkCoords(double origin[], int mode);
    Matrix<double> StrkBounds(int mode);
    void RandStrk(int strktype);
    int IsXOverlapStrk2Strk(Stroke s2,double& xgap);
    void MoveStrk(double vec[]);
    Matrix<double> getpoints(Stroke strk);
    Matrix<double> InterpStrkForSVM();
    Matrix<double> interpolateForSVM(Matrix<double> y,int k);
    Matrix<double> interp1(Matrix<double> x,Matrix<double> y,Matrix<double> xi);
	void setMatrix(vector<double>& x, vector<double>& y);


};
#endif // STROKE_H
