#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

const int PIXEL_WIDTH_C = 28;
const int PIXEL_HEIGHT_C = 28;

using std::string;

class DataArray{
protected:
	int size;
	int label;
public:
	DataArray(){};
	DataArray(const DataArray &);
	virtual int getFeatureAtInd(int index) = 0;
	int getsize() { return size; }
	int getlabel() { return label; }
};

class Img:public DataArray{
private:
	unsigned char * data;
public:
	Img();
	Img(const Img & copy);
	~Img();
	void inputData(std::vector<int> & readData, const int & label);
	int getPixelValue(int position);
	int getFeatureAtInd(int index);
	void printImg();
};

class Storage{
	std::vector<Img *> training_imgs;
	std::vector<Img *> testing_imgs;
	std::vector<DataArray *> training_set;
	std::vector<DataArray *> testing_set;
	int num_training;
	int num_testing;
	void naiveFeaturize();
	int readData(std::string filename, bool training);
public:
	~Storage();
	void readTrainingData(std::string filename);
	void readTestData(std::string filename);
	void featurize();
	void getfeatures(std::vector<DataArray*>&, std::vector<DataArray*>&);
};


#endif
