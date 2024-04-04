#include <iostream>
using namespace std;

class MarkovString {
private:
	string init_str;
	string resulting_str;
	
	struct rule {
		bool terminational;
		string from;
		string to;

		rule() : from(""), to("") {};
		rule(string from, string to, bool terminational = 0) : from(from), to(to), terminational(terminational) {};
	};

	rule* rules;
	size_t rules_size;

public:
	MarkovString(string init_str) : init_str(init_str), resulting_str(init_str), rules_size(0) {
		rules = new rule[rules_size];
	};
	
	~MarkovString() {
		delete[] rules;
	};

	string get_init() const { return init_str; };
	
	string get_computed() {
		if (init_str != resulting_str) {
			return resulting_str;
		}
		else {
			compute();
			return resulting_str;
		}
	};

	int get_rules_size() const { return rules_size; };

	void add_rule(string f, string t, bool terminational = false) {
		rule* new_rules =  new rule[rules_size + 1];
		for (int i = 0; i < rules_size; ++i) {
			new_rules[i] = rules[i];
		};

		new_rules[rules_size] = rule(f, t, terminational);

		delete[] rules;
		rules = new_rules;
		++rules_size;
	};

	void show_rules(ostream& os) {
		for (int i = 0; i < rules_size; ++i) {
			os << rules[i].from << " -> " << rules[i].to << "\n";
		};
	};

	string compute() {
		rule* n = nullptr;
		for (int j = 0; j < rules_size; ++j) {
			if (contains(resulting_str, rules[j].from)) {
				if (n == nullptr || resulting_str.find(rules[j].from) < resulting_str.find(n->from)) {
					n = &rules[j];
				};
			};
		};
		
		if (n != nullptr) {
			resulting_str.replace(resulting_str.find(n->from), n->from.length(), n->to);
			if (n->terminational) {
				return resulting_str;
			};
			compute();
		};
		
		return resulting_str;
	};

private:
	bool contains(string s1, string s2) {
		return s1.find(s2) != string::npos;
	};
};