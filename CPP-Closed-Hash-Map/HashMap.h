#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename Fruit, typename Id>
class HashMap
{
private:
	struct Entry {
		Fruit fruit;
		Id id;
		bool is_occupied;
		bool is_deleted;
		Entry() : is_occupied(false), is_deleted(false) {}
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

	void rehash() {
		size_t old_capacity = capacity;
		capacity *= 2;
		std::vector<Entry> oldBasket = std::move(fruitBasket);
		fruitBasket = std::vector<Entry>(capacity);
		size = 0;
		for (size_t i = 0; i < old_capacity; ++i) {
			if (oldBasket[i].is_occupied && !oldBasket[i].is_deleted) {
				insert(oldBasket[i].fruit, oldBasket[i].id);
			}
		}
	}

public:
	HashMap(size_t initial_capacity = 10) : capacity(initial_capacity), size(0) {
		fruitBasket.resize(capacity);
	}

	void insert(const Fruit& fruit, const Id& id) {
		if (size >= capacity / 2) {
			rehash();
		}

		size_t index = hash(fruit);
		for (size_t i = 0; i < capacity; ++i) {
			size_t current_index = probe(index, i);
			Entry& entry = fruitBasket[current_index];
			if (!entry.is_occupied || entry.is_deleted) {
				entry.fruit = fruit;
				entry.id = id;
				entry.is_occupied = true;
				entry.is_deleted = false;
				++size;
				return;
			}
			// Update if same fruit
			if (entry.is_occupied && !entry.is_deleted && entry.fruit == fruit) {
				entry.id = id;
				return;
			}
		}
	}

	bool erase(const Fruit& fruit) {
		size_t index = hash(fruit);
		for (size_t i = 0; i < capacity; ++i) {
			size_t current_index = probe(index, i);
			Entry& entry = fruitBasket[current_index];
			if (!entry.is_occupied && !entry.is_deleted) {
				return false;
			}
			if (entry.is_occupied && !entry.is_deleted && entry.fruit == fruit) {
				entry.is_deleted = true;
				--size;
				return true;
			}
		}
		return false;
	}

	size_t getSize() const {
		return size;
	}
};