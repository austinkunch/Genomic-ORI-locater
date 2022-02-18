#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

std::ifstream infile; //global file ptr to read from input file

//Counts and returns how many times a pattern occurs in a text
int PatternCount(string text, string pattern) {
	int count = 0;
	for (int i = 0; i < (text.length() + 1 - pattern.length()); ++i) {
		if (text.substr(i, pattern.length()) == pattern) {
			++count;
		}
	}
	return count;
}

//FreqTable builds the Map
//The map is a count of how many times any substring of length k appears in the string text
unordered_map<string, int> FreqTable(string text, int k) { //k is length of pattern to be used
	unordered_map<string, int> freqMap; //Key is string and mapped value is int
	string pattern; // stores individual sequences of length k
	unordered_map<string, int>::iterator itr; // itr works as a pointer to pair<string, double>

	for (int i = 0; i < (text.length() - k + 1); ++i) {
		pattern = text.substr(i, k);
		if (freqMap.find(pattern) == freqMap.end()) {  //if the pattern is not found in the freqMap
			//cout << "Not already in map\n";
			freqMap.insert(make_pair(pattern, 1));
		}
		// type itr->first stores the key and
		// itr->second stores the value
		else ++freqMap.at(pattern);
	}
	return freqMap;
}

//MaxMap finds the max value in the Map (finds the string that occurs most)
unordered_map<string, int> MaxMap(unordered_map<string, int> freqMap) {
	unordered_map<string, int>::iterator itr;
	int max;
	string maxString;
	max = freqMap.begin()->second;
	unordered_map<string, int> maxMap;

	for (itr = freqMap.begin(); itr != freqMap.end(); ++itr) {
		if (itr->second > max) {
			max = itr->second;
			maxString = itr->first;
		}
	}
	maxMap[maxString] = max;
	return maxMap;
}

//BetterFrequentWords returns a vector of patterns that are equally present among a text
vector<string> BetterFrequentWords(string text, int k) {
	vector<string> frequentPatterns;
	unordered_map<string, int> freqMap;
	unordered_map<string, int> newMap;
	unordered_map<string, int>::iterator itr;
	string maxString;
	int max;

	freqMap = FreqTable(text, k);
	newMap = MaxMap(freqMap);
	for (itr = freqMap.begin(); itr != freqMap.end(); ++itr) {
		if (itr->second == newMap.begin()->second) {
			frequentPatterns.push_back(itr->first);
		}
	}
	return frequentPatterns;
}

/* This function is used to iterate through an entire genome or large character array to identify potential ORIs.
   A pattern/substring appearing many times in a small 500 character window/frame is extremely unlikely, and thus
   if it occurs, it is most likely an evolutionarily conserved region of the genome used to start transcription
   (proteins attaching to it to read the DNA and do important stuff.
*/
//k is length of sequences to find, L is length of text to look at, t is amount of patterns in a clump
vector<string> FindClumps(string text, int k, int L, int t) {
	vector<string> patterns;
	unordered_map<string, int> freqMap;
	unordered_map<string, int>::iterator itr;

	for (int i = 0; i < text.length() - L; ++i) {
		string window = text.substr(i, L);
		freqMap = FreqTable(window, k);
		for (itr = freqMap.begin(); itr != freqMap.end(); ++itr) {
			if (itr->second >= t) {
				patterns.push_back(itr->first);
			}
		}
	}
	for (int i = 0; i < patterns.size(); ++i) {
		string temp = patterns.at(i);
		for (int j = 0; j < patterns.size();) {
			if (patterns.at(j) == temp) {
				patterns.erase(patterns.begin() + j);
			}
			else ++j;
		}
		patterns.push_back(temp);
	}
	return patterns;
}

void PrintFreqMap(unordered_map<string, int> freqMap) {
	unordered_map<string, int>::iterator itr;

	for (itr = freqMap.begin(); itr != freqMap.end(); ++itr) {
		cout << itr->second << ": " << itr->first << "   |   ";
	}
}

//vector<string> FindMers(string text, int k) {
//	MaxMap(FreqTable(text, k));
//}

int main() {
	string text = "TAAACGTGAGAGAAACGTGCTGATTACACTTGTTCGTGTGGTAT";
	int k = 3;
	int L = 500;
	int t = 3;
	vector<string> clumps;
	unordered_map<string, int> freqMap;
	/*infile.open("dataset_4_6.txt");

	infile >> text; */

	freqMap = FreqTable(text, k);

	PrintFreqMap(freqMap);
	cout << freqMap.size() << "\n";

//TODO: FindClumps is causing pgm to abort
	clumps = FindClumps(text, k, L, t);
	for (int i = 0; i < clumps.size(); ++i) {
		cout << clumps.at(i) << " ";
	}
	/*PrintFreqMap(FreqTable(text, k));
	cout << "\n\n";
	cout << text; */
}
