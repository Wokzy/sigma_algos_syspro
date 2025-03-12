#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define is_digit(c) (c >= '0' && c <= '9')

// vector<string> split(string s, const string &delimiter) {
// 	vector<string> tokens;
// 	size_t pos = 0;
// 	string token;
// 	while ((pos = s.find(delimiter)) != string::npos) {
// 		token = s.substr(0, pos);
// 		tokens.push_back(token);
// 		s.erase(0, pos + delimiter.length());
// 	}
// 	tokens.push_back(s);

// 	return tokens;
// }


unordered_map<string, int> operator_precedence = {
	{"**", 1}, // power (2 ** 3) == 8 righ-assosiative exponentiation
	{"*", 2},
	{"/", 2},
	{"%", 2},
	{"+", 3},
	{"-", 3},
	{"<<", 4},
	{">>", 4},
	{"&", 5},
	{"^", 6},
	{"|", 7},
	{"&&", 8},
	{"||", 9},
};

unordered_set<string> right_assosiative = {"**"};

vector<string> tokenize(string &input) {

	vector<string> res;

	string token;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ' ') {
			if (token.size()) {
				res.push_back(token);
				token = "";
			}
		} else if (is_digit(input[i])) {
			token += input[i];
		} else if (input[i] == '(' || input[i] == ')') {
			if (token.size()){
				res.push_back(token);
				token = "";
			}
			token += input[i];
			res.push_back(token);
			token = "";
		} else {
			token += input[i];
			if (input[i] == input[i + 1]) {
				token += input[i];
				i++;
			}
		}
	}

	if (token.size())
		res.push_back(token);

	return res;
}

string infix_to_postfix(string &input) {
	int n = input.size();
	if (input[n - 1] != ')' && !is_digit(input[n - 1])) {
		cout << "INVALID EXPRESSION\n";
		return "";
	}

	vector<string> res;
	vector<string> tokens = tokenize(input);
	vector<string> stack;

	for (string &token : tokens) {


		if (is_digit(token[0])) {
			res.push_back(token);
			continue;
		}

		if (token == "(") {
			stack.push_back(token);
			continue;
		}

		if (token == ")") {
			while (stack[stack.size() - 1] != "(") {
				res.push_back(stack[stack.size() - 1]);
				stack.pop_back();
			}
			stack.pop_back();
			continue;
		}

		while (stack.size()) {
			string op2 = stack[stack.size() - 1];
			if (op2 == "(")
				break;
			if (operator_precedence[op2] > operator_precedence[token])
				break;
			if (operator_precedence[op2] == operator_precedence[token] && right_assosiative.contains(token))
				break;
			res.push_back(op2);
			stack.pop_back();
		}
		stack.push_back(token);
	}

	while (stack.size()) {
		res.push_back(stack[stack.size() - 1]);
		stack.pop_back();
	}

	string out = res[0];
	for (int i = 1; i < res.size(); i++)
		out += " " + res[i];

	return out;
}

int main(void) {
	cout << "Test format: {input} -> {result}\n\n";

	string test;
	test = "3 + 4";
	cout << test << " -> " << infix_to_postfix(test) << endl;

	test = "2 * (5 + 6)";
	cout << test << " -> " << infix_to_postfix(test) << endl;

	test = "4 + 2 ** 4 - 150 / 3";
	cout << test << " -> " << infix_to_postfix(test) << endl;

	test = "1 | 4 + 2 ** (4 - 150 / 3) ** 122 << 12";
	cout << test << " -> " << infix_to_postfix(test) << endl;

	return 0;
}
