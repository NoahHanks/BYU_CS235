#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TodoListInterface.h"

using namespace std;

class TodoList: public TodoListInterface {
public:
  vector <string> tasks;
    TodoList() {
      cout << "In Constructor" << endl;
      ifstream infile("TODOList.txt");
      string line;
      if(infile.is_open()){
        while(getline(infile, line)){
          tasks.push_back(line);
        }
        infile.close();
      }
    }

    virtual ~TodoList() {
      cout << "In Destructor" << endl;
      ofstream outfile;
      outfile.open("TODOList.txt", ofstream::out | ofstream::trunc);
      for(int i = 0; i < tasks.size(); i++){
        outfile << tasks[i] << endl;
      }
      outfile.close();
    }

    virtual void add(string _duedate, string _task){
      cout << "In add" << _duedate << " " << _task << endl;
      tasks.push_back(_duedate+ " " + _task);
    }

    virtual int remove(string _task){
      cout << "In remove" << endl;
      for(int i = 0; i < tasks.size(); i++){
        if(tasks[i].find(_task) != std::string::npos){
          tasks.erase(tasks.begin() + i);
          return 1;
        }     
      }
      return 0;
    }

    virtual void printTodoList(){
      cout << "In list" << endl;
      for(int i = 0; i < tasks.size(); i++){\
        cout << tasks[i] << endl;
      }
    }

    virtual void printDaysTasks(string _date){
      cout << "In daystasks" << endl;
      for(int i = 0; i < tasks.size(); i++){
        if(tasks[i].compare(0, 2, _date.substr(0, 2)) == 0){
            cout << tasks[i] <<endl;
        }
      }
    }
};

#endif