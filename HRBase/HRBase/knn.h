#ifndef _KNN_H_
#define _KNN_H_

#include "learner.h"

class KNN:public Learner{
	vector<int> results;
	Storage * s;
	int k;
public:
	KNN();
	KNN(Storage *);
	void run();
	std::vector<int> get_results();
};

#endif