#pragma once
#include "GameNode.h"
#include "Map/Map.h"
#include "Map/MapTool.h"
#include "Character/Player.h"
class Arka : public GameNode
{
private:
	Map* m_Map;
	MapTool * maptool;
	Player* m_player;
public:
	Arka();
	~Arka() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

