#include "Room.h"
#include "SpawnManager.h"
#include "Randomize.h"
#include "EquipmentIncludes.h"
#include "GeneratorManager.h"

Room::Room(int width, int height, int xPosition, int yPosition, bool exit, bool spawn, int level) : m_width(width), m_height(height), m_xCoord(xPosition), m_yCoord(yPosition), m_exit(exit), m_spawn(spawn), m_level(level),
		ComplexSprite(generateComplexSpriteInfo(), 0, -2, 10, 5)
{
	m_scale = 5;
}

void Room::draw() 
{
	std::cout << m_xCoord << " " << m_yCoord << std::endl;
	std::cout << m_width << " " << m_height << std::endl;
	//algorithm for drawing a room 
	//SpawnManager::getInstance()->generateMiscSquare(m_xCoord+2, m_yCoord-2, 10, m_scale, "stoneTile.png", true);

	for (int i = 0; i < m_height; i++) 
	{
		for (int j = 0; j < m_width; j++) 
		{	
			bool skip = false;
			for (int k = 0; k < doorsX.size(); k++)
			{
				if (m_yCoord - i == doorsY[k] && m_xCoord + j == doorsX[k])
				{
					if (i == 0)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 1 - i * m_scale, Door::Direction::West, Door::Mode::Closed);
					}
					else if (j == 0)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 1 - i * m_scale, Door::Direction::South, Door::Mode::Closed);
					}
					else if (i == m_height - 1)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 1 - i * m_scale, Door::Direction::West, Door::Mode::Closed);
					}
					else if (j == m_width - 1)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 1 - i * m_scale, Door::Direction::North, Door::Mode::Closed);
					}
					
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				if (i == 0 && j == 0)
				{
					// top left corner
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "wallTopLeft_EdgeShift.png", false);
				}
				else if (i == 0 && j == m_width - 1)
				{
					//top right corner
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "wallTopRight_EdgeShift.png", false);
				}
				else if (i == m_height - 1 && j == 0)
				{
					//bottom left corner
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, 2000, m_scale, "wallBottomLeftShift.png", false);
				}
				else if (i == m_height - 1 && j == m_width - 1)
				{
					//bottom right corner
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, 2000, m_scale, "wallBottomRightShift.png", false);
				}
				else if (i == 0)
				{
					//top wall
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "WallHorizontalU.png", true, m_scale, m_scale/4.5, 0, -1.2f);
				}
				else if (j == 0)
				{
					//left wall
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "wallVerticalBothEdgeL.png", true, m_scale/4.5, m_scale, 2 ,0);
				}
				else if (i == m_height - 1)
				{
					//bottom wall
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, 2000, m_scale, "wallHorizontalD.png", true, m_scale, m_scale /4.5, 0, 1.3f);
				}
				else if (j == m_width - 1)
				{
					//right wall
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "wallVerticalBothEdgeR.png", true, m_scale/4.5, m_scale, -2, 0);
				}
				else
				{
					//floor
					SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + j * m_scale), m_yCoord * m_scale - 2 - i * m_scale, -1, m_scale, "stoneTile_Edge.png", false);
					//10% chance to spawn an item in every floor tile
					if (Randomize::Random(0, 9) == 0)
					{
						//item type all even chance
						int seed = Randomize::Random(0, 5);

						//item spawn offsets
						int xOffset = Randomize::Random(0, 4);
						int yOffset = Randomize::Random(0, 4);
						
						//10% gold chance
						//30% silver chance
						//60% wood chance
						int type = Randomize::Random(0, 9);

						switch (seed)
						{
						case 0:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShield>(BaseShield::GOLD_SHIELD_IMAGE_NAME, BaseShield::GOLD_SHIELD_ICON_NAME, BaseShield::GOLD_SHIELD_DAMAGE_MULT, BaseShield::GOLD_SHIELD_COOLDOWN_TIME));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShield>(BaseShield::SILVER_SHIELD_IMAGE_NAME, BaseShield::SILVER_SHIELD_ICON_NAME, BaseShield::SILVER_SHIELD_DAMAGE_MULT, BaseShield::SILVER_SHIELD_COOLDOWN_TIME));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShield>(BaseShield::WOODEN_SHIELD_IMAGE_NAME, BaseShield::WOODEN_SHIELD_ICON_NAME, BaseShield::WOODEN_SHIELD_DAMAGE_MULT, BaseShield::WOODEN_SHIELD_COOLDOWN_TIME));
							}
							break;
						case 1:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShortsword>(BaseShortsword::GOLD_SHORTSWORD_DAMAGE, BaseShortsword::GOLD_SHORTSWORD_IMAGE_NAME, BaseShortsword::GOLD_SHORTSWORD_DESTROY_ON_COLLISION));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShortsword>(BaseShortsword::SILVER_SHORTSWORD_DAMAGE, BaseShortsword::SILVER_SHORTSWORD_IMAGE_NAME, BaseShortsword::SILVER_SHORTSWORD_DESTROY_ON_COLLISION));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseShortsword>(BaseShortsword::WOODEN_SHORTSWORD_DAMAGE, BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME, BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION));
							}
							break;
						case 2:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseLongbow>(BaseLongbow::GOLD_LONGBOW_DAMAGE, BaseLongbow::LONGBOW_CASTING_TIME, BaseLongbow::GOLD_LONGBOW_IMAGE_NAME, BaseLongbow::GOLD_LONGBOW_PROJECTILE_IMAGE_NAME, BaseLongbow::GOLD_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseLongbow>(BaseLongbow::SILVER_LONGBOW_DAMAGE, BaseLongbow::LONGBOW_CASTING_TIME, BaseLongbow::SILVER_LONGBOW_IMAGE_NAME, BaseLongbow::SILVER_LONGBOW_PROJECTILE_IMAGE_NAME, BaseLongbow::SILVER_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseLongbow>(BaseLongbow::WOODEN_LONGBOW_DAMAGE, BaseLongbow::LONGBOW_CASTING_TIME, BaseLongbow::WOODEN_LONGBOW_IMAGE_NAME, BaseLongbow::WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME, BaseLongbow::WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION));
							}
							break;
						case 3:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseHelmet>(BaseHelmet::GOLD_HELMET_ICON_IMAGE, BaseHelmet::GOLD_HELMET_CRITICAL_RESIST_CHANCE));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseHelmet>(BaseHelmet::SILVER_HELMET_ICON_IMAGE, BaseHelmet::SILVER_HELMET_CRITICAL_RESIST_CHANCE));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseHelmet>(BaseHelmet::WOODEN_HELMET_ICON_IMAGE, BaseHelmet::WOODEN_HELMET_CRITICAL_RESIST_CHANCE));
							}
							break;
						case 4:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseGreaves>(BaseGreaves::GOLD_GREAVES_ICON_IMAGE_NAME, BaseGreaves::GOLD_GREAVES_COOLDOWN_TIME, BaseGreaves::GOLD_GREAVES_DASH_DURATION, BaseGreaves::GOLD_GREAVES_DASH_SPEED));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseGreaves>(BaseGreaves::SILVER_GREAVES_ICON_IMAGE_NAME, BaseGreaves::SILVER_GREAVES_COOLDOWN_TIME, BaseGreaves::SILVER_GREAVES_DASH_DURATION, BaseGreaves::SILVER_GREAVES_DASH_SPEED));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseGreaves>(BaseGreaves::WOODEN_GREAVES_ICON_IMAGE_NAME, BaseGreaves::WOODEN_GREAVES_COOLDOWN_TIME, BaseGreaves::WOODEN_GREAVES_DASH_DURATION, BaseGreaves::WOODEN_GREAVES_DASH_SPEED));
							}
							break;
						case 5:
							if (type == 0)
							{
								//gold
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseChestplate>(BaseChestplate::GOLD_CHESTPLATE_ICON_IMAGE_NAME, BaseChestplate::GOLD_CHESTPLATE_DAMAGE_MULTIPLIER));
							}
							else if (type < 4)
							{
								//silver
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseChestplate>(BaseChestplate::SILVER_CHESTPLATE_ICON_IMAGE_NAME, BaseChestplate::SILVER_CHESTPLATE_DAMAGE_MULTIPLIER));
							}
							else
							{
								//wood
								SpawnManager::getInstance()->generateWorldItem(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + xOffset + j * m_scale), m_yCoord * m_scale - yOffset - i * m_scale, std::make_shared<BaseChestplate>(BaseChestplate::WOODEN_CHESTPLATE_ICON_IMAGE_NAME, BaseChestplate::WOODEN_CHESTPLATE_DAMAGE_MULTIPLIER));
							}
							break;
						}
					}
				}
			}
			
		}
	}
	if (m_exit) 
	{
		//draw stairs
		int x = Randomize::Random() % m_width/2 + ceil(m_width/4);
		int y = Randomize::Random() % m_height/2 + ceil(m_height/4);
		if (m_level == PYRAMID_HEIGHT - 1) {
			SpawnManager::getInstance()->generateThrone(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + x * m_scale), m_yCoord * m_scale - 2 - y * m_scale);
		}
		else
		{
			SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + x * m_scale), m_yCoord * m_scale - 2 - y * m_scale, 0, m_scale, "spiralStairs.png", true, 3.0f, 3.0f);
		}
	
		GeneratorManager::getInstance()->levels[m_level]->stairX = m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + x * m_scale);
		GeneratorManager::getInstance()->levels[m_level]->stairY = m_yCoord * m_scale - 2 - y * m_scale;

	}
	if (m_spawn)
	{
		//draw spawn point
		int x = Randomize::Random() % m_width / 2 + ceil(m_width / 4);
		int y = Randomize::Random() % m_height / 2 + ceil(m_height / 4);
		SpawnManager::getInstance()->generateMiscSquare(m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + x * m_scale), m_yCoord * m_scale - 2 - y * m_scale, 0, m_scale/5, "spawnPoint.png", false, 0.0f, 0.0f);

		GeneratorManager::getInstance()->levels[m_level]->spawnX = m_level * LEVEL_OFFSET + (m_xCoord * m_scale + 2 + x * m_scale);
		GeneratorManager::getInstance()->levels[m_level]->spawnY = m_yCoord * m_scale - 2 - y * m_scale;
	}
}

std::shared_ptr<ComplexSpriteInfo> Room::generateComplexSpriteInfo()
{
	std::shared_ptr<ComplexSpriteInfo> spriteInfo = std::make_shared<ComplexSpriteInfo>();

	spriteInfo->addSprite("stoneTile.png", "stoneTile", 1, 1);

	return spriteInfo;
}