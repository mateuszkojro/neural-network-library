#pragma once

#include "matrix.h"



class net
{
private:
public:
	int input_size;
	matrix* input;

	int output_size;
	matrix* output;

	matrix* weights_input_h;
	matrix* weights_hidden_o;

	matrix* bias_hidden;
	matrix* bias_output;

	net();
	~net();

	void init();
	void feed_forward();
	void bacpropagate();
	void calculate_error();
	void predict();
	void teach();

	void export_json();
	void export_binary();

	void load_json();
	void load_binary();


};

