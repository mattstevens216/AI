//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: May 1, 2018
//hw4pr1.cpp

#include <iostream>


float fuzzyAnd(float x, float y){
	float temp;
	temp = std::min(x, y);
	return temp;
}
//a -> b = not(x and not(y))
float fuzzyImplies(float x, float y){
	float notResult;
	float notY;
	
	notY = 1.0 - y;
	notResult = 1.0 - fuzzyAnd(x,notY);
	
	return notResult;
}

int main(int argc, char* argv[]){
	float arrX[] = {0, 0.25, 0.5, 0.75, 1};
	float arrY[] = {0, 0.25, 0.5, 0.75, 1};
	float result;
	result = 0.0;
	
	printf("The truth table for fuzzyImples: \n");
	printf("x\t   \t y\t  \t result\n");
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			result = fuzzyImplies(arrX[i], arrY[j]);
			//x
			printf("%f\t", arrX[i]);
			printf("%f\t", arrY[j]);
			printf("%f\t", result);
			printf("\n");
			
		}
	}
	
}