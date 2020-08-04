#pragma once
#include "GameNode.h"
#include "MiniGame/Arka.h"
#include "MiniGame/Menu.h"
#include "MiniGame/BossStage.h"
#include "MiniGame/Tutorial.h"
#include "Map/TowerUp.h"
#include "Map/Cradit.h"
#include "Map/GameOver.h"
class MainGame :public GameNode
{
private:
	Cradit*		m_Cradit;
	Arka*		m_Arka;
	Map*		m_Map;
	MapTool*	maptool;
	Player*		m_player;
	Tutorial * m_to;
	Menu*		m_Menu;
	GameOver*	m_GameOver;
	Menu2*		m_Menu2;
	BossStage*		m_Boss;
	TowerUp*		m_TowerUp;
	float		Logo2Time = 1000.0f / 600.0f;
	
public:
	MainGame();
	~MainGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;


};

