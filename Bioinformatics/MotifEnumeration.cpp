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
//vector<int> approxpatterncount(string pattern, string dna, int d) {
//    vector<int> matches;
//    for (int i = 0; i<dna.length() - pattern.length() + 1; i++) {
//        string window = dna.substr(i, pattern.length());
//        if (HammingDistance(pattern, window) <= d) {
//            matches.push_back(i);
//        }
//    }
//    for (int match : matches) {
//    }
//    return matches;
//}

string suffix(string pattern)
{
    return pattern.substr(1, pattern.length() - 1);
}

vector<string> Neighbors(string kmer, int d)
{
    string kmer0 = kmer;
    
    if (d == 0) {
        return vector<string> {kmer};
    }
    if (kmer.length() == 1) return {"A", "C", "G", "T"}; {
        vector<string> Neighborhood;
        vector<string> SuffixNeighbors = Neighbors(suffix(kmer), d);
        for (string text : SuffixNeighbors){
            if (HammingDistance(suffix(kmer), text) < d) {
                vector<string> nucs =  {"A", "C", "G", "T"};
                    
                for (string nuc : nucs) {
                        Neighborhood.push_back(nuc + text);
                }
            }
            else {
                    Neighborhood.push_back(kmer.substr(0, 1) + text);
            }
        }
        
        //remove original kmer
//        auto itr = find(Neighborhood.begin(), Neighborhood.end(), kmer);
//        if (itr != Neighborhood.end()) Neighborhood.erase(itr);
        return Neighborhood;
    }
}

vector<string> FrequentWordsWithMismatches(string dna, int k, int d)
{
    vector<string> patterns;
    unordered_map<string, int> freqMap;
    __SIZE_TYPE__ n = dna.length();
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

unordered_map<string, unordered_map<string, vector<string>>> larynxMap(int k, int d, vector<string> Dna) {
    
    cout << "Dna size: " << Dna.size() << endl;
    unordered_map<string, unordered_map<string, vector<string>>> dnaMap;
    string kmerFinal;
    for (string currentElement : Dna){
        long n = currentElement.length();
        unordered_map<string, vector<string>> kmerMap;
        for (int i = 0; i <= n - k ; i++) {
            string kmer = currentElement.substr(i, k);
            kmerFinal = kmer;
            kmerMap[kmer] = Neighbors(kmer, d);
            
        }
        dnaMap[currentElement] = kmerMap;
    }
    cout << "larynxMap(" << dnaMap.size() << "): " << endl;
    for (auto pair1 : dnaMap) {
       cout << pair1.first << endl;
        for (auto pair2 : pair1.second) {
            //cout << pair1.first << endl;
            
            string neighborString;
            for (auto neightbor : pair2.second) {
                neighborString += neightbor + " ";
            }
            cout << "\t" << pair2.first << ": " << neighborString << endl;
        }
    }
    
    return dnaMap;
}

vector<string> MotifEnumeration(int k, int d, vector<string> Dna) {
    vector<string> Patterns;
    
    //generate larynx array
    unordered_map<string, unordered_map<string, vector<string>>> dnaMap = larynxMap(k, d, Dna);
    
    //take the first element of the array, take the source kmer
    string firstElementKey = dnaMap.begin()->first;
    cout << firstElementKey << endl;
    for (auto currentElement : dnaMap) {
        
        
        if (currentElement.first != firstElementKey) {
            cout << "\ncurrentElement: " << currentElement.first << endl;
            bool kmerMatchFound = false;
            for (auto currentKmer : currentElement.second) {
                cout << "\tcurrentKmer: " << currentKmer.first << endl;
                if (!kmerMatchFound) {
                    bool neighborMatchFound = false;
                    for (auto neighbor : currentKmer.second) {
                        if (!neighborMatchFound) {
                            
                            for (auto firstKmer : dnaMap[firstElementKey]) {
                                //                        cout << "\t\tfirstKmer: " << firstKmer.first << endl;
                                
                                for (auto firstNeighbor : firstKmer.second) {
                                    if (neighbor == firstNeighbor) {
                                        //TODO fix the double matches, we dont want double matches because its not breaking right
                                        cout << "\t\tneighbor match! " << neighbor << "=" << firstNeighbor << endl;
                                        kmerMatchFound = true;
                                        break;
                                    }
                                }
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    break;
                }
        }
        
        }
    }
        //for each kmer, take neighbor array and compare to neighbor array of other elements
        //if match, stop processing neighbor, stop processing test kmer, stop processing this element
        //mark element as count + 1
        //move to next element
        //at the end,
    //if all three match, add source kmer to output array
    return Patterns;
}
vector<string> MotifEnumerationx(int k, int d, vector<string> Dna) {
    vector<string> Patterns;
    unordered_map<string, int> uniques;
    unordered_map<string, int> foundcounts;
    
    for (string current_pattern : Dna) {
        
        cout << "\ncurrent pattern: " << current_pattern << endl;
        
        __SIZE_TYPE__ n = current_pattern.length();
        
        // iterate through each position of pattern
        for (int i = 0; i <= n - k; i++) {
            
            //get kmer of that position
            string kmer = current_pattern.substr(i, k);
            cout << "kmer at position " << i << ": "<< kmer << endl;
            
            vector<string> neighborhood = Neighbors(kmer, d);
            for (int j = 0; j <= neighborhood.size() - 1; j++) {
                string neighbor = neighborhood[j];
                cout << "from neighborhood set of " << kmer << ": " << neighbor << endl;

                                for (string otherpattern : Dna) {
                                    if (otherpattern == current_pattern) continue;
                                    // if neighbor found in other pattern
                                    if (otherpattern.find(neighbor) != -1) {
                                        foundcounts[neighbor]++;
                                        cout << neighbor << " is found in " << otherpattern << " foundcount for " << neighbor << " is: " << foundcounts[neighbor] << endl;
                                        continue;
                                    }
                                    else {
                                        cout << neighbor << " not found in pattern: " << otherpattern << endl;
                                        break;
                                    }
                                }
            }
        }
            for (pair<string, int> foundcount : foundcounts) {
                if (foundcount.second > Dna.size()) {
                    uniques[foundcount.first] = 1;
                    cout << "foundcount: " << foundcount.first << " " << foundcount.second << " matches in all " << Dna.size() << endl;
                }
            }
            
        
    }
    for (pair<string, int> unique : uniques) {
        cout << unique.first << endl;
        Patterns.push_back(unique.first);
    }
    
    return Patterns;
}

string readfile(const string& filename, int lineNumber) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return "";
    }

    string line;
    for (int i = 0; i < lineNumber; ++i) {
        if (!getline(file, line)) {
            cerr << "Error: Could not read line " << lineNumber << " from file " << filename << endl;
            return "";
        }
    }

    file.close();
    return line;
}

int main() {
    string s;
    string word = "";
    string filename = "/Users/nikolaimironov/bioinformatics/Bioinformatics/input_1.txt";
    string right_output = readfile("/Users/nikolaimironov/bioinformatics/Bioinformatics/output_1.txt", 1);
    cout <<  readfile(filename, 1) << endl;
    
        // parse line1 to k and d
    string line1 = readfile(filename, 1);
    cout << "Line1: " << line1 << endl;

    vector<string> parameters;
    int k, d;
    size_t start = 0, end = 0;
    char delimiter = ' ';//space
    while ((start = line1.find_first_not_of(delimiter, end)) != string::npos) {
        end = line1.find(delimiter, start);
        parameters.push_back(line1.substr(start, end - start));
    }

    if (parameters.size() < 2) {
        cerr << "Error: Not enough parameters in line1" << endl;
        return 1;
    }

    k = stoi(parameters[0]);
    d = stoi(parameters[1]);
    cout << "k: " << k << ", d: " << d << endl;

    // parse line2 to dna vector string
    vector<string> dna;
    string line2 = readfile(filename, 2);
    cout << "Line2: " << line2 << endl;

    start = end = 0;
    while ((start = line2.find_first_not_of(delimiter, end)) != string::npos) {
        end = line2.find(delimiter, start);
        dna.push_back(line2.substr(start, end - start));
    }

    cout << "DNA vector: ";
    for (const auto& seq : dna) {
        cout << seq << " ";
    }
    cout << endl;
    
//    string text;
//    for (auto i = 0; i <= text.length(); i++) {
//            if (text.substr(i, 1) != " ") {
//                word += (text.substr(i, 1));
//            }
//            else {
//                dna.push_back(word);
//                word = "";
//            };
//        }
    vector<string> patterns = MotifEnumeration(k, d, dna);
    for (string pattern : patterns) cout << pattern << " ";
    cout << endl << "debug output: " << right_output << endl;

    return 0;
}
