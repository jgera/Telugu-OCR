#include "Preclassmain.h"
#include <string>
#include <exception>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <math.h>
#include "svparams.h"
#include "common.h"
#include "Matrix.h"
#include <iostream>
#include <TCHAR.H>
#include <wchar.h>
#include "File_Data_Struct.h"
#include <sstream>

vector<string> character;
vector<string>character_rule;
vector <int> isciistream1;
string strklist;
Preclassmain::Preclassmain(){
//loadSVMs();

}
Preclassmain::~Preclassmain(){}
void Preclassmain::loadSVMs(){

    string filename="",strokename="";
    int i=0;
     try{
        english=new SVParams("resource/SVParamsenglish.txt");
        filename= english->strokeNamesFilename;
        ifstream  englishfile(filename.c_str());
        i = 0;
        while(!englishfile.eof())
        {
                 englishfile >> strokename;
                 english->strokeNameArray.push_back(strokename);
                i++;
        }
        englishfile.close();
		}
        catch(exception& e)
        {
            string str="MainForm:Exception in loadSVMs: ";
            str.append(e.what());
            logwrite(str);
        }

}
void Preclassmain::loadRules1()
{
    try
    {
		string filename=  "resource/rulefiles/English_ascii.txt";
	    const char *file=filename.c_str();
	
		ifstream rulefile(file);
        string line="";
        while(!rulefile.eof())
        {
            getline(rulefile,line);
			//cout << line <<endl;
			character.push_back(line);
        }
        rulefile.close();
	    string filename_rule=  "resource/Rulelist.txt";
	    const char *file1=filename_rule.c_str();
	
		ifstream rulefile_english(file1);
        string line1="";
        while(!rulefile_english.eof())
        {
            getline(rulefile_english,line1);
			character_rule.push_back(line1);
        }
        rulefile_english.close();
    }//end of try
    catch(exception &e)
    {
        string str="MainForm: Exception in loadRules: ";
        str.append(e.what());
        logwrite(str);
    }//end of catch
}//end of function



int Preclassmain::Recognize_English(FILE_STROKEINFO* pStructStrokeInfo,int iStrokeCount,std::ofstream& logFile)
{
	vector<double>xpoints1;
	vector<double>ypoints1;
	vector<double>xpoints;
	vector<double>ypoints;
	vector<double>xpoints2;
	vector<double>ypoints2;
	double char_ht,leftmostpt,bottommostpt;
	
    for (int k  = 0; k<pStructStrokeInfo->nstroke;k++)
    {
		for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpoints.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypoints.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);
			}
	}
   char_ht= max_pts(ypoints)-min_pts(ypoints);
   leftmostpt=min_pts(xpoints);
   bottommostpt=min_pts(ypoints);
  
   for (int k  = 0; k<pStructStrokeInfo->nstroke;k++)
   {
	   vector<double>newx;
	   vector<double>newy;
	   xpoints1.clear();
	   ypoints1.clear();
	   newx.clear();
	   newy.clear();
	   for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
	   {
			xpoints1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
			ypoints1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
	   }//end of for
	   xpoints2.clear();
	   ypoints2.clear();	
	   Matrix<double>K(xpoints1,ypoints1);
	   double minx = min_pts(xpoints1);
	   double miny = min_pts(ypoints1);
	   vector<double>xx,yy;
	   double diffx = 0.0,diffy = 0.0,threshold = 0.0,minxp=0.0,minyp=0.0;
	   for(int i = 0;i<xpoints1.size();i++)
	   {
		   diffx = xpoints1[i] - minx;
		   xx.push_back(diffx);
		   diffy = ypoints1[i] - miny;
		   yy.push_back(diffy);

	   }
	   int flag;
	   minxp = xx[0] - xx[xx.size()-1];
	   minyp = yy[0] - yy[yy.size()-1] ;
	   threshold = (minxp*minxp)+(minyp*minyp);
	   int count = 0,count1=0,count2=0,count3 = 0;
	   double slope = 0.0;
	   if(max_pts(yy)<=0.08 && threshold<0.0022)
	   {
		   cout<<"dot"<<endl;flag=0;
		   strklist += "dot ";
	   }
	   else
	   {
		    count=0;count1=0;count2=0;
            double tmpx = xpoints1[0];
			double tmpy = ypoints1[0];
			double dummy_s = 0.0;
			slope=0.0;
			int npts=xpoints1.size()/10; int k;
	
			for (int i = 0; i<xpoints1.size();i++)
			{		   
				if(xpoints1[i] > (tmpx-0.05)  && (xpoints1[i] < (tmpx+0.05)))
					count++;
				if(ypoints1[i] > (tmpy-0.05)  && (ypoints1[i] < (tmpy+0.05)))
		  			count1++;
		  
				if (xpoints1.size()<=20)
					k=xpoints1.size()/2;
				else 
					k=9;
				if (i==k-1)
					slope = (ypoints1[i]- ypoints1[0])/(xpoints1[i]-xpoints1[0]);
			}
			count3=0;
			for (int i = 0; i<xpoints1.size();i++)
				{
          
				 if (count!=xpoints1.size())
					{
						if (i>=(k-1) && (i)%(k-1)==0)
		  
							{
							 dummy_s=(ypoints1[i]- ypoints1[0])/(xpoints1[i]-xpoints1[0]);
								if (dummy_s >= (slope - 2) && dummy_s < (slope + 2))
								{
									count2++;
								}
							count3++;
							}
					}
				}
	   
     
	   if(count==xpoints1.size() || count1==ypoints1.size() || (count2)==count3 )
	   {
		   flag=1;
	   }   
	   else
	   {	
		  flag=2;
	   }   
    

      if (flag==1)
	  {
		int n2 = 32,dummy=0;
		Matrix<double>R(xpoints1,ypoints1);
		for (int i=1;i<ypoints1.size();i++)
		{
             if (ypoints1[i]==ypoints1[0])
				 dummy++;
		}
		for (int i=0;i<xpoints1.size();i++)
	   {
		   if (dummy!=(ypoints1.size()-1))
		   {
		    xpoints2.push_back((xpoints1[i] - min_pts(xpoints1))/(max_pts(ypoints1)-min_pts(ypoints1)));
            ypoints2.push_back((ypoints1[i] - min_pts(ypoints1))/(max_pts(ypoints1)-min_pts(ypoints1)));
		   }
	   }
		Matrix<double> strght_x1 = interpolateForSVM(R.Get(1,1,2),n2);
		Matrix<double> strght_y1 = interpolateForSVM(R.Get(2,2,2),n2);  
		double strk_width = strght_x1.Max()- strght_x1.Min();
		double stkht = strght_y1.Max()- strght_y1.Min();
		double aspectratio = strk_width/stkht;
		
		int flag_1 = 0;
		if((aspectratio >1))
		{
			strklist += "hbar ";
			flag_1 = 1;
		}
		else if (aspectratio < 0.08)
		{
			strklist += "vbar ";
			flag_1 = 1;
		}
            
		else if(strght_x1(1,1)>= strght_x1(strght_x1.nrows,1) && (flag_1==0))
		{
			strklist += "slash ";
			
		}
		else if(strght_x1(1,1)< strght_x1(strght_x1.nrows,1) && (flag_1==0))
		{
			 strklist += "back_slash ";
			 
		}
		else
		{
			strklist += "comma ";
		}
	  }
	  if (flag==2)
	   {
		   for (int i=0;i<xpoints1.size();i++)
	   {
		   
		   xpoints2.push_back((xpoints1[i] - min_pts(xpoints1))/(max_pts(ypoints1)-min_pts(ypoints1)));
           ypoints2.push_back((ypoints1[i] - min_pts(ypoints1))/(max_pts(ypoints1)-min_pts(ypoints1)));
			
	   }
			int n = 200;// no of interpolation points
			Matrix<double> B(xpoints2,ypoints2);
			//B.Display();
			Matrix<double> x1 = interpolateForSVM(B.Get(1,1,2),n);
			Matrix<double> y1 = interpolateForSVM(B.Get(2,2,2),n);
			Matrix<double>curve_norm_pts = Curvelengthbased_Normlzn(x1,y1,x1.nrows);
			Matrix<double> smooth_strk = Smoothstrk(curve_norm_pts,curve_norm_pts.nrows);
			int n1 = 32;
			Matrix<double> interp_x1 = interpolateForSVM(smooth_strk.Get(1,1,2),n1);
			Matrix<double> interp_y1 = interpolateForSVM(smooth_strk.Get(2,2,2),n1);
			unitsquare_Normalize(&interp_x1,&interp_y1);
			int temp_cnt = 1;
			Matrix<double>testfeature(1,2*n1);
			for (int i = 1;i<=interp_x1.nrows;i++)
			{
				testfeature(1,temp_cnt) = interp_x1(i,1);
				temp_cnt++;
			}
			for (int i = 1;i<=interp_y1.nrows;i++)
			{
				testfeature(1,temp_cnt) = interp_y1(i,1);
				temp_cnt++;
			}

			Matrix<double> character_vector(english->nClasses,1);
			character_vector=RecognizeSymbolVector(testfeature,english->sv_alpha,english->SVs,english->SVIndices,english->bias,english->inputDimension,english->nClasses,english->sigma);
			double val=character_vector.Max();
			int characterclasspredicted=0;
			for(int rc=1;rc<=character_vector.nrows;rc++)
			{
				for(int cc=1;cc<=character_vector.ncols;cc++)
					{
						if(character_vector(rc,cc)==val)
						{
							characterclasspredicted=rc;
							break;
						}
					}
			}

			string english_char = english->strokeNameArray.at(characterclasspredicted-1);
			strklist += english_char;
			strklist+=" ";
	   }//end of if
	 }
   }//end of for

vector<string>str2,str1;
int t = 0,t1=0,signal=0,char_code = 0;
vector<int> diff_ind;
string numeral1;
int charflg = 0;

istringstream iss1(strklist);
 
    while (iss1)
    {
        string sub1;
        iss1 >> sub1;
		int len1 = sub1.length();
		if(len1!=0)
		{
			str2.push_back(sub1);
		}
    } 
for(int i = 0;i<character_rule.size();i++)
{
	str1.clear();
    std::string delimiter3 = "-";
    string line1 = character_rule[i];
    size_t pos3 = 0;
    std::string token3;
    while ((pos3 = line1.find(delimiter3)) != std::string::npos) 
	{
          token3 = line1.substr(0, pos3);
          line1.erase(0, pos3 + delimiter3.length());
	}

	istringstream iss(token3);
 
    while (iss)
    {
        string sub;
        iss >> sub;
		int len = sub.length();
		if(len!=0)
		{
			str1.push_back(sub);
		}
    } 
    t = 0;t1=0;
    int sz;
	if(str2.size()==str1.size())
	{
	    for(int i = 0;i<str2.size();i++)
		{
			for(int j = 0;j<str1.size();j++)
			{
				if(str2[i]==str1[j])
				{
					t++;
					str1[j].clear();
					break;
				}
			}
		}	

		if(t==str2.size() )
		{
			numeral1 = line1;
			charflg = 1;
			break;
		}//end of if
	}//end of if
		
}//end of for 
if(numeral1.size()<2)
{
	char_code = (int)'a';
}
else
{
	char_code = (int)numeral1[1];
}

if(((numeral1.compare(" p")==0)||(numeral1.compare(" b")==0)||(numeral1.compare(" D")==0))&&(pStructStrokeInfo->nstroke==2))
{  
	double strk_14ht = 0.0,strk_34ht=0.0;
	vector<double>xpts1,xpts2,ypts1,ypts2;
	xpts1.clear();
	ypts1.clear();
	xpts2.clear();
	ypts2.clear();
	for (int k  = 0; k<pStructStrokeInfo->nstroke;k++)
	{
		
		if(k==0)
		{
			for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
			}
			 strk_14ht= (max_pts(ypts1)+(3*min_pts(ypts1)))/4;
			 strk_34ht= (3*max_pts(ypts1)+(min_pts(ypts1)))/4;
			 
		}
		if(k==1)
		{
			for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
			}
		}
		
	}//end of for

	// code to differentiate p,D,b	    
		 
		if((ypts2[0]>strk_34ht)&&(ypts2[ypts2.size()-1]>strk_14ht))
		{
			char_code = (int)'p';			
		}
		if((ypts2[0]<strk_34ht)&&(ypts2[ypts2.size()-1]<strk_14ht))
		{
			char_code = (int)'b';
		}
		if((ypts2[0]>strk_34ht)&&(ypts2[ypts2.size()-1]<strk_14ht))
		{
			char_code = (int)'D';
		}
}//end of if


if(((numeral1.compare(" x")==0)||(numeral1.compare(" y")==0))&&(pStructStrokeInfo->nstroke==2))
{  
	vector<double>xpts1,xpts2,ypts1,ypts2;
	double intersectxpt,intersectypt,strk1_14ht = 0.0,strk2_14ht=0.0;
    xpts1.clear();
	ypts1.clear();
	xpts2.clear();
	ypts2.clear();
	for (int k  = 0; k<pStructStrokeInfo->nstroke;k++)
	{
		
		if(k==0)
		{
			for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
			}
			 strk1_14ht= (max_pts(ypts1)+(3*min_pts(ypts1)))/4;
			 			 
		}
		if(k==1)
		{
			for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
			}
			strk2_14ht= (max_pts(ypts2)+(3*min_pts(ypts2)))/4;
			
			 
		}
		
	}//end of for

	// code to differentiate x,y	    
		 
		vector<double> y = Intersect(xpts1,ypts1,xpts2,ypts2);
		if (y.size()>1)			
		{
			 intersectxpt = y[1];
			 intersectypt = y[2];

			 if((intersectypt>strk1_14ht)&&(intersectypt>strk2_14ht))
			 {
				 cout<<"x"<<endl;
				 char_code = (int)'x';
			 }
			 else
			 {
				 cout<<"y"<<endl;
				 char_code = (int)'y';
			 }

		}		

}//end of if


if(((numeral1.compare(" F")==0)||(numeral1.compare(" I")==0))&&(pStructStrokeInfo->nstroke==3))
{  
	double strk_14ht = 0.0,strk_34ht=0.0,strk_width = 0.0,stkht=0.0,aspectratio = 0.0;
	vector<double>xpts1,xpts2,ypts1,ypts2;
	xpts1.clear();
	ypts1.clear();
	xpts2.clear();
	ypts2.clear();	

	for (int k  = 0; k<pStructStrokeInfo->nstroke;k++)
	{
		for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
		{
			xpts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
			ypts1.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
		}
		strk_width = max_pts(xpts1) - min_pts(xpts1);
	    stkht = max_pts(ypts1)- min_pts(ypts1);
		aspectratio = strk_width/stkht;		
		if (aspectratio < 0.08)
		{
		     strk_14ht= (max_pts(ypts1)+(3*min_pts(ypts1)))/4;
			 strk_34ht= (3*max_pts(ypts1)+(min_pts(ypts1)))/4;			 
		}

			 
		
		if(k==2)
		{
			for (int j = 0; j<pStructStrokeInfo[k].nPointCount;j++)
			{
				xpts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].x);
				ypts2.push_back(pStructStrokeInfo[k].ptrPointInfo[j].y);		
			}
		}
		
	}//end of for

	// code to differentiate F,I	
	if((ypts2[0]<strk_34ht)&&(ypts2[0]>strk_14ht))
	{
		cout<<"F"<<endl;
	    char_code = (int)'F';
	}
	else
	{
		char_code = (int)'I';
	}		 
		
}//end of if

return char_code;
	
 }//end of function
 vector<double> Preclassmain::Intersect(vector<double>x1,vector<double>y1,vector<double>x2,vector<double>y2)
 {
	    vector<double>interctflagxy;
	    double m1, c1, m2, c2;
		double dx1, dy1,dx2,dy2;
		double intersection_X, intersection_Y;
		dx1 = x1[x1.size()-1]-x1[0];
		dy1 = y1[y1.size()-1]-y1[0];
		m1 = dy1 / dx1;
		c1 = y1[0] - m1 * x1[0];

		dx2 = x2[x2.size()-1]-x2[0];
		dy2 = y2[y2.size()-1]-y2[0];
		m2 = dy2 /dx2;
		c2 = y2[0] - m2 * x2[0];
		if( (m1 - m2) == 0)
		{
			interctflagxy.push_back(0);
		}
		else
		{
			interctflagxy.push_back(1);			
			intersection_X = (c2 - c1) / (m1 - m2);
			intersection_Y = m1 * intersection_X + c1;
			interctflagxy.push_back(intersection_X);
			interctflagxy.push_back(intersection_Y);
		}
	return interctflagxy;
 }
void Preclassmain::showchar(Matrix<double> points)
{
	points.Display();
}
double Preclassmain::max_pts(vector<double> points)
{
	double max=points[0];
	for (int i=0;i<points.size();i++)
	{
		if (max<=points[i])
            max=points[i];

	}
	return max;
}
double Preclassmain::min_pts(vector<double> points)
{
	double min=points[0];
	for (int i=0;i<points.size();i++)
	{
		if (min>points[i])
            min=points[i];

	}
	return min;
}

void Preclassmain::unitsquare_Normalize(Matrix<double> *strokex,Matrix<double> *strokey)
{
		double minx=(*strokex).Min();
        double miny=(*strokey).Min();
		for(int i=1;i<=(*strokex).nrows;i++)
        {
            (*strokex)(i,1)=(*strokex)(i,1)-minx;
        }
        for(int i=1;i<=(*strokey).nrows;i++)
        {
            (*strokey)(i,1)=(*strokey)(i,1)-miny;
        }
        double maxx11=(*strokex).Max();
        double maxy11=(*strokey).Max();
        if(maxx11!=0)
        {
			for(int cnt=1;cnt<=(*strokex).nrows;cnt++)
            {
                (*strokex)(cnt,1)=(*strokex)(cnt,1)/maxx11;
            }
        }
        if(maxy11!=0)
        {
            for(int cnt=1;cnt<=(*strokey).nrows;cnt++)
            {
                (*strokey)(cnt,1)=(*strokey)(cnt,1)/maxy11;
            }
        }

       
}
 string Preclassmain::relabel_strk(vector<double>x1,vector<double>y1,vector<double>x2,vector<double>y2)
 {
        vector<double>rpt,lpt,tpt,bpt; 
	    double xmax1 = x1[0];
		double xmin1 = x1[0];
		double ymin1 = y1[0];
		double ymax1 = y1[0];

		for (int i = 0;i<x1.size();i++)
		{
			if(y1[i] > ymax1)
				ymax1 = y1[i];
			if(x1[i] > xmax1)
				xmax1 = x1[i];
			if(x1[i] < xmin1)
				xmin1 = x1[i];
			if(y1[i] < ymin1)
				ymin1 = y1[i];
        }


		double xmax2 = x2[0];
		double xmin2 = x2[0];
		double ymin2 = y2[0];
		double ymax2 = y2[0];

		for (int i = 0;i<x2.size();i++)
		{
			if(y2[i] > ymax2)
				ymax2 = y2[i];
			if(x2[i] > xmax2)
				xmax2 = x2[i];
			if(x2[i] < xmin2)
				xmin2 = x2[i];
			if(y2[i] < ymin2)
				ymin2 = y2[i];
        }


double yl = (ymax1+(3*ymin1))/4;
double yh = ((3*ymax1)+ymin1)/4;

double m1, c1, m2, c2;
double dx1, dy1,dx2,dy2;
double intersection_X, intersection_Y; 
dx1 = x1[x1.size()-1]-x1[0];
dy1 = y1[y1.size()-1]-y1[0];
m1 = dy1 / dx1;
c1 = y1[0] - m1 * x1[0];

dx2 = x2[x2.size()-1]-x2[0];
dy2 = y2[y2.size()-1]-y2[0];
m2 = dy2 /dx2;
c2 = y2[0] - m2 * x2[0];
if( (m1 - m2) == 0)
{
     cout << "No Intersection between the lines\n";
	 strklist += ("B ");
}
else
{
	intersection_X = (c2 - c1) / (m1 - m2);
    intersection_Y = m1 * intersection_X + c1;
	if((intersection_Y>=yl)&&(intersection_Y<=yh))
	{
		strklist += ("BI ");
	}
	else
	{
		strklist += ("B ");
	}
}

 return strklist;
 }

 Matrix<double> Preclassmain::Smoothstrk(Matrix<double> x1,int n)
 {
	Matrix<double>pts_x = x1.Get(1,1,2);
	Matrix<double>pts_y = x1.Get(2,2,2);
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
return smoothstrk;
}//end of smoothening fn


 Matrix<double> Preclassmain::Curvelengthbased_Normlzn(Matrix<double> x1,Matrix<double>y1,int n)
 {
    vector<double>diffvect;
	diffvect.push_back(0);
	int temp = 0;
	double diffx,diffy,diffxsqr,diffysqr,sumxy,xysqrt;
	for(int i = 2;i<=n;i++)
		{
			diffx = x1(i,1) - x1(i-1,1);
			diffxsqr = diffx*diffx;
			diffy = y1(i,1) - y1(i-1,1);
			diffysqr = diffy*diffy;
			sumxy = diffxsqr + diffysqr;
			xysqrt = sqrt(sumxy);
			diffvect.push_back((xysqrt+diffvect[temp]));
			temp++;
		}

		double smax = diffvect.back();
		vector<double> diffvect1;
		int r = 0;
		for (int j = 0; j < (diffvect.size()-1); j++)
		{
			if(diffvect[j]!=diffvect[j+1])
			{
				r++;
				diffvect1.push_back(diffvect[j]);
			}	
		}
		diffvect1.push_back(diffvect[r]);
		vector<int> i_x,j_y;
		for (int i=0; i<diffvect1.size(); i++)
		{
			int count = 0,flag_x;
			for(int j=0;j<diffvect.size();j++)
			{
				if (diffvect[j]==diffvect1[i])
				{
					count++;
					flag_x=j;
				}
			}	
			i_x.push_back(flag_x);
		}
		for (int j=0;j<diffvect.size();j++)
		{
			int flag_y;
			for(int i=0;i<diffvect1.size();i++)
			{
				if (diffvect1[i]==diffvect[j])
				{
					flag_y=i;
				}
			}
			j_y.push_back(flag_y);
		}

		vector<double> unif_s;
		for(int i = 0; i<=r; i++)
		{
			unif_s.push_back((smax*i)/r);
		}
		vector<double> x1_new,y1_new;
		for (int i=0;i<j_y.size();i++)
		{
		for (int j=0;j<i_x.size();j++)
		{
			if (i==j)
			{
				x1_new.push_back(x1(i+1,1));
				y1_new.push_back(y1(i+1,1));
			}
		}
	}
Matrix<double> C(x1_new,y1_new),unif_snew(unif_s.size(),1),diffvect1new(diffvect1.size(),1);
for (int i=0;i<diffvect1.size();i++)
{
   unif_snew(i+1,1)=unif_s[i];
   diffvect1new(i+1,1)= diffvect1[i];
}

Matrix<double> pts_x =interp1(diffvect1new,C.Get(1,1,2),unif_snew);
Matrix<double> pts_y =interp1(diffvect1new,C.Get(2,2,2),unif_snew);

vector<double> pts_x1,pts_y1;
for (int i = 1;i<=pts_x.nrows;i++){
	pts_x1.push_back(pts_x(i,1));
}

for (int i = 1;i<=pts_y.nrows;i++){
	pts_y1.push_back(pts_y(i,1));
}
Matrix<double>result(pts_x1,pts_y1);
return result;
 }

Matrix<double> Preclassmain::interpolateForSVM(Matrix<double> y,int size)
{
    try{
      //  Matrix<double> interp1(Matrix<double>, Matrix<double>, Matrix<double>);

        Matrix<int> len(1,2);
        double k;
        int i;
        len =y.Size();
        Matrix<double> x(len(1),1);

        for(i = 1; i <= len(1); i++)
            x.Set(i,1,i);
        Matrix<double> xi, yo;

        double step;

        k = (double)(size-1)/(double)(len(1)-1);
        step = (double)1/k;

        xi.SetRowCol(size,1);
        for(i = 1; i <= size; i++)
            xi.Set(i,1,1+(i-1)*step);

       yo=interp1(x,y,xi);
        return yo;
    }
    catch(exception& e)
    {
        Matrix<double> yo;
        string str="Stroke:Exception in interpolateForSVM: ";
        //str.append(e.what());
        //logwrite(str);
        return yo;
    }
}
Matrix<double> Preclassmain::interp1(Matrix<double> x,Matrix<double> y,Matrix<double> xi)
{
  Matrix<int> size(1,2);
  Matrix<int> size1(1,2);
  size1=x.Size();
  size=xi.Size();
  Matrix<double> yi(size(1),size(2));
  vector<double> yi_dummy;
 
  int j,l=1,m;
  double a,b,c1,c2;
  //cout<<size(1)<<"   " <<size1(1)<<endl;
  try{
	  
	  
  for(m=1;m<=size(1);m++)
    {
      for(j=1;j<size1(1);j++)
        {
          if(xi(m)>=x(j) && xi(m)<=x(j+l))
            {
              a=x(j);
              b=x(j+l);
			  if ((b-a)>0.0001 || (a-b)>0.0001)
			  {
                c1=((b-xi(m))/(b-a));
                c2=1-c1;
                //yi.Set(m,1,c1*y(j)+c2*y(j+l));
				yi_dummy.push_back(c1*y(j)+c2*y(j+l));
			  }
			  
            }
          else
            continue;
        }
    }
  Matrix<double> yi_new(yi_dummy.size(),1);
  for(int i = 0;i<yi_dummy.size();i++)
  {
	  yi_new(i+1,1) = yi_dummy[i]; 
  }
  return yi_new;
  }
  catch(exception& e)
  {
      Matrix<double> yo;
      string str="Stroke:Exception in interpolateForSVM: ";
     // str.append(e.what());
     // logwrite(str);
      return yi;
  }

}


void Preclassmain ::ClearRules()
{

   if(  english!=NULL)
    {
        delete   english;
    }    


}




