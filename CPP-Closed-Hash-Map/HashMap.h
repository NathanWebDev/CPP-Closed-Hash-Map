#include <iostream>
#include <vector>
#include <string>

template <typename Fruit, typename Id>
class HashMap
{
private:
	struct Entry {
		Fruit fruit;
		Id id;
		bool is_occupied;
		bool is_deleted;
	};

	std::vector<Entry> fruitBasket;
	size_t capacity;
	size_t size;

	size_t hash(const Fruit& fruit) const {
		return std::hash<Fruit>()(fruit) % capacity;
	}

	size_t probe(size_t index, size_t i) const {
		return (index + i) % capacity;
	}

public:
	ClosedHashMap(size_t initial_capacity = 10) : capacity(initial_capacity), size(0) {
		fruitBasket.resize(capacity);
		for (size_t i = 0; i < capacity; i++) {
			fruitBasket[i].is_occupied = false;
			fruitBasket[i].is_deleted = false;
		}
	}

	void insert(const Fruit& fruit, Id& id) {
		if (size >= capacity / 2) {
			rehash();
		}

		size_t index = hash(fruit);
		for (size_t i = 0; i < capacity; ++i) {
			size_t current_index = probe(index, i);
		}
	}
		
		
};

