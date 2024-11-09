#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <C:\Users\maumi\OneDrive\Documents\GitHub\bioinformatics\minimumskew.cpp>
using namespace std;

int HammingDistance(string dna1, string dna2)
{
    int hammingdistance = 0;
    for (int i = 0; i < dna1.length(); i++) {
        if (dna1[i] != dna2[i]) hammingdistance++;
    }
    return hammingdistance;
}

string reversecompliment(string pattern)
{
    string reversepattern;
    for (char base : pattern) {
        if (base == 'C' ) reversepattern.insert(0, 1, 'G');
        else if (base == 'G' ) reversepattern.insert(0, 1, 'C');
        else if (base == 'A' ) reversepattern.insert(0, 1, 'T');
        else if (base == 'T' ) reversepattern.insert(0, 1, 'A');
    }
    return reversepattern;

}

int maxMap(unordered_map<string, int> freqmap)
{
    int themax = -1;
    
    for (pair<string, int> m : freqmap ) {
        if (themax != -1) {
            cout << themax << endl;
            if (m.second > themax) themax = m.second;
        }
        else themax = m.second; cout << "new max: " << themax << endl;
    }
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
                    Neighborhood.push_back(nuc + Text);
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
            if (freqMap.empty()){
                freqMap[neighbor] = 1; 
                freqMap[reversecompliment(neighbor)] = 1;
            } else freqMap[neighbor] = freqMap[neighbor] + 1; freqMap[reversecompliment(neighbor)] = freqMap[reversecompliment(neighbor)] + 1;
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

vector<string> MotifEnumeration(int k, int d, vector<string> Dna) {
    vector<string> Patterns;
    unordered_map<string, int> uniques;
    string pattern = Dna[0];
    cout << pattern << endl;
    int n = pattern.length();
    for (int i = 0; i <= n - k; i++) {
        string kmer = pattern.substr(i, k);
        vector<string> neighborhood = Neighbors(kmer, d);
        for (int j = 0; j<= neighborhood.size() - 1; j++) {
            string neighbor = neighborhood[j];
            bool isfound = true;
            for (string otherpattern : Dna) {
                cout << otherpattern << endl;
                if (otherpattern.find(neighbor) != -1) {
                    cout << neighbor << " is found in " << otherpattern << endl;

                    continue;
                }
                else isfound = false ; break;
            }
            if (isfound) uniques[kmer] = 1; break;
        }
    } 
for (pair unique : uniques) Patterns.push_back(unique.first);
return Patterns;
}

string readfile(string filename, int line_number) {
    ifstream file;
    file.open(filename);
    // Open the file with the provided filename

    
    // We'll read in the file one line at a time until we find the line we're 
    // looking for... current_line will keep track of the current line number 
    // of the line we're reading in, and line will store the line content/string.
    int current_line = 0;
    string line;
    
    // Continue to read the file one line at a time, unless we reach the end of 
    // the file at which point we stop
    while (!file.eof())
    {
        // Increment the current line number being read as we are reading in the 
        // next line now
        current_line++;

        // Read the next line from the 'file' into the 'line' string 
        getline(file, line);
        // If current line number of the line we've read in matches the line number 
        // that we're looking for, use break to stop the loop
        if (current_line == line_number) break;
    }
    // Close the file as we are done working with it
    file.close();
    return line;
}

int main() {
    string s;
    string word = "";
    string filename = "C:/Users/maumi/Downloads/dataset_30302_8 (2).txt";
    vector<string> dna;
    cout << "hello world \n";
    int k = stoi(readfile(filename, 1));
    int d = stoi(readfile(filename, 2));
    string text = readfile(filename, 3);
    cout << k << endl << d << endl << text << endl;
    for(auto i = 0; i < text.length(); i++) {
            if (text.substr(i, 1) != " ") {
                word += (text.substr(i, 1));
            }
            else {
                dna.push_back(word);
                word = "";
            };
        }
    for (string w : dna){
        cout << w << endl;
    }
    for (string pattern : MotifEnumeration(k, d, dna)) cout << pattern << endl;

    return 0;
}