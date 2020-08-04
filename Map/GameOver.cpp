#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

HRESULT GameOver::init()
{
	return	S_OK;
}

void GameOver::release()
{
}

void GameOver::update()
{
	
	if ((!SOUNDMANAGER->isPlaySound("Game_Over"))) SOUNDMANAGER->play("Game_Over");
	if(KEYMANAGER->isKeyDown(VK_SPACE))
	{ 
		SCENEMANAGER->SceneNext("Menu");
	}
}

void GameOver::render()
{
	IMGMANAGER->GetImage("gameover")->Scale(WINSIZEX , WINSIZEY );
	IMGMANAGER->GetImage("gameover")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
	IMGMANAGER->Render("gameover");
	
}
