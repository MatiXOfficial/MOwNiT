#pragma once

#include <fstream>
#include <string>
#include <functional>
#include <vector>

#include "integrals.h"


void printIntegralJson(std::ofstream &file, std::string title, std::string x_title, 
                       Integral &&integral, std::function<double(double)> f,
                       double start, double end, double trueValue, const std::vector<int> &N);

void printFunctionIntegralsJson(int f_idx, std::ofstream &file, std::function<double(double)> f,
                                double start, double end, double trueValue, 
                                const std::vector<int> &N_intervals, const std::vector<int> &N_samples);


#include "utils.cpp"