#include <iostream>
#include "storage.h"
#include "learner.h"
#include "knn.h"
#include "verify.h"

using namespace std;

const char * DEFAULT_TRAINING_FILE_C = "train.csv";
const char * DEFAULT_TESTING_FILE_C = "test.csv";
const char * DEFAULT_VERIFYING_FILE_C = "verified.cvs";

int main(int argc, char * argv)
{
	string training_file;
	string testing_file;
	//get filenames
	if(argc == 1)
	{
		training_file = DEFAULT_TRAINING_FILE_C;
		testing_file = DEFAULT_TESTING_FILE_C;
	}

	//create storage class
	Storage store;

	//read training data into storage class
	store.readTrainingData(training_file);
	//read test data into storage class
	store.readTestData(training_file);
	//process training data into features
	//process test data into storage class
	store.featurize();
	//create algorithm class
	Learner * alg = new KNN(&store);
	//feed training data to the algorithm
	alg->run();
	//run test data here
	vector<int> results = alg->get_results();

	verifier v;
	v.get_correct_labels(DEFAULT_VERIFYING_FILE_C);
	v.get_predicted_labels(&results);
	v.verify();
	return 0;
}