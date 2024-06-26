#include <iostream>
#include "Constants.hpp"
#include <fstream>
using namespace std;
#ifndef NOYOUNGHEADERDEF
#define NOYOUNGHEADERDEF

double* waveEq(int modeX, int modeY, double freq, double ampl, int L, int time) {
	int x, y, t, rowMaj, iter;
	double w, w_sq, modeX_sq, modeY_sq;
	double L_sq = pow(L, 2);
	double L_half = L / 2;

	double* wav = new double[L_sq + L + 1];

	modeX_sq = pow(modeX, 2);
	modeY_sq = pow(modeY, 2);
	w_sq = freq * (modeX_sq + modeY_sq);
	w = sqrt(w_sq);

	double cosNxMatch_coef, cosNxDiff_coef, cosNyMatch_coef, cosNyDiff_coef;
	double cosNxMatch, cosNxDiff, cosNyMatch, cosNyDiff;
	for (t = 0; t < time; t++) {
		for (x = 0; x < L; x++) {
			for (y = 0; y < L; y++) {
				rowMaj = y * L;
				iter = rowMaj + x;
				cosNxMatch_coef = (modeX * pi * x) / L_half;
				cosNxDiff_coef = (modeX * pi * y) / L_half;
				cosNyMatch_coef = (modeY * pi * y) / L_half;
				cosNyDiff_coef = (modeY * pi * x) / L_half;
				cosNxMatch = cos(cosNxMatch_coef);
				cosNxDiff = cos(cosNxDiff_coef);
				cosNyMatch = cos(cosNyMatch_coef);
				cosNyDiff = cos(cosNyDiff_coef);

				wav[iter] = (ampl * ((cosNxMatch * cosNyMatch) + (cosNyDiff * cosNxDiff)) * cos(w * t));
			}
		}
	}
	return wav;
}

double* waveEqCircle(int modeX, int modeY, double freq, double ampl, int L, int time) {
	//Not very confident on this one
	int theta, r, t, rowMaj, iter, pi_doub_int;
	double w, w_sq, modeX_sq, modeY_sq, theta_real;
	double L_sq = pow(L, 2);
	double L_half = L / 2;
	double L_half_sq = L_half / 2;

	double* wav = new double[L_sq + L + 1];

	pi_doub_int = int(pi_doub * time);

	modeX_sq = pow(modeX, 2);
	modeY_sq = pow(modeY, 2);
	w_sq = freq * (modeX_sq + modeY_sq);
	w = sqrt(w_sq);

	//Theta is in radians
	double sinNx_coef, sinNy_coef, cosNy_coef;
	double sinNx, sinNy, cosNy;
	for (t = 0; t < time; t++) {
		for (r = 0; r < L; r++) {
			for (theta = 0; theta < pi_doub_int; theta++) {
				rowMaj = theta * L;
				iter = r + rowMaj;
				theta_real = theta / time;
				sinNx_coef = modeX * L_half * cos(theta_real);
				sinNy_coef = modeY * L_half * sin(theta_real);
				cosNy_coef = modeY * r;
				sinNx = sin(sinNx_coef);
				sinNy = sin(sinNy_coef);
				cosNy = cos(cosNy_coef);

				wav[iter] = (ampl * (L_sq * ((sinNx) * (sinNy)) - cosNy) * cos(w * t));
			}
		}
	}
	return wav;
}

double* waveEqSquared(int modeX, int modeY, double freq, double ampl, int L, int time) {
	int x, y, t, rowMaj, iter;
	double w, w_sq, modeX_sq, modeY_sq;
	double L_sq = pow(L, 2);
	double L_half = L / 2;
	double ampl_sq = pow(ampl, 2);

	double* wav = new double[L_sq + L + 1];

	modeX_sq = pow(modeX, 2);
	modeY_sq = pow(modeY, 2);
	w_sq = freq * (modeX_sq + modeY_sq);
	w = sqrt(w_sq);

	double cosNxMatch_coef, cosNxDiff_coef, cosNyMatch_coef, cosNyDiff_coef;
	double cosNxMatch, cosNxDiff, cosNyMatch, cosNyDiff;
	double cosOmega_sq;
	for (t = 0; t < time; t++) {
		for (x = 0; x < L; x++) {
			for (y = 0; y < L; y++) {
				rowMaj = y * L;
				iter = rowMaj + x;
				cosNxMatch_coef = (modeX * pi * x) / L_half;
				cosNxDiff_coef = (modeX * pi * y) / L_half;
				cosNyMatch_coef = (modeY * pi * y) / L_half;
				cosNyDiff_coef = (modeY * pi * x) / L_half;
				cosNxMatch = cos(cosNxMatch_coef) * cos(cosNxMatch_coef);
				cosNxDiff = cos(cosNxDiff_coef) * cos(cosNxDiff_coef);
				cosNyMatch = cos(cosNyMatch_coef) * cos(cosNyMatch_coef);
				cosNyDiff = cos(cosNyDiff_coef) * cos(cosNyDiff_coef);
				cosOmega_sq = cos(w * t) * cos(w * t);

				wav[iter] = (ampl_sq * ((cosNxMatch * cosNyMatch) - (cosNyDiff * cosNxDiff)) * cosOmega_sq);
			}
		}
	}
	return wav;
}

void animation(int low, int high, int modeX, int modeY, double ampl, int L, int time) {
	ofstream datafile("ChladniAnim.txt");
	int i, j, l;
	int range = high - low;
	double* output;
	double** wave = new double* [range];
	for (i = low; i < high; i++) {
		int k = i - low;
		wave[k] = waveEq(modeX, modeY, i, ampl, L, time);
	}
	for (j = 0; j < range; j++) {
		output = wave[j];
		for (l = 0; l < time; l++) {
			datafile << output[l] << "\n";
		}
		//Can't print out as I would like just yet
		datafile << "\n";
	}
}

double* conversion(double* waveFunc, int L) {
	int i;
	double L_sq = pow(L, 2);
	double* output = new double[L_sq + L + 1];

	for (i = 0; i < L_sq; i++) {
		if (waveFunc[i] < -0.05) {
			output[i] = 1;
		}
		else if (waveFunc[i] > 0.05) {
			output[i] = 1;
		}
		else {
			output[i] = 0;
		};
	}
	return output;
}

//This is to graph the impedance and Resonant Frequencies
void impedanceGraph(double v_nought, double a, int low, int high, int time) {
	ofstream impedancefile("Impedance.m");
	//This doesn't work. Find other route to impedance
	int i, j;
	double coef, sine, val, w, v, z;
	val = low;
	int range = high - low;
	double increment = double(range) / double(time);
	double* freq = new double[time + 1];
	double* output = new double[time + 1];

	for (i = 0; i < time; i++) {
		val = val + increment;
		freq[i] = val;
	}

	for (j = 0; j < time; j++) {
		w = freq[j];
		coef = w * j;
		sine = sin(coef);
		v = v_nought * sine;
		z = v / a;
		impedancefile << "\n" << w << "\t" << z;
	}

}


#endif
