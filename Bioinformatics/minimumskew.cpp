#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int minimumskew(string pattern)
{
    int minimum = 0;
    int skew = 0;
    for (int i = 0; i <= pattern.length(); i++) {
        char nuc = pattern[i];
        if (nuc == 'G') skew++;
        else if (nuc == 'C') {
            skew--;
            if (skew < minimum) minimum = i;
        }
    }
    return minimum;
}