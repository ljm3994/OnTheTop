#pragma once
#include "Map/Map.h"
#include "Character/Player.h"

class Tutorial : public GameNode
{
	float		CloudMove;
	Player * m_player;
	Image * NPC;
	UINT BagroundCount;
	D3DXVECTOR2 NPCPos;
	wstring *m_TalkStr;
	bool m_IsTalk;
	UINT m_Focus;
public:
	Tutorial();
	~Tutorial();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

