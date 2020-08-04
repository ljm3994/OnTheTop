#include "stdafx.h"
#include "MapInfo.h"


MapInfo::MapInfo(string Name, UINT TileMaxX, UINT TileMaxY, UINT TileWidth, UINT TileHeight)
	:MapName(Name), TileMaxX(TileMaxX), TileMaxY(TileMaxY), TileWidth(TileWidth), TileHeight(TileHeight)
{
	WindowTileNum();
}

MapInfo::~MapInfo()
{
}

void MapInfo::SetMaxTile(UINT TileMaxX, UINT TileMaxY)
{
	this->TileMaxX = TileMaxX;
	this->TileMaxY = TileMaxY;
	WindowTileNum();
}

void MapInfo::SetSizeTile(float TileWidth, float TileHeight)
{
	this->TileWidth = TileWidth;
	this->TileHeight = TileHeight;
	WindowTileNum();
}

void MapInfo::WindowTileNum()
{
	TileWindowNumX = (((WINSIZEX) / TileWidth) + 1);
	TileWindowNumY = (((WINSIZEY) / TileHeight) + 1);
}
