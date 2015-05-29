#ifndef MAINFORM_H
#define MAINFORM_H

#pragma once 
//#pragma warning
#include "stdafx.h"
/*
#include <vector>
#include <iostream>
#include "svparams.h"
#include "Matrix.h"
#include "strokegroup.h"
#include "word.h"
#include "selection.h"
#include "character.h"

*/

#include "selection.h"
#include "svparams.h"
#include <vector>

using namespace std;




class MainForm
{
 public:
    
    vector<string> strokeLabel;
/*SVParams *mainrules;
    SVParams *pre;
    SVParams *mainstroke;
    SVParams *mainvowel;
    SVParams *maincon;
    SVParams *base;
    SVParams *bottom;
    SVParams *top;*/

//    vector<string> mainstrokelabel;
    //vector<string> char1;
    //vector<string> stlabel;
  //  vector<string> rules;
    //vector<string> bottomrules;
    //vector<int> isciistream;
    int noOfStrokes;
	void OnOK();
	void loadSVMs();

     // int IsStrkInWritableArea(Stroke strk);
    //int IsRectInRect(Matrix<double>& mat1,Matrix<double>& mat2);
    //void ReInit();
    void loadRules();
	void ClearRules();
	//void LButtonUP(Stroke &strk)

    //Functions for recognition
     vector<int> Annotate(vector<Stroke> strklist); //modified 20/12/12
	//void Annotate(vector<Character> strklist);modified 20/12/12
protected:
		//void showoptions(vector<int> test);
        void getVms();
        void loadConfusionRulesFile();
	    void SaveFile();

 private:
		
		//StrokeGroup oldstrokes;
		//Character currchar;
		Matrix<double> wwbnds;
		Matrix<double> wabnds;
		double linepos;
		string language;
		selection *slt;
		//vector<vector <QPoint>> m_points;
//getCmImage(int charcode);
/*protected slots:
		//virtual void languageChange();
		void SaveFile();
		//QString getCmImage(int charcode);**/

};
#endif // MAINFORM_H
