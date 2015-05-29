#ifndef CHARACTER_H
#define CHARACTER_H
#pragma once
//#include <vector>
//#include "matrix.h"
//#include "stroke.h"
//#include "strokegroup.h"
#include "stdafx.h"
class StrokeGroup;

using namespace std;

class Character
{
private:
    string language;
    int codetype;
    int ncodes;
    double origin[2];
    double linespace;
    double top2botratio;
	double xspan;
    int nsgs;
    //vector<Character> charlist;
    vector<StrokeGroup> sglist;
    vector<int> arraylist;

public:
	StrokeGroup *charobj;
    vector<int> chararraylist;
    string label;
    Character();
    Character(double origin[],double  linespace,double xspan);
    Character(double origin[],double  linespace,int nsg,StrokeGroup sg[]);
	~Character();
    int IsProximChar2Strk(Stroke strk,int& sgnum,double& xgap);
    void AppendStrk2CharAtSG(Stroke strk,int sgnum);
    double LocaliseSGCoordSysInChar();
	vector<int> Preclassification(ofstream& log);
	void SVMRecognizeChar(ofstream& log);
};

#endif // CHARACTER_H
