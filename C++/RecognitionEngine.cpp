/**																
	\file Engine.cpp
	\brief DevRecognitionEngine.cpp contains definations of the  interfaces functions of the Application for Online Handwritten Character Recognition (OHWR) System
	\date(Date of Creation)
	\date  (Last modified)
  	\author xxxxx
  	\version 1.0.0.0
  	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "File_Data_Struct.h"
#include "example.h"
#include <string>
//#include "strokegroup.h"
//#include "character.h"
//#include "word.h"
//#include "common.h"
#include "stroke.h"
#include "Matrix.h"
*/
#include "stdafx.h"
#include <vector>
#include "mainform.h"//below lines commented
#include <TCHAR.H>

    

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
{
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
	logFile << "Engine type-----------" << DataType <<endl; 
				Matrix<double> a(1,2);
				Stroke laststroke(a);
				double origin[]  = {0,0};
				double linespace = 1;
				double xspan     = 0;
				double origin1[]  = {0,0};
				int ma;
			    int xmax=0,ymax=0,xmin=0,ymin=0;
				int newxmax=0,newymax=0,newxmin=0,newymin=0;
				vector<double>xpoints;
				vector<double>ypoints;
			
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
								logFile<<"xgap :  "<<xgap<<endl;
								if(xgap > CHAR2CHARGAP)
								{
									
									mode = 1; 
									currword.AddChar2Word(currchar);
									newcharorigin[0]=0;
									newcharorigin[1]=0;
									Character tmpchar(newcharorigin,linespace,0);
									currchar=tmpchar;
									currchar.AppendStrk2CharAtSG(laststroke, sgnum);
								}


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
				logFile << "Fontstream size" << font_stream.size()<<endl;
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
				logFile <<endl; 
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
				wcscpy(ptrTextBlockUniInfo->ptrLineSegInfo[iLineIndex].ptrWordSegInfo[iWordIndex].strUniOut[iWordSuggIndex],L"कमल");
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
}
#endif
