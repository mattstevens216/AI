//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: February 12, 2018
//hw1pr1.cpp

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

//room 2d vector (input)
std::vector<std::vector<int> > room;
//roomba 2d vector (self-made map)
std::vector<std::vector<int> > roombaMap;

/*global variables*/
int performance;
int numSteps;
int numClean;

/*struct Roomba{
	//timesteps
	int numSteps;
	//clean tile counter
	int numClean;
	//performance counter
	int performance;
	//current row
	int currRow = 0;
	//current column
	int currCol = 0;
};*/

//print function for debugging purposes
void print(int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			printf("%d ", roombaMap.at(i).at(j));
		}
		std::cout << std::endl;
	}
	
}

 void checkTile(int currRow, int currCol){
	if(roombaMap.at(currRow).at(currCol) == 1){
		//suck dirt
		roombaMap.at(currRow).at(currCol) = 0;
		//increment steps
		numSteps++;
		//increment clean tiles
		numClean++;
		//calculate performance
		performance += numClean;
	}
	else{	
	}
}

void run(int rows, int cols){
	//begins at (0,0)
	//current column
	int currCol = 0;
	//current row
	int currRow = 0;
	//boolean for map_complete
	bool isComplete = false;
	//timesteps
	numSteps = 0;
	//clean tile counter
	numClean = 0;
	//performance counter
	performance = 0;
	//total tiles of the room
	int totalTiles = rows*cols;

	//get initial tile value (dirty or clean)
	roombaMap.at(0).at(0) = room.at(0).at(0);
	
	
	while(!isComplete){
		//print(rows,cols);
		//travel to the right
		while(currCol < cols){
			//checks to see if tile is dirty or clean
			checkTile(currRow, currCol);
			//if already visited and cleaned exit loop
			if(currCol+1 < cols){
				if(roombaMap.at(currRow).at(currCol+1) == -1){
					//moves to the right one tile
					currCol++;
					//increments action
					numSteps++;
					//calculate performance
					performance += numClean;
					roombaMap.at(currRow).at(currCol) = room.at(currRow).at(currCol);
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}	

		//travels down
		while(currRow < rows){
			//checks to see if tile is dirty or clean
			checkTile(currRow, currCol);
			//if already visited and cleaned exit loop
			if(currRow+1 < rows){
				if(roombaMap.at(currRow+1).at(currCol) == -1){
					//moves to the right one tile
					currRow++;
					//increments action
					numSteps++;
					//calculate performance
					performance += numClean;
					roombaMap.at(currRow).at(currCol) = room.at(currRow).at(currCol);
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
		//travels left
		while(currCol > -1){
			//checks to see if tile is dirty or clean
			checkTile(currRow, currCol);
			//if already visited and cleaned exit loop
			if(currCol-1 > -1){
				if(roombaMap.at(currRow).at(currCol-1) == -1){
					//moves to the right one tile
					currCol--;
					//increments action
					numSteps++;
					//calculate performance
					performance += numClean;
					roombaMap.at(currRow).at(currCol) = room.at(currRow).at(currCol);
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
	
		//travels up
		while(currRow > -1){
			//checks to see if tile is dirty or clean
			checkTile(currRow, currCol);
			//if already visited and cleaned exit loop
			if(currRow-1 > -1){
				if(roombaMap.at(currRow-1).at(currCol) == -1){
					//moves to the right one tile
					currRow--;
					//increments action
					numSteps++;
					//calculate performance
					performance += numClean;
					roombaMap.at(currRow).at(currCol) = room.at(currRow).at(currCol);
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
		//checks to see if all tiles are clean
		isComplete = true;
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(roombaMap.at(i).at(j) == -1 || roombaMap.at(i).at(j) == 1){
					//if there are any unknown or dirty tiles
					isComplete = false;
				}
			}
		}
	}
	while(numSteps < 1000){
		performance += numClean;
		numSteps++;
	}
	//print performance
	std::cout << "performance: " << performance << std::endl;
	
}

int main(int argc, char* argv[]){
	int rows;
	int cols;
	int n;
	int unknownTile = -1;
	std::string line;
	


	std::cout << "Enter the number of rows: ";
	getline(std::cin, line);
	
	std::cout << "Enter the number of columns: ";
	rows = stoi(line);
	
	getline(std::cin, line);
	
	cols = stoi(line);

	//create the roombas map
	for(int i = 0; i < rows; i++){
		//make a new current row filled with unknown tiles
		std::vector<int> populateMap;
		
		for(int j = 0; j < cols; j++){
			populateMap.push_back(unknownTile);
		}
		//row is now completed with unvisited tiles
		
		//push onto map matrix
		roombaMap.push_back(populateMap);
		//roomba now has a map filled with unknown tiles
	}
	
	
	//populate rows one at a time
	for(int i = 0; i < rows; i++){
		//make a new current row vector to store into room
		std::vector<int> row;
		//get current line
		getline(std::cin, line);
		//stringstream object
		std::istringstream input(line);
		//while there are elements in the current line
		while(input >> n)
			row.push_back(n);
		//row is now completed
		
		//push onto room matrix
		room.push_back(row);
	}

	//the matrix is now populated
	
	//then execute the run() command for running the roomba
	run(rows, cols);
	//return values
	print(rows, cols);
	
return 0;
}
