#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

struct Student{
	string id,name,gender,address;
	double gpa;
};
typedef struct Student Student;


struct node{
	Student data;
	struct node *next;
};

typedef struct node node;


node *makeNode (Student student){
	cout << "Enter id: ";
	cin >> student.id;
	cin.ignore();
	cout << "Enter name: ";
	getline(cin,student.name);
	cout << "Enter gender: ";
	cin >> student.gender;
	
	cout << "Enter address: ";
	cin >> student.address;
	
	cout << "Enter gpa: ";
	cin >> student.gpa;
	
	
	
	node *newStudent = new node();
	newStudent->data = student;
	newStudent->next = NULL;
	
	return newStudent;
}



void pushFront(node **head,Student student){
	node *newStudent = makeNode(student);
	newStudent->next = *head;
	*head = newStudent;
}

void pushBack(node **head,Student student){
	node *newStudent = makeNode(student);
	node *temp = *head;
	if (*head == NULL){
		*head = newStudent;
		return;
	}
	
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newStudent;
	
}

void toString(Student student){
	cout << student.id << " " << student.name << " " <<
	student.gender << " " << student.address << " " <<  student.gpa << endl;
}

void printfList(node *head){
	while (head != NULL){
		toString(head->data);
		head = head->next;
	}
}

void popFront(node **head){
	if (*head == NULL) return;
	node *temp = *head;
	*head = (*head)->next;
	delete temp;
}

void popBack(node **head){
	if (*head == NULL ) return;
	
	node *temp = *head;
	if (temp->next == NULL){
		*head = NULL;
		delete temp;
		return;
	}
	while (temp->next->next != NULL){
		temp = temp->next;
	}
	node *deleteNode = temp->next;
	temp->next = NULL;
	delete deleteNode;
}

node *findNode(node *head,string id){
	node *temp = head;
	while (temp != NULL and temp->data.id != id){
		temp = temp->next;
	}
	return temp;
}


void deleteStudent(node **head,string id){
	node *temp = *head, *pre;
	if (temp == NULL){
		return;
	}
	while (temp != NULL && temp->data.id != id){
		pre = temp;
		temp = temp->next;
	}
	
	if (temp != NULL && temp->data.id == id){
		node *deleteNode = temp;
		pre->next = temp->next;
		delete deleteNode;	
	}
}

void listStudent(node *head){
	while (head != NULL){
		if(head->data.gpa >= 5)
			toString(head->data);
		head = head->next;
	}
}

int totalMaleStudent(node *head){
	int count = 0;
	while (head != NULL){
		if (head->data.gender == "Nam" or head->data.gender == "nam"){
			count++;
		}
		head = head->next;
	}
	return count;
}

void updateNode(node **head){
	string id;
	cout << "Enter id: ";
	cin >> id;
	node *updateNode = findNode(*head,id);
	if (updateNode == NULL){
		cout << "Student invalid" << endl;
	}else{
		double gpa;
		cout << "Enter gpa: ";
		cin >> gpa;
		updateNode->data.gpa = gpa;
	}
}

node *getEnd(node *head){
	node *temp = head;
	while (temp!= NULL & temp->next != NULL){
		temp = temp->next;
	}
	return temp;
}

node *partition(node *head,node *end){
	node *pivot = head;
	node *preNode = head;
	node *cur = head->next;
	while (cur != end->next){
		if (pivot->data.gpa > cur->data.gpa){
			swap(preNode->next->data,cur->data);
			preNode = preNode->next;
		}
		cur = cur->next;
	}
	swap(preNode->data,pivot->data);
	return preNode;
}

void solve(node *head,node *end){
	if (head == NULL || end == NULL || head == end) return;
	node *pivot = partition(head,end);
	solve(head,pivot);
	solve(pivot->next,end);
}

void sortedGPA(node **head){
	node *temp = *head;
	if (temp == NULL || temp->next == NULL) return;
	
	node *end = getEnd(*head);
	solve(temp,end);
	return;
}

void selectionSortGPA(node **head){
	for (node *i = *head;i!= NULL; i = i->next){
		node *minNode = i;
		for (node *j = i->next;j!= NULL; j = j->next){
			if (j->data.gpa < minNode->data.gpa){
				minNode = j;
			}
		}
		swap(minNode->data,i->data);
	}
}

void addStudentAfter(node **head,Student student){
	string id;
	cout << "Enter id: ";
	cin >> id;
	node *addNode = findNode(*head,id);
	if (addNode == NULL){
		cout << "Not valid" << endl;
		return;
	}
	if (addNode->next == NULL){
		pushBack(head,student);
	}
	node *newStudent = makeNode(student);
	newStudent->next = addNode->next;
	addNode->next = newStudent;
}

void deleteNodeAfter(node **head,Student student){
	string id;
	cout << "Enter id: ";
	cin >> id;
	node *deleteNode = findNode(*head,id);
	if (deleteNode == NULL){
		cout << "Not valid" << endl;
		return;
	}
	if (deleteNode->next == NULL){
		popBack(head);
	}
	node *afterDeleteNode = deleteNode->next;
	deleteNode->next = afterDeleteNode->next;
	delete afterDeleteNode;
}

int main (){
	node *head = NULL;
	int choice = 0;
	do{
		cout << "1.  Push front." << endl;
		cout << "2.  Push back. " << endl;
		cout << "3.  Add student after node q. " << endl;
		cout << "4.  Display student." << endl;
		cout << "5.  Pop front. " << endl;
		cout << "6.  Pop back. " << endl;
		cout << "7.  Delete all student. " << endl;
		cout << "8.  Delete student after node q. " << endl;
		cout << "9.  Selection sort by GPA." << endl;
		cout << "10. QuickSort by GPA." << endl;
		cout << "11. Listed student have GPA >= 5." << endl;
		cout << "12. Number of student have gender with male." << endl;
		cout << "13. Update student by studentID." << endl;
		cout << "Enter option: ";
		cin >> choice;
		
		if (choice == 1){
			Student student;
			pushFront(&head,student);
		}
		else if (choice == 2){
			Student student;
			pushBack(&head,student);
		}else if (choice == 3){
			Student student;
			addStudentAfter(&head,student);
		}else if (choice == 4){
			printfList(head);
		}else if (choice == 5){
			popFront(&head);
		}else if (choice == 6){
			popBack(&head);
		}else if (choice == 7){
	
		}else if (choice == 8){
			Student student;
			deleteNodeAfter(&head,student);
		}else if (choice == 9){
			selectionSortGPA(&head);
		}else if (choice == 10){
			sortedGPA(&head);
		}else if (choice == 11){
			listStudent(head);
		}else if (choice == 12){
			cout << "Number of students with male: " << totalMaleStudent(head) << endl; 	
		}else if (choice == 13){
			updateNode(&head);
		}else{
			cout << "Function does not have in system!" << endl;
		}
	}while (choice != 0);
	
}
