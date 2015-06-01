/**																
\file Engine.cpp
\brief DevRecognitionEngine.cpp contains definations of the  interfaces functions of the Application for Online Handwritten Character Recognition (OHWR) System
\date(Date of Creation)
\date  (Last modified)
\author xxxxx
\version 1.0.0.0
<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "strokegroup.h"
#include "Character.h"
#include "word.h"
#include "datastructures.h"
#include "File_Data_Struct.h"
#include "stdafx.h"
#include <vector>
#include "mainform.h"//below lines commented
#include <TCHAR.H>
#include "Matrix.h"
#include <stdlib.h>
#include "common.h"
#include "stroke.h"


#ifdef __cplusplus
#define SMALL_BUFFER_SIZE 32
//typedef enum{ TOP_LEFT=1,TOP_RIGHT=2,BTM_LEFT=3,BTM_RIGHT=4}DEVICE_INFO_T;
//SVParams *baseSvm, *botSvm, *topSvm, *mainSvm, *preclassSvm, *numericSvm;
//TernarySearchTree *tstMain, *tstBottom,*tstNumeric;	
int year,month,sgnum=1,proxflag,word1=0,deviceinfo,wordcount = 1,linecount = 1,nstroke=1;
string fname,userid;
ofstream secpts;
double linepos=0.25,xgap=0,newcharorigin[2]={0,0};
double CHAR2CHARGAP = 0,lineorig[2]={0,0},WORD2WORDGAP = 0,LINE2LINEGAP = 0;
int CODERUN=0;
MainForm *objSVM;
StrokeGroup oldstrokes;
double xdiv,ydiv,xmin,xmax,ymin,ymax;
vector<Word> wordlist;
vector <int> word_countvec;
vector <int>  noOfStrokes;
string ResoursePath;

extern "C"
#endif
int fn_InitEngine(const char *const WordlistFilePath,int UserID,DEVICE_INFO_T device)
{
	//time_t startTime;
	//time(&startTime);
	//struct tm *timeInfo1 = localtime (&startTime); 
	//year=timeInfo1->tm_year;
	//month=timeInfo1->tm_mon;
	//year=year+1900;
	//month=month+1;


	//if(year<=2009)
	//{	

	/*string ResoursePath = (string) WordlistFilePath + "Engines\\IITM\\TEL\\";
	BOOL b= SetCurrentDirectory((LPTSTR)ResoursePath.c_str());
	deviceinfo=devic;
	logFile.open("Log\\logfile.txt");
	secpts.open("secpots.txt");
	logFile<<"device info "<<devic<<endl;**/

	/*tstMain = new TernarySearchTree("resource\\rulefiles\\TeluguRules.txt");
	tstNumeric = new TernarySearchTree("resource\\rulefiles\\NumericRules.txt");
	tstBottom = new TernarySearchTree("resource\\rulefiles\\TeluguRulesBottom.txt");**/
	// MainForm mainobj = new MainForm();
	objSVM->loadRules();
	objSVM->loadSVMs();
	/*
	string ResoursePath = (string) WordlistFilePath + "Engines\\IITM\\TEL\\";
	BOOL b= SetCurrentDirectory((LPTSTR)ResoursePath.c_str());
	deviceinfo=devic;
	logFile.open("Log\\logfile.txt");
	secpts.open("secpots.txt");
	logFile<<"device info "<<devic<<endl;

	*/


	//SetCurrentDirectory((LPCTSTR)WordlistFilePath);

	return 1;
	//}
	//else
	//{
	//return -1;

}



int fn_FreeEngine()
{
	objSVM-> ClearRules();
	//logFile.close();
	return 1;

}

void fn_EngineVersionInfo(char** p_charEngineVersionInfo)
{
	char* version="1.0.0.1";
	//strcpy(p_charEngineVersionInfo,"1.0.0.1");
	*p_charEngineVersionInfo=version;
}



//char*  g_strEngineDirectoryPath;
//char*  g_strWordListDirectoryPath;


/*data types included above*/

int fn_RecognizeWord( FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount, ENGINE_TYPE DataType,wchar_t** strOut,int topN,std::ofstream& logFile,std::ofstream& result)
{   
	//logFile << "Engine type-----------" << DataType <<endl; 
	Matrix<double> a(1,2);
	Stroke laststroke(a);
	double origin[]  = {0,0};
	double linespace = 1;
	double xspan     = 0;
	double origin1[]  = {0,0};
	int ma,end,start;
	double xmax=0,ymax=0,xmin=0,ymin=0,y1=0,y2=0,tempx=0,tempy=0;
	double newxmax=0,newymax=0,newxmin=0,newymin=0,sumpositiveslope=0,sumnegativeslope=0,meannegativeslope=0,meanpositiveslope=0;

	vector<double>xpoints;
	vector<double>ypoints;
	vector<double>newxpoints;
	vector<double>newypoints;
	vector<double>baseshapexpoints;
	vector<double>baseshapeypoints,slopeBase,positiveslope,negativeslope;

	Character currchar(origin, linespace, xspan);
	Word currword(origin, linespace, xspan);
	int noOfStrokes = 0;
	int strokcount=0;
	vector<int> font_stream;
	/////////////////////////////////////////////////////////////
	while(strokcount<iStrokeCount)
	{
		ma=0;
		while(pStructStrokeInfo[strokcount].nPointCount>ma) //Number of points in a single stroke
		{
			newxpoints.push_back(pStructStrokeInfo[strokcount].ptrPointInfo[ma].x);
			newypoints.push_back(pStructStrokeInfo[strokcount].ptrPointInfo[ma].y);
			xpoints.push_back(pStructStrokeInfo[strokcount].ptrPointInfo[ma].x);
			ypoints.push_back(pStructStrokeInfo[strokcount].ptrPointInfo[ma].y);
			secpts<<pStructStrokeInfo[strokcount].ptrPointInfo[ma].x<<" "<<pStructStrokeInfo[strokcount].ptrPointInfo[ma].y<<endl;
			ma=ma+1;
		}
		Matrix<double> newstrkpts(newxpoints,newypoints);
		Matrix<double> strkpts(xpoints,ypoints);

		Stroke actstrk(strkpts);
		laststroke   = actstrk;
		CHAR2CHARGAP = 20;
		WORD2WORDGAP = 750;
		lineorig[0] = 0;
		lineorig[1] = 0;
		int mode=1;
		laststroke.ChangeStrkCoords(lineorig, mode);

		proxflag = currchar.IsProximChar2Strk(laststroke,sgnum,xgap);

		//IS ABOVE FUNCTION
		/*newxmax=newstrkpts.Max(1,2);
		newymax=newstrkpts.Max(2,2);
		newxmin=newstrkpts.Min(1,2);
		newymin=newstrkpts.Min(2,2);
		xmax=strkpts.Max(1,2);
		ymax=strkpts.Max(2,2);
		xmin=strkpts.Min(1,2);
		ymin=strkpts.Min(2,2);
		if (xmin>=newxmin && xmin <=newxmax || xmax>=newxmin && xmax <=newxmax)
		{
			// Now overlap is there. we need to check for is it top stroke or bottom stroke.
			if (ymin>=(0.7*(newymax-newymin))){
				// This is the top stroke
				sgnum = 1;//it was modified in IsProximChar2Strk, if not overlapping. swetha 3/7/06.
				currchar.AppendStrk2CharAtSG(laststroke,sgnum);
			}
			else if(ymax<=(newymin+0.15*(newymax-newymin)))
			{
				// this is a bottom stroke
				sgnum = 1;//it was modified in IsProximChar2Strk, if not overlapping. swetha 3/7/06.
				currchar.AppendStrk2CharAtSG(laststroke,sgnum);
			}

		}

		if(ymin>=newymin && ymin <=newymax || ymax>=newymin && ymax <=newymax)
		{
			//assume the points are all smooth
			//Smoothing starts
			int n = strkpts.nrows;
			Matrix<double>pts_x = strkpts.Get(1,1,2);
			Matrix<double>pts_y = strkpts.Get(2,2,2);
			int win = 15;int win2; double sigma = 4;
			win2=(win-1)/2;
			double pi=3.1428;
			vector<double> gau,gau1;
			vector<double> xmod,ymod,xmod1,ymod1;
			double sum=0;
			for (int i=1;i<=win;i++)
			{
				gau.push_back(1/(sqrt(2*pi)*sigma)*exp(((-1*(double)(i-win2)*(double)(i-win2))/(2*sigma*sigma))));
				sum=sum+gau[i-1];
			}

			for (int i=0;i<win;i++)
				gau1.push_back(gau[i]/sum);


			for (int i=0;i<(n+2*win2+win);i++)
			{
				if (i<win2)
				{
					xmod.push_back(pts_x(1,1));
					ymod.push_back(pts_y(1,1));
					xmod1.push_back(xmod[i]);
					ymod1.push_back(ymod[i]);

				}
				if (i>=win2 && i<(n+win2))
				{
					xmod.push_back(pts_x(i+1-win2,1));
					ymod.push_back(pts_y(i+1-win2,1));
					xmod1.push_back(xmod[i]);
					ymod1.push_back(ymod[i]);

				}
				if (i>=(n+win2) && i<(n+2*win2))
				{
					xmod.push_back(pts_x(n,1));
					ymod.push_back(pts_y(n,1));
					xmod1.push_back(xmod[i]);
					ymod1.push_back(ymod[i]);

				}

				if (i>=(n+2*win2) && i<(n+2*win2+win))
				{
					xmod1.push_back(0);
					ymod1.push_back(0);
				}

			}
			for (int i = gau1.size();i<(xmod.size()+win);i++)
				gau1.push_back(0);




			vector<double> pts_xn,pts_yn;
			for (int k=0;k<(xmod.size()+win-1);k++)
			{
				int dummy=0,dummy1=xmod.size();
				double sumx=0,sumy=0;

				for(int j=0;j<dummy1;j++)
				{// cout<<k-j<<endl;
					if((k-j+1)>0)
					{
						sumx+=xmod1[j]*gau1[(k-j)];
						sumy+=ymod1[j]*gau1[(k-j)];
					}
				}
				if (k>=(win-1) && k<(xmod.size()))
				{
					pts_xn.push_back(sumx);
					pts_yn.push_back(sumy);
				}
			}

				Matrix<double>smoothstrk(pts_xn,pts_yn);
				strkpts = smoothstrk;
				//Smoothing ends above
				//strkpts = strkpts.Smoothstrk();
				strkpts.Sort(2,1,2);
				end=(strkpts.Size()).Get(1,1);
				start=int(0.06*end);
				//cropping the required shape-positive x bump, with first decreasing and then increasing slope
				strkpts=strkpts.Get(start,end,1);
				tempx=strkpts.Get(1,1);
				tempy=strkpts.Get(1,2);
				for(int j=1;j<end;j++){
					baseshapexpoints.push_back(strkpts.Get(j,1)-tempx);
					baseshapeypoints.push_back(strkpts.Get(j,2)-tempy);
					if(baseshapeypoints[j-1]==0){

						break;
					}
				}
				// checking for starting direction of the curve// first condition for baseaux
				if (baseshapeypoints.size()>0){
					y1=1;


					for (int dummy1=0;dummy1<baseshapexpoints.size()-1;dummy1++){
						slopeBase.push_back((baseshapeypoints[dummy1+1]-baseshapeypoints[dummy1])/(baseshapexpoints[dummy1+1]-baseshapexpoints[dummy1]));
					}
					//checking the first condition for base auxilary i.e. initial shape should be positive X bump
					for (int dummy2=0;dummy2<slopeBase.size();dummy2++){
						if (slopeBase[dummy2]>=0){
							positiveslope.push_back(dummy2);
						}

						if (slopeBase[dummy2]>=0){
							negativeslope.push_back(dummy2);
						}
					}
					// calculating mean of negativeslope and positive slope
					for(int dummy3=0;dummy3<positiveslope.size();dummy3++){
						sumpositiveslope=sumpositiveslope+positiveslope[dummy3];
					}
					for(int dummy4=0;dummy4<positiveslope.size();dummy4++){
						sumpositiveslope=sumpositiveslope+positiveslope[dummy4];
					}
					meanpositiveslope=sumpositiveslope/positiveslope.size();
					meannegativeslope=sumnegativeslope/negativeslope.size();
					if(meanpositiveslope>meannegativeslope){
						y2=1;
					}
					else{
						y2=0;
					}

				}
				if(y1==1 && y2==1){
					//it is baux
					currchar.AppendStrk2CharAtSG(laststroke,sgnum);
				}
				else{
					//next main
					currword.AddChar2Word(currchar);
					Character tmpchar(newcharorigin,linespace,0);
					currchar=tmpchar;
					currchar.AppendStrk2CharAtSG(laststroke, sgnum);
				}
			}*/



			if (proxflag==1)
				{
					currchar.AppendStrk2CharAtSG(laststroke,sgnum);	
				}
			else if (proxflag==0 && xgap > 0 && xgap <= CHAR2CHARGAP)
				{
					sgnum = 1;//it was modified in IsProximChar2Strk, if not overlapping. swetha 3/7/06.
					currchar.AppendStrk2CharAtSG(laststroke,sgnum);	
				}
			else
				{
					//logFile<<"xgap :  "<<xgap<<endl;
					if(xgap > CHAR2CHARGAP)
					{
						
						mode = 1; 
						currword.AddChar2Word(currchar);
						newcharorigin[0]=0;
						newcharorigin[1]=0;
						Character tmpchar(newcharorigin,linespace,0);
						currchar=tmpchar;
						currchar.AppendStrk2CharAtSG(laststroke, sgnum);
					}}


			if(xgap >= WORD2WORDGAP)
			{
				//this is a new word.  save the current character, word, etc. and form a new word.
				//saving old word and making a new one
				mode = 1; 
				//saving old character and making a new char
				currword.AddChar2Word(currchar);
				wordlist.push_back(currword);
				currword.clear();

				newcharorigin[0] = 0;
				newcharorigin[1] = 0;
				Character tmpchar(newcharorigin,linespace,0);
				currchar=tmpchar;
				currchar.AppendStrk2CharAtSG(laststroke, sgnum);
			}  
			else
			{
				cerr << "Spacing between strokes " << xgap << endl;
			}


			strkpts.MakeNull();
			newstrkpts.MakeNull();
			ypoints.clear();//By mari raja.K
			xpoints.clear();
			strokcount++;

		}
		/////////////////////////////////////////////////////////////
		currword.AddChar2Word(currchar);
		wordlist.push_back(currword);
		int numwd=0;
		//for(int ij=0;ij<wordlist.size();ij++){	
		//font_stream = wordlist[ij].SVMRecognizeWord(logFile,dataType);

		font_stream = currword.SVMRecognizeWord(logFile);
		//logFile << "Fontstream size" << font_stream.size()<<endl;
		for (int i1 = 0; i1 < font_stream.size(); i1++)
		{
			if (font_stream[i1]!=32)
			{
				//temparr.push_back( font_stream[i1]);
				result<<font_stream[i1]<<"  ";
			}
		}
		result<<endl;
		font_stream.clear();
		if (DataType == 2)
		{
			//for(numwd=0;numwd<wordlist.size();numwd++){	
			/*vector <int> temparr;
			for (int i1 = 0; i1 < font_stream.size(); i1++)
			{
			temparr.push_back( font_stream[i1]);
			}*/

			TCHAR myname[256];
			int i,k=0,j=0;
			for (i = 0; i < font_stream.size(); i++)
			{
				TCHAR mychar=(TCHAR)font_stream[i] ;
				myname[i]=mychar;
				//logFile << font_stream[i] ;
				//logFile<<" ";

			}
			myname[i]= '\0';
			wcscpy(strOut[0], myname);
			//wcscpy(strOut[numwd], myname);
			//numwd++;
			//}
			//logFile <<endl; 
			font_stream.clear();
			//temparr.clear();

		} 
		return 1;

	}

	/*int fn_RecognizeTextBlock (const FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount , int topN, TEXT_BLOCK_UNI_INFO* ptrTextBlockUniInfo)
	{
	// use doxygen standard comments in your code

	/**
	*	Mdoule 1 or step 1 E.g. Line and Word Segmetation
	*	used for xxxxxxxxxxxx
	*/
	// delete this code -------------

	/*ptrTextBlockUniInfo->iNoOfLines=2;
	ptrTextBlockUniInfo->ptrLineSegInfo=(LINE_SEG_INFO*)calloc(sizeof(LINE_SEG_INFO),ptrTextBlockUniInfo->iNoOfLines);

	for(int iLineIndex=0;iLineIndex<ptrTextBlockUniInfo->iNoOfLines;iLineIndex++)
	{

	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].iNoOfWords=2;
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo=(WORD_SEG_INFO*)calloc(sizeof(WORD_SEG_INFO),ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].iNoOfWords);

	for(int iWordIndex=0;iWordIndex < ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].iNoOfWords; iWordIndex++)
	{
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].iNoOfStrokes=5;
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].arr_iStrokeIndexes=(int*)calloc(sizeof(int),ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].iNoOfStrokes);
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].strUniOut=(wchar_t**)calloc(sizeof(wchar_t),2);
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].iSuggest=2;
	for(int iWordSuggIndex=0;iWordSuggIndex < ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].iSuggest; iWordSuggIndex++)
	{
	ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].strUniOut[iWordSuggIndex]=	(wchar_t*)calloc(sizeof(wchar_t),50);
	wcscpy(ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].strUniOut[iWordSuggIndex],L"à¤•à¤®à¤²");
	}
	}
	}
	//------------------------

	/**
	*	Mdoule 2 or step 2
	*	used for xxxxxxxxxxxxxxx
	*/
	// delete this line and write code module 2 and so on...


	/** 
	*	copy all suggession string Outputs to strOut
	*/
	// write code 

	/*return 1;//No Of OP suggessions;
	}

	*/

	/*int fn_InitEngine (const char* WorkingDirPath,int UserID, DEVICE_INFO_T Test)
	{	

	int len=strlen(WorkingDirPath);


	/**	allocating and stroing Engine directory path
	*/
	/*g_strEngineDirectoryPath=(char*)calloc(len+50,sizeof(char));
	strcpy(g_strEngineDirectoryPath,WorkingDirPath);
	strcat(g_strEngineDirectoryPath,"\\Engines\\IITM\\TEL\\"); //change according to Engine

	/**	allocating and stroing Word List directory path
	*/
	/*g_strWordListDirectoryPath=(char*)calloc(len+50,sizeof(char));
	strcpy(g_strWordListDirectoryPath,WorkingDirPath);
	strcat(g_strWordListDirectoryPath,"\\Templates\\TEL\\"); //change according to Engine



	/**
	*	Loading resource 1 E.g Read Model Files
	*	used for .........
	*/
	//delete this line and write code for Loading resource 1


	/**
	*	Loading resource 2 E.g. Read Word List
	*	used for .........
	*/
	//delete this line and write code for Loading resource 2


	/*return 0; 
	}
	*/

	/*int  fn_FreeEngine()
	{
	/**	releasing Engine directory path var
	*/
	/*if(g_strEngineDirectoryPath!=NULL)
	{
	free(g_strEngineDirectoryPath);
	g_strEngineDirectoryPath=NULL;
	}
	/**	releasing and stroing Engine directory path var
	*/
	/*if(g_strWordListDirectoryPath!=NULL)
	{
	free(g_strWordListDirectoryPath);
	g_strWordListDirectoryPath=NULL;
	}

	/**
	*	free resource 1
	*/
	//delete this line and write code for free resource 1


	/**
	*	free resource 2
	*/
	//delete this line and write code for free resource 2

	/*return(1); 
	}

	*/

	/*void fn_EngineVersionInfo(const char** EngineVersionInfo )//const char** 
	{
	static char* Version = "MEMBER_LANG_v1.0.0.0";// E.g CDACP_HIN_v2.1.0.0
	*EngineVersionInfo = Version;
	}*/

	//below lines commented
#ifdef __cplusplus
#endif
