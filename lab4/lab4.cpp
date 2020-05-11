#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;
typedef unsigned int uint;
const uint N = 10;
string delta(uint power);
string dispH(uint n);
string dispChebPol(uint n, double*);
string divFunc(uint n);
string top(uint n);
void fillChebArr(uint n, double a, double b, double* chebArr);
void dispChebPoints(uint n, double*);
int main()
{	
	// enter amount of xi
	cout << "Amount of points: " << N << "\n\n";
	cout << "Equal-spaced points:\n";
	cout << dispH(N) << "\n";
	double* chebArr = new (nothrow) double[N];
	if (chebArr == nullptr) exit(123);
	cout << "Chebyshev points: \n";
	fillChebArr(N, -1, 1, chebArr);
	cout << dispChebPol(N, chebArr) << "\n";
	dispChebPoints(N, chebArr);
}

string dispChebPol(uint n, double* chebArr) {
	string res = "f0 + \n";
	string xbraces = "";
	for (uint i = 0; i < n-1; i++) {
		i == n - 1 ? xbraces += "" : xbraces += "(x-x" + to_string(i) + ")";
		res += xbraces + divFunc(i + 2);
		i == n - 2 ? res += "\n" : res += "+\n";
	}
	return res;
}

string divFunc(uint n) {
	string res = "f(";
	for (uint i = 0; i < n; i++) {
		res += "x" + to_string(i);
		i == n - 1 ? res += ")" : res += ";";
	}
	return res;
}
void fillChebArr(uint n, double a, double b, double* chebArr) {
	double eps = 1e-14;
	for (uint k = 0; k < n; k++) {
		double res = (a + b) / 2 - (b - a) / 2 * cos((2.0 * k + 1) * M_PI / (2.0 * n));
		res = -res;
		if (fabs(res) < eps) res = 0;
		chebArr[k] = res;
	}
}

string dispH(uint n) {
	string res = "f0 + \nt(f1 - f0) + \n";
	uint fact = 1;
	for (uint i = 1; i < n - 1; i++) {
		fact *= (i + 1);
		res += top(i) + "*" + delta(i + 1) + "/" + to_string(fact);// +" + ";
		i == n - 2 ? res += "" : res += " + ";
		res += "\n";
	}
	return res;
}

string top(uint n) {
	string res = "t";
	for (uint i = 1; i <= n; i++) {
		res += "(t-" + to_string(i) + ")";
	}
	return res;
}

string delta(uint power) {
	string res = "(f";
	res += to_string(power);
	res += " -2*f";
	res += to_string(power - 1);
	res += " +f";
	res += to_string(power - 2) + ")";
	return res;
}

void dispChebPoints(uint n, double* chebArr) {
	cout << "Where xi are:\n";
	for (uint i = 0; i < n; i++) {
		cout << "x" + to_string(i) + ": " << setw(7) << chebArr[i] << "\n";
	}
}