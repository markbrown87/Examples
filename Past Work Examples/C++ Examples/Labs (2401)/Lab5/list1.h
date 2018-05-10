#include<iostream>
#include<string>

struct Node{
	std::string data;
	Node  *link;
};

class Lilist{
	public:
		Lilist() {head = NULL;}
		void add(std::string item);
		void show();
		Node* search(std::string target);
		void move_front_to_back();
	private:
		Node *head;
};

void Lilist::add(std::string item){
	Node * tmp;
	if (head==NULL){
		head = new Node;
		head -> data = item;
		head -> link = NULL;
	}
	else{
		for(tmp = head;tmp->link != NULL;tmp = tmp->link)
			; //this loop simply advances the pointer to last node in the list
		tmp->link = new Node;
		tmp = tmp->link;
		tmp->data = item;
		tmp->link = NULL;
	}
}

void Lilist::show(){
	for(Node *tmp = head; tmp != NULL; tmp = tmp->link)
		std::cout <<tmp->data<<"  ";
}

Node* Lilist::search(std::string target){
	Node *cursor;
	for(cursor = head; cursor != NULL; cursor = cursor -> link)
		if(cursor ->data == target)
			return cursor;
	return NULL;
}

void Lilist::move_front_to_back(){
	Node *tmp;
	Node *tail;
	tmp = head;
	
	for(tail = head; tail->link != NULL; tail = tail ->link)
		;
	head = head -> link;
	tail ->link = tmp;
	tmp -> link = NULL;
}
