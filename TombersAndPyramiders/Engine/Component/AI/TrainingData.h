#pragma once
#include <vector>
#include "Vector2.h"

using namespace std;

//struct Data {
//	vector<Vector2> friendlySnowballPos;
//	vector<Vector2> enemySnowballPos;
//	vector<Vector2> playerSnowballPos;
//	vector<Vector2> enemyBattlerPos;
//	vector<Vector2> friendlyAIPos;
//	Vector2 friendlyPlayerPos;
//	double myTeam;
//
//	double threwSnowball;
//	double movedLeft;
//	double movedRight;
//	double movedUp;
//	double movedDown;
//};

struct Data
{
	Data() {}
	Vector2 friendlyPlayerPos = Vector2(0.0, 0.0);
	Vector2 friendlyPlayerVelocity = Vector2(0.0, 0.0);

	double threwSnowball;
	double velocityX;
	double velocityY;
};

class TrainingData
{
public:
	TrainingData();
	~TrainingData();

	void getTopology(vector<unsigned> &topology);
	unsigned getNextInputs(vector<double> &inputValues, Data &gameState);
	unsigned getTargetOutputs(vector<double> &targetOutputValues, Data &gameState);

	vector<Data> savedData;

private:
	int getInputNeuronCount();
	Vector2 normalizeVector2(Vector2 &position);
};

