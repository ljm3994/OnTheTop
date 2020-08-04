#include "stdafx.h"
#include "CharacterManager.h"

CharacterManager::CharacterManager(string strKey, D3DXVECTOR2 Pos, D3DXVECTOR2 Scale, Map* map)
{
	ImgKey = strKey;
	m_CharacterImage = IMGMANAGER->GetImage(ImgKey);
	m_TileIndex = Pos;
	m_Scale = Scale;
	m_map = map;

	m_rect = new Rect();
	m_MoveDir = MOVE_IDLE;

	m_pos = m_map->GetPointTile(m_TileIndex)->Getm_pos();
	m_rect->Position(m_pos);
	m_rect->Scale(m_Scale);
	m_CharacterImage->Position(m_pos);
	m_CharacterImage->Scale(m_Scale);

	m_rect->Color({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_Dir.x = 0.0f;
	m_Dir.y = 0.0f;
	m_Speed = 100.0f;
	m_Gravity = { 0.0f, 0.0f };
}

CharacterManager::CharacterManager()
{
}


void CharacterManager::GravityApply()
{
	m_pos.y -= m_Gravity.y * g_ETime;
}

void CharacterManager::Move(MOVE_DIR dir)
{
	switch (dir)
	{
	case MOVE_IDLE:
		m_Dir.x = 0;
		m_Dir.y = 0;
		break;
	case MOVE_LEFT:
		if (TileCheck(m_map, COLISION_LEFT) != ColisionDir::COLISION_LEFT)
		{
			m_Dir.x = -1;
		}
		else
		{
			m_Dir.x = 0;
		}
		break;
	case MOVE_RIGHT:
		if (TileCheck(m_map, COLISION_RIGHT) != ColisionDir::COLISION_RIGHT)
		{
			m_Dir.x = 1;
		}
		else
		{
			m_Dir.x = 0;
		}
		break;
	case MOVE_UP:
		if (TileCheck(m_map, COLISION_RIGHT) == ColisionDir::COLISION_RIGHT || TileCheck(m_map, COLISION_LEFT) == ColisionDir::COLISION_LEFT)
		{
			m_Dir.x = 0;
		}
		break;
	}

	m_pos.x += m_Dir.x * m_Speed * g_ETime;

}

void CharacterManager::MapChange()
{
	m_pos = m_map->GetPointTile(m_TileIndex)->Getm_pos();
	m_rect = new Rect();
	m_rect->Position(m_pos);
	m_rect->Scale(m_Scale);
	m_CharacterImage = IMGMANAGER->GetImage(ImgKey);
	m_CharacterImage->Position(m_pos);
	m_CharacterImage->Scale(m_Scale);
}

void CharacterManager::SetMap(Map * map)
{
	m_map = map;
}

void CharacterManager::RectSetting()
{
	m_rect->Position(m_pos);
	m_rect->Scale(m_Scale);
	m_CharacterImage->Position(m_pos);
	m_CharacterImage->Scale(m_Scale);
}

ColisionDir CharacterManager::TileCheck(Map *m_Map, ColisionDir dir)
{
	D3DXVECTOR2 Index = m_Map->GetPositionTile({ m_pos.x, m_pos.y});            // 좌표값을 통해 인덱스의 타일 값을 구해온다
	float Height = m_map->Getm_Info()->GetTileHeight();
	float Width = m_map->Getm_Info()->GetTileWidth();
	D3DXVECTOR2 pos = m_map->GetPointTile(Index)->Getm_pos();

	if (Index.x < 0)
	{
		Index.x = 0;
	}
	else if (Index.x > m_Map->Getm_Info()->GetTileMaxX() - 1)
	{
		Index.x = m_Map->Getm_Info()->GetTileMaxX() - 1;
	}
	if (Index.y < 0)
	{
		Index.y = 0;
	}
	else if (Index.y > m_Map->Getm_Info()->GetTileMaxY() - 1)
	{
		Index.y = m_Map->Getm_Info()->GetTileMaxY() - 1;
	}

	switch (dir)
	{
	case COLISION_LEFT:
		if (Index.x > 0)
		{
			if (m_Map->GetPointTile({ Index.x - 1, Index.y })->GetTileState() == TileProperty::NONPASS && m_pos.x - m_Scale.x <= pos.x - Width)
			{
				return COLISION_LEFT;
			}
		}
		break;
	case COLISION_RIGHT:
		if (Index.x < m_Map->Getm_Info()->GetTileMaxX() - 1)
		{
			if (m_Map->GetPointTile({ Index.x + 1, Index.y })->GetTileState() == TileProperty::NONPASS && m_pos.x + m_Scale.x >= pos.x + Width)
			{
				return COLISION_RIGHT;
			}
		}
		break;
	case COLISION_UP:

		if (Index.y < m_Map->Getm_Info()->GetTileMaxY() - 1)
		{
			if (m_Map->GetPointTile({ Index.x, Index.y + 1 })->GetTileState() == TileProperty::NONPASS && m_pos.y + m_Scale.y >= pos.y + Height)
			{
				return COLISION_UP;
			}
		}
		break;
	case COLISION_DOWN:
		if (Index.y > 0)
		{
			if (m_Map->GetPointTile({ Index.x, Index.y - 1 })->GetTileState() == TileProperty::NONPASS && m_pos.y - m_Scale.y <= pos.y - Height)
			{
				return COLISION_DOWN;
			}
		}
		break;
	}

	return COLISION_NO;
}
