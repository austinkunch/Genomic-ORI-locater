#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream infile; //global file ptr to read from input file

int PatternCount(string text, string pattern) {
	int count = 0;
	for (int i = 0; i < (text.length() + 1 - pattern.length()); ++i) {
		//	if (text.find(pattern) )
		if (text.substr(i, pattern.length()) == pattern) {
			count = count + 1;
		}
	}
	return count;
}


//FreqTable builds the Map
unordered_map<string, int> FreqTable(string text, int k) { //k is length of pattern to be used
	unordered_map<string, int> freqMap; //Key is string and mapped value is int
	string pattern; // stores individual sequences of length k
	unordered_map<string, int>::iterator itr; // itr works as a pointer to pair<string, double>

	for (int i = 0; i < (text.length() - k + 1); ++i) {
		pattern = text.substr(i, k);
		if (freqMap.find(pattern) == freqMap.end()) {  //if the pattern is not found and it reaches end i think???
			//cout << "Not already in map\n";
			freqMap.insert(make_pair(pattern, 1));
		}
		// type itr->first stores the key part  and
		// itr->second stores the value part
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

//This shitshow ties the other 2 func together and does some redundant bullshit I think
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
		cout<< itr->second<<": "<<itr->first << "   |   ";	
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
	/*infile.open("E.coli genome.txt");

	infile >> text; */

	freqMap = FreqTable(text, k);
	 
	PrintFreqMap(freqMap);
	cout << freqMap.size();

	/*clumps = FindClumps(text, k, L, t);
	for (int i = 0; i < clumps.size(); ++i) {
		cout << clumps.at(i) << " ";
	} 
	/*PrintFreqMap(FreqTable(text, k));
	cout << "\n\n";
	cout << text; */ 
} 
	/*
	string sequence = "";
	string subsequence = "";
	int subsequenceNum = 0;

	infile.open("dataset_2_13.txt");
	infile >> sequence;
	infile >> subsequence;

	cout << PatternCount(sequence, subsequence);
	*/

