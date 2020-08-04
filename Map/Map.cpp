#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	InfoSetting("Map1", 100, 100, 50, 50);

	TileSetting();
}


Map::~Map()
{
	for (int i = 0; i < m_Info->GetTileMaxX() * m_Info->GetTileMaxY(); i++)
	{
		OBJECTPOOL(Tile)->PushObject(m_tile[i]);
	}
}

void Map::InfoSetting(string MapName, UINT MaxTileX, UINT MaxTileY, UINT TileWidth, UINT TileHeight)
{
	m_Info = new MapInfo(MapName, MaxTileX, MaxTileY, TileWidth, TileHeight);
}

void Map::TileSetting()
{
	int index = 0;

	//타일 초기화
	for (int i = 0; i < m_Info->GetTileMaxX(); i++)
	{
		for (int j = 0; j < m_Info->GetTileMaxY(); j++)
		{
			//타일을 새로 생성해서 전체타일벡터에 넣어두기
			Tile * TempTile = OBJECTPOOL(Tile)->GetObObject();
			TempTile->TileInit({ static_cast<float>(i), static_cast<float>(j) }, TileProperty::EMPTY, m_Info->GetTileWidth(), m_Info->GetTileHeight());
			m_tile.emplace_back(TempTile);
		}
	}

	//LoadMap();
}

void Map::WallTileSetting(D3DXVECTOR2 Pos)
{
	int Index = static_cast<int>((Pos.x * m_Info->GetTileMaxY()) + Pos.y);
	Tile * node = m_tile[Index];
	node->SetTileState(TileProperty::NONPASS);
}

Tile * Map::GetPointTile(D3DXVECTOR2 Pos)
{
	int Index = GetTileIndex(Pos);

	return m_tile[Index];
}

D3DXVECTOR2 Map::GetPositionTile(D3DXVECTOR2 Pos)
{
	D3DXVECTOR2 ReturnValue;
	float TileWitdh = m_Info->GetTileWidth();
	float TileHeight = m_Info->GetTileHeight();
	ReturnValue.x = round((Pos.x + (TileWitdh * 0.5f)) / TileWitdh);
	ReturnValue.y = round((Pos.y + (TileHeight * 0.5f)) / TileHeight);
	ReturnValue.x -= 1;
	ReturnValue.y -= 1;
	return ReturnValue;
	
}

int Map::GetTileIndex(D3DXVECTOR2 Pos)
{
	return Pos.y + (Pos.x * m_Info->GetTileMaxX());
}


HRESULT Map::init()
{
	TileSetting();
	return S_OK;
}

void Map::release()
{
}

void Map::update()
{

}

void Map::render()
{
	UINT m_iCullX = static_cast<int>(round((fabs(g_ptCam.x) / (m_Info->GetTileWidth()))));
	UINT m_iCullY = static_cast<int>(round(fabs(g_ptCam.y) / m_Info->GetTileHeight()));
	m_iCullX -= 1;
	m_iCullY -= 1;
	int iIndex = 0;

	for (int i = 0; i <= m_Info->GetTileWindowNumX(); i++)
	{
		for (int j = 0; j <= m_Info->GetTileWindowNumY(); j++)
		{
			iIndex = (i + m_iCullX) * m_Info->GetTileMaxX() + (j + m_iCullY);

			if (iIndex >= m_Info->GetTileMaxX() * m_Info->GetTileMaxY())
				continue;

			m_tile[iIndex]->Render(m_ViewPass, m_ViewTile, m_ViewIndex);
		}
	}

}
bool Map::SaveMap(LPCSTR SaveName)
{
	HANDLE file = nullptr;
	bool ReturnValue = false;
	DWORD write;

	/*file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);*/

	file = CreateFile(SaveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReturnValue = WriteFile(file, m_Info, sizeof(MapInfo), &write, NULL);

	Tile* tile = new Tile[m_tile.size()];

	for (int i = 0; i < m_tile.size(); i++)
	{
		tile[i] = *m_tile[i];
	}

	ReturnValue = WriteFile(file, tile, sizeof(Tile) * m_tile.size(), &write, NULL);

	CloseHandle(file);

	SAFE_DELETE_ARRAY(tile);

	return ReturnValue;
}

void Map::SetMaxTile(UINT X, UINT Y, float W, float H)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			int index = j + (i * X);
			if ((m_tile.size()-1) > index)
			{
				m_tile[index]->TilePosSetting({ static_cast<float>(i), static_cast<float>(j) }, W, H);
			}
			else
			{
				Tile * TempTile = OBJECTPOOL(Tile)->GetObObject();
				TempTile->TileInit({ static_cast<float>(i), static_cast<float>(j) }, TileProperty::EMPTY, m_Info->GetTileWidth(), m_Info->GetTileHeight());
				m_tile.emplace_back(TempTile);
			}
		}
	}

	int index = Y * X;
	vector<Tile* >::iterator it;

	for (it = m_tile.begin() + index; it != m_tile.end();)
	{
		it = m_tile.erase(it);
	}

	m_Info->SetMaxTile(X, Y);
	m_Info->SetSizeTile(W, H);
}

bool Map::LoadMap(LPCSTR SaveName)
{
	HANDLE file = nullptr;
	bool ReturnValue = false;
	DWORD read;
	for (int i = 0; i < m_tile.size(); i++)
	{
		OBJECTPOOL(Tile)->PushObject(m_tile[i]);
	}
	m_tile.clear();
	file = CreateFile(SaveName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReturnValue = ReadFile(file, m_Info, sizeof(MapInfo), &read, NULL);

	TileSetting();
	Tile* tile = new Tile[m_Info->GetTileMaxX() * m_Info->GetTileMaxY()];

	ReturnValue = ReadFile(file, tile, sizeof(Tile) * m_Info->GetTileMaxX() * m_Info->GetTileMaxY(), &read, NULL);

	for (int i = 0; i < m_tile.size(); i++)
	{
		m_tile[i]->SetObjFrame(tile[i].GetObjFrame());
		m_tile[i]->SetImagKey(tile[i].GetImagKey());
		m_tile[i]->SetImgObjKey(tile[i].GetImagKey2());
		m_tile[i]->SetObjectState(tile[i].Getm_Object());
		m_tile[i]->SetTileState(tile[i].GetTileState());
		m_tile[i]->SetTerrianFrame(tile[i].GetTerrianFrame());
		m_tile[i]->Setm_Width(tile[i].Getm_Width());
		m_tile[i]->Setm_Height(tile[i].Getm_Height());
	}

	CloseHandle(file);

	//SAFE_DELETE_ARRAY(tile);

	return ReturnValue;
}

void Map::setMap(LONG m_SelectFrameX, LONG m_SelectFramey, Mode m_Mode, string imgKey1, TileProperty Property, bool m_ObjectSelect, TileObject m_Object, string imgKey2)
{
	int iIndex = 0;
	UINT m_iCullX = static_cast<int>(round((fabs(g_ptCam.x) / m_Info->GetTileWidth())));
	UINT m_iCullY = static_cast<int>(round(fabs(g_ptCam.y) / m_Info->GetTileHeight()));

	for (int i = 0; i < m_Info->GetTileWindowNumX(); i++)
	{
		for (int j = 0; j < m_Info->GetTileWindowNumY(); j++)
		{
			iIndex = (i + m_iCullX) * m_Info->GetTileMaxX() + (j + m_iCullY);

			if (iIndex >= m_Info->GetTileMaxX() * m_Info->GetTileMaxY())
				continue;

			if (PtInRect(m_tile[iIndex]->GetRect(), g_ptMouse + g_ptCam))
			{
				POINT n;
				n = { m_SelectFrameX, m_SelectFramey };

				if (Property != TileProperty::EMPTY && m_Mode == MODE_DRAW)
				{
					//현재버튼이 지형이냐?
					if (!m_ObjectSelect)
					{
						m_tile[iIndex]->SetTerrianFrame(n);
						m_tile[iIndex]->SetImagKey(imgKey1);
						m_tile[iIndex]->SetObjectState(TileObject::OBJECT_EMPTY);
					}
					//현재버튼이 오브젝트냐?
					else
					{
						m_tile[iIndex]->SetObjFrame(n);
						m_tile[iIndex]->SetImgObjKey(imgKey2);
						m_tile[iIndex]->SetObjectState(m_Object);
					}
				}
				else if (m_Mode == MODE_REMOVE)
				{
					m_tile[iIndex]->SetObjFrame({ 0, 0 });
					m_tile[iIndex]->SetTerrianFrame({ 0, 0 });
					m_tile[iIndex]->SetImagKey("");
					m_tile[iIndex]->SetImgObjKey("");
					m_tile[iIndex]->SetObjectState(TileObject::OBJECT_EMPTY);
					Property = TileProperty::EMPTY;
				}

				m_tile[iIndex]->SetTileState(Property);
			}
		}
	}
}

