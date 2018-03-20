
#include "Codec.h"
#include "Room.h"
#include "Corridor.h"
#include "Doorway.h"
#include "BinaryTree.h"
#include <vector>

class GeneratorManager
{
private:
	static GeneratorManager* s_instance;
	std::shared_ptr<BinaryTree> m_worldTree;

public:
	struct Level {
	public:
		std::vector<std::shared_ptr<Room>> rooms;
		std::vector<std::shared_ptr<Corridor>> corridors;
		std::vector<std::shared_ptr<Doorway>> doorways;

		Level() {};
	};
	
	std::vector<std::shared_ptr<Level>> levels;
	static GeneratorManager* getInstance();
	void generateLevel(int width, int height, int detailLevel, int level);
	void drawLevel(int level);
	GeneratorManager();
};