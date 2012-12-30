#ifndef _VERIFY_H_
#define _VERIFY_H_

#include <string>
#include <vector>

class verifier{
	std::vector<int> correct_labels;
	std::vector<int> * predicted_labels;
public:
	verifier();
	void get_correct_labels(std::string filename);
	void get_predicted_labels(std::vector<int> * labels);
	void verify();
}

#endif