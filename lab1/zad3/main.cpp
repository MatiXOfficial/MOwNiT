#include <vector>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <iostream>

using namespace std;

template <class T>
T iterativeSum(vector<T> &arr);
template <class T>
T iterativeSumBackward(vector<T> &arr);
template <class T>
void printIterativeResults(ofstream &resultsFile, string title, vector<int> &seriesLength, vector<T> &series);
template <class T>
T kahanSum(vector<T> &arr);
template <class T>
void printKahanResults(ofstream &resultsFile, string title, vector<int> &seriesLength, vector<T> &series);


int main()
{
    ofstream resultsFile;
    resultsFile.open("results3.txt", ios::trunc);

    // 3.1, 3.2 -----------------------------------------------
    resultsFile << "3.1, 3.2" << endl;
    vector<int> seriesLength = {50, 100, 200, 500, 800};
    vector< vector<float> > floatSeries;
    vector< vector<double> > doubleSeries;
    for (int i = 0; i < seriesLength.size(); i++)
    {
        floatSeries.push_back({1.0 / 4.0});
        doubleSeries.push_back({1.0 / 4.0});
        for (int j = 1; j <= seriesLength[i]; j++)
        {
            floatSeries[i].push_back(floatSeries[i][j - 1] / 2.0);
            doubleSeries[i].push_back(doubleSeries[i][j - 1] / 2.0);
        }
    }
    resultsFile << "Iterative sum: " << endl;
    printIterativeResults(resultsFile, "float", seriesLength, floatSeries);
    printIterativeResults(resultsFile, "double", seriesLength, doubleSeries);
    resultsFile << endl;

    // 3.4 ----------------------------------------------------
    resultsFile << "3.4" << endl;
    resultsFile << "Kahan sum: " << endl;
    printKahanResults(resultsFile, "float", seriesLength, floatSeries);
    printKahanResults(resultsFile, "double", seriesLength, doubleSeries);
    resultsFile.close();
}


template <class T>
T iterativeSum(vector<T> &arr)
{
    T sum = 0;
    for (auto el : arr)
    {
        sum += el;
    }
    return sum;
}

template <class T>
T iterativeSumBackward(vector<T> &arr)
{
    T sum = 0;
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        sum += arr[i];
    }
    return sum;
}

template <class T>
void printIterativeResults(ofstream &resultsFile, string title, vector<int> &seriesLength, vector<T> &series)
{
    resultsFile << title << endl;
    resultsFile << setw(4) << "N" << setw(36) << "FORWARD" << setw(36) << "BACKWARD" << endl;
    for (int i = 0; i < seriesLength.size(); i++)
    {
        resultsFile << setw(4) << seriesLength[i] << setw(36) << setprecision(32) << iterativeSum(series[i])
        << setw(36) << setprecision(32) << iterativeSumBackward(series[i]) << endl;
    }   
}

template <class T>
T kahanSum(vector<T> &arr)
{
    T sum = 0;
    T err = 0;
    for (auto el : arr)
    {
        T y = el - err;
        T temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}

template <class T>
void printKahanResults(ofstream &resultsFile, string title, vector<int> &seriesLength, vector<T> &series)
{
    resultsFile << title << endl;
    resultsFile << setw(4) << "N" << setw(36) << "kahanSum" << endl;
    for (int i = 0; i < seriesLength.size(); i++)
    {
        resultsFile << setw(4) << seriesLength[i] << setw(36) << setprecision(32) << kahanSum(series[i]) << endl;
    }   
}