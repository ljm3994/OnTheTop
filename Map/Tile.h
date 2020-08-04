#pragma once
#include "GameNode.h"
enum TileProperty
{
	EMPTY,
	PASS,
	NONPASS
};
enum TileObject
{
	OBJECT_EMPTY,
	OBJECT_DOOR,
	OBJECT_TRAP,
	OBJECT_SCAFFOLDING,
	OBJECT_ETC
};

class Tile
{
	float m_Width;                                  // 타일의 넓이
	float m_Height;                                // 타일의 높이
	D3DXVECTOR2 m_Index;                             //타일의 x,y 인덱스 번호
	D3DXVECTOR2 m_pos;                                //타일의 중심좌표
	TileProperty m_TileProperty;                    // 타일의 상태 PASS : 빈곳(플레이어가 지나다닐수 있음) NONPASS : 벽 (이동 불가)
	POINT m_objFrame;                                  // 출력할 이미지의 아이디 번호
	TileObject m_Object;
	string ImagKey;
	string ImagKey2;
	string ImagKey3;
	POINT m_TerrianFrame;
public:
	Tile();
	~Tile();
	void TileInit(D3DXVECTOR2 pos, TileProperty TileState, float Width, float Height);
	void Render(bool PassView, bool TileView, bool TileIndexView);
	void TilePosSetting(D3DXVECTOR2 pos, float Width, float Height);
	void SetTileState(TileProperty State);
	float GetWidth();
	TileProperty GetTileState();
	FRECT GetRect() { return RectMakeCenter(m_pos.x, m_pos.y, m_Width, m_Height); }
	POINT GetObjFrame();
	void SetObjectState(TileObject State) { m_Object = State; }
	void SetObjFrame(POINT Frame);
	void SetTerrianFrame(POINT Frame);
	POINT GetTerrianFrame();
	void SetImagKey(string imgkey);
	void SetImgObjKey(string Imgkey);
	D3DXVECTOR2 GetIndex() { return m_Index; }
	bool operator == (Tile & a) const;
	MAKEGETSET(D3DXVECTOR2, m_pos);
	MAKEGET(string, ImagKey);
	MAKEGET(string, ImagKey2);
	MAKEGET(string, ImagKey3);
	MAKEGET(TileObject, m_Object);
	MAKESET(D3DXVECTOR2, m_Index);
	MAKEGETSET(float, m_Width);
	MAKEGETSET(float, m_Height);
};

