#include <iostream>
#include <type_traits>
#include <list>
#include <string>
#include <forward_list>

using std::string;
using std::forward_list;

class HashTable {
	const int table_size;
	forward_list<int>* ht;
public:
	class Bad_Table_Size {
		int bts;
	public:
		Bad_Table_Size(int ts) : bts{ ts } {}
		int ts() { return bts; }
	};
	HashTable(int ts) : table_size{ ts } {
		if (ts < 0) 
			throw Bad_Table_Size(ts);
		ht = new forward_list<int>[ts]; 
	}
	int get_ts() const { return table_size; }
	int simple_hash(int value) { return value % table_size; }

	//return true if value found in hash table, else return false
	bool search(int value) {
		for (auto x : ht[simple_hash(value)]) {
			if (x == value)
				return true;
		}
		return false;
	}

	void insert(int value) { ht[simple_hash(value)].push_front(value); }

	void delete_val(int value) {
		int hash = simple_hash(value);
		forward_list<int>::iterator it = ht[hash].begin();
		//empty list
		if (it == ht[hash].end()) return;
		if (*it == value) {
			ht[hash].pop_front();
			return;
		}
		while (next(it) != ht[hash].end()) {
			if (*next(it) == value) {
				ht[hash].erase_after(it);
				return;
			}
			it++;
		}
	}

	void print_ht() {
		for (int i = 0; i < table_size; i++) {
			std::cout << "index: " << i << ": ";
			for (forward_list<int>::iterator it = ht[i].begin(); it != ht[i].end(); it++) {
				std::cout << *it << ' ';
			}
			std::cout << '\n';
		}
	}
	~HashTable() {
		delete[] ht;
	}
};


int main() {
	std::size_t h1 = std::hash<std::string>{}("Anton"); //h1 is of type std::size_ t
	std::cout << h1;
	auto a = static_cast<int>(h1 % 13);
	std::cout << '\n' << typeid(a).name() << '\n';;

	//std::list<int> htable[13];
	//htable[0].push_back(3);
	//htable[0].push_back(4);
	//std::cout << '\n' << htable[0].front();
	//std::cout << '\n' << htable[0].back();

	HashTable ht(10);
	int arr[]{ 42,521,2,4,3,65,77,55,45,52 };
	/*int arrSize = sizeof(arr) / sizeof(arr[0]);
	std::cout << arrSize << '\n';*/
	for (int x : arr)
		ht.insert(x);
	ht.print_ht();
	std::cout << ht.search(55) << ' ' << ht.search(20) << '\n';
	ht.insert(400);
	ht.delete_val(65);
	ht.print_ht();
}