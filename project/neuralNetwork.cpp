#include "neuralNetwork.h"

neuralNetwork::neuralNetwork() {
	output1 = new float[HIDDEN_LAYER_SZ];
	output2 = new float[OUTPUT_LAYER_SZ];
	layer1 = new float*[HIDDEN_LAYER_SZ];
	layer2 = new float*[OUTPUT_LAYER_SZ];
	temp1 = new float[HIDDEN_LAYER_SZ];
	temp2 = new float[OUTPUT_LAYER_SZ];
	for (int i = 0; i < HIDDEN_LAYER_SZ; i++) {
		layer1[i] = new float[INPUT_LAYER_SZ];
	}
	for (int i = 0; i < OUTPUT_LAYER_SZ; i++) {
		layer2[i] = new float[HIDDEN_LAYER_SZ];
	}
}

neuralNetwork::~neuralNetwork() {
	delete output1;
	delete output2;
	for (int i = 0; i < INPUT_LAYER_SZ; i++) {
		delete layer1[i];
	}
	for (int i = 0; i < OUTPUT_LAYER_SZ; i++) {
		delete layer2[i];
	}
	delete temp1;
	delete temp2;
	delete layer1;
	delete layer2;
}

