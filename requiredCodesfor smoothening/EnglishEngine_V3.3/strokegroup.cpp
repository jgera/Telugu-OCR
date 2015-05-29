#include "strokegroup.h"
//#include "common.h"
//#include "stroke.h"
//#include <exception>
//#include <iostream>
#include "mainform.h"
//#include "mainform.cpp"
#include "stdafx.h"
//using namespace std;

StrokeGroup::StrokeGroup()
{
    try
    {
        label="none";
        nstrokes = 0;
        origin[0]=0;
        origin[1]=0;
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in constructor: ";
        str.append(e.what());
        logwrite(str);
    }
}

StrokeGroup::StrokeGroup(double argorigin[])
{
    try
	{
  label="none";
  nstrokes = 0;
  origin[0]=argorigin[0];
  origin[1]=argorigin[1];
  Stroke emptystrk;
  emptystrk.RandStrk(0);
  strklist.push_back(emptystrk);
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in constructor1: ";
        str.append(e.what());
        logwrite(str);
    }
}
StrokeGroup::~StrokeGroup()
{

}


void StrokeGroup::AddStrk2SG(Stroke strk)
{
    try
    {
        if(nstrokes==0)
        {
            strklist.clear();
        }
        strklist.push_back(strk);
        nstrokes++;
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in constructor: ";
        str.append(e.what());
        logwrite(str);
    }
}

void StrokeGroup::AppendStrk2Char(Stroke strk1,int mode)
{
    try
	{
  if(nstrokes==0)
  {
        strklist.clear();
        strk1.ChangeStrkCoords(origin,mode);
        strklist.push_back(strk1);
        nstrokes++;
        return;
  }
  else
  {
        strk1.ChangeStrkCoords(origin,mode);
        AddStrk2SG(strk1);
  }
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in AppendStrk2Char: ";
        str.append(e.what());
        logwrite(str);
    }
}

int StrokeGroup::IsXOverlapSG2Strk(Stroke strk,double& xgap)
{
  int nstrk=nstrokes,i,y=0,yi;
  double tmpxgap;
  try
  {
  if(nstrokes==0)
  {
    xgap=0;
    y=1;
    return y;
  }

  y = 0;
  xgap = 10000;
  for(i = 0; i < nstrk; i++)
  {
    yi=strklist[i].IsXOverlapStrk2Strk(strk,tmpxgap);
    if(xgap > tmpxgap)
      xgap = tmpxgap;
    if(yi)
      y = 1;
  }
  }
  catch(exception& e)
  {
      string str="StrokeGroup:Exception in IsXOverlapSG2Strk: ";
      str.append(e.what());
     logwrite(str);
  }
  return y;
}

double StrokeGroup::LocaliseSGCoordSysInChar()
{
  Matrix<double> sgbnds;
  double offset[2];
  try{
  sgbnds = SGBounds();
  //to shift all strokes in SG such that the left bound is at origin.
  origin[0]= sgbnds(1);
  //offset[0]=origin[0]*(-1);
  offset[0]=origin[0]=0;

  origin[1]=offset[1]=0;
  MoveSG(offset);
  }
  catch(exception& e)
  {
      string str="StrokeGroup:Exception in LocaliseSGCoordSysInChar: ";
      str.append(e.what());
    logwrite(str);
  }
  return(origin[0]);
}

Matrix<double> StrokeGroup::SGBounds()
{
  Matrix<double> sgbnds(1,4),strkbnds(1,4),tmpbnds;
  double xl,xr,yb,yt;
  int i,bndsmode;
  try{
  if(nstrokes==0){
    sgbnds.MakeNull();
    return sgbnds;
  }
  bndsmode = 1; //y-coord increases bottom up
  for(i=0;i<nstrokes;i++){
    tmpbnds = strklist[i].StrkBounds(bndsmode);
   if(i==0)
     strkbnds=tmpbnds;
   strkbnds.Append(tmpbnds,1);
  }

  xl = strkbnds.Min(1,2);
  xr = strkbnds.Max(2,2);
  yb = strkbnds.Min(3,2);
  yt = strkbnds.Max(4,2);

 sgbnds.Set(1,1,xl);
 sgbnds.Set(1,2,xr);
 sgbnds.Set(1,3,yb);
 sgbnds.Set(1,4,yt);
  }
  catch(exception& e)
  {
      string str="StrokeGroup:Exception in SGBounds: ";
      str.append(e.what());
     logwrite(str);
  }
  return(sgbnds);
}

void StrokeGroup::MoveSG(double vec[])
{
    try{
  for(int i=0;i<nstrokes;i++)
   strklist[i].MoveStrk(vec);
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in MoveSG: ";
        str.append(e.what());
    logwrite(str);
    }
}

void StrokeGroup::InterpStrokesForSVM()
{
    try{
        for(int i=0;i<nstrokes;i++)
        {
                strklist[i].InterpStrkForSVM();
        }
    }
    catch(exception& e)
    {
        string str="StrokeGroup:Exception in InterpStrokesForSVM: ";
        str.append(e.what());
     logwrite(str);
    }
}
vector<int> StrokeGroup::Preclassification( ofstream& logFile)
{
if(nstrokes >= 1)
	{
  MainForm *sgobj = new MainForm();
  
  sgarraylist = sgobj->Annotate(strklist,logFile);
  }
return sgarraylist;

}
StrokeGroup::StrokeGroup(double argorigin[],int argnstrokes,Stroke argstrklist[])
 
{
  label="none";
  origin[0]=argorigin[0];
  origin[1]=argorigin[1];
  nstrokes=argnstrokes;
  int maxVal=2;
  /*
  if (nstrokes != 0)
  {
  	cout << "StrokeGroup() 2 : nstrokes = " << nstrokes << endl;
  }
  */
  for(int i=0;i<nstrokes;i++)
  {
    strklist.push_back(argstrklist[i]);
  }
}