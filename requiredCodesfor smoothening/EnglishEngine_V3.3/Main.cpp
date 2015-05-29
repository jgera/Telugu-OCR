#include <fstream>
#include "common.h"
#include "Preclassmain.h"
#include "svparams.h"
#include <tchar.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <TCHAR.h>
#include <wchar.h>
#include "File_Data_Struct.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{ 
	string filename  = "1.txt";
	ifstream ptfile(filename.c_str(), ios::in);
    if(!ptfile)
    {
		cerr << "Error in opening training paramaeters' file\n" << filename << endl;
        exit(0);
    }

	ofstream logFile ;  
	//logFile.open("2_test.txt"); 
	Preclassmain *obj = new  Preclassmain();
	int english_unicode;
	obj->loadSVMs(); 
	obj->loadRules1(); 
    if(!ptfile)
    {
            cerr << "Error in opening training paramaeters' file\n" << filename << endl;
            exit(0);
    }
	int iStrokeCount = 0;
	vector<double>xpoints1;
	vector<double>ypoints1;
	vector<int>xall0;
	vector<int>yall0;
	vector<double>lams;
	Matrix<double> strokex,strokey;
	vector<int> npoint;
	int stkcount = 0,npoints = 0;
	double x;
	double y;
	int p;
	while(!ptfile.eof())
	{
		ptfile >> x ;
		xpoints1.push_back(x);
		ptfile >> y;
		ypoints1.push_back(y);
	    ptfile >> p;
		if (p == 1)
			npoints++;
		if(p==0)
		{
           stkcount++;
           npoints++;
           npoint.push_back(npoints);
           npoints = 0;
        }
    }
	ptfile.close();

	Matrix<double> A(xpoints1,ypoints1);
	iStrokeCount = stkcount;
	int n = npoint.size();
	FILE_STROKEINFO *pStructStrokeInfo; 
	pStructStrokeInfo=(FILE_STROKEINFO*)malloc(iStrokeCount*sizeof(FILE_STROKEINFO));
	pStructStrokeInfo->nstroke = iStrokeCount;
	int temp = 0,j1 = 0;
	for (int i = 0; i< iStrokeCount;i++)
	{
		pStructStrokeInfo[i].nPointCount = npoint[i];
		//cout << " Number of points " << pStructStrokeInfo[i].nPointCount << endl;
		pStructStrokeInfo[i]. ptrPointInfo =  (FILE_POINTINFO*)malloc(pStructStrokeInfo[i].nPointCount*sizeof(FILE_POINTINFO));
		for (  int j = 0;j< pStructStrokeInfo[i].nPointCount;j++)
		{
			pStructStrokeInfo[i]. ptrPointInfo[j].x  = xpoints1[temp];
			pStructStrokeInfo[i]. ptrPointInfo[j].y  = ypoints1[temp];
			temp++;
		}
	}//end of for

   
    english_unicode = obj->Recognize_English(pStructStrokeInfo,iStrokeCount,logFile);
	cout<<english_unicode<<endl;
    obj->ClearRules();
 return (0);
}


