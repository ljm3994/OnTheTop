#pragma once
class MapInfo
{
	string MapName;
	UINT TileMaxX;
	UINT TileMaxY;
	float TileWidth;
	float TileHeight;
	UINT TileWindowNumX;
	UINT TileWindowNumY;
public:
	MapInfo(string Name, UINT TileMaxX, UINT TileMaxY, UINT TileWidth, UINT TileHeight);
	~MapInfo();
	void SetMaxTile(UINT TileMaxX, UINT TileMaxY);
	void SetSizeTile(float TileWidth, float TileHeight);
	void WindowTileNum();
	MAKEGET(UINT, TileMaxX);
	MAKEGET(UINT, TileMaxY);
	MAKEGET(float, TileWidth);
	MAKEGET(float, TileHeight);
	MAKEGET(UINT, TileWindowNumX);
	MAKEGET(UINT, TileWindowNumY);
};

