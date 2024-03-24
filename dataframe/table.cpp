#include <iostream>
#include <string>
using namespace std;

class Table {
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

private:
	size_t size;
	size_t amount_of_records;
	size_t end_of_array;
	KeyNode* keys;
	ValueNode* values;

	void resize() {
		size_t new_size = size + 15;
		KeyNode* new_keys = new KeyNode[new_size];
		ValueNode* new_values = new ValueNode[new_size];

		int i;
		for (i = 0; i < size; ++i) {
			new_keys[i] = keys[i];
			new_values[i] = values[i];
		}
		end_of_array = i;

		size = new_size;
		delete[] keys;
		keys = new_keys;
		delete[] values;
		values = new_values;
	};

	size_t find_key(keytype key) const {
		int start = 0; int end = amount_of_records - 1;
		while (start <= end)
		{
			int middle = (start + end) / 2;
			if (key == keys[middle].key)
			{
				return middle;
			}
			else if (key > keys[middle].key)
			{
				start = middle + 1;
			}
			else if (key < keys[middle].key)
			{
				end = middle - 1;
			}
		}

		throw key_not_found("There is no key in keys collection");
	};

public:
	Table(size_t size) {
		keys = new KeyNode[size];
		values = new ValueNode[size];
		amount_of_records = 0;
		this->size = size;
		end_of_array = 0;

		for (int i = 0; i < size; ++i) {
			keys[i].key = "";
		}
	};

	size_t get_amount_of_records() const { return amount_of_records; };
	
	Table& put(keytype key, const valuetype& value) {
		try {
			this->find_key(key);
		}
		catch (const key_not_found& err) {
			if (size == amount_of_records) resize();

			int i = end_of_array;
			for (i = amount_of_records - 1; (i >= 0 && keys[i].key > key); i--) {
				keys[i + 1] = keys[i];
			}

			keys[i + 1].key = key;
			keys[i + 1].value_index = end_of_array;
			values[end_of_array].key_index = i + 1;
			values[end_of_array].value = value;
			++end_of_array;
			++amount_of_records;

			return *this;
		}

		values[keys[this->find_key(key)].value_index].value = value;
		return *this;
	};

	Table& remove(keytype key) {
		size_t index2remove = this->find_key(key);
		size_t index2remove_value = keys[index2remove].value_index;

		for (int i = index2remove; i < amount_of_records - 1; ++i) {
			keys[i] = keys[i + 1];
		}
		for (int i = index2remove_value; i < amount_of_records - 1; ++i) {
			values[i] = values[i + 1];
		}

		--amount_of_records;
		--end_of_array;

		return *this;
	};

	bool has_own_property(keytype key) {
		try {
			this->find_key(key);
		}
		catch (const key_not_found& err) {
			return false;
		}

		return true;
	};

	valuetype get_value(keytype key) {
		return values[keys[this->find_key(key)].value_index].value;
	};

	valuetype& operator[](keytype key) {
		return values[keys[this->find_key(key)].value_index].value;
	};

	void print(ostream& os) {
		for (int i = 0; i < amount_of_records; ++i) {
			os << keys[i].key << ": " << this->get_value(keys[i].key) << endl;
		}
	};

};