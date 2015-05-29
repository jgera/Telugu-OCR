#ifndef SELECTION_H
#define SELECTION_H
/*
#include <fstream>
#include <string>
#include <vector>
*/

#include "stdafx.h"
using namespace std;

class selection
{
public:

    vector<int> getconfusechars(vector<int> isciistream);
    static int corvflg;
    static int cvmflg;
    static int ccvflg1;
    static int ccvflg2;
    static vector<int> cmstrokes;
    static vector<string> confusionrules;
    static vector<string> confusionrules_cv;
    static vector<string> confusionrules_cm;
};

#endif // SELECTION_H
