#include "storage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

bool debug = true;

void stringToChArray(string s, vector<int> & arr_out, bool training, int & label_out)
{
	stringstream ss (stringstream::in | stringstream::out);
	ss << s;
	while (ss) {
		string num;
		if (!getline( ss, num, ',' )) break;
		if(training){
			training = false;
			label_out = atoi(num.c_str());
		}
		else arr_out.push_back(atoi(num.c_str()));
	}
}

Img::Img(){
	data = new unsigned char[PIXEL_WIDTH_C * PIXEL_HEIGHT_C];
	label = -1;
}

Img::~Img(){
	delete data;
}

void Img::inputData(vector<int> & readData, const int & label){
	for(unsigned int i = 0; i < readData.size(); i++) data[i] = (char) readData[i];
	this->label = label;
}

int Img::getPixelValue(int position){
	return (int) data[position];
}

int Img::getFeatureAtInd(int index){
	return getPixelValue(index);
}

Img::Img(const Img & copy)
{
	data = new unsigned char[PIXEL_WIDTH_C * PIXEL_HEIGHT_C];
	for(int i = 0; i < PIXEL_WIDTH_C * PIXEL_HEIGHT_C; i++)
	{
		data[i] = copy.data[i];
	}
	label = copy.label;
	size = PIXEL_HEIGHT_C * PIXEL_WIDTH_C;
}

void Img::printImg()
{
	cout <<"Label: " << label <<endl;
	for(int i = 0; i < PIXEL_WIDTH_C * PIXEL_HEIGHT_C; i++)
	{
				if(i%PIXEL_WIDTH_C ==0 && i != 0) cout <<endl;
		if((int)data[i] > 0)
		{
			cout <<"*";
		}
		else cout <<"-";
	}
	cout <<endl;
}

void Storage::featurize(){
	naiveFeaturize();
}

int Storage::readData(string filename, bool training)
{
	cout <<"Reading: " << filename <<endl;
	ifstream in(filename.c_str(), ifstream::in);
	Img * input;
	int counter = 0;
	while(in)
	{
		if(true){
			cout.precision(2);
			if(training) cout <<"\r"<<counter/42000.0 << "%\t";
			else cout <<"\r"<<counter/28000.0 << "%\t";
		}
		string line;
		getline(in, line);
		if(counter == 0){
			counter++;
			continue;
		}
		input = new Img();
		vector<int> training_data;
		int label = 0;
		stringToChArray(line, training_data, training, label);
		input->inputData(training_data, label);
		if(debug){
			input->printImg();
			Sleep(3000);
		}
		if(training)training_imgs.push_back(input);
		else testing_imgs.push_back(input);
		counter++;
	}
	cout << endl;
	return counter;
}

void Storage::readTrainingData(string filename)
{
	num_training = readData(filename, true);
}

void Storage::readTestData(string filename)
{
	num_testing = readData(filename, false);
}

Storage::~Storage()
{
	for(int i = 0; i < num_training; i++)
	{
		delete training_imgs[i];
		delete training_set[i];
	}
	for(int i = 0; i < num_testing; i++)
	{
		delete testing_imgs[i];
		delete testing_set[i];
	}
}

void Storage::naiveFeaturize()
{
	for(int i = 0; i < num_training;i++){
		Img * new_training = new Img(*training_imgs[i]);
		training_set.push_back(new_training);
	}
	for(int i = 0; i < num_training;i++){
		Img * new_testing = new Img(*testing_imgs[i]);
		training_set.push_back(new_testing);
	}
}