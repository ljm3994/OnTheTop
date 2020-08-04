#include "stdafx.h"
#include "Arka.h"


Arka::Arka()

{
}


Arka::~Arka()
{
}

HRESULT Arka::init()
{
	//m_Map = new Map;
	//m_Map->init();
	maptool = new MapTool;
	maptool->init();
	//m_player = new Player(m_Map, { 50, 50 }, { 50, 50 });
	return S_OK;
}

void Arka::release()
{

}

void Arka::update()
{
	//m_Map->update();
	//m_player->update();
	maptool->update();
	//m_Map->update();
	//m_player->update();
}

void Arka::render()
{
	//m_Map->render();
	//m_player->render();
	maptool->render();
	//m_Map->render();
	//m_player->render();
}
