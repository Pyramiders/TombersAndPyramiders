#include "Randomize.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

boost::mt19937 gen;

const int Randomize::MAX_INT = 2147483647;

void Randomize::SetSeed (int seed) {
	gen.seed (seed);
	//rng.distribution().reset();
}

int Randomize::Random (int min, int max) {
	boost::random::uniform_int_distribution<> dist (min, max);
	return dist (gen);
}

float Randomize::RandomFloat (int min, int max) {
	boost::random::uniform_int_distribution<> dist (min, max);
	return (float)dist (gen) / (float)MAX_INT;
}