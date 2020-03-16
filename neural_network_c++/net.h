#pragma once

#include "matrix.h"



class net
{
private:
public:
	int input_size;
	matrix input;

	int hidden_size;
	matrix hidden;

	int output_size;
	matrix output;

	matrix errors;

	double learning_rate;
	double (*activation_func)(double);

	matrix weights_input_h;
	matrix weights_hidden_o;

	matrix bias_hidden;
	matrix bias_output;

	net();
	net(int input, int hidden ,int output, double lerning_rate, double (*activation_func)(double));
	~net();

	//void init(int input, int hidden, int output ,double lerning_rate, double (*activation_func)(double));
	void feed_forward();
	void bacpropagate();
	void calculate_error();
	
	void predict(matrix a);
	void teach(matrix input , matrix train_data);

	void export_json();
	void export_binary();

	void load_json();
	void load_binary();


};

