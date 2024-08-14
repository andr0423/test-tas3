#pragma once
#include <random>

using namespace std;

random_device rd;   // non-deterministic generator
mt19937 gen(rd());  // to seed mersenne twister.
uniform_int_distribution<> dist(1,255);

