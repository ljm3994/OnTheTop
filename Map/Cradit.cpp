#include "stdafx.h"
#include "Cradit.h"


Cradit::Cradit()
{
}


Cradit::~Cradit()
{
}

HRESULT Cradit::init()
{

	return S_OK;
}

void Cradit::release()
{
}

void Cradit::update()
{	

	if (SCENEMANAGER->Getm_boss().GetBossHp().x <= -477.0f)
	{
		if ((SOUNDMANAGER->isPlaySound("boss_2p")))SOUNDMANAGER->stop("boss_2p");
		if ((!SOUNDMANAGER->isPlaySound("Intro"))) SOUNDMANAGER->play("Intro");
		cradit = true;
	}
}

void Cradit::render()
{
	IMGMANAGER->GetImage("hp2")->Scale(480.0f, 50.0f);
	IMGMANAGER->GetImage("hp2")->Position(267.0f, 570.0f);
	IMGMANAGER->Render("hp2");

	IMGMANAGER->GetImage("hp")->Scale(480.0f + SCENEMANAGER->Getm_boss().GetBossHp().x, 50.0f + SCENEMANAGER->Getm_boss().GetBossHp().y);
	IMGMANAGER->GetImage("hp")->Position(267.0f + (SCENEMANAGER->Getm_boss().GetBossHp().x / 2.5f), 570.0f);
	IMGMANAGER->Render("hp");

	if (cradit == true)
	{

		IMGMANAGER->GetImage("Back")->Scale(1200.0f, 1200.0f);
		IMGMANAGER->GetImage("Back")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Back");


		IMGMANAGER->GetImage("Menu")->Scale(800.0f - 100.0f, 550.0f);
		IMGMANAGER->GetImage("Menu")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Menu");

		IMGMANAGER->GetImage("Cradit")->Scale(800.0f - 100.0f, 550.0f);
		IMGMANAGER->GetImage("Cradit")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Cradit");
	}
}
