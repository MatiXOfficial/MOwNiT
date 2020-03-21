#include <fstream>

using namespace std;

template <class T>
T findEpsilon(T epsilon);

int main()
{
    ofstream resultsFile;
    resultsFile.open("results4.txt", ios::trunc);

    resultsFile << "Machine epsilon for float: " << findEpsilon(1.0f) << endl;
    resultsFile << "Machine epsilon for double: " << findEpsilon(1.0) << endl;

    resultsFile.close();
}

template <class T>
T findEpsilon(T epsilon)
{
    T expression = 2;
    while (expression > 1)
    {
        epsilon /= 2;
        expression = 1 + epsilon;
    }
    return epsilon;
}