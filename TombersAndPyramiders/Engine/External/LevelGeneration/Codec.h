
#include <vector>
/**
*	Encodes and Decodes the map created from the Generator class so the data can be sent across the network.
*
*/

class Codec {
private:
	int m_x;
	int m_y;
	int m_tileType;
	int m_tilePosition;
	std::vector<unsigned __int32> encodedTiles;
public:
	void encode(std::vector<std::vector<int>> level);
	void decode(unsigned __int32);
	void sendLevel();
	int getX();
	int getY();
	int getTileType();
	int getTilePosition();
};