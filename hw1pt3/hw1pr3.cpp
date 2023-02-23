//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: February 12, 2018
//hw1pr3.cpp

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <stack>

void solve(std::vector<int> eightPuzzle, std::vector<int> solutionPuzzle) {
	//bfs (parent node explores all children before going deeper. Only 10 moves or less) using queues
	//can move the blank (0) up down left or right each action increments the stepCounter
	//checks if it is completed
	//make a queue for the possible moves
	std::queue<std::vector<int>> possibleMoveList;
	//make a queue for the level and previous moves
	std::queue<std::pair<int, int> > previousAndDepth;
	//vectors for pruning
	std::vector<int> allPossibleMoves;
	std::vector<std::vector<int> > allPossibleStates;

	bool stackComplete = false;

	int stateCounter = 0;
	int position;
	int depth;
	int move;

	//bfs takes fifo order (thats why we use a queue) and pops the first element (priority) of the moveset
	//populate with the eightpuzzle before making any moves
	possibleMoveList.push(eightPuzzle);

	//makes a pair at depth 0 and move 0
	previousAndDepth.push(std::make_pair(0, 0));

	//start bfs
	while (!possibleMoveList.empty()) {
		//obtains a move from all possible moves
		 std::vector<int> frontState = possibleMoveList.front();

		 stateCounter++;
		 possibleMoveList.pop();
		 
		 //obtains a move at the depth
		 std::pair<int, int> frontDepthMove = previousAndDepth.front();
		 depth = frontDepthMove.first;
		 move = frontDepthMove.second;
		 previousAndDepth.pop();

		 //find our position
		 for (int i = 0; i < frontState.size(); i++) {
			 if (frontState.at(i) == 0) {
				 position = i;
			 }
		 }

		 //store current move and current state
		 allPossibleMoves.push_back(move);
		 allPossibleStates.push_back(frontState);

		 //if it takes more than 10 moves, exit the program because there will be no moves better than 10 at that point
		 if (depth == 10) {
			 exit(0);
		 }
		 //take the moves around 0 and evaluate (at most 4 possible moves)
		 for (int i = 0; i < 4; i++) {
			 //possible right move if it didnt move left (cant move right in last column)
			 if (i = 0) {
				 if (((position != 2) || (position != 5) || (position != 8)) && (move != 2)) {
					 //make a possible right move and swap values
					 frontState.at(position) = frontState.at(position + 1);
					 frontState.at(position+1) = 0;
					 //checks for solution
					 if (frontState == solutionPuzzle) {
						 while (!possibleMoveList.empty()) {
							 possibleMoveList.pop();
						 }
						 //store the move into the move list
						 allPossibleMoves.push_back(0);
						//store the state into the state list
						 allPossibleStates.push_back(frontState);
						 break;
					 }
					 //push onto the possible move list
					 possibleMoveList.push(frontState);
					 //push the possible vector
					 previousAndDepth.push(std::make_pair(depth+1, 1));
					//swap the front state back to the original position before the move to be used for the other possible moves
					 frontState.at(position + 1) = frontState.at(position);
					 frontState.at(position) = 0;

				 }
			 }
			 //possible down move
			 if (i = 1) {
				 if (((position != 6) || (position != 7) || (position != 8)) && (move != 3)) {
					 //make a possible down move and swap values
					 frontState.at(position) = frontState.at(position + 3);
					 frontState.at(position + 3) = 0;
					 //checks for solution
					 if (frontState == solutionPuzzle) {
						 while (!possibleMoveList.empty()) {
							 possibleMoveList.pop();
						 }
						 //store the move into the move list
						 allPossibleMoves.push_back(1);
						 //store the state into the state list
						 allPossibleStates.push_back(frontState);
						 break;
					 }
					 //push onto the possible move list
					 possibleMoveList.push(frontState);
					 //push the possible vector
					 previousAndDepth.push(std::make_pair(depth + 1, 1));
					 //swap the front state back to the original position before the move to be used for the other possible moves
					 frontState.at(position + 3) = frontState.at(position);
					 frontState.at(position) = 0;

				 }
			 }
			 //possible left move
			 if (i = 2) {
				 if (((position != 0) || (position != 3) || (position != 6)) && (move != 0)) {
					 //make a possible left move and swap values
					 frontState.at(position) = frontState.at(position - 1);
					 frontState.at(position - 1) = 0;
					 //checks for solution
					 if (frontState == solutionPuzzle) {
						 while (!possibleMoveList.empty()) {
							 possibleMoveList.pop();
						 }
						 //store the move into the move list
						 allPossibleMoves.push_back(2);
						 //store the state into the state list
						 allPossibleStates.push_back(frontState);
						 break;
					 }
					 //push onto the possible move list
					 possibleMoveList.push(frontState);
					 //push the possible vector
					 previousAndDepth.push(std::make_pair(depth + 1, 1));
					 //swap the front state back to the original position before the move to be used for the other possible moves
					 frontState.at(position - 1) = frontState.at(position);
					 frontState.at(position) = 0;

				 }
			 }
			 //possible up move
			 if (i = 3) {
				 if (((position != 0) || (position != 1) || (position != 2)) && (move != 1)) {
					 //make a possible up move and swap values
					 frontState.at(position) = frontState.at(position - 3);
					 frontState.at(position - 3) = 0;
					 //checks for solution
					 if (frontState == solutionPuzzle) {
						 while (!possibleMoveList.empty()) {
							 possibleMoveList.pop();
						 }
						 //store the move into the move list
						 allPossibleMoves.push_back(3);
						 //store the state into the state list
						 allPossibleStates.push_back(frontState);
						 break;
					 }
					 //push onto the possible move list
					 possibleMoveList.push(frontState);
					 //push the possible vector
					 previousAndDepth.push(std::make_pair(depth + 1, 1));
					 //swap the front state back to the original position before the move to be used for the other possible moves
					 frontState.at(position - 3) = frontState.at(position);
					 frontState.at(position) = 0;

				 }
			}
		 }
	}
	//make two stacks that filter the possibilities
	std::stack<std::vector<int> > listPrunedStates;
	std::stack<int> prunedMoves;

	std::vector<int> prunedState = allPossibleStates.at(allPossibleStates.size()-1);
	int prunedMove = allPossibleMoves.at(allPossibleMoves.size()-1);
	
	while (!stackComplete) {
		//obtain last state (solution)
		listPrunedStates.push(prunedState);
		//obtain last move
		prunedMoves.push(prunedMove);
		//find our position
		for (int i = 0; i < prunedState.size(); i++) {
			if (prunedState.at(i) == 0) {
				position = i;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (i = 0) {
				prunedState.at(position) = prunedState.at(position - 1);
				prunedState.at(position - 1) = 0;
				for (int j = 0; j < listPrunedStates.size(); j++) {
					auto iter = std::find(listPrunedStates.at(j).begin(), listPrunedStates.at(j).end(), prunedState);
				}
			}
			if (i = 1) {
				prunedState.at(position) = prunedState.at(position - 3);
				prunedState.at(position - 3) = 0;

			}
			if (i = 2) {
				prunedState.at(position) = prunedState.at(position + 1);
				prunedState.at(position + 1) = 0;
			}
			if (i = 3) {
				prunedState.at(position) = prunedState.at(position + 3);
				prunedState.at(position + 3) = 0;

			}
		}
	}
}

int main(int argc, char* argv[]) {
	//for storing the puzzle in a vector
	std::vector<int> eightPuzzle;
	//for comparing the puzzle to the solution
	std::vector<int> solutionPuzzle;
	//read in input
	std::string line;
	std::string ss;
	int n;
	std::cout << "Input your eightPuzzle: " << std::endl;
	getline(std::cin, line);
	std::stringstream input(line);

	//storing the data without commas
	while (getline(input, ss, ',')){
		n = stoi(ss);
		eightPuzzle.push_back(n);
	}

	//9 is the number of tiles in the eight puzzle
	for (int i = 0; i < 9; i++) {
		solutionPuzzle.push_back(i);
	}

	std::cout << "eight puzzle: " << std::endl;
	for (int j = 0; j < 9; j++){
		std::cout << eightPuzzle.at(j) << " ";
	}

	std::cout << std::endl;
	std::cout << "solution: " << std::endl;
	for (int k = 0; k < 9; k++) {
		std::cout << solutionPuzzle.at(k) << " ";
	}

	solve(eightPuzzle, solutionPuzzle);

	return 0;
}