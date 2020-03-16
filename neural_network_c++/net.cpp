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

void net::teach(matrix input ,matrix train_data) {

}
