#pragma once
#ifndef QS_H_
#define QS_H_
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include "QSInterface.h"
using namespace std;

class QS: 
public QSInterface{
    public:
        QS();
        virtual ~QS();
        virtual void sortAll();
        virtual int medianOfThree(int left, int right);
        virtual int partition(int left, int right, int pivotIndex);
        virtual string getArray() const;
        virtual int getSize() const;
        virtual bool addToArray(int value);
        virtual bool createArray(int capacity);
        virtual void clear();
        void quicksort(int left, int right);
    private:
        int* userArray = NULL;
        int arrayIndex;
        int arraySize;     
        string emptyString = "";   
    };
#endif