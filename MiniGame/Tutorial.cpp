#include "stdafx.h"
#include "Tutorial.h"


Tutorial::Tutorial()
{

}


Tutorial::~Tutorial()
{
}

HRESULT Tutorial::init()
{
	g_ptCam.x = 0;
	g_ptCam.y = 0;
	MAPMANAGER->MapChange("Tutorial.map");
	m_player = &SCENEMANAGER->Getm_player();
	m_player->SetMap(MAPMANAGER->GetMap());
	m_player->GetRefm_TileIndex().x = 2.0f;
	m_player->GetRefm_TileIndex().y = 5.0f;
	m_player->Setm_Scale({ 30, 50 });
	m_player->SetImgKey("playerIdle");
	m_player->MapChange();

	m_player->SetXCamMove(true);
	m_player->SetYCamMove(true);
	m_player->RectSetting();
	m_player->init();
	m_player->Setm_Stage(RectMakeCenter(WINSIZEX /2, WINSIZEY / 2, WINSIZEX, WINSIZEY));

	if ((!SOUNDMANAGER->isPlaySound("guard_before"))) SOUNDMANAGER->play("guard_before");
	NPCPos = MAPMANAGER->GetMap()->GetPointTile({ 57, 5 })->Getm_pos();
	BagroundCount = (MAPMANAGER->GetMap()->Getm_Info()->GetTileMaxX() * MAPMANAGER->GetMap()->Getm_Info()->GetTileWidth()) / (WINSIZEX);
	NPCPos.y += 20.0f;
	CloudMove = 0.0f;
	m_Focus = 0;
	m_TalkStr = new wstring[10];
	m_TalkStr[0] = L"어이! 여기는 올라가면 안돼\n";
	m_TalkStr[1] = L"아저씨는 누구시죠?\n";
	m_TalkStr[2] = L"난 이 탑을 지키는 문지기다\n너 처럼 아무것도 모르고\n이 탑을 오르려는사람들을 막고 있지\n";
	m_TalkStr[3] = L"어서 돌아가라!\n";
	m_TalkStr[4] = L"하지만 전 이탑을 무조건 올라가야 하는 걸요\n";
	m_TalkStr[5] = L"흐음\n귀찮구만\n어쩔 수 없지 지나가라! 지나가\n";
	m_TalkStr[6] = L"감사합니다!!!!\n";
	m_TalkStr[7] = L"어이\n근데 탑을 올라가는 방법은 알고 있나?\n";

	m_IsTalk = false;
	return S_OK;
}

void Tutorial::release()
{
}

void Tutorial::update()
{
	CloudMove += g_ETime;
	m_player->update();

	if (!m_IsTalk)
	{
		if (m_player->GetRefm_pos().x >= MAPMANAGER->GetMap()->GetPointTile({ 53, 5 })->Getm_pos().x)
		{
			
			g_ptCam.x = (WINSIZEX / 2) + (m_player->GetRefm_pos().x - WINSIZEX);
			m_player->Setm_IsMove(false);
			if ((SOUNDMANAGER->isPlaySound("guard_before"))) SOUNDMANAGER->stop("guard_before");
			if ((!SOUNDMANAGER->isPlaySound("guard_tutorial"))) SOUNDMANAGER->play("guard_tutorial");
			m_IsTalk = true;
		}
	}
	else
	{
		if (KEYMANAGER->isKeyDown(VK_SPACE))
		{

			if (m_Focus < 7)
			{
				m_Focus++;
			}
			else
			{
				SCENEMANAGER->SceneNext("TowerUp");
				if ((SOUNDMANAGER->isPlaySound("guard_tutorial"))) SOUNDMANAGER->stop("guard_tutorial");
				if ((!SOUNDMANAGER->isPlaySound("Game_idle"))) SOUNDMANAGER->play("Game_idle");
			}
		}
	}
}

void Tutorial::render()
{
	for (int i = 0; i <= BagroundCount; i++)
	{
		IMGMANAGER->GetImage("Tutorial")->Position({ (WINSIZEX / 2) + (static_cast<float>(i) * WINSIZEX), (WINSIZEY / 2) + 120 });
		IMGMANAGER->GetImage("Tutorial")->Scale(WINSIZEX, WINSIZEY);
		IMGMANAGER->LoofRender("Tutorial", CloudMove);
	}
	IMGMANAGER->GetImage("GuardNPC")->Position(NPCPos);
	IMGMANAGER->GetImage("GuardNPC")->Scale({ 120, 137 });

	MAPMANAGER->Render();
	IMGMANAGER->GetImage("GuardNPC")->Render();
	m_player->render();

	if (m_IsTalk)
	{
		RECT rc = { 170.0f,150.0f,420.0f,82.0f };

		IMGMANAGER->GetImage("C_Talk")->Scale(560.0f, 180.0f);
		IMGMANAGER->GetImage("C_Talk")->Position({ NPCPos.x - 200, 500 });
		IMGMANAGER->Render("C_Talk");
		if (m_Focus != 1 && m_Focus != 4 && m_Focus != 6)
		{
			rc = { static_cast<LONG>(170.0f),static_cast<LONG>(180.0f),static_cast<LONG>(660.0f),static_cast<LONG>(50.0f) };
		}
		else
		{
			rc = { static_cast<LONG>(170.0f),static_cast<LONG>(180.0f),static_cast<LONG>(660.0f),static_cast<LONG>(50.0f) };
		}
		WRITEMANAGER->RenderText(m_TalkStr[m_Focus], rc, 20, L"돋움체", D3DXCOLOR(0, 0, 0, 1), DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_MEDIUM);
	}
}