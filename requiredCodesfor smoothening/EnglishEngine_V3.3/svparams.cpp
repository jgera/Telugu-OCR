#include "svparams.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdlib.h>
#include <vector>

using namespace std;

SVParams::SVParams(){}
SVParams::SVParams(string filename)
{
    try{
            SV_ready = false;
            ifstream paramsFile(filename.c_str(), ios::in);
            if(!paramsFile)
            {
                    cerr << "Error in opening training paramaeters' file\n" << filename << endl;
                    exit(0);
            }

            paramsFile >> inputDimension;
            paramsFile >> nClasses;
            paramsFile >> sigma;
            paramsFile >> strokeNamesFilename;
            paramsFile >> dataPath;
            paramsFile >> nSVsFilename;
            paramsFile >> SVIndexFilename;
            paramsFile >> AlphasSVsFilename;
            paramsFile >> biasFilename;
            paramsFile >> lineLength;

            y = new float[nClasses];

            loadSVIndices();
            loadnSVsPerClass();
            loadBiasValues();
            loadAlphasSVs();
            /**********load stroke labels for mapping strk. num. to strk.**/
            //loadStrokeLabels(strokeNamesFilename, strokeNameArray);
        }
        catch(exception& e)
        {
            string str="SVParams:Exception in constructor: ";
            str.append(e.what());
            logwrite(str);
        }
}

void SVParams::loadSVIndices()
{
    try{
            int i;
            ifstream indexFile;
            string filename = dataPath;
            filename += SVIndexFilename;
            indexFile.open(filename.c_str());
            if(!indexFile)
            {
                    cerr << "Error in opening training file\n" << filename << endl;
                    exit(0);
            }

            //the indices will be loaded, so keep 1 more entry for nSVs for last class
            SVIndices = new int[nClasses + 1];
            for(i = 0; i < nClasses + 1; i++)
            {
                    indexFile >> SVIndices[i];
            }

            indexFile.close();
        }
    catch(exception& e)
    {
        string str="SVParams:Exception in loadSVIndices: ";
        str.append(e.what());
        logwrite(str);
    }
}

void SVParams::loadnSVsPerClass()
{
    try{
            int i;
            ifstream nSVsFile;
            string filename = dataPath;
            filename += nSVsFilename;
            nSVsFile.open(filename.c_str());
            if(!nSVsFile)
            {
                    cerr << "Error in opening training file\n" << filename << endl;
                    exit(0);
            }

            //the indices will be loaded, so keep 1 more entry for nSVs for last class
            nSVsPerClass = new int[nClasses + 1];
            for(i = 0; i < nClasses + 1; i++)
            {
                    nSVsFile >> nSVsPerClass[i];
            }

            nSVsFile.close();
        }
    catch(exception& e)
    {
        string str="SVParams:Exception in loadnSVsPerClass: ";
        str.append(e.what());
        logwrite(str);
    }
}

void SVParams::loadBiasValues()
{
    try{
            int i;
            ifstream biasFile;
            string filename = dataPath;
            filename += biasFilename;
            biasFile.open(filename.c_str());
            if(!biasFile)
            {
                    cerr << "Error in opening training file\n" << filename << endl;
                    exit(0);
            }

            bias = new float[nClasses];
            for(i = 0; i < nClasses; i++)
            {
                    biasFile >> bias[i];
					
            }
            biasFile.close();
        }
    catch(exception& e)
    {
        string str="SVParams:Exception in loadBiasValues: ";
        str.append(e.what());
        logwrite(str);
    }
}

void SVParams::loadAlphasSVs()
{
    try{
            int ncols = 0;

            string filename = dataPath;
            filename += AlphasSVsFilename;
            ifstream trainFile(filename.c_str());
            if(!trainFile)
            {
                    cerr << "Error in opening training file\n" << filename << endl;
                    exit(0);
            }
            trainFile >> totalnSVs;
            trainFile >> ncols;

            sv_alpha = new float[totalnSVs];
            SVs = new float*[totalnSVs];
            for(int ii = 0; ii < totalnSVs; ii++)
            {
                    SVs[ii] = new float[inputDimension];
            }
            for(int t = 0; t < totalnSVs; t++)
            {
                    trainFile >> sv_alpha[t];
                    for(int t1 = 0; t1 < inputDimension; t1++)
                    {
                            trainFile >> SVs[t][t1];
                    }
            }
            trainFile.close();
            SV_ready = true;
        }
    catch(exception& e)
    {
        string str="SVParams:Exception in loadAlphasSVs: ";
        str.append(e.what());
        logwrite(str);
    }
}

void SVParams::loadStrokeLabels(string filename, vector<string> strokeNameArray)
{
    try{
            ifstream inFile(filename.c_str());
            string strokename;
            int i = 1;
    //check how it is done for shape features matching
            while(!inFile.eof())
            {
                   inFile>>strokename;
                   strokeNameArray.push_back(strokename);
                    i++;
            }
            inFile.close();
        }
    catch(exception& e)
    {
        string str="SVParams:Exception in loadStrokeLabels: ";
        str.append(e.what());
        logwrite(str);
    }
}
