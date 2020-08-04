#pragma once
#include "Map.h"

//�̹���Ÿ��(�ΰ���)
#define TILESIZEGAME 48
#define MaxImgKey 13

struct ImageInfo
{
	string ImageName;
	int MaxFrameX;
	int MaxFrameY;
	float FrameSizeX;
	float FrameSizey;
	float ImageWitdh;
	float ImageHegiht;
};

class MapTool : public GameNode
{
	vector<ImageInfo> m_ImageInfo;
	Map * m_Map;
	Mode m_Mode;
	string ImageKey1;
	string ImageKey2;
	TileProperty _SelectType;
	TileObject m_Object;
	bool m_ObjectSelect;
	bool m_bStateSelect[2];
	bool TileSettingOpen;
	UINT m_SelectFramx;
	UINT m_SelectFramy;
	bool m_PassView;
	bool m_TileView;
	bool m_TileIndexView;
	string MapName;
	int SelectImage;
	int X, Y;
	float W, H;
public:
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void ImgSet();
	//��������
	//�ʼ���
	void setMap();
	//���̺�
	//�ε�
	void ImGuiSetting();
	void ImGuiMain();
	void ImGuiTileSettingMenu(bool * Popen);
	MapTool();
	~MapTool() {}
};

