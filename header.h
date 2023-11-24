#pragma once

#include<iostream>
#include<string>
#include<cstdlib>
#include <sstream>

using namespace std;
enum color { red, black, db };

class Assignee {
public:
	string firstname;
	string lastname;
	string address;
	string dob;
	int id;	
	string ID;
	bool taskass;

	Assignee* parent;
	Assignee* left;
	Assignee* right;
	color c;

	Assignee(string fn, string ln, string add, string d,int k) {
		firstname = fn;
		lastname = ln;
		address = add;
		dob = d;
		taskass = false;
		id = k;
		ID = generateid();
		

		parent = nullptr;
		left = nullptr;
		right = nullptr;
		c = red;
	}
	string generateid() {
		
		string i = "A0";
		if (id < 10) {
			i += "0";
		}
		string j = to_string(id);
		i += j;

		return i;
	}
	string getID() {
		cout << ID << endl;
		return ID;
	}
};



class Task {
public:
	int ID;
	string dcrp;
	int prilev;
	string assid;
	bool status; //0_if in progress and 1_if completed

	Task* left;
	Task* right;
	Task* parent;
	color c;
	

	Task(int id, string d, int pl, string aid) {
		ID = id;
		dcrp = d;
		prilev = pl;
		assid = aid;
		status = 0;

		parent = nullptr;
		left = nullptr;
		right = nullptr;
		

		c = red;
	}

};

class taskManagementSystem {
public:
	Assignee* ah;
	int assic = 0;
	int taskcount = 0;
	Task* th;

	taskManagementSystem() {
		
		ah = nullptr;
		th = nullptr;

	}
	//**********************************************************
	//adding assignee
	void addAssignee(string fn, string ln, string add, string d) {
		assic++;
		int count = assic;
		cout << "here" << endl;
		Assignee* z = bstinsertionA(fn, ln, add, d,count);
		if (z->parent == nullptr) {
			return;
		}
		if (z->parent->parent == nullptr) {
			return;
		}
		cout << "here1" << endl;
		fixinsetrba(z);
	}
	Assignee* bstinsertionA(string fn, string ln, string add, string d, int count) {
		Assignee* newa = new Assignee(fn, ln, add, d, count);
		cout << newa->id << endl;
		if (ah == nullptr) {
			ah = newa;
			ah->parent = nullptr;
			newa->c = black;


		}
		else {
			Assignee* current = ah;

			while (current != nullptr) {

				if (newa->id < current->id) { // Left subtree
					if (current->left != nullptr) { current = current->left; }
					else {

						current->left = newa;
						newa->parent = current;
						break;
					}
				}
				else if (newa->id >= current->id) { // Right subtree
					if (current->right != nullptr) current = current->right;
					else {
						current->right = newa;
						newa->parent = current;
						break;
					}
				}

			}
		}

		return newa;
	}
	void fixinsetrba(Assignee* z) {
		Assignee* y = nullptr;
		while (z->parent != nullptr && z->parent->c == red) {
			if (z->parent == z->parent->parent->right) {
				y = z->parent->parent->left;
				if (y != nullptr && y->c == red) {
					z->parent->c = black;
					y->c = black;
					z->parent->parent->c = red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						rra(z);
					}
					z->parent->c = black;
					z->parent->parent->c = red;
					lra(z->parent->parent);
				}
			}
			else {
				y = z->parent->parent->right;
				if (y != nullptr && y->c == red) {
					z->parent->c = black;
					y->c = black;
					z->parent->parent->c = red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						lra(z);
					}
					z->parent->c = black;
					z->parent->parent->c = red;
					rra(z->parent->parent);
				}
			}
			if (z == ah) { break; }
		}
		ah->c = black;
	}
	//displaying stuff
	void displaybyID(ostream& output, string i) {
		string last2 = i.substr(i.length() - 2);
		int num;
		stringstream(last2) >> num;

		if (ah == nullptr) {
			return;
		}
		else {
			Assignee* current = ah;
			while (current != nullptr) {
				if (current->id == num) {

					output << "Name: " << current->firstname << " " << current->lastname << ", Address: " << current->address << ", DOB: " << current->dob << ", Assignee ID: " << current->ID << "\n";
					return;
				}
				else if (num > current->id) {
					if (current->right != nullptr) { current = current->right; }
					else { return; }
				}
				else if (num < current->id) {
					if (current->left != nullptr) { current = current->left; }
					else { return; }
				}



			}
			return;
		}
	}
	void displaybyname(ostream& output, string n1, string n2) {
		Assignee* ptr = ah;
		dbnr(ptr, output, n1, n2);
	}
	void dbnr(Assignee* node, ostream& o, string n1, string n2) {
		if (node == nullptr) {
			return;
		}
		dbnr(node->left, o, n1, n2);
		if (node->firstname == n1 && node->lastname == n2) {
			o << "Name: " << node->firstname << " " << node->lastname << ", Address: " << node->address << ", DOB: " << node->dob << ", Assignee ID: " << node->ID << "\n";
		}
		dbnr(node->right, o, n1, n2);
	}
	
	
	void awni(Assignee* node, ostream& o) {
		if (node == nullptr) {
			return;
		}
		awni(node->left, o);
		if (node->taskass == false) {
			o << "Name: " << node->firstname << " " << node->lastname << ", Address: " << node->address << ", DOB: " << node->dob << ", Assignee ID: " << node->ID << "\n";
		}
		awni(node->right, o);
	}
	void AssigneeWithNoTask(ostream& output) {
		Assignee* ptr = ah;
		awni(ptr, output);
	
	}
	void DisplayAssignee(ostream& output) {
		Assignee* ptr = ah;
		displayassigneehelper(ptr, output);
	}
	
	void AssigneeInOrder(ostream& output) {
		Assignee* ptr = ah;
		displayassigneeinorderhelper(ptr, output);
	}
	void displayassigneehelper(Assignee* node, ostream& o) {
		if (node != nullptr) {
			displayassigneehelper(node->left, o);
			o << "Name: " << node->firstname << " " << node->lastname << ", Address: " << node->address << ", DOB: " << node->dob << ", Assignee ID: " << node->ID << "\n";
			displayassigneehelper(node->right, o);
			
		}
		

	}
	void displayassigneeinorderhelper(Assignee* node, ostream& o) {
		if (node != nullptr) {
			displayassigneeinorderhelper(node->left, o);
			
			o << node->ID <<"("<<node->c<<")\n";
			displayassigneeinorderhelper(node->right, o);

		}

	}
	//searching stuff

	Assignee* searchbyid(string identity) {
		string last2 = identity.substr(identity.length() - 2);
		int num;
		stringstream(last2) >> num;

		if (ah == nullptr) {
			return nullptr;
		}
		else {
			Assignee* current = ah;
			while (current != nullptr) {
				if (current->id == num) {


					return current;
				}
				else if (num > current->id) {
					if (current->right != nullptr) { current = current->right; }
					else { return nullptr; }
				}
				else if (num < current->id) {
					if (current->left != nullptr) { current = current->left; }
					else { return nullptr; }
				}



			}
			return nullptr;
		}

	}
	//rotations
	void lra(Assignee* x) {


		Assignee* y = x->right;



		x->right = y->left;

		if (y->left != nullptr) {
			y->left->parent = x;
		}

		if (x->parent == nullptr) {
			cout << x->firstname << endl;
			y->parent = nullptr;
			ah = y;
		}
		else if (x->parent != nullptr) { y->parent = x->parent; 


		if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
	}

		y->left = x;
		x->parent = y;
	}


	void rra(Assignee*& x) {
		Assignee* y = x->left;
		x->left = y->right;

		if (y->right != nullptr) {
			y->right->parent = x;
		}
		if (x->parent == nullptr) {
			y->parent = nullptr;
			ah = y;
		}
		else if (x->parent != nullptr) { y->parent = x->parent; 
		if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
	}
		y->right = x;
		x->parent = y;
	}
	//deletion code of assignee
	void DeleteAssignee(string i) {
		
		Assignee* ptr = searchbyid(i);
		if (ptr->taskass == true) {
			return;
		}
		deleteNodeHelper(ptr);
	}
	//void deleteNodeHelper(Assignee* node) {
	//	// find the node containing key
	//	Assignee* z = node;
	//	Assignee* x = nullptr;
	//	Assignee* y = nullptr;

	//	y = z;
	//	color y_original_color = y->c;
	//	if (z->left == nullptr) {
	//		x = z->right;
	//		rbTransplant(z, z->right);
	//	}
	//	else if (z->right == nullptr) {
	//		x = z->left;
	//		rbTransplant(z, z->left);
	//	}
	//	else {
	//		y = minimum(z->right);
	//		y_original_color = y->c;
	//		x = y->right;
	//		if (y->parent == z) {
	//			x->parent = y;
	//		}
	//		else {
	//			rbTransplant(y, y->right);
	//			y->right = z->right;
	//			y->right->parent = y;
	//		}

	//		rbTransplant(z, y);
	//		y->left = z->left;
	//		y->left->parent = y;
	//		y->c = z->c;
	//	}
	//	delete z;
	//	if (y_original_color == black) {
	//		fixDelete(x);
	//	}
	//}

	//Assignee* minimum(Assignee* node) {
	//	while (node->left != nullptr) {
	//		node = node->left;
	//	}
	//	return node;
	//}
	void deleteNodeHelper(Assignee* node) {
		// find the node containing key
		Assignee* z = node;
		Assignee* x = nullptr;
		Assignee* y = nullptr;

		y = z;
		color y_original_color = y->c;
		if (z->left == nullptr) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == nullptr) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = maximum(z->left);  // Change to find maximum instead of minimum
			y_original_color = y->c;
			x = y->left;           // Change to left child instead of right child
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->left);  // Change to left child instead of right child
				y->left = z->left;
				y->left->parent = y;
			}

			rbTransplant(z, y);
			y->right = z->right;
			y->right->parent = y;
			y->c = z->c;
		}
		delete z;
		if (y_original_color == black) {
			fixDelete(x);
		}
	}

	Assignee* maximum(Assignee* node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	void rbTransplant(Assignee* u, Assignee* v) {
		if (u->parent == nullptr) {
			ah = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		if (v != nullptr) {
			v->parent = u->parent;
		}
		else {
			// Update ah if v is nullptr (i.e., if u was the root)
			ah = u->parent;
		}
	}


	void fixDelete(Assignee* x) {
		Assignee* s = nullptr;
		if (x == nullptr) { return; }
		while (x != ah && x->c == black) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->c == red) {
					// case 3.1
					s->c = black;
					x->parent->c = red;
					lra(x->parent);
					s = x->parent->right;
				}

				if (s->left->c == black && s->right->c == black) {
					// case 3.2
					s->c = red;
					x = x->parent;
				}
				else {
					if (s->right->c == black) {
						// case 3.3
						s->left->c = black;
						s->c = red;
						rra(s);
						s = x->parent->right;
					}

					// case 3.4
					s->c = x->parent->c;
					x->parent->c = black;
					s->right->c = black;
					lra(x->parent);
					x = ah;
				}
			}
			else {
				s = x->parent->left;
				if (s->c == red) {
					// case 3.1
					s->c = black;
					x->parent->c = red;
					rra(x->parent);
					s = x->parent->left;
				}

				if (s->right->c == black && s->left->c == black) {
					// case 3.2
					s->c = red;
					x = x->parent;
				}
				else {
					if (s->left->c == black) {
						// case 3.3
						s->right->c = black;
						s->c = red;
						lra(s);
						s = x->parent->left;
					}

					// case 3.4
					s->c = x->parent->c;
					x->parent->c = black;
					s->left->c = black;
					rra(x->parent);
					x = ah;
				}
			}
		}
		x->c = black;
	}
//********************************************************
	//insertion
	void addTask(int id, string d, int pl, string aid) {
		taskcount++;
		Task* z = bstinsertionT(id, d, pl, aid);
		
		Assignee* temp = searchbyid(aid);
		temp->taskass = true;

		if (z->parent == nullptr) {
			return;
		}
		if (z->parent->parent == nullptr) {
			return;
		}
		cout << "here1" << endl;
		fixinsetrbT(z);
	
	}
	Task* bstinsertionT(int id, string d, int pl, string aid) {
		Task* newt = new Task(id, d, pl, aid);
		if (th == nullptr) {
			th = newt;
			th->c = black;
		}
		else {
			Task* current = th;
			while (current != nullptr) {
				if (newt->prilev < current->prilev) { // Left subtree
					if (current->left) { current = current->left; }
					else {
						current->left = newt;
						newt->parent = current;
						break;
					}
				}
				else if (newt->prilev >= current->prilev) { // Right subtree
					if (current->right) current = current->right;
					else {
						current->right = newt;
						newt->parent = current;
						break;
					}
				}

			}
		}
		return newt;
	}

	void fixinsetrbT(Task* z) {
		Task* y = nullptr;
		while (z->parent != nullptr && z->parent->c == red) {
			if (z->parent == z->parent->parent->right) {
				y = z->parent->parent->left;
				if (y != nullptr && y->c == red) {
					z->parent->c = black;
					y->c = black;
					z->parent->parent->c = red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						rrt(z);
					}
					z->parent->c = black;
					z->parent->parent->c = red;
					lrt(z->parent->parent);
				}
			}
			else {
				y = z->parent->parent->right;
				if (y != nullptr && y->c == red) {
					z->parent->c = black;
					y->c = black;
					z->parent->parent->c = red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right) {
						z = z->parent;
						lrt(z);
					}
					z->parent->c = black;
					z->parent->parent->c = red;
					rrt(z->parent->parent);
				}
			}
			if (z == th) { break; }
		}
		th->c = black;
	}
	//required functions
	void ShiftTask(string id1, string id2) {

		Assignee* A1 = searchbyid(id1);
		Task* ptr = th;
		Task* T1 = searchtaskbyass(ptr, id1);
		Assignee* A2 = searchbyid(id2);
		
		
		T1->assid = id2;
		A2->taskass = true;
		A1->taskass = false;
		

	}
	void completeTask(int id) {
		Task* ptr = th;
		Task* t1=searchtaskbyid(ptr,id);
		t1->status = 1;
		Assignee* A1 = searchbyid(t1->assid);
		A1->taskass = false;
	}
	void updateTaskPriority(int id1, int p) {
		Task* ptr = th;
		Task* t1 = searchtaskbyid(ptr, id1);
		t1->prilev = p;
		
	}
	void findHighestPriorityTask(ostream& output) {
		
		
		Task* ptr = th;
		Task* hd = th;
		if (ptr == nullptr) { return; }
		while (ptr->left != nullptr) {
			ptr = ptr->left;
			cout << "hereeeeee" << endl;
		}
		
		highestpriorityhelper(th, ptr->prilev,output);
		
	}
	void highestpriorityhelper(Task* ptr,int val,ostream& o) {
		if (ptr == nullptr) {
			return;
		}
		highestpriorityhelper(ptr->left, val,o);
		if (ptr->prilev == val) {
			Assignee* name = searchbyid(ptr->assid);
			o << "Highest Priority Task: ";
			o << "Task ID: " << ptr->ID << ", Description: " << ptr->dcrp << ", Priority: " << ptr->prilev << ", Assignee: " << name->firstname << " (" << ptr->assid << ")\n";
		}
		highestpriorityhelper(ptr->right, val, o);
	
	}
	void findTasksByAssignee(string id, ostream& output) {
		Task* t1 = th;
		Assignee* a1 = searchbyid(id);
		output << "Tasks Assigned to \"" << a1->firstname <<" (" << id << ")\":\n";
		findTaskshelper(th, id, output);
	}
	void findTaskshelper(Task* ptr, string id,ostream& o) {
		if (ptr == nullptr) {
			return;
		}
		findTaskshelper(ptr->left, id,o);
		if (ptr->assid == id) {
			Assignee* name = searchbyid(ptr->assid);
			o << "Task ID: " << ptr->ID << ", Description: " << ptr->dcrp << ", Priority: " << ptr->prilev << ", Assignee: " << name->firstname << " (" << ptr->assid << ")\n";
		}
		findTaskshelper(ptr->right, id,o);
	}
	void countTotalTasks(ostream& output) {
		output << "Total Tasks in the System: " << taskcount << "\n";
	}
	void displayCompletedTasks(ostream& output) {
		Task* ptr = th;
		output << "Completed Tasks:\n";
		printComTaskhelper(ptr, output);
	
	}
	void printComTaskhelper(Task* r, ostream& o) {
		if (r == nullptr) {
			return;
		}

		printComTaskhelper(r->left, o);
		if (r->status == 1) {
			Assignee* name = searchbyid(r->assid);
			o << "Task ID: " << r->ID << ", Description: " << r->dcrp << ", Priority: " << r->prilev << ", Assignee: " << name->firstname << " (" << r->assid << ")\n";
		}
		printComTaskhelper(r->right, o);

	}
	void searchTasksByPriorityRange(int pl1, int pl2, ostream& output) {
		Task* t1 = th;
		output << "Tasks within Priority Range ("<<pl1<<" to "<<pl2<<"):\n";
		searchTaskByPR(th, pl1, pl2, output);
	}
	void searchTaskByPR(Task* ptr, int i1, int i2, ostream& o) {
		if (ptr == nullptr) {
			return;
		}
		searchTaskByPR(ptr->left, i1,i2, o);
		if (ptr->prilev >= i1 && ptr->prilev <= i2) {
			Assignee* name = searchbyid(ptr->assid);
			o << "Task ID: " << ptr->ID << ", Description: " << ptr->dcrp << ", Priority: " << ptr->prilev << ", Assignee: " << name->firstname << " (" << ptr->assid << ")\n";
		}
		searchTaskByPR(ptr->right, i1,i2,o);
	
	}
	void PrintTreeInorder(ostream& output) {
		Task* ptr = th;
		displaytaskinorderhelper(ptr, output);
	}
	void displaytaskinorderhelper(Task* node, ostream& o) {
		if (node != nullptr) {
			displaytaskinorderhelper(node->left, o);
			string colo = node->c == 0 ? "red" : "black";
			o << node->ID << " (" << colo << ")\n";
			displaytaskinorderhelper(node->right, o);

		}

	}
	
	//searching
	Task* searchtaskbyass(Task* node,string id) {
		if (node == nullptr) {
			return nullptr;
		}
		searchtaskbyass(node->left,id);
		if (node->assid == id ) {
			return node;
		}
		searchtaskbyass(node->right,id);
	
	}
	Task* searchtaskbyid(Task* node, int id) {
		if (node == nullptr) {
			return nullptr;
		}
		searchtaskbyid(node->left, id);
		if (node->ID == id) {
			return node;
		}
		searchtaskbyid(node->right, id);

	}
	//printing
	void printTaskQueue(ostream& output) {
		Task* ptr = th;
		printTaskhelper(ptr, output);
	
	}
	void printTaskhelper(Task* r, ostream& o) {
		if (r == nullptr) {
			return;
		}
		
		printTaskhelper(r->left,o);
		if (r->status == 0) {
			Assignee* name = searchbyid(r->assid);
			o << "Task ID: " << r->ID << ", Description: " << r->dcrp << ", Priority: " << r->prilev << ", Assignee: " << name->firstname << " (" << r->assid << ")\n";
		}
		printTaskhelper(r->right, o);
	
	}
	//rotations:
	void lrt(Task* x) {


		Task* y = x->right;



		x->right = y->left;

		if (y->left != nullptr) {
			y->left->parent = x;
		}

		if (x->parent == nullptr) {
			
			y->parent = nullptr;
			th = y;
		}
		else if (x->parent != nullptr) {
			y->parent = x->parent;


			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}

		y->left = x;
		x->parent = y;
	}


	/*void rrt(Task*& x) {
		Task* y = x->left;
		x->left = y->right;

		if (y->right != nullptr) {
			y->right->parent = x;
		}
		if (x->parent == nullptr) {
			y->parent = nullptr;
			th = y;
		}
		else if (x->parent != nullptr) {
			y->parent = x->parent;
			if (x == x->parent->right) {
				x->parent->right = y;
			}
			else {
				x->parent->left = y;
			}
		}
		y->right = x;
		x->parent = y;
	}*/

	void rrt(Task* x) {
		Task* y = x->left;
		x->left = y->right;
		if (y->right != NULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->th = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
	//deletion of task
	void deleteTask(int i) {

		Task* ptr = th;
		Task* t1 = searchtaskbyid(ptr, i);

		deleteTaskNodeHelper(t1);
	}

	void deleteTaskNodeHelper(Task* node) {
		// find the node containing key
		Task* z = node;
		Task* x = nullptr;
		Task* y = nullptr;

		y = z;
		color y_original_color = y->c;
		if (z->left == nullptr) {
			x = z->right;
			rbtransplant(z, z->right);
		}
		else if (z->right == nullptr) {
			x = z->left;
			rbtransplant(z, z->left);
		}
		else {
			y = Maximum(z->left);  // Change to find maximum instead of minimum
			y_original_color = y->c;
			x = y->left;           // Change to left child instead of right child
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbtransplant(y, y->left);  // Change to left child instead of right child
				y->left = z->left;
				y->left->parent = y;
			}

			rbtransplant(z, y);
			y->right = z->right;
			y->right->parent = y;
			y->c = z->c;
		}
		delete z;
		if (y_original_color == black) {
			fixDeleteT(x);
		}
	}

	Task* Maximum(Task* node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	void rbtransplant(Task* u, Task* v) {
		if (u->parent == nullptr) {
			th = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		if (v != nullptr) {
			v->parent = u->parent;
		}
		else {
			// Update ah if v is nullptr (i.e., if u was the root)
			th = u->parent;
		}
	}


	void fixDeleteT(Task* x) {
		Task* s = nullptr;
		if (x == nullptr) { return; }
		while (x != th && x->c == black) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->c == red) {
					// case 3.1
					s->c = black;
					x->parent->c = red;
					lrt(x->parent);
					s = x->parent->right;
				}

				if (s->left->c == black && s->right->c == black) {
					// case 3.2
					s->c = red;
					x = x->parent;
				}
				else {
					if (s->right->c == black) {
						// case 3.3
						s->left->c = black;
						s->c = red;
						rrt(s);
						s = x->parent->right;
					}

					// case 3.4
					s->c = x->parent->c;
					x->parent->c = black;
					s->right->c = black;
					lrt(x->parent);
					x = th;
				}
			}
			else {
				s = x->parent->left;
				if (s->c == red) {
					// case 3.1
					s->c = black;
					x->parent->c = red;
					rrt(x->parent);
					s = x->parent->left;
				}

				if (s->right->c == black && s->left->c == black) {
					// case 3.2
					s->c = red;
					x = x->parent;
				}
				else {
					if (s->left->c == black) {
						// case 3.3
						s->right->c = black;
						s->c = red;
						lrt(s);
						s = x->parent->left;
					}

					// case 3.4
					s->c = x->parent->c;
					x->parent->c = black;
					s->left->c = black;
					rrt(x->parent);
					x = th;
				}
			}
		}
		x->c = black;
	}
};