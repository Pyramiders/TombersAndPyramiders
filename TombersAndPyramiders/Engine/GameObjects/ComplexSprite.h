#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include <string>
#include <vector>

class ComplexSpriteinfo
{
private:
	std::vector<std::string> m_filePaths;
	std::vector<int> m_numberOfColumns;
	std::vector<int> m_numberOfRows;

public:
	void addInfo(std::string filePath, int columnCount, int rowCount)
	{
		m_filePaths.push_back(filePath);
		m_numberOfColumns.push_back(columnCount);
		m_numberOfRows.push_back(rowCount);
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
};

//MenuSprite* TitleMenu("Title.png", x, y, scale = 1, nondefaultShader = nullptr);
class ComplexSprite : public GameObject
{
private:
	Shader* m_shader;
	std::vector<SpriteSheet*> m_sprites;
	int m_currentSpriteSheet;
	int m_spriteToReturnTo;
	int m_framesTilReturn;
	int m_framesPerSecond;
	double m_timeAlive = 0;
	double m_lastFrame = 0;

public:
	ComplexSprite(ComplexSpriteinfo* info, float x, float y, float z = 0.0f, float scale = 1.0f, Shader* nonDefaultShader = nullptr, int framesPerSecond = 8);
	~ComplexSprite();

	void setFPS(int fps);
	void updateFrames(float delta);
	void nextFrame();
	void changeSprite(int spriteIndexInComplexInfo);
	int getCurrentSprite();
	void changeSprite(int spriteIndexInComplexInfo, int returnSprite);
};