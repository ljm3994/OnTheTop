#pragma once
#include "Map/Map.h"

class MapManager : public SingletonBase<MapManager>
{
	Map * m_map;

public:
	MapManager();
	~MapManager();
	void MapChange(LPCSTR strkey);
	void Render();
	Map * GetMap() { return m_map; }
};

