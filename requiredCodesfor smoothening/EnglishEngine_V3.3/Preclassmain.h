#ifndef PRECLASSMAIN_H
#define PRECLASSMAIN_H
#include <string>
#include <fstream>
#include "svparams.h"
#include "common.h"
#include "File_Data_Struct.h"
//using namespace std;

class Preclassmain
{

public:
    Preclassmain();
    ~Preclassmain();       
    
	
	int nrow;
	int ncol;
	double **data;
    //SVParams *pre;
    SVParams *english;   

      
    void loadSVMs();	
	void loadRules1();
	int Preclassmain::Recognize_English(FILE_STROKEINFO* pStructStrokeInfo,int iStrokeCount,std::ofstream& logFile);
	Matrix<double> Preclassmain::Smoothstrk(Matrix<double> x1,int n);
	Matrix<double> Preclassmain::Curvelengthbased_Normlzn(Matrix<double> x,Matrix<double> y,int n);
    Matrix<double> interpolateForSVM(Matrix<double> y,int size);
    Matrix<double> interp1(Matrix<double> x,Matrix<double> y,Matrix<double> xi);
    void Preclassmain::showchar(Matrix<double> points);
	double Preclassmain::max_pts(vector<double> points);
	double Preclassmain::min_pts(vector<double> points);
	void Preclassmain::unitsquare_Normalize(Matrix<double> *strokex,Matrix<double> *strokey);
	vector<double> Preclassmain::Intersect(vector<double>x1,vector<double>y1,vector<double>x2,vector<double>y2);
	void ClearRules();
	string Preclassmain::relabel_strk(vector<double>x1,vector<double>y1,vector<double>x2,vector<double>y2);
    



};

#endif // PRECLASSMAIN_H
