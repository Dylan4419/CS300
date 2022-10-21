//============================================================================
// Name        : FinalProject.cpp
// Author      : Dylan Coulter
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//Please note Resources below are included due to the fact that they were used to complete the BST assignment and reflected on for this project
// Resource:https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
// Resource:https://www.tutorialspoint.com/cplusplus-program-to-perform-postorder-recursive-traversal-of-a-given-binary-tree
// Resource:https://www.programiz.com/dsa/tree-traversal
// Resource:https://www.techiedelight.com/postorder-tree-traversal-iterative-recursive/
// Resource:https://stackoverflow.com/questions/73645060/created-a-program-for-binary-tree-traversal-inorder-and-postorder-print-wrong-s
// Resource:https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
// Resource:https://www.tutorialspoint.com/deletion-in-a-binary-tree-in-cplusplus-program
// Resource:https://www.tutorialspoint.com/binary-search-tree-delete-operation-in-cplusplus
// Resource:https://www.techiedelight.com/deletion-from-bst/
// Resource:https://stackoverflow.com/questions/31715769/c-delete-a-node-from-binary-search-tree
//Please note the Resource below were Utilized to complete this assignment
// Resource:https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/
// Resource:https://stackoverflow.com/questions/70281393/how-to-store-an-instance-of-class-in-a-vector
// Resource:https://stackoverflow.com/questions/42797819/iterating-values-into-a-vector-while-reading-in-a-file-using-getline
// Resource:https://stackoverflow.com/questions/61403356/c-csv-getline
// Resource:https://stackoverflow.com/questions/67938586/how-to-prevent-wrong-user-input-on-a-variable
// Resource:https://stackoverflow.com/questions/63667334/c-using-a-binary-search-tree-to-sort-a-file-of-numbers
//============================================================================
#include <iostream>
#include <fstream>
#include "CSVparser.hpp"
#include <vector>
#include <string.h>
#include <string>
#include <CoreWindow.h>
using namespace std;
//==============================================================================//
// Global definitions visible to all methods and classes
//==============================================================================//

//Every course contains a course number, course name, and
//also a vector to hold the prerequisites the course may have
struct Course {
	string courseNumber;
	string nameOfCourse;
	vector<string> preRequisites;
	Course() {}
};

//Every node that is in the BST will contain the course information
//There will also be child nodes to the left and right
struct Node {
	Course course;
	Node* left;
	Node* right;
	Node() {
		left = nullptr;
		right = nullptr;
	}
	Node(Course aCourse) : Node() {
		this->course = aCourse;
	}
};
//==============================================================================//
// CourseTree Class Definition
//==============================================================================//

//Here we define a class that will be containing data members and methods
// to implement into the BST
class CourseTree {
private:
	Node* root;
	void newNode(Node* node, Course course);
	void inOrder(Node* node);
	void printCourseInfo(Node* node, string courseNumber);
public:
	CourseTree();
	virtual ~CourseTree();
	void DeleteRec(Node* node);
	void Insert(Course course);
	int NumPrereqCourses(Course course);
	void InOrder();
	void PrintCourseInfo(string courseNumber);
};
//This is the default constructor 
//Here we construct the BST and initialize the root
CourseTree::CourseTree() {
	root = nullptr;
}
//Recurse from root deleting every node
CourseTree::~CourseTree() {
	DeleteRec(root);
}
//This is where the program will delete the BST
//nodes recursively and this will be used by the deconstructor
void CourseTree::DeleteRec(Node* node) {
	if (node) {
		DeleteRec(node->left);
		DeleteRec(node->right);
		delete node;
	}
}
//Insertion of a node into the BST
void CourseTree::Insert(Course course) {
	//If statement if the root is not initialized 
	if (root == nullptr)
		//This will initialize it with the current course info
		root = new Node(course);
	//Else the node will be sent to the newNode method 
	//then will be added to the BST
	else
		this->newNode(root, course);
}
//Program will return the number of prerequisites the course has
int CourseTree::NumPrereqCourses(Course course) {
	int numPrereq = 0;
	for (unsigned int i = 0; i < course.preRequisites.size(); i++) {
		if (course.preRequisites.at(i).length() > 0)
			numPrereq++;
	}
	return numPrereq;
}
//The program will the root of the BST to the private method
void CourseTree::InOrder() {
	this->inOrder(root);
}
//This iwll pass the root of the BST and the course ID to be searched, 
//and if found it will be displayed
void CourseTree::PrintCourseInfo(string courseNumber) {
	this->printCourseInfo(root, courseNumber);
}
//This uses the the public insertion method
//This will also set the correct alphanumeric location for the courses 
//If current child node is nullptr the node will be added to BST
//Else the BST will keep being traversed until nullptr is found
void CourseTree::newNode(Node* node, Course course) {
	//If current course number is less than the current node's course number
	if (node->course.courseNumber.compare(course.courseNumber) > 0) {
		if (node->left == nullptr)
			node->left = new Node(course);
		else
			this->newNode(node->left, course);
	}
	//If the current course number is greater than or equal to the current node's course number
	else {
		if (node->right == nullptr)
			node->right = new Node(course);
		else
			this->newNode(node->right, course);
	}
}
//The program will recursively print the courses in order
void CourseTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->course.courseNumber << ", " << node->course.nameOfCourse << endl;
		inOrder(node->right);
	}
	return;
}
//Program outputs a single course including all required prerequisites
void CourseTree::printCourseInfo(Node* curr, string courseNumber) {
	//The program will travers the BST until matching course number found or the end is reached 
	while (curr != nullptr) {
		//If the passed course number is a match to the current cours number
		if (curr->course.courseNumber.compare(courseNumber) == 0) {
			//The program will output the course and retrieve the number of prerequisites
			cout << endl << curr->course.courseNumber << ", " << curr->course.nameOfCourse << endl;
			unsigned int size = NumPrereqCourses(curr->course);
			cout << "Prerequisite(s): ";
			//If the course has existing prerequisites the program will properly format and out each
			unsigned int i = 0;
			for (i = 0; i < size; i++) {
				cout << curr->course.preRequisites.at(i);
				if (i != size - 1)
					cout << ", ";
			}
			// If the course has no required prerequisites,
			//output "No prerequisites required." and then return to stop the search
			if (i == 0)
				cout << "No prerequisites required.";
			cout << endl;
			return;
		}
		//Else If the passed course number is less than the current course number traverse left
		else if (courseNumber.compare(curr->course.courseNumber) < 0)
			curr = curr->left;
		//Else If the passed course number is greater than the current course number traverse right
		else
			curr = curr->right;
	}
	//If program reaches nullptr and no course has been found output to user
	cout << "Course " << courseNumber << " not found." << endl;
}
//==============================================================================//
// Static methods used for testing
//==============================================================================//
 bool loadCourses(string csvPath, CourseTree* coursesTree) {

	//Program will open the course file and seperate each line then insert in the BSt
	try {
		ifstream txtFile(csvPath);
		if (txtFile.is_open()) {
			while (!txtFile.eof()) {
				//The vector will hold each csv that the course contains
				vector<string> courseInformation;
				string courseTxt;
				getline(txtFile, courseTxt);
				while (courseTxt.length() > 0) {
					//The program will get a substring of each course and then add it to the vector
					//Then delete from the string
					unsigned int comma = courseTxt.find(',');
					if (comma < 100) {
						courseInformation.push_back(courseTxt.substr(0, comma));
						courseTxt.erase(0, comma + 1);
					}
					// The last course will be added after the final comma
					else {
						courseInformation.push_back(courseTxt.substr(0,
							courseTxt.length()));
						courseTxt = "";
					}
				}
				//The program will seperate values into a course and then insert into the BST
				Course course;
				course.courseNumber = courseInformation[0];
				course.nameOfCourse = courseInformation[1];
				for (unsigned int i = 2; i < courseInformation.size(); i++) {
					course.preRequisites.push_back(courseInformation[i]);
				}
				coursesTree->Insert(course);
			}
			//Close file
			txtFile.close();
			return true;
		}
	}
	catch (csv::Error& e) {
		cerr << e.what() << std::endl;
	}
	return false;
}
/**
The one and only main() method
**/
int main(int argc, char* argv[]) {
	//Here the program will process command line argument
	string csvPath, courseId;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	case 3:
		csvPath = argv[1];
		courseId = argv[2];
		break;
	default:
		csvPath = "CourseFile.txt";
		break;
	}
	// Define BST
	CourseTree* coursesTree = nullptr;
	//Welcome user to the course planner
	cout << "\nWelcome to the course planner!\n" << endl;
	// Utilizing a string for user input choice and then converting the first 
	//character to an int will help prevent invalid data
	string choice = "0";
	int userInput = choice[0] - '0';
	//While user input not 9
	while (userInput != 9) {
		cout << "1. Load Data Structure" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "9. Exit" << endl;
		cout << "\nWhat would you like to do? ";
		cin >> choice;
		// checks to see if user input is a double digit 
		if (choice.length() == 1)
			userInput = choice[0] - '0';
		else
			userInput = 0;
		bool loadComplete = 1;
		switch (userInput) {
			// Instantiate the Binary Search Tree and get the file name
			//Then load courses into Binary Search Tree
		case 1:
			if (coursesTree == nullptr)
				coursesTree = new CourseTree();
			if (csvPath.length() == 0) {
				cout << "Enter the file name that contains the course data: ";
				cin >> csvPath;
			}
			// If the course file was opened successfully output "All courses have been loaded"
			loadComplete = loadCourses(csvPath, coursesTree);
			if (loadComplete)
				cout << "All Courses have been loaded.\n" << endl;
			else
				cout << "Sorry, File not found.\n" << endl;
			break;
			//The program will validate that the Binary Search Tree exists
				//Then print a sample schedule
		case 2:
			if (coursesTree != nullptr && loadComplete) {
				cout << "Here is a sample schedule:\n" << endl;
				coursesTree->InOrder();
				cout << endl;
			}
			else
				cout << "Load courses first - option 1\n" << endl;
			break;
			//The program will validate that the Binary Search Tree exists
				//Then search and output the course information
		case 3:
			if (coursesTree != nullptr && loadComplete) {
				if (courseId.length() == 0) {
					cout << "What course do you want to know about? ";
					cin >> courseId;
					for (auto& userChoice : courseId) userChoice =
						toupper(userChoice);
				}
				coursesTree->PrintCourseInfo(courseId);
				cout << endl;
			}
			else
				cout << "Load courses first - option 1\n" << endl;
			courseId = "";
			break;
			//If user inputs and invalid option 
		default:
			if (userInput != 9)
				cout << choice << " is not a valid option\n" << endl;
			break;
		}
	}
	cout << "\nThank you for using the course planner!" << endl;
	return 0;
}




