#include "stdafx.h"
#include "MapManager.h"


MapManager::MapManager()
{
	m_map = new Map;
	m_map->init();
}


MapManager::~MapManager()
{
}

void MapManager::MapChange(LPCSTR strkey)
{
	m_map->LoadMap(strkey);
}

void MapManager::Render()
{
	m_map->render();
}
