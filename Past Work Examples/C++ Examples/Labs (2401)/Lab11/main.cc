#include <queue>
#include <string>
#include <iostream>

using namespace std;

class chore{
	public:
		chore();
		bool operator < (const chore& other)const{return pri_num < other.pri_num;};
		void input();
		void output()const;
	private:
		string what;
		int pri_num;
};

int main(){
	priority_queue<chore> toDo;
	chore temp;
	
	for(int i = 0; i < 5; i++){
		temp.input();
		toDo.push(temp);
	}
	for(int i = 0; i < 5; i++){
		toDo.top().output();
		toDo.pop();
	}
}

chore::chore(){
	what = "";
	pri_num = 1;
};

void chore::input(){
	cout << "What is the description of the chore?: ";
	if(cin.peek() == '\n')
		cin.ignore();
	getline(cin, what);
	cout << "Now please provide the priority number for the chore starting at 1\n"
		 << "with the higher the number the greater the priority: ";
	if(cin.peek() == '\n')
		cin.ignore();
	cin >> pri_num;
};

void chore::output()const{
	cout << "The description of the chore is: " << what << endl
		 << "And the priority number of: " << pri_num << endl;
};