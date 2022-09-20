#include <iostream>
#include <fstream>
#include <string>
#include "TodoList.h"
using namespace std;
int main(int argc, char*argv[]) {
  TodoList mylist;

  string firstarg = argv[1];
  if(firstarg.compare("add") == 0){
    string date = argv[2];
    string task = argv[3];
    mylist.add(date, task);
  }
  if(firstarg.compare("remove") == 0){
    string taskToRemove = argv[2];
    mylist.remove(taskToRemove);
  }
  if(firstarg.compare("printList") == 0){
    mylist.printTodoList();
  }
  if(firstarg.compare("printDay") == 0){
    mylist.printDaysTasks(argv[2]);
  }
}