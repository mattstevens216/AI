#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
int main(int argc, char* argv[]){
	srand(time(NULL));
	
	//35 bits (on or off) in the form of hex or binary
	if((strlen(argv[1])) != 35){
		printf("the binary string is not 35 char length. ", NULL);
		exit(0);
	}

	//35 inputs to 30 neurons
	int firstWeights[30][35];

	float randomWeight;
	int signRoll;
	int i, j;
	
	
	//generating random weights
	for(i = 0; i < 30; i++){
		for(j = 0; j < 35; j++){
			//avoid 0 rolls
			randomWeight = ((float)rand()/RAND_MAX)*.1;
			if(randomWeight == 0.0000){
				while(randomWeight == 0.0000){
					randomWeight = ((float)rand()/RAND_MAX)*.1;
				}
			}

			signRoll = rand()%2;
			//negative flip chance
			if(signRoll == 0){
				randomWeight = randomWeight * -1;
			}
		}
	}
	

	//reset iterators
	i = 0;
	j = 0;

	//each of the incoming values the neurons of the next layer receives
	for(i = 0; i < 30; i++){
		//each of the inputs "fanned" out to the inputs of the first neurons
		for(j = 0; j < 35; j++){
				
		}
	} 





}
