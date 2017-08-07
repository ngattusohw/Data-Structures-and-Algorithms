#include "linkedlist.h"

linkedlist::linkedlist(){
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
}


linkedlist::~linkedlist(){
	for(int x=0;x<size;x++){
		removeLast();
	}

	head = nullptr;
	tail = nullptr;
}

linkedlist::Node::Node(){
	Node* next = nullptr;
	int elem = 0;
}

linkedlist::Node::~Node(){
	printf("%s\n", "Deconstructing node");
}


void linkedlist::insertLast(int elem){
	Node* to_insert = new Node;
	to_insert->elem = elem;
	size++;
	if(head==nullptr){
		head = to_insert;
		tail = to_insert;
	}else{
		Node* temp = tail;
		temp->next = to_insert;
		tail = to_insert;
	}
}


void linkedlist::insertAt(int index, int elem){
	Node* to_insert = new Node;
	to_insert->elem = elem;
	if(!(index>size || index<0)){ //index is inbounds
		int curr = 0;
		Node* current = head;
		Node* temp;
		while(curr!=index){
			current = current->next;
		}
		temp = current->next;
		current->next = to_insert;
		to_insert->temp;
		if(size-1==index){
			tail = to_insert;
		}
	}else if(index==0){
		to_insert->next = head;
		head = to_insert;
	}else{ //not in bounds
		printf("%s\n", "Not in bounds!");
	}
}


int linkedlist::removeLast(){
	Node* current = head;
	while(current!=head){
		current = current->next;
	}
	int the_return = current->next->elem;
	delete current->next;
	tail = current;
	return the_return;
}


int linkedlist::removeAt(int index){
	if(size-1==index){
		return removeLast();
	}else if(!(index>size || index<0)){ //index is inbounds
		int curr = 0;
		Node* current = head;
		Node* temp;
		while(curr!=index){
			current = current->next;
		}
		temp = current->next;
		current->next = temp->next;
		delete temp;
	}else if(index==0){
		Node temp = head->next;
		delete head;
		head = temp;
	}else{ //not in bounds
		printf("%s\n", "Not in bounds!");
	}
}


int linkedlist::getSize(){
	return size;
}


bool linkedlist::findElement(int elem){
	Node current = head;
	for(int x=0;x<size;x++){
		if(current->elem == elem){
			return true;
		}else{
			current = current->next;
		}
	}

	return false; //will be called if for loop is left
}





