#include "net.h"

net::net(int _input, int _hidden, int _output, double _learning_rate, double (*_activation_func)(double)) :input_size(_input), hidden_size(_hidden), output_size(_output), learning_rate(_learning_rate), activation_func(_activation_func) {

	weights_input_h.init(hidden_size, input_size);//kolejnosc jest wazna a nie wiem czy ta jest ok
	weights_hidden_o.init(output_size, hidden_size);
	weights_input_h.random_fill();
	weights_hidden_o.random_fill();

	bias_hidden.init(hidden_size, 1);
	bias_output.init(output_size, 1);
	bias_hidden.random_fill();
	bias_output.random_fill();

}

void  net::predict(matrix a) {
	
	input = a;
	hidden = weights_input_h * input;
	hidden = hidden + bias_hidden;
	hidden.apply_function(activation_func);
	 
	output = weights_hidden_o * hidden;
	output = output + bias_output;
	output.apply_function(activation_func);

}

void net::teach(matrix _input ,matrix _train_data) {
	/*
	
	JESZCZE RAZ BO KOMPLETNIE NIE JESTEM PEWNY TEGO CZY TO JEST OK 
	
	*/

	//calculate values with current weights
	predict(input);

	matrix output_errors = _train_data - output;

	//calculate gradient
	matrix gradient = output;
	gradient.apply_function();
	gradient = gradient * output_errors;
	gradient = gradient * learning_rate;

	//calculate delta
	matrix hidden_t = hidden.transpose();
	matrix weights_hidden_o_delta = gradient * hidden_t;

	weights_hidden_o = weights_hidden_o + weights_hidden_o_delta;
	bias_output = bias_output + gradient;

	matrix who_t = weights_hidden_o.transpose();
	matrix hidden_errors = who_t * output_errors;

	matrix hidden_gradient = hidden;
	hidden_gradient.apply_function();
	hidden_gradient = hidden_gradient * hidden_errors;
	hidden_gradient = hidden_gradient * learning_rate;

	matrix input_t = _input.transpose();
	matrix weights_input_h_delta = hidden_gradient * input_t;
	weights_input_h = weights_input_h + weights_hidden_o_delta;
	bias_hidden = bias_hidden + hidden_gradient;


}
