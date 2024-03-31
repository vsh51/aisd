#include <iostream>
using namespace std;

class MarkovString {
private:
	string init_str;
	string resulting_str;
	string termination;
	string* rules;

public:
	MarkovString(string init_str) : init_str(init_str) {};
	~MarkovString() {
		delete[] rules;
	};

private:
	bool contains(string substr) {		
		int substr_counter = 0;
		for (int i = 0; i < resulting_str.length(); ++i) {
			if (resulting_str[i] == substr[substr_counter]) {
				++substr_counter;
				if (substr.length() == substr_counter) return true;
			}
			else {
				substr_counter = 0;
			};
		};
		return false;
	};
};