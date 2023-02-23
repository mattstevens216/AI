//Matthew Stevens
//924000693
//CSCE 420
//Due: March 5, 2018
//hw2pr2.cpp

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

/*begin structures here*/

//node w\ children
struct node {
	int winValue;
	bool isRoot;
	std::vector<node*> children;
};

//constructs a new node with winValue
node *makeTreeNode(int nodeValue){
	node *curr = new node();
	curr->winValue = nodeValue;
	curr->isRoot = false;
	return curr;
}

//max def for min to use
int playerMax(node*);

/*begin functions here*/
//starts with root
void parseInput(std::string treeInput, struct node **anyNode){
	//index of parent 
	int currDepth = 0;
	string temp = treeInput;
	
	//length of input
	for(int i = 0; i < temp.size(); i++){
		string childInput;
		//starting first depth
		if(temp[i] == '('){
			currDepth++;
			i++;
		}
		if(temp[i] == ')'){
			currDepth--;
			i++;
		}
		//if it is the correct depth
		if(currDepth > 0){
			childInput.push_back(temp[i]);
		}
					
		if(currDepth == 0){
			//when there is a child with children and it is not the root node
			if(!((*anyNode)->isRoot) && (childInput.size() > 0)){
				string child;
				node *tempNode = makeTreeNode(0);
				parseInput(childInput,&tempNode);
				//tempnode will have contents now
				(*anyNode)->children.push_back(tempNode);
				
				if(temp[i] == ')'){
					//eat the end parentheses
					i++;
				}
				//reset child input
				childInput = "";
			}
			//default string storage of child until it hits a comma
			if(childInput.size() == 0){
				string child;
				while(temp[i] != ','){
					child.push_back(temp[i]);
					i++;
				}
				int value = stoi(child);
				node *childNode = makeTreeNode(value);
				(*anyNode)->children.push_back(childNode);
			}
			//if it is the root node
			if(((*anyNode)->isRoot) && (childInput.size() > 0)){
				parseInput(childInput,&(*anyNode));
				
				if(temp[i] == ')'){
					//eat the end parentheses
					i++;
				}
				//reset child input
				childInput = "";
			}
		}
	}
}
		

//obtains the minimum value move from the set of the possible moves that max can do
int playerMin(node *current) {
	node *curr = current;
	//set to a high number for comparison
	int smallest = 999999;
	//will find the max values for each of the children 
	for(int i = 0; i < curr->children.size(); i++){
		curr->children[i]->winValue = playerMax(curr->children[i]);
	}
	for(int i = 0; i < curr->children.size(); i++){
		if(curr->children[i]->winValue < smallest){
			smallest = curr->children[i]->winValue;
			curr->winValue = smallest;
		}
	}	

	return curr->winValue;
}

//obtains the maximum value move from the set of possible moves that min can do
int playerMax(node *current) {
	node *curr = current;
	//set to a low number for comparison
	int largest = -999999;
	//will find the min value for each of the children
	for(int i = 0; i < curr->children.size(); i++){
		curr->children[i]->winValue = playerMin(curr->children[i]);
	}
	//find the largest of the children
	for(int i = 0; i < curr->children.size(); i++){
		if(curr->children[i]->winValue > largest){
			largest = curr->children[i]->winValue;
			curr->winValue = largest;
		}
	}
	
	return curr->winValue;
}

int main(int argc, char *argv[]) {
	
	//initalize root with value 0 (will be replaced later w\ actual value)
	node *root = makeTreeNode(0);
	root->isRoot = true;
	string treeInput;

	if (argc == 1) {
		cout << "Please enter input during execution in the format: ./progName 'input' where ' represents double quotes" << endl;
		exit(0);
	}
	else if (argc == 2) {
		treeInput = argv[1];
	}
	else {
		cout << "You have entered too many commands, please only provide the input upon execution." << endl;
		exit(0);
	}
	//separate input into nodes
	parseInput(treeInput, &root);

	
	playerMin(root);

	cout << "The best value for min as the root is: " << root->winValue << endl;


return 0;
}