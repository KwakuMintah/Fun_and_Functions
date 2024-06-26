#include <iostream>
using namespace std;
#ifndef CONSTANTSHEADERDEF
#define CONSTANTSHEADERDEF

//Young's Modulus is in N/m^2

double pi = 3.14;
double pi_doub = 2 * pi;

double sound_v = 346000;

double young_al = 68;
double young_kev = 70.5;
double young_bone = 14;
double young_brass = 106;
double young_bronze = 112;
double young_cop = 110;
double young_poly = 2.5;
double young_rub = 0.01;
double young_steel = 200;
double young_tit = 116;
double young_map = 9.6;
double young_zinc = 108;

double pois_al = 0.33;
double pois_brass = 0.34;
double pois_cop = 0.34;
double pois_steel = 0.3;
double pois_tit = 0.34;

//Divide it by 1000000 to get it in N/mm^2
double young_al_exp = young_al / 1000000;
double young_steel_exp = young_al / 1000000;

double v_nought = 230;
double current = 2.3;


#endif