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

int maxMap(unordered_map<string, int> freqmap)
{
    int themax = -1;
    
    // for (pair<string, int> m : freqmap ) {
    //     if (themax != -1) {
    //         cout << themax << endl;
    //         if (m.second > themax) themax = m.second;
    //     }
    //     else themax = m.second; cout << "new max: " << themax << endl;
    // }
    return themax;
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
    return pattern.substr(1, pattern.length() - 1);
}

vector<string> Neighbors(string pattern, int d)
{
    if (d == 0) {
        return vector<string> {pattern};
    }
    if (pattern.length() == 1) return {"A", "C", "G", "T"}; {
        vector<string> Neighborhood;
        vector<string> SuffixNeighbors = Neighbors(suffix(pattern), d);
        for (string Text : SuffixNeighbors){
            if (HammingDistance(suffix(pattern), Text) < d) {
                vector<string> nucs =  {"A", "C", "G", "T"};
                for (string nuc : nucs) {
                    if (nuc != Text) {
                        Neighborhood.push_back(nuc + Text);
                    }
                }
            }
            else {
                Neighborhood.push_back(pattern.substr(0, 1) + Text);
            }    
        }
        return Neighborhood;
    }
}

vector<string> FrequentWordsWithMismatches(string dna, int k, int d)
{
    vector<string> patterns;
    unordered_map<string, int> freqMap;
    int n = dna.length();
    for (int i = 0; i <= n - k; i++) {
        string pattern = dna.substr(i, k);
        vector<string> neighborhood = Neighbors(pattern, d);
        for (int j = 0; j<= neighborhood.size() - 1; j++) {
            string neighbor = neighborhood[j];
            if (freqMap.empty()) freqMap[neighbor] = 1;
            else freqMap[neighbor] = freqMap[neighbor] + 1;
        }
    }
    int m = maxMap(freqMap);
    for (pair<string, int> pattern : freqMap){
        if (pattern.second == m) {
            patterns.push_back(pattern.first); 
            cout << "matching frequency!: " << pattern.second << " " << m << " " << pattern.first << endl; 
        }
    }
    return patterns;
}
int main() {
    ifstream file;
    string pattern;
    int k;
    int d;
    file.open("C:/Users/Nikolai Mironov/Downloads/dataset_30278_9.txt");
    while(file >> pattern >> k >> d);
    for (string bob : FrequentWordsWithMismatches(pattern, k, d)) {
        cout << bob << " ";
    }
    return 0;
}