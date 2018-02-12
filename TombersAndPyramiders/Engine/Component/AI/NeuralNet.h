#pragma once
#include <vector>
#include "Neuron.h"

using namespace std;

typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet();
	~NeuralNet();
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; };
	void initialize(const vector<unsigned> &topology);

private:
	vector<Layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

