#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include "neuralNetwork.h"
#include <sstream>
#include <bitset>

//training data
std::vector<std::pair<std::string, int>> training = {
	{ "0x7E, 0x11, 0x11, 0x11, 0x7E", 0 },// A
	{ "0x7F, 0x49, 0x49, 0x49, 0x36", 1 },// B
	{ "0x3E, 0x41, 0x41, 0x41, 0x22", 2 },// C
	{ "0x7F, 0x41, 0x41, 0x22, 0x1C", 3 },// D
	{ "0x7F, 0x49, 0x49, 0x49, 0x41", 4 },// E
	{ "0x7F, 0x09, 0x09, 0x01, 0x01", 5 },// F
	{ "0x3E, 0x41, 0x41, 0x51, 0x32", 6 },// G
	{ "0x7F, 0x08, 0x08, 0x08, 0x7F", 7 },// H
	{ "0x00, 0x41, 0x7F, 0x41, 0x00", 8 },// I
	{ "0x20, 0x40, 0x41, 0x3F, 0x01", 9 },// J
	{ "0x7F, 0x08, 0x14, 0x22, 0x41", 10 },// K
	{ "0x7F, 0x40, 0x40, 0x40, 0x40", 11 },// L
	{ "0x7F, 0x02, 0x04, 0x02, 0x7F", 12 },// M
	{ "0x7F, 0x04, 0x08, 0x10, 0x7F", 13 },// N
	{ "0x3E, 0x41, 0x41, 0x41, 0x3E", 14 },// O
	{ "0x7F, 0x09, 0x09, 0x09, 0x06", 15 },// P
	{ "0x3E, 0x41, 0x51, 0x21, 0x5E", 16 },// Q
	{ "0x7F, 0x09, 0x19, 0x29, 0x46", 17 },// R
	{ "0x46, 0x49, 0x49, 0x49, 0x31", 18 },// S
	{ "0x01, 0x01, 0x7F, 0x01, 0x01", 19 },// T
	{ "0x3F, 0x40, 0x40, 0x40, 0x3F", 20 },// U
	{ "0x1F, 0x20, 0x40, 0x20, 0x1F", 21 },// V
	{ "0x7F, 0x20, 0x18, 0x20, 0x7F", 22 },// W
	{ "0x63, 0x14, 0x08, 0x14, 0x63", 23 },// X
	{ "0x03, 0x04, 0x78, 0x04, 0x03", 24 },// Y
	{ "0x61, 0x51, 0x49, 0x45, 0x43", 25 }// Z
};

//converts hex to string
//https://stackoverflow.com/questions/12851379/c-how-do-i-convert-hex-integer-to-string
std::string convert_int(int n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}

//returns binary string per hex char
const char* hexToBin(char c) {
	switch (toupper(c)) {
	case '0': return "000";
	case '1': return "001";
	case '2': return "010";
	case '3': return "011";
	case '4': return "100";
	case '5': return "101";
	case '6': return "110";
	case '7': return "111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}
}

//converts hex to binary
std::string hexStringToBin(const std::string& hex) {
	int i;
	std::string bin;
	//every 4 characters (5 iterations total)
	for (i = 0; i < hex.length(); i++) {
		//first 3 bits
		bin += hexToBin(hex[i + 2]);
		//last 4 bits per arg
		if (isalpha(hex[i + 3]) || hex[i + 3] == '8' || hex[i + 3] == '9') {
			bin += hexToBin(hex[i + 3]);
		}
		else {
			bin += "0";
			bin += hexToBin(hex[i + 3]);
		}
		i = i + 3;

	}
	return bin;
}

//populates all weights to be -.1 < x < .1 && x != 0
void populateMatrix(neuralNetwork* net) {
	int signRoll, signRoll2, i, j;

	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		for (j = 0; j < INPUT_LAYER_SZ; j++) {
			//avoid 0 rolls
			net->layer1[i][j] = ((float)rand() / RAND_MAX)*.10;
			if (net->layer1[i][j] == 0.0000) {
				while (net->layer1[i][j] == 0.0000) {
					net->layer1[i][j] = ((float)rand() / RAND_MAX)*.10;
				}
			}

			signRoll = rand() % 2;
			//negative flip chance
			if (signRoll == 0) {
				net->layer1[i][j] = 0.0 - net->layer1[i][j];
			}
		}
	}


	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		for (j = 0; j < HIDDEN_LAYER_SZ; j++) {
			//avoid 0 rolls
			net->layer2[i][j] = ((float)rand() / RAND_MAX)*.10;
			if (net->layer2[i][j] == 0.0000) {
				while (net->layer2[i][j] == 0.0000) {
					net->layer2[i][j] = ((float)rand() / RAND_MAX)*.10;
				}
			}

			signRoll2 = rand() % 2;
			//negative flip chance
			if (signRoll2 == 0) {
				net->layer2[i][j] = 0.0 - net->layer2[i][j];
			}
		}
	}

}

//bias is set to 0.0 (additional option to turn it on)
void populateBias(neuralNetwork* net) {
	int i;

	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		net->output1[i] = 0.0;
	}

	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		net->output2[i] = 0.0;
	}
}


//matrix dot product
std::vector<float> dotProduct(neuralNetwork* net, int layer, std::vector<int> arr, std::vector<float> out) {
	int i, j;
	float sum = 0.0;
	//	printf("entered", NULL);
	out.clear();
	if (layer == 1) {
		sum = 0.0;
		for (i = 0; i < HIDDEN_LAYER_SZ; i++) {

			for (j = 0; j < INPUT_LAYER_SZ; j++) {
				sum += net->layer1[i][j] * (float)(arr[j]);

			}
			out.push_back(sum);

		}
		//printf("done layer 1: ", NULL);
	}

	else if (layer == 2) {
		for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
			sum = 0.0;
			for (j = 0; j < HIDDEN_LAYER_SZ; j++) {
				sum += net->layer2[i][j] * net->temp1[j];
			}
			//printf("sum: %f\n", sum);
			out.push_back(sum);

		}
		//		printf("done layer 2: ", NULL);
	}

	return out;
}

//Applies the tanh function
void tanhProduct(neuralNetwork* net) {
	int i;
	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		float temp;
		temp = 0.0;
		//temp = net->temp1[i] / (1 + abs(net->temp1[i]));
		temp = tanh(net->temp1[i]);
		net->temp1[i] = temp;
	}

}

//applies the sigmoid function
void sigProduct(neuralNetwork* net) {
	int i;
	float temp;
	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		temp = 0.0;
		
		//this is to avoid calculating two exp() for speed, see @piazza
		//temp = ((net->temp2[i] / (1.0 + abs(net->temp2[i]))) + 1.0) / 2.0;
		temp = exp(net->temp2[i]) / (exp(net->temp2[i]) + 1.0);
		net->temp2[i] = temp;
	

	}
	//reset just in case
	temp = 0.0;
}

//derivative of the tanh function
std::vector<float> tanhDerive(neuralNetwork* net) {
	int i;
	float temp;
	temp = 0.0;
	std::vector<float> tanDerivative;
	tanDerivative.clear();
	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		
		
		temp = 1.0 - (net->temp1[i] * net->temp1[i]);
		tanDerivative.push_back(temp);
	}
	temp = 0.0;
	return tanDerivative;
}

//derivative of the sigmoid function
std::vector<float> sigDerive(neuralNetwork* net) {
	int i;
	float x;
	std::vector<float> sigDerivative;
	sigDerivative.clear();
	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		x = 0.0;
		x = net->temp2[i] * (1.0 - net->temp2[i]);
		sigDerivative.push_back(x);
	}
	return sigDerivative;
}


int main(int argc, char* argv[]) {
	srand(time(NULL));

	//initialize the neural net
	neuralNetwork* net = new neuralNetwork();

	//input layer vector
	std::vector<int> arr;
	//example layer vector
	std::vector<std::vector<int> > ex;
	//output layer vector
	std::vector<float> out;
	//hidden layer Activation vector
	std::vector<float> activationInput;
	//hidden layer vector
	std::vector<float> hiddenOut;
	//derivative vector
	std::vector<float> tanhDerivative;
	//sig derivative vector
	std::vector<float> sigDerivative;
	//delta vector
	std::vector<float> tanhDelta;
	//second delta
	std::vector<float> sigDelta;

	std::vector<std::string> example;

	//temp storage vector
	std::vector<float> tempFloat;
	//for parsing
	std::string inputHex;
	//for parsing
	std::string resultBin;
	//epoch storage
	std::vector<float> accuracyVector;
	//storage for plot
	std::vector<int> epochCount;

	char alphaCAPS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	
	double accuracy = 0.0;
	int i, j, l;
	int epochs = 0;
	int numExamples = 0;
	int level = 0;
	float alpha = 0.3;
	float max = 0.0;
	float randomWeight = 0.0;
	float acc_average = 0.0;

	//35 bits (on or off) in the form of hex or binary
	if (argc == 2) {
		if ((strlen(argv[1])) != 35) {
			printf("the binary string is not 35 char length. ", NULL);
			exit(0);
		}
		else {
			for (i = 0; i < INPUT_LAYER_SZ; i++) {
				char k = argv[1][i];
				arr.push_back((int)k - '0');
			}
		}
	}
	else if (argc == 6) {
		int iter;
		for (iter = 1; iter < argc; iter++) {
			std::string temp;
			temp = argv[iter];
			//this is to catch if input in incorrectly entered
			if (temp.at(0) == '0' && temp.at(1) == 'x' && temp.length() == 4) {
				inputHex.append(temp);
			}
			else {
				printf("error", NULL);
				exit(0);
			}
		}
		if (inputHex.length() == 20) {
			printf("Beginning Hex \n", NULL);
		}

		resultBin = resultBin.append(hexStringToBin(inputHex));


		//store in array
		for (iter = 0; iter < resultBin.length(); iter++) {
			arr.push_back((int)(resultBin.at(iter) - '0'));
		}
		printf("converted\n", NULL);
	}
	else {
		printf("error in input", NULL);
		exit(0);
	}

	//precompute example input vectors with 5 hex values for all 130 values (26 characters)
	for (i = 0; i < strlen(alphaCAPS); i++) {
		resultBin.clear();
		std::stringstream ss;
		std::string delimiter = ", ";

		ss << std::hex << training.at(i).first;

		resultBin.append(training.at(i).first);

		std::string token = resultBin.substr(0, resultBin.find(delimiter));
		std::string token2 = resultBin.substr(6, resultBin.find(delimiter));
		std::string token3 = resultBin.substr(12, resultBin.find(delimiter));
		std::string token4 = resultBin.substr(18, resultBin.find(delimiter));
		std::string token5 = resultBin.substr(24, resultBin.find(delimiter));

		resultBin.clear();

		resultBin = token;
		resultBin = resultBin.append(token2);
		resultBin = resultBin.append(token3);
		resultBin = resultBin.append(token4);
		resultBin = resultBin.append(token5);

		resultBin = hexStringToBin(resultBin);
		example.push_back(resultBin);

	}

	//generating random weights
	populateMatrix(net);
	populateBias(net);
	printf("done populating \n", NULL);

	for (i = 0; i < strlen(alphaCAPS); i++) {
		std::vector<int> inputs;

		for (j = 0; j < INPUT_LAYER_SZ; j++) {
			int store = (int)(example[i].at(j) - '0');
			inputs.push_back(store);
		}
		ex.push_back(inputs);

		inputs.clear();
	}

	while (epochs < 10000) {
		//26 characters are examples, we find 26 bitwise outputs.
		accuracy = 0.0;
		acc_average = 0.0;
		for (numExamples = 0; numExamples < strlen(alphaCAPS); numExamples++) {
			
			level = 1;
			//here, out is empty and will not be used because it is layer 1.
			activationInput = dotProduct(net, level, ex[numExamples], out);

			//add the bias before tanh/sigmoid
			for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
				net->temp1[i] = net->output1[i] + activationInput[i];
			}
			//apply tanh
			tanhProduct(net);
			//calc derivative
			tanhDerivative = tanhDerive(net);

			level = 2;
			//send neural net to layer 2, with the input vector (going to be unused), and an empty vector out
			hiddenOut = dotProduct(net, level, ex[numExamples], out);
			//in this case this is 0.0 = 0.0 + hiddenOut[i]
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				net->temp2[i] = net->output2[i] + hiddenOut[i];
			}

			//sigmoid the results
			sigProduct(net);
			sigDerivative = sigDerive(net);

			sigDelta.clear();
			//calculate the delta for sig
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				float f;
				float y;
				if (training.at(numExamples).second == i) {
					y = 1.0;
				}
				else {
					y = 0.0;
				}
				f = sigDerivative[i] * (y - net->temp2[i]);
				sigDelta.push_back(f);
			}

			//tanh delta
			tanhDelta.clear();
			for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
				float sum;
				sum = 0.0;
				for (j = 0; j < OUTPUT_LAYER_SZ; j++) {
					//weight of node i * (weight of node j * delta j)
					sum = sum + net->layer2[j][i] * sigDelta[j];
				}
				sum = sum * tanhDerivative[i];
				tanhDelta.push_back(sum);
			}

			//update inner layer weight
			for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
				for (j = 0; j < INPUT_LAYER_SZ; j++) {
					if (ex[numExamples][j] == 0) {
						net->layer1[i][j] = net->layer1[i][j] + alpha * net->temp1[i] * tanhDelta[i];
					}
					else if (ex[numExamples][j] == 1) {
						net->layer1[i][j] = net->layer1[i][j] - alpha * net->temp1[i] * tanhDelta[i];
					}
				}
			}

			//update the weight
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				for (j = 0; j < HIDDEN_LAYER_SZ; j++) {
					if (net->temp1[j] <= 0.0) {
						net->layer2[i][j] = net->layer2[i][j] - alpha *  net->temp2[i] * sigDelta[i];
					}
					else {
						net->layer2[i][j] = net->layer2[i][j] + alpha *  net->temp2[i] * sigDelta[i];
					}
				}
			}
			int a;
			max = 0.0;
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				if (max < net->temp2[i]) {
					max = net->temp2[i];
					a = i;
				}
				else {
				}
			}
			if (a == training.at(numExamples).second) {
				accuracy += 1.0;
			}
			else {

			}

		}
		acc_average = (accuracy) / 26.0;
		accuracyVector.push_back(acc_average);
		printf("\r acc_average %f", acc_average);
		epochs++;
		accuracy = 0.0;
		acc_average = 0.0;
		epochCount.push_back(epochs);
	}

	printf("completed training \n", NULL);
	printf("beginning input analysis \n", NULL);

	level = 1;
	//here, out is empty and will not be used because it is layer 1.
	hiddenOut = dotProduct(net, level, arr, out);

	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		net->temp1[i] = net->output1[i] + hiddenOut[i];
	}



	//apply tanh
	tanhProduct(net);

	for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
		printf("hidden activation: %f\n", net->temp1[i]);
	}

	level = 2;
	//send neural net to layer 2, with the input vector (going to be unused), and an empty vector out
	hiddenOut = dotProduct(net, level, arr, out);

	//in this case, 0.0 + hiddenOut[i]
	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		net->temp2[i] = net->output2[i] + hiddenOut[i];
	//	printf("net->t2 %f\n", net->temp2[i]);
	}

	//sigmoid the results
	sigProduct(net);

	for (i = 0; i < OUTPUT_LAYER_SZ; i++)
		printf("sig activation %f\n", net->temp2[i]);
	//find most likely character
	max = -99999999.99999;
	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		if (max < net->temp2[i]) {
			max = net->temp2[i];
		}
		else {
		}
	}
	//display output
	for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
		if (max == net->temp2[i]) {
			printf("the input is: %c ", alphaCAPS[i]);
			printf("with a %f certainty\n", max);
		}
	}
	
	FILE *temp = fopen("data.temp", "w");
	for (i = 0; i < accuracyVector.size(); i++){
		fprintf(temp, "%ld %lf\n", epochCount[i], accuracyVector[i]);
	}
	fflush(temp);
	
	FILE *gnuplot = popen("gnuplot -persistent", "w");
	fprintf(gnuplot, "set terminal dumb \n");
	
	fprintf(gnuplot, "plot 'data.temp' \n");
	fflush(gnuplot);
	
	printf("testing bit flips : \n");
	//for each example
	for(numExamples = 0; numExamples < strlen(alphaCAPS); numExamples++) {
	bool matches;
	int flip;
	float localmax;
	localmax = 0.0;
	flip = 0;
	matches = true;
		while(matches){
			std::vector<int> temporary;
			//propagate forward to see if output is correct
			level = 1;
			
			temporary = ex[numExamples];

			//flip a random bit
			int random = rand() % 35;
			if(temporary[random] == 1){
				temporary[random] = 0;
			}
			else{
				temporary[random] = 1;
			}

			hiddenOut = dotProduct(net, level, temporary, out);

			for (i = 0; i < HIDDEN_LAYER_SZ; i++) {
			net->temp1[i] = net->output1[i] + hiddenOut[i];
			}

			//apply tanh
			tanhProduct(net);

			level = 2;
			//send neural net to layer 2, with the input vector (going to be unused), and an empty vector out
			hiddenOut = dotProduct(net, level, temporary, out);

			//in this case, 0.0 + hiddenOut[i]
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				net->temp2[i] = net->output2[i] + hiddenOut[i];
			}

			//sigmoid the results
			sigProduct(net);
			
			localmax = 0.0;
			//find most likely character
			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				if (localmax < net->temp2[i]) {
				localmax = net->temp2[i];
				}
				else {
				}
			}

			for (i = 0; i < OUTPUT_LAYER_SZ; i++) {
				if (localmax == net->temp2[i]) {
					if(i == numExamples){
						flip++;
						
					}
					else{
						printf("%c ", alphaCAPS[numExamples]);
						printf("tolerated %d bitflips\n", flip);
						matches = false;
					}
				}
				else{

					}
			}
			localmax = 0.0;

		}

	}


	delete net;

	return 0;
}
