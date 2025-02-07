#ifndef LEVEL_H
#define LEVEL_H

#include "my_functions.h"
#include "console.h"

class Block{
public:
	int m_texture_id;

	Block(){}

	Block(int texture_id){
		m_texture_id= texture_id;
	}
};

class Level{
public:
	int m_width;
	int m_height;
	int m_depth;
	std::vector<std::vector<std::vector<Block>>> m_blocks;

	Level(){}

	Level(int width, int height, int depth){
		m_width= width;
		m_height= height;
		m_depth= depth;
		m_blocks.resize(m_width, std::vector<std::vector<Block>>(m_height, std::vector<Block>(m_depth)));
	}
};

class LevelMaster{
public:
	std::vector<Level> m_levels;
	std::vector<Block> m_blocks;
	DeveloperConsole *developerConsole;
	int m_current_level= 0;

	LevelMaster(){}

	bool AddBlock(Block new_block){
		bool already_exist= false;
		for(auto block: m_blocks){
			if(block.m_texture_id== new_block.m_texture_id){
				already_exist= true;
			}
		}
		if(!already_exist) m_blocks.push_back(new_block);
		return !already_exist;
	}

	bool AddBlock(int texture_id){
		bool already_exist= false;
		for(auto block: m_blocks){
			if(block.m_texture_id== texture_id){
				already_exist= true;
			}
		}
		if(!already_exist){
			Block new_block(texture_id);
			m_blocks.push_back(new_block);
		}
		return !already_exist;
	}

	void LoadLevel(int id);
	
	void SaveLevel(int id);
};

#endif // LEVEL_H