#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <vector>
#include <iostream>
#include "Matrix.h"

//using namespace std;

void logwrite(string msg);
double Getsvm(int i,Matrix<double> teststroke,float *sv_alpha,float **SVs,int *SVIndices,float *bias,int inputDimension,float sigma);
double kernelGaussian(int SVIndex,Matrix<double> teststroke,float **SVs,int inputDimension,float sigma);
Matrix<double> RecognizePreclassVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma);
Matrix<double> RecognizeDigitVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma);
Matrix<double> RecognizeSymbolVector(Matrix<double> teststroke, float *sv_alpha, float **SVs, int *SVIndices, float *bias, int inputDimension, int nClasses, float sigma);
#endif // COMMON_H
