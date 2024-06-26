#include <iostream>
#include "Constants.hpp"
using namespace std;
#ifndef KCHEADERDEF
#define KCHEADERDEF

double kVal(double freq) {
	double val = (freq * pi_doub) / sound_v;
	cout << "\n" << "Wave Number is: " << val;
	return val;
}

double otherKVal(int modeX, int modeY, int size) {
	double coef = pi / size;
	double modeX_sq = pow(modeX, 2);
	double modeY_sq = pow(modeY, 2);
	double root = sqrt(modeX_sq + modeY_sq);
	double val = coef * root;
	cout << "\n" << "Wave Number is: " << val;
	return val;
}

double cVal(double young, double thick, double dens, double pois) {
	double coef = 1 / pi_doub;
	double thi_sq = pow(thick, 2);
	double num = young * thi_sq;
	double pois_sq = pow(pois, 2);
	double brac = 1 - pois_sq;
	double out_brac = 12 * dens;
	double den = out_brac * brac;
	double frac = num / den;
	double frac_root = sqrt(frac);
	double val = coef * frac_root;
	cout << "\n" << "The Coefficient is: " << val;
	return val;
}

double freqPlate(double C, double K) {
	double k_sq = pow(K, 2);
	double val = C * k_sq;
	return val;
}

#endif