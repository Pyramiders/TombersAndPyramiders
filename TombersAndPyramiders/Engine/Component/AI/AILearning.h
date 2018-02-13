#pragma once
#include "NeuralNet.h"
#include "TrainingData.h"

/*
Dustin,

This class had Battler specific logic. I commented it out for the project to compie as we're extracting the engine.

~ Carson
*/

class AILearning
{
public:
	AILearning();
	~AILearning();
	//vector<double> MakeDecision(Battler *player);
	//void TrainData(Battler *player, double didShoot);

private:
	//void PrintVectorValues(string initialLine, const vector<double> &vectorToPrint);
	void initialize();
	TrainingData m_trainingData;
	NeuralNet m_myNet;
};

