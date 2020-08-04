#pragma once
#include "GameNode.h"
#include "Map/Map.h"
enum class my
{
	as = 'C',
};
enum MOVE_DIR
{
	MOVE_IDLE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP
};
enum ColisionDir
{
	COLISION_NO,
	COLISION_LEFT,
	COLISION_RIGHT,
	COLISION_DOWN,
	COLISION_UP,
	COLISION_EMPTY
};
class CharacterManager : public GameNode
{
protected:
	Map* m_map;
	Rect* m_rect;
	Image * m_CharacterImage;
	string ImgKey;
	MOVE_DIR m_MoveDir;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_TileIndex;
	D3DXVECTOR2 m_Scale;
	D3DXVECTOR2 m_Frame;
	D3DXVECTOR2 m_Dir;
	D3DXVECTOR2 m_Gravity;
	float m_Speed;
public:
	CharacterManager(string strKey, D3DXVECTOR2 Pos, D3DXVECTOR2 Scale, Map * map);
	CharacterManager();
	void GravityApply();
	void Move(MOVE_DIR dir);
	void MapChange();
	void SetMap(Map * map);
	FRECT GetRect() {return RectMakeCenter(m_pos.x, m_pos.y, m_Scale.x, m_Scale.y); }
	void RectSetting();
	ColisionDir TileCheck(Map * m_Map, ColisionDir dir);
};

