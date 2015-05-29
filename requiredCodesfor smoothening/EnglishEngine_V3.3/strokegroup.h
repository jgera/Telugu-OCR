#ifndef STROKEGROUP_H
#define STROKEGROUP_H
#pragma once
//#include <vector>
//#include "matrix.h"
//#include "stroke.h"
#include "mainform.h"
#include "stdafx.h"

using namespace std;

class StrokeGroup
{
private:
    string label;
    int nstrokes;
    double origin[2];

public:
	vector<int> sgarraylist;
    StrokeGroup();
    StrokeGroup(double origin[]);
	StrokeGroup(double origin[],int n,Stroke argstrklist[]);
	~StrokeGroup();
    void AddStrk2SG(Stroke strk);
    vector<Stroke> strklist;
    void AppendStrk2Char(Stroke strk,int mode);
    int IsXOverlapSG2Strk(Stroke strk,double& xgap);
    double LocaliseSGCoordSysInChar();
    Matrix<double> SGBounds();
    void MoveSG(double vec[]);
    void InterpStrokesForSVM();
	//void Preclassification(int maxVal,ofstream& logFile);
	vector<int> Preclassification(ofstream& logFile);
	//MainForm *sgobj;
	//Annotate(vector<Stroke> strklist);
	void SVMRecognizeSG(ofstream& log);
	
};

#endif // STROKEGROUP_H
