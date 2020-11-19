#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const string COMPARE_LIST = "23456789TJQKASDHC";

int calcRank(string pair, string suit);
bool checkStraight(string pair);
int checkPokerHand(vector<string> a);
int count(string input, char charToFind);
