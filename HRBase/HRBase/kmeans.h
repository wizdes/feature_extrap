#ifndef _KMEANS_H_
#define _KMEANS_H_

#include "learner.h"

class KMeans:public Learner{
	KMeans();
	KMeans(Storage *);
	void run();
	std::vector<int> get_results();
};

#endif