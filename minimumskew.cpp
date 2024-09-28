#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    string pattern = "ATTCCAGTACTTCGATGATGGCGTGAAGA";
    int skew = 0;
    for (char nuc : pattern) {
        if (nuc == 'G') skew++;
        else if (nuc == 'C') skew--;
    }
    cout << skew << endl;
    return 0;
}