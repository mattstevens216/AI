To compile all of my programs:
	execute the command: g++-7.2.0 std=c++17 ./hw4pr1.cpp
	replace the file with the corresponding file.
	
To run: ./a.out

Notes:
hw4pr1 provides a truth-table
hw4pr2 is designed for acyclic paths.
hw4pr3 contains a small getline/fstream bug. If you run the query (by entering the n-gram when prompted), 
it should respond with the highest ocuring letter. 
If it just simply restates what you have entered, please close the program using ctrl+c or ctrl+d and run it again.
This possibly occurs because of the filestream getting overloaded with too many requests.
It sometimes fails on querys it previously worked with before! 
ex: qu results in a, but sometimes after that will not give an output.


	