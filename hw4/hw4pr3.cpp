//Name: Matthew Stevens
//UIN: 924000693
//CSCE 420
//Due: May 1, 2018
//hw4pr3.cpp

#include <iostream>
#include <fstream>
#include <vector>

int main(){
	
	std::vector<int> counters;
	char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string gram;
	std::string dictionary;
	int max;
	max = 0;
	for(int i = 0; i < 26; i++){
		counters.push_back(0);
	}

	printf("enter a n-gram: ");
	
	printf("\n");
	
	while(std::getline(std::cin,gram) ){
		std::cout << "you have entered: " << gram << std::endl;
		
		std::ifstream ifs;
		ifs.open("/usr/share/dict/words", std::ifstream::in);
		//begin library analysis of n-gram
		while(std::getline(ifs,dictionary)){
			if(dictionary.size() > gram.size()){
				for(int i = 0; i < (dictionary.size() - gram.size()); i++){
					if(dictionary[i] == gram[0] && (dictionary.size()-i) > gram.size()){
						for(int j = 1; j < gram.size(); j++){
							if(dictionary[i+j] != gram[j]){
								break;
							}
							//end of the gram
							else if(j == gram.size()-1){
								char c;
								c = dictionary[i+j+1];
								//52 letters (caps and lowercase)
								for(int m = 0; m < 52; m++){
									if(c == alpha[m]){
										if(m > 25){
											int num;
											num = m % 26;
											counters[num] += 1;
										}
										else{
											counters[m] += 1;
										}
									}
								}
							}
							else{
								
							}
						}
					}
				}
			}

		}
		ifs.close();
		//find max
		for(int i = 0; i < counters.size(); i++){
			if(counters[i] > max){
				max = counters[i];
			}
		}
		
		for(int i = 0; i < counters.size(); i++){
			if(counters[i] == max){
				std::cout << "the highest occurring letter after the n-gram is: " << alpha[i] << " with " << max << " occurances " << std::endl;
			}
			else if(max == 0){
				std::cout << "there are no results that contain: " << gram << std::endl;
			}
			else{
				
			}
		}
		
		//reset counter
		for(int i = 0; i < counters.size(); i++){
			counters[i] = 0;
		}
		
		printf("enter a new n-gram or ctrl+d to quit: ");
	}
	return 0;
}