#include <stdio.h>

#include "matrix.h"


	matrix::matrix(int _size_x ,int _size_y):size_x(_size_x),size_y(_size_y) {
		this->data = new double* [this->size_y];
		for (int i = 0; i < size_y; i++) {
			data[i] = new double[size_x];
		}

		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				data[y][x] = 0;
			}
		}

	}

	void matrix::show() {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				printf(" | %0.2lf ", data[y][x]);
			}
			printf("\n");
		}
	}

	void matrix::apply_function(double(* func)(double)) {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				data[y][x] = func(data[y][x]);
			}
		}
	}

	void matrix::fill(double b) {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				data[y][x] = b;
			}
		}
	}

	void matrix::fill_table(double** tab) {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				data[y][x] = tab[y][x];
			}
		}
	}

	/*
	safe copy
	
		matrix matrix::operator*(matrix b) {
		matrix c(size_x, b.size_y);
		for (int y = 0; y < b.size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				for (int z = 0; z < size_x; z++) {
					c.data[y][x] += this->data[y][z] * b.data[z][x];
				}
			}
		}
		return c;
	}

	*/
	matrix matrix::operator*(matrix b) {
		matrix c(b.size_x, size_y);
		for (int y = 0; y < b.size_y; y++) {
			for (int x = 0; x < b.size_x; x++) {
				for (int z = 0; z < size_x; z++) {
					c.data[y][x] += this->data[y][z] * b.data[z][x];
					//printf("y=%d , x=%d , z = %d \n", y, x, z);
				}
			}
		}
		return c;
	}

	

	matrix matrix::operator*(double b) {
		matrix c(size_x, size_y);
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				c.data[y][x] = this->data[y][x] * b;
			}
		}
		return c;
	}

	matrix matrix::operator+(matrix b) {
		matrix c(size_x, size_y);
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				c.data[y][x] = this->data[y][x] + b.data[y][x];
			}
		}
		return c;
	}

	matrix matrix::operator+(double b) {
		matrix c(size_x, size_y);
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				c.data[y][x] = this->data[y][x] + b;
			}
		}
		return c;
	}

	matrix matrix::operator-(matrix b) {
		matrix c(size_x, size_y);
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				c.data[y][x] = this->data[y][x] - b.data[y][x];
			}
		}
		return c;
	}

	matrix matrix::operator-(double b) {
		matrix c(size_x, size_y);
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				c.data[y][x] = this->data[y][x] - b;
			}
		}
		return c;
	}

	matrix::~matrix() {
		//delete [] data;
		data = nullptr;
	}





