#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include "matrix.h"

matrix::matrix() :size_x(0), size_y(0) {
#if arr == 1
	data = nullptr;
#endif

};

	matrix::matrix(int _size_x ,int _size_y):size_x(_size_x),size_y(_size_y) {
		init(size_x, size_y);
	}

	matrix::matrix(const matrix& other) : size_x(other.size_x), size_y(other.size_y) {
		init(size_x, size_y);
#if arr == 1
		memcpy(data, &other.data, sizeof(other.data));
#endif
	}

	void matrix::init(int _size_x, int _size_y) {

		//reserve enough memory
		size_x = _size_x;
		size_y = _size_y; 

#if arr == 1

		this->data = new double* [this->size_y];
		for (int i = 0; i < size_y; i++) {
			data[i] = new double[size_x];
		}

		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				data[y][x] = 0;
			}
		}

#else
		/*
		
		for (int i = 0; i < size_y; i++) {
			std::vector<double> temp;
			data[i]push_back(temp);
		}

		*/

		for (int y = 0; y < size_y; y++) {
			std::vector<double> temp;
			for (int x = 0; x < size_x; x++) {
				temp.push_back(0);
			}
			data.push_back(temp);
		}

#endif


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

	void matrix::random_fill() {

		printf("tablice sa inicjalizowane stala wartoscia zamiast losowej w funckcji matrix::random_fill()\n");

		
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				
				data[y][x] = 0,5;
			}
		}
	}
	
	matrix matrix::transpose() {
		matrix a(size_y, size_x);

		//przetestowac dla macierzy prostokatnej

			for (int y = 0; y < size_y; y++) {
				for (int x = 0; x < size_x; x++) {
					a.data[x][y] = data[y][x];
				}
			}
		
		return a;
	}
	
	matrix matrix::operator*(matrix b) {
		if (size_x != b.size_y) { throw std::invalid_argument("ilosc kolumn pierwszej macierzy nie jest rowna ilosci wierszy drugiej "); }
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
		if (size_x != b.size_y) { throw std::invalid_argument("rozmiary macierzy nie sa takie same"); }
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
		if (size_x != b.size_y) {throw std::invalid_argument("rozmiary macierzy nie sa takie same"); }
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
		//data = nullptr;
	}







