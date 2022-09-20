#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include "QS.h"
using namespace std;

QS::QS(){}
QS::~QS(){
    delete[] userArray;
}

void QS::sortAll(){
    quicksort(0, getSize() - 1);
}

void QS::quicksort(int left, int right){
    if((right - left) < 1){
        return;
    }
    int pivot = medianOfThree(left, right);
    pivot = partition(left, right, pivot);
    quicksort(left, pivot - 1);
    quicksort(pivot + 1, right);
}

int QS::medianOfThree(int left, int right){
    if((getSize() < 1) 
    || left < 0  
    || right < 0
    || left > getSize() - 1 
    || right > getSize() - 1
    || !(right > left)){
        return -1;
    }
    int middle = (left + right) / 2;
    int tempVal;
    if(userArray[left] > userArray[middle]){
        tempVal = userArray[left]; 
        userArray[left] = userArray[middle];
        userArray[middle] = tempVal;
    }
    if(userArray[middle] > userArray[right]){
        tempVal = userArray[middle]; 
        userArray[middle] = userArray[right];
        userArray[right] = tempVal;
    }
    if(userArray[left] > userArray[middle]){
        tempVal = userArray[left]; 
        userArray[left] = userArray[middle];
        userArray[middle] = tempVal;
    }
    return middle;
}

int QS::partition(int left, int right, int pivotIndex){
    if((getSize() < 1) 
    || left < 0
    || right < 0 
    || left > getSize() - 1 
    || right > getSize() - 1
    || pivotIndex < left 
    || pivotIndex > right
    || !(right > left)){
        return -1;
    }
    int tempVal = userArray[left]; 
    userArray[left] = userArray[pivotIndex];
    userArray[pivotIndex] = tempVal;
    int up = left + 1;
    int down = right;
    do{
        while((userArray[up] < userArray[left] + 1) && (up < right)){
            up++;
        }
        while((userArray[down] > userArray[left]) && (down > left)){
            down--;
        }
        if(up < down){
            tempVal = userArray[up];
            userArray[up] = userArray[down];
            userArray[down] = tempVal;
        }
    } while(up < down);
    tempVal = userArray[left];
    userArray[left] = userArray[down];
    userArray[down] = tempVal;
    return down;
}

string QS::getArray() const{
    if(!((getSize() < 1) 
    || (getSize() > arraySize))){ 
        stringstream ss;
        for(int i = 0; i < getSize() - 1; i++){ 
            ss << userArray[i] << ",";
        }
        ss << userArray[getSize()-1];
        string arrayOutput;
        while(!ss.fail()){
            ss >> arrayOutput;
        }
        return arrayOutput;
    }
    return emptyString;
}

int QS::getSize() const{
    return arrayIndex;
}

bool QS::addToArray(int value){
    if(arraySize < arrayIndex + 1){
        return false;
    }
    userArray[arrayIndex] = value;
    arrayIndex++;
    return true;
}

bool QS::createArray(int capacity){
    if(capacity < 1){
        return false;
    }
    arrayIndex = 0;
    arraySize = capacity;
    if(userArray != NULL){
        delete[] userArray;
        userArray = NULL;
    }
    userArray = new int[capacity];
    return true;
}

void QS::clear(){
    for(int i = 0; i < arraySize; i++){
        userArray[i] = 0;
    }
    arrayIndex = 0;
}