#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <chrono>

using namespace std;

constexpr int N = 1e+7;
constexpr float val = 0.7;
constexpr int step = 25000;

float recursiveSum(vector<float> &arr, int p, int r);
float kahanSum(vector<float> &arr);

int main()
{
    ofstream resultsFile;
    resultsFile.open("results1,2.txt", ios::trunc);
    resultsFile << "N: " << N << ", val: " << val << ", step: " << step << endl << endl;

    vector<float> arr(N, val);

    // 1.1, 1.2 -----------------------------------------
    resultsFile << "1.1, 1.2" << endl;
    float trueSum = N * val;
    float arrSum = 0;
    auto startIteration = chrono::high_resolution_clock::now();    // 1.6
    for (auto el : arr)
    {
        arrSum += el;
    }
    auto endIteration = chrono::high_resolution_clock::now();      // 1.6
    float absoluteError = abs(trueSum - arrSum);
    float relativeError = absoluteError / trueSum;
    resultsFile << "Absolute error: " << absoluteError << ", Relative error: " << relativeError << endl << endl;

    // 1.3 ----------------------------------------------
    resultsFile << "1.3" << endl;
    resultsFile << "Iteration number Absolute error Relative error" << endl;
    trueSum = 0, arrSum = 0;
    for (int i = 0; i < N; i++)
    {
        arrSum += arr[i];
        if ((i + 1) % step == 0)
        {
            trueSum = i * val;
            absoluteError = abs(trueSum - arrSum);
            relativeError = absoluteError / trueSum;
            resultsFile << setw(8) << i + 1 << setw(10) << absoluteError << setw(14) << relativeError << endl; 
        }
    }
    resultsFile << endl;

    // 1.4, 1.5 ------------------------------------------
    resultsFile << "1.4, 1.5" << endl;
    trueSum = N * val;
    auto startRecursive = chrono::high_resolution_clock::now(); // 1.6
    arrSum = recursiveSum(arr, 0, arr.size() - 1);
    auto endRecursive = chrono::high_resolution_clock::now();   // 1.6
    absoluteError = abs(trueSum - arrSum);
    relativeError = absoluteError / trueSum;
    resultsFile << "Absolute error: " << absoluteError << ", Relative error: " << relativeError << endl << endl;

    // 1.6 ----------------------------------------------
    resultsFile << "1.6" << endl;
    chrono::duration<double> durationIteration = endIteration - startIteration;
    chrono::duration<double> durationRecursive = endRecursive - startRecursive;
    resultsFile << "Iteration summing time: " << durationIteration.count() << " s" << endl;
    resultsFile << "Recursive summing time: " << durationRecursive.count() << " s" << endl << endl;

    // 2.1 -----------------------------------------------
    resultsFile << "2.1" << endl;
    auto startKahan = chrono::high_resolution_clock::now(); // 2.3
    arrSum = kahanSum(arr);
    auto endKahan = chrono::high_resolution_clock::now();   // 2.3
    absoluteError = abs(trueSum - arrSum);
    relativeError = absoluteError / trueSum;
    resultsFile << "Absolute error: " << absoluteError << ", Relative error: " << relativeError << endl << endl;

    // 2.3 -----------------------------------------------
    resultsFile << "2.3" << endl;
    chrono::duration<double> durationKahan = endKahan - startKahan;
    resultsFile << "Kahan summing time: " << durationKahan.count() << " s" << endl;
    resultsFile << "Recursive summing time: " << durationRecursive.count() << " s" << endl;

    resultsFile.close();
}


float recursiveSum(vector<float> &arr, int p, int r)
{
    if (p == r)
    {
        return arr[p];
    }
    int q = (p + r) / 2;
    return recursiveSum(arr, p, q) + recursiveSum(arr, q + 1, r);
}

float kahanSum(vector<float> &arr)
{
    float sum = 0;
    float err = 0;
    for (auto el : arr)
    {
        float y = el - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }
    return sum;
}