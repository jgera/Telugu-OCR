#ifndef WORD_H
#define WORD_H
#pragma once
#include <iostream>
#include <vector>
#include "common.h"
//#include "Character.h"
#include "stdafx.h"
class Character;
class Word
{
private:
    string language;
    int codetype;
    int ncodes;
    string label;
    double origin[2];
    double linespace;
    double top2botratio;
    double xspan;
    int nchars;
    vector<int> codearray;
    vector<int> arraylist;
    vector<Character> charlist;


public:
	vector<int> wordarraylist;
	Word();
    Word(const Word& obj);
    Word(double origin[],double  linespace,double xspan);
	Word(double origin[],double  linespace,int nchars,Character charlist[]);
	~Word();
    void AddChar2Word(Character chr);
    void clear();
	vector<int> SVMRecognizeWord(ofstream& logFile);

	
};
#endif // WORD_H
