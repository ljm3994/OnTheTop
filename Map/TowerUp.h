#pragma once
#include "GameNode.h"
#include "Character/Player.h"

class TowerUp :public GameNode
{
private:
	bool tower = false;
	Player*	m_player;
	bool m_Cheat;
	float CloudMove;
	D3DXVECTOR2 DoorPos;
	D3DXVECTOR2 * PlayerPos;
	wstring *TalkChar;
	bool m_IsTalk;
	UINT m_Focus;
public:
	TowerUp();
	~TowerUp();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

