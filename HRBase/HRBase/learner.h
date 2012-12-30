#ifndef _LEARNER_H_
#define _LEARNER_H_

#include "storage.h"

class Learner{
public:
	Learner();
	Learner(Storage *);
	virtual void run() = 0;
	virtual std::vector<int> get_results() = 0;
};


#endif