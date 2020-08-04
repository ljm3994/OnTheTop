#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	ImagKey = "";
}


Tile::~Tile()
{
}

void Tile::TileInit(D3DXVECTOR2 Index, TileProperty TileState, float Width, float Height)
{
	m_Index = Index;
	m_Width = Width;
	m_Height = Height;
	m_Object = OBJECT_EMPTY;
	m_TileProperty = TileState;
	m_pos = D3DXVECTOR2(m_Index.x * m_Width + (m_Width / 2), m_Index.y * m_Height + (m_Height / 2));
}

void Tile::Render(bool PassView, bool TileView, bool TileIndexView)
{
	if (TileView)
	{
		IMGMANAGER->Getrect()->SetisFill(false);
		IMGMANAGER->Getrect()->Position(m_pos);
		IMGMANAGER->Getrect()->Scale(m_Width, m_Height);
		IMGMANAGER->Getrect()->Color(1, 0, 1, 0.3f);
		IMGMANAGER->RectRender();
	}

	if (m_TileProperty != TileProperty::EMPTY)
	{
		IMGMANAGER->GetImage(ImagKey)->SetCurrentFrameX(m_TerrianFrame.x);
		IMGMANAGER->GetImage(ImagKey)->SetCurrentFrameY(m_TerrianFrame.y);
		IMGMANAGER->GetImage(ImagKey)->Position(m_pos.x, m_pos.y);
		IMGMANAGER->GetImage(ImagKey)->Scale(m_Width, m_Height);
		IMGMANAGER->Render(ImagKey);
	}

	if (m_Object != TileObject::OBJECT_EMPTY)
	{
		IMGMANAGER->GetImage(ImagKey2)->SetCurrentFrameX(m_objFrame.x);
		IMGMANAGER->GetImage(ImagKey2)->SetCurrentFrameY(m_objFrame.y);
		IMGMANAGER->GetImage(ImagKey2)->Position(m_pos.x, m_pos.y);
		IMGMANAGER->GetImage(ImagKey2)->Scale(m_Width, m_Height);
		IMGMANAGER->Render(ImagKey2);
	}

	if (PassView)
	{
		RECT rect;

		rect.left = static_cast<LONG>((m_pos.x - (m_Width * 0.5f)) - g_ptCam.x);
		rect.bottom = static_cast<LONG>(WINSIZEY - (m_pos.y) - (m_Height * 0.5f) + g_ptCam.y);
		rect.right = static_cast<LONG>(m_pos.x + (m_Width * 0.5f) - g_ptCam.x);
		rect.top = static_cast<LONG>(WINSIZEY - (m_pos.y) + (m_Height * 0.5f) + g_ptCam.y);

		if (m_TileProperty == PASS)
		{
			WRITEMANAGER->RenderText(L"P", rect, 20.0f, L"µ¸¿òÃ¼", D3DXCOLOR(1, 0, 0, 1), DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_CONDENSED);
		}
		else if (m_TileProperty == NONPASS)
		{
			WRITEMANAGER->RenderText(L"NP", rect, 20.0f, L"µ¸¿òÃ¼", D3DXCOLOR(1, 0, 0, 1), DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_CONDENSED);
		}
	}

	if (TileIndexView)
	{
		wchar_t str[256];
		swprintf_s(str, L"%d,%d", static_cast<int>(m_Index.x), static_cast<int>(m_Index.y));
		RECT rect;

		rect.left = static_cast<LONG>((m_pos.x - (m_Width * 0.5f)) - g_ptCam.x);
		rect.bottom = static_cast<LONG>(WINSIZEY - (m_pos.y) - (m_Height * 0.5f) + g_ptCam.y);
		rect.right = static_cast<LONG>(m_pos.x + (m_Width * 0.5f) - g_ptCam.x);
		rect.top = static_cast<LONG>(WINSIZEY - (m_pos.y) + (m_Height * 0.5f) + g_ptCam.y);
		WRITEMANAGER->RenderText(str, rect, 10.0f, L"µ¸¿òÃ¼", D3DXCOLOR(1, 0, 0, 1));
	}
}

void Tile::TilePosSetting(D3DXVECTOR2 pos, float Width, float Height)
{
	m_Index = pos;
	m_Width = Width;
	m_Height = Height;
	m_pos = D3DXVECTOR2(m_Index.x * m_Width + (m_Width / 2), m_Index.y * m_Height + (m_Height / 2));
}

void Tile::SetTileState(TileProperty State)
{
	m_TileProperty = State;
}

float Tile::GetWidth()
{
	return m_Width;
}

TileProperty Tile::GetTileState()
{
	return m_TileProperty;
}

POINT Tile::GetObjFrame()
{
	return m_objFrame;
}

void Tile::SetObjFrame(POINT Frame)
{
	m_objFrame.x = Frame.x;
	m_objFrame.y = Frame.y;
}

void Tile::SetTerrianFrame(POINT Frame)
{
	m_TerrianFrame = Frame;
}

POINT Tile::GetTerrianFrame()
{
	return m_TerrianFrame;
}

void Tile::SetImagKey(string imgkey)
{
	ImagKey = imgkey;
}

void Tile::SetImgObjKey(string Imgkey)
{
	ImagKey2 = Imgkey;
}

bool Tile::operator==(Tile & a) const
{
	return (m_Index.x == a.GetIndex().x) && (m_Index.y == a.GetIndex().y);
}
