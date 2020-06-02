#include <fstream>
#include <string>
#include <iostream>
#include "fourier/dft.h"
#include "fourier/fft.h"

int main()
{
    // Zad. 3
    std::ofstream resultsFile("data/results.json", std::ios::trunc);
    resultsFile << "{" << std::endl;

    resultsFile << "\"times\" : " << std::endl << "{" << std::endl;
    resultsFile << "\"DFT\" : [";
    std::vector<int> dftSizes;
    int start = std::pow(2, 7), stop = std::pow(2, 13);
    for (double n = start; n <= stop; n *= 2)
    {
        double time = DFT(n).timeCalculate();
        resultsFile << "[" << n << "," << time << "]";
        if (n < stop)
            resultsFile << ", ";
    }
    resultsFile << "]," << std::endl;

    resultsFile << "\"FFT\" : [";
    std::vector<int> fftSizes;
    start = std::pow(2, 9), stop = std::pow(2, 21);
    for (double n = start; n <= stop; n *= 2)
    {
        double time = FFT(n).timeCalculate();
        resultsFile << "[" << n << "," << time << "]";
        if (n < stop)
            resultsFile << ", ";
    }

    resultsFile << "]" << std::endl;
    resultsFile << "}," << std::endl;

    // Zad. 4
    std::vector<std::string> xData;
    std::vector<double> yData;

    std::ifstream csvFile("data/summer.csv");
    std::string buffer;
    while(getline(csvFile, buffer, ','))
    {
        xData.push_back(buffer);
        getline(csvFile, buffer, '\n');
        yData.push_back(std::stod(buffer));
    }
    csvFile.close();
    
    resultsFile << "\"summer\" : [";

    auto fft = FFT(yData);
    auto result = fft.calculate();
    int N_new = fft.getDataSize();

    for (int i = 0; i < N_new; i++)
    {
        resultsFile << "[" << (i * 12.0) / N_new << "," << std::abs(result[i]) << "]";
        if (i < N_new - 1)
            resultsFile << ", ";
    }
    resultsFile << "]" << std::endl;
    resultsFile << "}" << std::endl;
    
    resultsFile.close();
}