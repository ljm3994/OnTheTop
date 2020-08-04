#pragma once
#include "Tile.h"
#include "MapInfo.h"

enum Mode
{
	MODE_DRAW,
	MODE_REMOVE
};

class Map : public GameNode
{
	vector<Tile* > m_tile;                                  // 타일 설정
	MapInfo * m_Info;
	bool m_ViewTile;
	bool m_ViewPass;
	bool m_ViewIndex;
public:
	Map();
	~Map();
	void InfoSetting(string MapName, UINT MaxTileX, UINT MaxTileY, UINT TileWidth, UINT TileHeight);
	void TileSetting();
	void WallTileSetting(D3DXVECTOR2 Pos);
	Tile* GetPointTile(D3DXVECTOR2 Pos);
	D3DXVECTOR2 GetPositionTile(D3DXVECTOR2 Pos);
	int GetTileIndex(D3DXVECTOR2 Pos);
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	bool LoadMap(LPCSTR SaveName);
	bool SaveMap(LPCSTR SaveName);
	void SetMaxTile(UINT X, UINT Y, float W, float H);
	// 맵 세팅시에만 사용
	void setMap(LONG m_SelectFrameX, LONG m_SelectFramey, Mode m_Mode = MODE_DRAW, string imgKey1 = "", TileProperty Property = TileProperty::PASS, bool m_ObjectSelect = false, TileObject m_Object = TileObject::OBJECT_EMPTY, string imgKey2 = "");
	vector<Tile* > GetMap() { return m_tile; }
	MAKEGET(MapInfo*, m_Info);
	MAKEGETSET(bool, m_ViewTile);
	MAKEGETSET(bool, m_ViewPass);
	MAKEGETSET(bool, m_ViewIndex);
};

