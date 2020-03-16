#pragma once

#define DEBUG

class matrix
{
private:
public:
	int size_x;
	int size_y;

	double** data;

	matrix();
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

