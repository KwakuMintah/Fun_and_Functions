// Chladni_Simulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "KC.hpp"
#include "Piano.hpp"
#include "WaveFunc.hpp"
using namespace std;

//This is all in mm

void announcement(bool choice_mat, bool choice_shape, double freq, int size) {
    //True is Al and Square
    if (choice_mat == true) {
        if (choice_shape == true) {
            cout << "\n" << "Simulation of Aluminium Chladni Plate at frequency of " << freq << " and side length of " << size << ".";
        }
        else {
            cout << "\n" << "Simulation of Aluminium Chladni Plate at frequency of " << freq << " and diameter of " << size << ".";
        }
    }
    else {
        if (choice_shape == true) {
            cout << "\n" << "Simulation of Steel Chladni Plate at frequency of " << freq << " and side length of " << size << ".";
        }
        else {
            cout << "\n" << "Simulation of Steel Chladni Plate at frequency of " << freq << " and diameter of " << size << ".";
        }
    }
};

int main()
{
    std::cout << "Hello World!\n";
    ofstream datafile("Chladni.txt");

    int i;

    double kE = kVal(629.8);
    //double kE = otherKVal(2, 0, 200);
    //Divide density by 1000 to go from g/cm to g/mm
    double cE = cVal(young_al_exp, 0.168, 0.0027, pois_al);
    double freqE = freqPlate(cE, kE);

    int size = 240;
    int size_sq = pow(size, 2);

    announcement(true, true, freqE, size);

    impedanceGraph(v_nought, current, 50, 60, size);

    //animation(50, 60, 2, 1, 1, size, 100);


    cout << "\n" << "Testing Different Times.";
    double* waveTestOne = waveEq(2, 1, freqE, 1, size, 10);
    cout << "\n" << "Measuring Time of 10s Finished";
    double* waveTestTwo = waveEq(2, 1, freqE, 1, size, 20);
    cout << "\n" << "Measuring Time of 20s Finished";
    double* waveTestThree = waveEq(2, 1, freqE, 1, size, 50);
    cout << "\n" << "Measuring Time of 50s Finished";
    double* waveTestFour = waveEq(2, 1, freqE, 1, size, 100);
    cout << "\n" << "Measuring Time of 100s Finished";
    double* waveTestFive = waveEq(2, 1, freqE, 1, size, 200);
    cout << "\n" << "Measuring Time of 200s Finished";
    double* waveTestSix = waveEq(2, 1, freqE, 1, size, 500);
    cout << "\n" << "Measuring Time of 500s Finished";
    for (i = 0; i < size_sq; i++) {
        datafile << "\n" << waveTestOne[i] << "\t" << waveTestTwo[i] << "\t" << waveTestThree[i] << "\t" << waveTestFour[i] << "\t" << waveTestFive[i] << "\t" << waveTestSix[i];
    }


}