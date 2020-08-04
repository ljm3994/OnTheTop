#include "stdafx.h"
#include "TowerUp.h"


TowerUp::TowerUp()
{
}


TowerUp::~TowerUp()
{
}

HRESULT TowerUp::init()
{
	m_Cheat = false;
	MAPMANAGER->MapChange("TowerUp.map");
	g_ptCam.x = 0;
	g_ptCam.y = 0;
	m_player = &SCENEMANAGER->Getm_player();
	m_player->SetMap(MAPMANAGER->GetMap());
	m_player->init();
	m_player->GetRefm_TileIndex().x = 2.0f;
	m_player->GetRefm_TileIndex().y = 2.0f;
	m_player->Setm_Scale({ 30, 50 });
	m_player->SetImgKey("playerIdle");
	m_player->MapChange();

	m_player->SetXCamMove(false);
	m_player->SetYCamMove(true);
	m_player->Setm_JumpTime(250.0f);
	m_player->Setm_Stage(RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 550, WINSIZEY));


	m_IsTalk = false;
	CloudMove = 0.0f;
	TalkChar = new wstring[3];
	TalkChar[0] = L"오래도 걸렸군\n";
	TalkChar[1] = L"사실 내가 바로 이곳의 보스다\n";
	TalkChar[2] = L"음하하하!\n자신있으면 이 문으로 들어와라\n";
	m_Focus = 0;

	DoorPos = MAPMANAGER->GetMap()->GetPointTile({ 9, 97 })->Getm_pos();
	PlayerPos = &m_player->GetRefm_pos();
	return S_OK;
}

void TowerUp::release()
{
}

void TowerUp::update()
{

	if (tower == false)
	{
		m_player->update();
		CloudMove++;
	}

	if (KEYMANAGER->isKeyDown(VK_F10))
	{
		m_Cheat = !m_Cheat;
	}

	// 10, 97
	if (DoorPos.x <= PlayerPos->x && DoorPos.y <= PlayerPos->y)
	{
		g_ptCam.y = DoorPos.y - 200;
		m_player->Setm_IsMove(false);
		m_IsTalk = true;
		if (KEYMANAGER->isKeyDown(VK_SPACE))
		{
			m_Focus++;

			if (m_Focus > 2)
			{
				SCENEMANAGER->SceneNext("Boss");
			}
		}
	}
	if (m_Cheat)
	{
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			g_ptCam.y += g_ptMouse.y;
			m_player->GetRefm_pos().x = g_ptMouse.x + g_ptCam.x;
			m_player->GetRefm_pos().y = g_ptMouse.y + g_ptCam.y;
		}
	}
}

void TowerUp::render()
{
	if (tower == false)
	{
		
		//구름
		IMGMANAGER->GetImage("Tutorial")->Scale(WINSIZEX, WINSIZEY);
		IMGMANAGER->GetImage("Tutorial")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Tutorial");

		//타워
		IMGMANAGER->GetImage("towerA")->Scale(WINSIZEX-100.0f, 2941.0f);
		IMGMANAGER->GetImage("towerA")->Position(400.0f, (WINSIZEY / 2.0f) + g_ptCam.y);
		IMGMANAGER->Render("towerA");

		IMGMANAGER->GetImage("GuardNPC")->Position(DoorPos.x + 50, DoorPos.y + 25);
		IMGMANAGER->GetImage("GuardNPC")->Scale({ 120, 137 });
		MAPMANAGER->Render();
		IMGMANAGER->GetImage("GuardNPC")->Render();
		if (m_IsTalk)
		{
			RECT rc = { 170.0f,150.0f,420.0f,82.0f };

			IMGMANAGER->GetImage("C_Talk")->Scale(560.0f, 180.0f);
			IMGMANAGER->GetImage("C_Talk")->Position({ WINSIZEX / 2, DoorPos.y + 200 });
			IMGMANAGER->Render("C_Talk");
			rc = { static_cast<LONG>((WINSIZEX / 2) - 180.0f),static_cast<LONG>(190),static_cast<LONG>((WINSIZEX / 2) + 280.0f),static_cast<LONG>(590) };
			WRITEMANAGER->RenderText(TalkChar[m_Focus], rc, 20, L"돋움체", D3DXCOLOR(0, 0, 0, 1), DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_MEDIUM);
		}

		m_player->render();
		//촛불
		//IMGMANAGER->GetImage("Light")->Scale(50.0f, 50.0f);
		//IMGMANAGER->GetImage("Light")->Position(200.0f - 15.0f, 435.0f);
		//IMGMANAGER->Render("Light");

		//m_player->render();
	}

}
