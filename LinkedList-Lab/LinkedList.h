#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "LinkedListInterface.h"

using namespace std;

template<class T>
class LinkedList : public LinkedListInterface<T>
{
private:
	struct Node{
	T data;
	Node* next;
	Node(const T& the_data, Node* next_val = NULL) : data(the_data){next = next_val;}
	};
	Node *head;
	int num_items;
public:
	LinkedList(void){
		head = NULL;
		num_items = 0;
	}
	virtual ~LinkedList(void){
		clear();
	}

	virtual void insertHead(T value) override{
        if(num_items != 0){
            if(valueFound(value)){
                return;
            }
        }
        Node *newNode = new Node(value, NULL);
        newNode->next = head;
        head = newNode;
        num_items++;
	}

	virtual void insertTail(T value) override{
		Node *newNode = new Node(value);
		if(head == NULL){
			head = newNode;
			num_items++;
			return;
		}
		Node *prePtr = head;
		for(Node *ptr = head; ptr != NULL; ptr = ptr->next){
			if(ptr->data == value){
				delete newNode;
				return;
			}
			prePtr = ptr;
		}
		prePtr->next = newNode;
		num_items++;
	}

	virtual void insertAfter(T value, T insertionNode) override{
        Node *ptr = head;
        if(valueFound(value)){
            return;
        }
        ptr = head;
        Node *newNode = new Node(value, NULL);
        while(ptr != NULL){
            if(ptr->data == insertionNode){
                newNode->next = ptr->next; 
                ptr->next = newNode;
                num_items++;
                return;
            }
            else{
                ptr = ptr->next;
            }
        }
    }

	virtual void remove(T value) override{
		if(num_items == 0){
			return;
        }
		if(head->data == value){
			Node* nextPtr = head->next;
			delete head;
			head = nextPtr;
			num_items--;
			return;
		}
		Node* prePtr = head;
		for(Node *ptr = head->next; ptr != NULL; ptr = ptr->next){
			if(ptr->data == value){
				prePtr->next = ptr->next;
				delete ptr;
				num_items--;
				return;
			}
			prePtr = ptr;
		}
	}

	virtual void clear() override{
		Node *ptr = head;
		while(num_items > 0){
			Node *nextPtr = ptr->next;
			delete ptr;
			ptr = nextPtr;
			num_items--;
		}
		head = NULL;
	}

	virtual T at(int index) override{
        if((index >= num_items) || (index < 0)){
			throw std::out_of_range("At Error");
		} 
        else{
			Node *ptr = head;
			for(int i = 0; i <= index; i++){
		  		if(i == (index)){ 
		  			return(ptr->data);
		  		}
                else{
		  			ptr = ptr->next;
		  		}
			}
		}
        return head->data;
	}

	virtual int size() override{
		return num_items;
	}

	virtual string toString() override{
        stringstream ss;
        for(Node *ptr = head; ptr != NULL; ptr = ptr->next){
			ss << ptr->data;
            if(ptr->next != NULL){
                ss << " ";
            }
		}
        return ss.str();
	}

    bool valueFound(T value){
        Node *ptr = head;
        while(ptr != NULL){
            if(ptr->data == value){
                return true;
            }
            else{
                ptr = ptr->next;
            }
        }
        return false;
    }

};
