#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Rank {
	int rank = 1;
	int high_pair = 1;
	int high_suit = 0;
}Rank;

//const string COMPARE_LIST = "23456789TJQKASDHC";
int getPairToInt(char pair);
int getSuitToInt(char suit);
string getHandToString(int rank);
Rank calcRank(int table[4][13], int* sum_pairs, int* sum_suits);
Rank checkPokerHand(vector<string> a);
