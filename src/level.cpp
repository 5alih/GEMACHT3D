#include "Level.h"
#include <fstream>

void LevelMaster::InitLvl(){
	LoadLevel(0);
}

void LevelMaster::AddLevel(Level level)
{
	m_levels.push_back(level);
}

void LevelMaster::LoadLevel(int id)
{
	for(auto lvl: m_levels){
		if(lvl.m_id== id){
			developerConsole->PrintError(cat_2string("Level already loaded: ", to_string(id)));
			return;
		}
	}
	std::ostringstream oss;
	oss<< "resource/levels/"<< id<< ".txt";
	std::string filepath= oss.str();
	std::ifstream file(filepath);
	if(!file){
		developerConsole->PrintError(cat_2string("Error opening file: ", filepath));
		return;
	}
	std::string width;	file>> width;
	std::string height;	file>> height;
	std::string depth;	file>> depth;
	Level level( std::stoi(width), std::stoi(height), std::stoi(depth) );

	std::string block_id;
	for(int x= 0; x<std::stoi(width); x++){ // storing all the blocks for now, will compress later by stacking same blocks: 1 1 1 1 8 8 -> 4:1 2:8 
		for(int y= 0; y<std::stoi(height); y++){
			for(int z= 0; z<std::stoi(depth); z++){
				file>>block_id;
				Block block(std::stoi(block_id));
				level.m_blocks[x][y][z]= block;
			}
		}
	}
	m_levels.push_back(level);
	file.close();
}

void LevelMaster::SaveLevel(int id){
	std::ostringstream oss;
	oss<< "resource/levels/"<< id<< ".txt";
	std::string filepath= oss.str();
	std::ofstream file(filepath);
	if(!file){
		developerConsole->PrintError(cat_2string("Error opening file: ", filepath));
		return;
	}
	if(id< 0 || id>= (int)m_levels.size()){
		if(developerConsole){
			developerConsole->PrintError("Invalid level ID");
		}
		return;
	}
	file<< m_levels[id].m_width<< " ";
	file<< m_levels[id].m_height<< " ";
	file<< m_levels[id].m_depth<< " ";
	file<< "\n";
	for(int x= 0; x<m_levels[id].m_width; x++){ // storing all the blocks for now, will compress later by stacking same blocks: 1 1 1 1 8 8 -> 4:1 2:8 
		for(int y= 0; y<m_levels[id].m_height; y++){
			for(int z= 0; z<m_levels[id].m_depth; z++){
				Block block(m_levels[id].m_blocks[x][y][z].m_texture_id);
				file<< block.m_texture_id;
				file<< " ";
			}
		}
	}
	file.close();
}

Level& LevelMaster::GetCurrentLevel(){	// UNSAFE ASF
	return m_levels[m_current_level];
}
