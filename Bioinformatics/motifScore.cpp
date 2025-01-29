#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath> // For log2

using namespace std;

vector<unordered_map<char, double> > countMotifPercent(const vector<string>& motifs) {
    vector<string> columns(motifs[0].size());
    for (const auto& motif : motifs) {
        for (size_t i = 0; i < motif.size(); ++i) {
            columns[i].push_back(motif[i]);
        }
    }

    vector<unordered_map<char, double> > count(columns.size());
    for (size_t i = 0; i < columns.size(); ++i) {
        unordered_map<char, int> nucleotide_count;
        for (char nucleotide : columns[i]) {
            nucleotide_count[nucleotide]++;
        }
        count[i]['A'] = static_cast<double>(nucleotide_count['A']) / columns[i].size();
        count[i]['C'] = static_cast<double>(nucleotide_count['C']) / columns[i].size();
        count[i]['G'] = static_cast<double>(nucleotide_count['G']) / columns[i].size();
        count[i]['T'] = static_cast<double>(nucleotide_count['T']) / columns[i].size();
    }
    return count;
}

double motifEntropy(const vector<string>& motifs) {
    vector<unordered_map<char, double> > percents = countMotifPercent(motifs);
    double entropy = 0.0;
    for (size_t i = 0; i < percents.size(); ++i) {
        for (const auto& pair : percents[i]) {
            double frequency = pair.second;
            if (frequency > 0) {
                entropy += frequency * log2(frequency);
            }
        }
    }
    entropy = -entropy; // Entropy is typically the negative sum
    return entropy;
}

int main() {
    vector<string> motifs = {
        "TCGGGGGTTTTT",
        "CCGGTGACTTAC",
        "ACGGGGATTTTC",
        "TTGGGGACTTTT",
        "AAGGGGACTTCC",
        "TTGGGGACTTCC",
        "TCGGGGATTCAT",
        "TCGGGGATTCCT",
        "TAGGGGAACTAC",
        "TCGGGTATAACC"
    };

    cout << "Entropy: " << motifEntropy(motifs) << endl;

    return 0;
}