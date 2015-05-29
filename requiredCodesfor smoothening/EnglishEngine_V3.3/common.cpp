#include <fstream>
#include <exception>
#include "common.h"
#include <iostream>
//#include "stdafx.h"


void logwrite(string msg)
{
    try
    {
   /*     
        //QTime time=QTime::currentTime();
        //QDate date=QDate::currentDate();
        //std::string timestr=time.toString("hh:mm:ss").toStdString();
        std::string datestr=date.toString("dd.MM.yyyy").toStdString();
        myfile<<datestr;
        myfile<<" ";
        myfile<<timestr;
        myfile<<" ";
		*/
		ofstream myfile;
       myfile.open ("error.log",ios::app);
//        myfile << msg <<endl;
        myfile.close();
        ////cout<<"\nException occurred. Please refer error.log for details\n";
   
	}
    catch(exception& e)
    {
        ////cout<<"\nException occurred. Please refer error.log for details\n";
    }
}
double kernelGaussian(int SVIndex, Matrix<double> teststroke, float **SVs, int inputDimension, float sigma)
{
    double oneBySigmaSquared = 1./(sigma*sigma);
    double sum = 0;

    try
    {
    for(int t = 0; t < inputDimension; t++)
    {
		    
            double z = teststroke(1,t+1) - SVs[SVIndex][t];
            sum =sum - z*z;
    }
    }
    catch(...)
    {
        logwrite("SVMRecognize:Exception in kernelGaussian");
    }

    return(exp(sum*oneBySigmaSquared));
}

double Getsvm(int i, Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, float sigma)
{
    int j;
    double term = 0, y = 0;
try
    {
		
    for(j = SVIndices[i]; j < SVIndices[i+1]; j++)
    {
            term = kernelGaussian(j, teststroke,SVs,inputDimension,sigma);
            y += term * sv_alpha[j];
    }
    y += bias[i];
}
    catch(...)
    {
        logwrite("SVMRecognize:Exception in Getsvm");
    }
    return y;
}

Matrix<double> RecognizePreclassVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma)
{
    Matrix<double> charvect(nClasses,1);
    for(int i=1;i<=nClasses;i++)
    {
        charvect(i,1)=Getsvm(i-1,teststroke,sv_alpha,SVs,SVIndices,bias,inputDimension,sigma);
    }
    return charvect;


}
Matrix<double> RecognizeDigitVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma)
{
    Matrix<double> charvect(nClasses,1);
    for(int i=1;i<=nClasses;i++)
    {
        charvect(i,1)=Getsvm(i-1,teststroke,sv_alpha,SVs,SVIndices,bias,inputDimension,sigma);
    }
    return charvect;


}
Matrix<double> RecognizeSymbolVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma)
{
    Matrix<double> charvect(nClasses,1);
    for(int i=1;i<=nClasses;i++)
    {
        charvect(i,1)=Getsvm(i-1,teststroke,sv_alpha,SVs,SVIndices,bias,inputDimension,sigma);
    }
    return charvect;


}


