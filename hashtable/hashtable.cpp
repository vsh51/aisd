#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class HashTable {
public:
	using keytype = string;
	using valuetype = string;

	struct KeyNode {
		keytype key;
		size_t value_index;
	};

	struct ValueNode {
		valuetype value;
		size_t key_index;
	};

	class key_not_found : public exception {
	private:
		const char* mess;
	public:
		key_not_found(const char* mess) : mess(mess) {};
	  	const char* what() const noexcept {return mess;}
	};

	class key_collision : public exception {
	private:
		const char* mess;
	public:
		key_collision(const char* mess) : mess(mess) {};
	  	const char* what() const noexcept {return mess;}
	};
    
private:
	size_t size;
	size_t amount_of_records;
	KeyNode* keys;
	ValueNode* values;
    double A = 0.618033;

	void resize() {
		size_t old_size = size;
        size += 30;
		KeyNode* new_keys = new KeyNode[size];
		ValueNode* new_values = new ValueNode[size];

		int i;
		for (i = 0; i < old_size; ++i) {
            if (keys[i].key != "") {
                int new_index = hash(keys[i].key);
                
                new_keys[new_index].key = keys[i].key;
                new_keys[new_index].value_index = new_index;

                new_values[new_index].value = values[i].value;
                new_values[new_index].key_index = new_index;
            }
		}

        for (int i = old_size; i < size; ++i) {
            keys[i].key = "";
        }

		delete[] keys;
		keys = new_keys;
		delete[] values;
		values = new_values;
	};

    int string2int(string s) const {
        size_t len = s.length();
        string part_result = "";

        for (int i = 0; i < len; ++i) {
            part_result += to_string(static_cast<int>(s[i]));
        }

        stringstream stoi_converter(part_result);
        int result;
        stoi_converter >> result;
        return result;
    }

    int hash(string key) const {
        int k = string2int(key);
        double koef = (k * A) - static_cast<int>(k * A);
        return (size * koef);
    }

	size_t find_key(keytype key) const {
        if (keys[hash(key)].key != "") {
            return hash(key);
        }
        else {
            throw key_not_found("key is not found");
        }
    };

public:
	HashTable(size_t size = 15) {
        if (size <= 1) throw invalid_argument("size must be grater than 1");
        
		keys = new KeyNode[size];
		values = new ValueNode[size];
		amount_of_records = 0;
		this->size = size;

		for (int i = 0; i < size; ++i) {
			keys[i].key = "";
		}
	};

    ~HashTable() {
        delete[] keys;
        delete[] values;
    }

	size_t get_amount_of_records() const { return amount_of_records; };
	
	HashTable& put(keytype key, const valuetype& value) {
        for (int i = 0; i < 2; ++i) {
            try {
                find_key(key);
            } catch (const key_not_found& err) {
                int index = hash(key);

                KeyNode key_node;
                key_node.key = key;
                key_node.value_index = index;

                ValueNode value_node;
                value_node.value = value;
                value_node.key_index = index;

                keys[index] = key_node;
                values[index] = value_node;
                
                amount_of_records += 1;
                
                return *this;
            }

            resize();
        }

        throw key_collision("there is a collision or you are trying to put an existing key");
    };

	HashTable& remove(keytype key) {
        int trash_index = find_key(key);

        keys[trash_index].key = "";
        keys[trash_index].value_index = -1;

        values[trash_index].value = "";
        values[trash_index].key_index = -1;

        amount_of_records -=1;

        return *this;
    };

	bool has_own_property(keytype key) const {
        try {
            find_key(key);
        } catch (const key_not_found& err) {
            return false;
        }
        return true;
    };

	valuetype get_value(keytype key) const {
        return values[find_key(key)].value;
    };

	valuetype& operator[](keytype key) {
        return values[find_key(key)].value;
    };

	void print(ostream& os) const {
        for (int i = 0; i < size; ++i) {
            if (keys[i].key != "") {
                os << keys[i].key << "\t|\t" << values[i].value << "\n";
            }
        }
    };

};