#pragma once

#define DEBUG
#include <vector>

class matrix
{
private:
public:
	int size_x;
	int size_y;

#if arr == 1

	double** data;

#else
	std::vector<std::vector<double>> data;

#endif

	matrix();
	matrix(const matrix& other); //konstruktor kopiujacy
	matrix(int, int);
	~matrix();

	void init(int, int);

	matrix operator+(matrix);
	matrix operator+(double);

	matrix operator-(matrix);
	matrix operator-(double);
	
	matrix operator*(matrix);
	matrix operator*(double);

	matrix transpose();

	void fill_table(double**);
	void fill(double);
	void random_fill();

	void show();
	void apply_function(double (*)(double));
	
};

