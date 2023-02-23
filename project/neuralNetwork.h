#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#define INPUT_LAYER_SZ 35
#define HIDDEN_LAYER_SZ 35
#define OUTPUT_LAYER_SZ 26

class neuralNetwork {
public:
	neuralNetwork();
	~neuralNetwork();
	float* output1;
	float* output2;
	float* temp1;
	float* temp2;
	float** layer1;
	float** layer2;
};
#endif