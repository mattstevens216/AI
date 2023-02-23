//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: May 1, 2018
//hw4pr2.cpp




#include <iostream>
#include <fstream>
#include <vector>


int main(){
	std::vector<std::pair<std::string, std::string> > compileOrder;
	std::vector<std::pair<std::string, std::string> > sortedOrder;
	std::vector<std::pair<std::string, std::string> > temp;
	std::vector<std::string> completeOrder;
	std::string first;
	std::string second;
	
	printf("please enter an acyclic path!\n");
	printf("enter the compiler package (first word): ");
	int numRootChild;
	numRootChild = 0;

	//obtain input and set dependencies
	while(std::getline(std::cin,first)){
		printf("enter the package it is dependent on (second word): ");
		std::getline(std::cin,second);

		//temp pair
		std::pair<std::string, std::string> p;
		p = std::make_pair(first, second);
		compileOrder.push_back(p);
		
		printf("enter the compiler package (first word): ");
	}
	
	std::cout << "Done receiving input." << std::endl;
	std::cout << "Beginning Dependency sorting" << std::endl;
	
	for(int i = 0; i < compileOrder.size(); i++){
		std::string root;
		bool isRoot;
		
		isRoot = true;
		root = compileOrder[i].first;
		for(int j = 0; j < compileOrder.size(); j++){
			if(root == compileOrder[j].second){
				isRoot = false;
			}
			else{
		
			}
		}
		
		if(isRoot){
			//root becomes first element
			sortedOrder.push_back(compileOrder[i]);
			numRootChild++;
		}	
	}
	
	//begin with root
	std::string current;
	current = sortedOrder[0].first;
	int children;
	int position;
	position = 0;
	//set root dependencies in order
	while(sortedOrder.size() != compileOrder.size()){
		children = 0;
		//for the input size
		for(int i = 0; i < compileOrder.size(); i++){
			//find current node
			if(compileOrder[i].first == current){
				bool independent;
				independent = true;
				//find all the seconds that are dependent on something else
				for(int j = 0; j < compileOrder.size(); j++){
					if(compileOrder[i].second == compileOrder[j].first){
						independent = false;
						children++;
						sortedOrder.push_back(compileOrder[j]);
					}
				}
				if(independent){
					children++;
				}

			}
		}
		position = position + children;

		current = sortedOrder[position].first;
		
	}
	
	//remove duplicates
	for(int i = sortedOrder.size()-1; i >= 0; i--){
		bool contains;
		contains = false;
		if(completeOrder.empty()){
			completeOrder.push_back(sortedOrder[i].second);
		}
		for(int j = 0; j < completeOrder.size(); j++){
			if(completeOrder[j] == sortedOrder[i].second){
				contains = true;
			}
		}
		
		if(!contains){
			completeOrder.push_back(sortedOrder[i].second);
		}
	}
	
	std::cout << "done removing duplicates" << std::endl;
	std::cout << "Compile in numerical order below: " << std::endl;
	
	for(int i = 0; i < completeOrder.size(); i++){
		std::cout << i+1 << ". " << completeOrder[i] << std::endl;
	}
	std::cout << "Lastly, compile " << sortedOrder[0].first << std::endl;
	
	return 0;
}