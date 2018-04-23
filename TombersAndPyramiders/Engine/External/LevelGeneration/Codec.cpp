#include "Codec.h"

/*
2 bits for status		(00 start - 01 transmiting - 10 end)
12 bits for x position
12 bits for y position
5 bits for tile type

31 total
*/

void Codec::encode(std::vector<std::vector<int>> level)
{
	for (int i = 0; i < level.size(); i++) 
	{
		for (int j = 0; j < level[i].size(); j++) 
		{

		}
	}
}

void Codec::decode(int)
{

}

void Codec::sendLevel()
{
	int packetCount = encodedTiles.size();
	// send

	for (auto t : encodedTiles)
	{
		//send
	}
	int endPacket = 2;
	endPacket = endPacket << 30;
	//send
}

int Codec::getX()
{
	return 0;
}

int Codec::getY()
{
	return 0;
}

int Codec::getTileType()
{
	return 0;
}

int Codec::getTilePosition()
{
	return 0;
}
