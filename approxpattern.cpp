#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

int HammingDistance(string dna1, string dna2)
{
    int hammingdistance = 0;
    for (int i = 0; i < dna1.length(); i++) {
        if (dna1[i] != dna2[i]) hammingdistance++;
    }
    return hammingdistance;
}

void getdna( string dataset )
{
    ifstream file;
    string dna1;
    string dna2;
    file.open("C:/Users/Nikolai Mironov/Downloads/dataset_30278_3 (5).txt");
    while(file >> dna1 >> dna2)
    cout << HammingDistance(dna1, dna2) << endl;
} 

string opp(string pattern)
{
    string reversepattern;
    for (auto base : pattern) {
        if (base == 'C' ) reversepattern.push_back('G');
        else if (base == 'G' ) reversepattern.push_back('C');
        else if (base == 'A' ) reversepattern.push_back('T');
        else if (base == 'T' ) reversepattern.push_back('A');
    }
    return reversepattern;

}

vector<int> approxpatterncount(string pattern, string dna, int d) {
    vector<int> matches;
    for (int i = 0; i<dna.length() - pattern.length() + 1; i++) {
        string window = dna.substr(i, pattern.length());
        if (HammingDistance(pattern, window) <= d) {
            matches.push_back(i);
        }
    }
    for (int match : matches) {
    }
    return matches;
}
string suffix(string pattern)
{
    return pattern.substr(1, pattern.length() - 1 );
}
vector<string> Neighbors(string pattern, int d)
{
    cout << pattern << endl;
    if (d == 0) {
    return vector<string> {pattern};
    }
    if (pattern.length() == 1) return {"A", "C", "G", "T"};
    vector<string> Neighborhood;
    vector<string> SuffixNeighbors = Neighbors(suffix(pattern), d);
    for (string Text : SuffixNeighbors){
        if (HammingDistance(suffix(pattern), Text) < d) {
            vector<string> nucs =  {"A", "C", "G", "T"};
            for (string nuc : nucs) {
                cout << "text: " << Text << endl;
                cout << "nuc: " << nuc << endl;
                cout << "added nuc:" << nuc + Text << endl; 
                Neighborhood.push_back(nuc + Text);
            }
        }
        else {
            cout << pattern.substr(0, 1) << ", " << Text << ", " << pattern.substr(0, 1) + Text << endl;
            Neighborhood.push_back(pattern.substr(0, 1) + Text);
        }     
    }
    cout << "pattern: " << pattern << endl;
    return Neighborhood;
}
// vector<string> FrequentWordsWithMismatches(string dna, int k, int d) {
//     vector<string> patterns;
//     unordered_map<string, int>;
//     int n = dna.length();
//     for (int i = 0; i <= n - k; i++) {
//         string pattern = dna.substr(i, k);
//         vector<string> neighborhood = Neighbors(pattern, d)
//         for (int j = 0; j<= neighborhood.length - 1; j++)
//             string neighbor = neighborhood[j];
//             if freqMap[neighbor] doesnt exist
//                 freqMap[neighbor] ← 1
//             else
//                 freqMap[neighbor] ← freqMap[neighbor] + 1
//     }
//     m = MaxMap(freqMap)
//     for every key pattern in freqMap
//         if freqMap[pattern] = m
//             append pattern to patterns
//     return patterns
// }
int main() {
    ifstream file;
    string pattern;
    string dna;
    int d;
    vector<int> matches;
    file.open("C:/Users/Nikolai Mironov/Downloads/dataset_30282_4.txt");
    while(file >> pattern >> d)
    pattern = "ACG";
    d = 1;
    cout << pattern << d << " ";
    for (string neighbor : Neighbors(pattern, d)) cout << neighbor << endl;
    return 0;
}