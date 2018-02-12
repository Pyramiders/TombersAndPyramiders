#include "Neuron.h"
#include <cstdlib>
#include <cmath>

double Neuron::s_learningRate = 0.15;
double Neuron::s_alpha = 0.5;

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	m_myIndex = myIndex;

	for (unsigned connections = 0; connections < numOutputs; ++connections)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}
}


Neuron::~Neuron()
{
}

double Neuron::randomWeight(void)
{
	return rand() / double(RAND_MAX);
} 

void Neuron::feedForward(const Layer &previousLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer.
	for (unsigned n = 0; n < previousLayer.size(); ++n)
	{
		sum += previousLayer[n].getOutputValue() *
			previousLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x)
{
	// Tanh - output range {-1.0...1.0}
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	// Tanh derivative
	return 1.0 - x * x;
}

void Neuron::calculateOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calculateHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
	double sum = 0.0;

	// Sum out contributions of the errors at the nodes we feed
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Individual input, magnified by the gradient and training rate
			Neuron::s_learningRate * neuron.getOutputValue() * m_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ Neuron::s_alpha * oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}
