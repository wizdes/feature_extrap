#include "verify.h"
#include <iostream>
#include <fstream>

using namespace std;

verifier::verifier(){
	correct_labels.clear();
}

void verifier::get_correct_labels(string filename)
{
	ifstream in(filename.c_str(), ifstream::in);
	while(in)
	{
		string input = "";
		getline(in, input);
		correct_labels.push_back(atoi(input.c_str()));
	}
}

void verifier::get_predicted_labels(vector<int> * labels)
{
	predicted_labels = labels;
}

void verifier::verify()
{
	int total = 0;
	int correct = 0;
	for(int i = 0; i < correct_labels.size(); i++)
	{
		if((*predicted_labels)[i] == correct_labels[i]) correct++;
		total++;
	}
	cout <<"Total samples: " << total <<endl;
	cout <<"Correct: " << correct << " - " << correct/total <<endl;
}