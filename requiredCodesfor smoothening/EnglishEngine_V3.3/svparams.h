#ifndef SVPARAMS_H
#define SVPARAMS_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class SVParams
{
private:
                bool SV_ready;
public:
    SVParams();
    SVParams(string filename);

    float *sv_alpha;
    float **SVs;
    int *SVIndices;
    float *bias;
    float *y;
    int *nSVsPerClass;
    int totalnSVs;

    int inputDimension;
    int nClasses;
    float sigma;

    vector<string> strokeNameArray;
    string strokeNamesFilename;
    string dataPath;
    string nSVsFilename;
    string SVIndexFilename;
    string AlphasSVsFilename;
    string biasFilename;
    int lineLength;

    void loadSVIndices();
    void loadnSVsPerClass();
    void loadBiasValues();
    void loadAlphasSVs();
    void loadStrokeLabels(string filename, vector<string> strokeNameArray);

};

#endif // SVPARAMS_H
