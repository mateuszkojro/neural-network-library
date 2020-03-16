#pragma once
class matrix
{
private:
public:
	int size_x;
	int size_y;

	double** data;

	matrix(int, int);
	~matrix();

	matrix operator+(matrix);
	matrix operator+(double);

	matrix operator-(matrix);
	matrix operator-(double);
	
	matrix operator*(matrix);
	matrix operator*(double);

	void fill_table(double**);
	void fill(double);
	void random_fill();
	void show();
	void apply_function(double (*)(double));
	
};

