#pragma once
#include <vector>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	~Neuron();
	void setOutputValue(double val) { m_outputVal = val; }
	double getOutputValue() const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calculateOutputGradients(double targetVal);
	void calculateHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);

private:
	double m_outputVal;
	vector<Connection> m_outputWeights;
	static double randomWeight(void);
	unsigned m_myIndex;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	double sumDOW(const Layer &nextLayer) const;

	double m_gradient;
	static double s_learningRate; // Goes from 0 (no learning) to 1 (reckless)
	static double s_alpha; // Goes from 0 to n (multiplier of last weight change - momentum)
};