#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include <set>

class ComplexSpriteInfo
{
private:

	std::vector<std::string> m_filePaths;
	std::vector<std::string> m_spriteNames;
	std::vector<int> m_numberOfColumns;
	std::vector<int> m_numberOfRows;

public:
	struct Animation
	{
		Animation(std::string animationName, int startFrameIndex, int endFrameIndex)
		{
			m_animationName = animationName;
			m_startFrameIndex = startFrameIndex;
			m_endFrameIndex = endFrameIndex;
		}

		bool operator== (std::string animName)
		{
			return m_animationName == animName;
		}

		std::string m_animationName = "";
		int m_startFrameIndex = 0;
		int m_endFrameIndex = 0;
	};
	std::map<int, vector<Animation>> m_animations;

	// Adds a new sprite sheet.
	// Returns true if successful, false if a sprite sheet with that name already exists.
	bool addSprite(std::string filePath, std::string spriteName, int columnCount, int rowCount)
	{
		// A sprite with that name already exists
		if (getSpriteIndex(spriteName) != -1)
		{
			return false;
		}

		m_filePaths.push_back(filePath);
		m_spriteNames.push_back(spriteName);
		m_numberOfColumns.push_back(columnCount);
		m_numberOfRows.push_back(rowCount);

		return true;
	}

	// Defines a series of frames in a spritesheet to use as an animation. Can have as many animations as you want.
	// Returns true if the sprite you're trying to create an animation from exists, false if it doesn't.
	bool addAnimation(std::string spriteName, std::string animationName, int startFrameIndex, int endFrameIndex)
	{
		// Check to see if the spritesheet exists, return false if it doesn't
		int spriteIndex = getSpriteIndex(spriteName);
		if (spriteIndex < 0 || spriteIndex > m_filePaths.size() - 1) 
		{
			return false;
		}

		// If an animation with that name already exists, return false.
		if (getAnimationIndex(spriteIndex, animationName) != -1)
		{
			return false;
		}

		Animation newAnimation = Animation(animationName, startFrameIndex, endFrameIndex);
		m_animations[spriteIndex].push_back(newAnimation);

		return true;
	}
	bool addAnimation(int spriteIndex, std::string animationName, int startFrameIndex, int endFrameIndex)
	{
		if (spriteIndex < 0 || spriteIndex > m_filePaths.size() - 1)
		{
			return false;
		}

		// If an animation with that name already exists, return false.
		if (getAnimationIndex(spriteIndex, animationName) != -1)
		{
			return false;
		}

		Animation newAnimation = Animation(animationName, startFrameIndex, endFrameIndex);
		m_animations[spriteIndex].push_back(newAnimation);

		return true;
	}

	std::string getFilePath(int index)
	{
		return m_filePaths[index];
	}

	int getColumnCount(int index)
	{
		return m_numberOfColumns[index];
	}

	int getRowCount(int index)
	{
		return m_numberOfRows[index];
	}

	int getSpriteCount()
	{
		return m_filePaths.size();
	}

	// Gets the index to a spritesheet by name.
	int getSpriteIndex(std::string spriteName)
	{
		auto pos = find(m_spriteNames.begin(), m_spriteNames.end(), spriteName) - m_spriteNames.begin();
		if (pos >= m_spriteNames.size())
		{
			// Doesn't exist
			return -1;
		}

		return pos;
	}

	// Gets the index to an animation by name.
	int getAnimationIndex(int spriteSheetIndex, std::string animationName)
	{
		auto pos = find(m_animations[spriteSheetIndex].begin(), m_animations[spriteSheetIndex].end(), animationName) - m_animations[spriteSheetIndex].begin();
		if (pos >= m_animations[spriteSheetIndex].size())
		{
			// Doesn't exist
			return -1;
		}

		return pos;
	}
};

//MenuSprite* TitleMenu("Title.png", x, y, scale = 1, nondefaultShader = nullptr);
class ComplexSprite : public GameObject
{
private:
	Shader* m_shader;
	std::vector<std::shared_ptr<SpriteSheet>> m_spriteSheets;
	int m_currentSpriteSheetIndex;
	std::string m_currentSpriteSheetName;
	int m_currentAnimationIndex;
	int m_animationtoReturnTo;
	int m_spriteSheetToReturnTo;
	int m_framesTilReturn;
	int m_framesPerSecond;
	std::shared_ptr<ComplexSpriteInfo> m_spriteInfo;
	double m_timeAlive = 0;
	double m_lastFrame = 0;

public:
	ComplexSprite(std::shared_ptr<ComplexSpriteInfo> info, float x, float y, float z = 0.0f, float scale = 1.0f, Shader* nonDefaultShader = nullptr, int framesPerSecond = 8);

	void setFPS(int fps);
	void updateFrames(float delta);
	void nextFrame();
	bool changeSpriteSheet(int spriteIndexInComplexInfo);
	bool changeSpriteSheet(std::string spriteName);
	bool changeSpriteSheet(int spriteIndexInComplexInfo, int returnSprite);

	// Changes to an animation in the currently loaded sprite sheet, returns true if found and false if not
	bool changeAnimation(std::string animationName, int animationIndexToReturnTo = -1);
	bool changeAnimation(std::string animationName, std::string animationNameToReturnTo);
	bool changeAnimation(int animationIndex, int animationIndexToReturnTo = -1);
	void updateSpriteSheetAnimation(int animationIndex);

	int getCurrentSpriteSheetIndex();
	std::string getCurrentSpriteSheetName();
};