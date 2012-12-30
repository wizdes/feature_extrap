#include <queue>
#include <cmath>
#include "knn.h"

using namespace std;

KNN::KNN(){
	k = 10;
	results.clear();
}

KNN::KNN(Storage * input_storage){
	s = input_storage;
	k = 10;
	results.clear();
}

struct comp_measure{
	int index;
	double comp_val;
	int label;
	comp_measure(){
		index = 0;
		comp_val = 0;
		label = 0;
	}
};

double length(DataArray * d)
{
	double length = 0;
	for(int i = 0; i < d->getsize(); i++)
	{
		length += d->getFeatureAtInd(i) * d->getFeatureAtInd(i);
	}
	length = sqrt(length);
	return length;
}


double cosSimImg(DataArray * d1, DataArray * d2)
{
	double cos_val = 0;
	for(int i = 0; i < d1->getsize(); i++)
	{
		cos_val += d1->getFeatureAtInd(i) * d2->getFeatureAtInd(i);
	}
	cos_val = cos_val/(length(d1) * length(d2));
	return cos_val;
}

double get_min_in_array(comp_measure * array, int size){
	double min = -1;
	for(int i = 0; i < size; i++){
		if(array[i].comp_val < min || min == -1)
		{
			min = array[i].comp_val;
		}
	}
	return min;
}

void KNN::run(){
	vector<DataArray*> training_set;
	vector<DataArray*> testing_set;
	s->getfeatures(training_set, testing_set);
	for(int i = 0; i < testing_set.size(); i++){
		comp_measure * comp = new comp_measure[k];
		double min_comp_val = -1;
		//compare testing_set[i] and training_set[i] and stick values in comp
		for(int j = 0; j < k; j++){
			comp[j].index = j;
			comp[j].label = training_set[j]->getlabel();
			comp[j].comp_val = cosSimImg(testing_set[i], training_set[j]);
		}

		min_comp_val = get_min_in_array(comp, k);

		for(int j = k; j < training_set.size(); j++){
			//compare testing_set[i] and training_set[i]
			double comp_val = cosSimImg(testing_set[i], training_set[j]);
			//if greater than min_comp_val, then replace elt with min_comp_val
			if(comp_val > min_comp_val)
			{
				for(int it = 0; it < k; it++)
				{
					if(comp_val > comp[it].comp_val){
						comp[it].index = j;
						comp[it].label = training_set[j]->getlabel();
						comp[it].comp_val = comp_val;
						break;
					}
				}
			}
			//calculate min_comp_val
			min_comp_val = get_min_in_array(comp, k);
		}
		int destined_label = -1;
		//now comp has k labels. Use this to vote on a label
		int votes[] = {0,0,0,0,0,0,0,0,0,0};
		for(int it = 0; it < k; it++) votes[comp[it].label]++;
		for(int it = 0; it < 10; it++)
		{
			if(votes[it] > destined_label) destined_label = it;
		}
		results.push_back(destined_label);
	}
}

std::vector<int> KNN::get_results(){
	return results;
}