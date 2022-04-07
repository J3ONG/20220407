#include <iostream>


class Array {
	const int dim;
	int* size;

	struct Address {
		int level;

		void* next;

	};

	Address* top;

public:

	Array(int dim, int* array_size) :dim(dim) {
		size = new int[dim];
		for (int i = 0; i < dim; i++) {
			size[i] = array_size[i];
		}
		top = new Address;
		top->level = 0;
		
		initialize_address(top);
	}

	Array(const Array& arr) : dim(arr.dim) {
		size = new int[dim];

		for (int i = 0; i < dim; i++) {
			size[i] = arr.size[i];
		}
		top = new Address;
		top->level = 0;

		initialize_address(top);

		copy_address(top, arr.top);
	}

	void copy_address(Address * dst, Address * src) {
		if (dst->level == dim - 1) {
			for (int i = 0; i < size[dst->level]; ++i) {
				static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];

			}
			return;
		}
		for (int i = 0; i != size[dst->level]; i++) {
			Address* new_dst = static_cast<Address*> (dst->next) + i;
			Address* new_src = static_cast<Address*> (src->next) + i;
			copy_address(new_dst,new_src);
		}
	}

	~Array() {
		delete_address(top);

		delete[] size;
	}

	void initialize_address(Address* current) {
		if (!current)	return;

		if (current->level == dim - 1) {//종료조건
			current->next = new int[size[current->level]];
			return;
		}

		current->next = new Address[size[current->level]];

		for (int i = 0; i != size[current->level]; i++) {//다음단계
			(static_cast<Address*>(current->next) + i)->level = current->level + 1;

			initialize_address(static_cast<Address*>(current->next) + 1);
		}

	}


	void delete_address(Address* current) {
		if (!current)return;

		for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++) {
			delete_address(static_cast<Address*> (current->next) + i);
		}

		if (current->level == dim - 1) {
			delete[]	static_cast<int*>	(current->next);

		}

		delete[] static_cast<Address*>	(current->next);
	}

};

