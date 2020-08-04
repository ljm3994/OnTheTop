#include "stdafx.h"
#include "BossStage.h"


BossStage::BossStage()
{
}


BossStage::~BossStage()
{
}

HRESULT BossStage::init()
{
	m_boss = &SCENEMANAGER->Getm_boss();
	m_boss->init();
	m_player = &SCENEMANAGER->Getm_player();
	m_player->init();
	m_player->SetMap(MAPMANAGER->GetMap());
	m_player->GetRefm_TileIndex().x = 2.0f;
	m_player->GetRefm_TileIndex().y = 2.0f;
	m_player->Setm_Scale({ 30, 50 });
	m_player->SetImgKey("playerIdle");
	m_player->MapChange();


	m_player->Setm_Stage(RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 550, WINSIZEY));
	m_player->SetXCamMove(false);
	m_player->SetYCamMove(false);
	cloude.x = 250.0f;
	cloude.y = 510.0f;
	CloudeScale.x = 450.0f;
	CloudeScale.y = 300.0f;
	g_ptCam.x = 0;
	g_ptCam.y = 0;
	BossChange = false;
	m_FirstSound = true;
	m_isBossAttack = false;
	m_Stage = RectMakeCenter(WINSIZEX / 2.0f - 150.0f, (WINSIZEY / 2.0f - 110.0f) + (cloude.y - (WINSIZEY / 2.0f - 110.0f)), WINSIZEX - 350.0f, (WINSIZEY / 2.0f + 350.0f) + CloudeScale.y);
	m_player->Setm_Stage(m_Stage);
	m_boss->SetPlayerPos(&m_player->GetRefm_pos());
	m_boss->Setm_Stage(m_Stage);
	m_player->RectSetting();
	note = new Note();
	note->init();
	CountLeft = 0;
	notedir = NOTE_LEFT;
	DeleayTime = 0;
	CountUP = 0;
	CountRight = 0;
	CountDown = 0;
	m_IsNote = false;
	NoteDown = false;
	NextNote = 1;
	NoteTime = 0;
	JSKILL = 0.38f;
	MaxTime = 0.38f;
	time = 0.0f;
	m_Cradit = new Cradit();
	m_Cradit->init();
	GameClear = false;
	return S_OK;
}

void BossStage::release()
{
}

void BossStage::update()
{
	CloudMove += g_ETime / 4.0f;
	if (m_FirstSound)
	{
		if ((!SOUNDMANAGER->isPlaySound("boss"))) SOUNDMANAGER->play("boss");
		MAPMANAGER->MapChange(_T("BossStage.map"));
		m_player->MapChange();
		m_FirstSound = false;
	}

	if (m_boss->GetBossChange(2))
	{
		CloudMove += g_ETime / 3.0f;
		m_player->update();
	}
	m_boss->update();
	float DX = m_boss->Getm_DeleyTime();

	if (DX > 0.0f)
	{
		m_IsNote = true;
	}
	if (m_IsNote)
	{
		time += g_ETime;


		if (time > JSKILL && Count < 4)
		{
			autonote(time, NextNote, MaxTime);
			NextNote++;
		}
		if (time > JSKILL && Count < 4)
		{
			autonote2(time, NextNote, MaxTime);
			NextNote++;
		}
		if (time > JSKILL && Count < 4)
		{
			autonote3(time, NextNote, MaxTime);
			NextNote++;
		}
		if (time > JSKILL && Count < 4)
		{
			autonote4(time, NextNote, MaxTime);
			NextNote++;
		}
		if (time > JSKILL && Count < 4)
		{
			MaxTime += 0.8f;
			JSKILL += 0.8f;
			Count++;
		}
		DeleayTime += g_ETime;
		if (KEYMANAGER->StayKeyDown('Z'))
		{
			if (DeleayTime > 0.2f)
			{
				m_player->MakeBullet();
				DeleayTime = 0.0f;
			}
		}

		if (KEYMANAGER->StayKeyDown('C'))	//치트
		{
			D3DXVECTOR2 hp = m_boss->GetBossHp();
			hp.x = -476.0f;
			m_boss->SetBossHp(hp);
		}

		m_player->BulletFire();

		if (m_player->EnemyColide(RectMakeCenter(m_boss->Getposition().x, m_boss->Getposition().y, 100, 70)))
		{
			D3DXVECTOR2 hp = m_boss->GetBossHp();
			hp.x -= 10;
			m_boss->SetBossHp(hp);

		}

		if (m_boss->GetBossHp().x <= 0)
		{
			GameClear = true;
		}
		//MaxTime += 0.8f;
		//DeleayTime += g_ETime;
		//NoteTime = SOUNDMANAGER->GetPosition("boss_2p");

		//if(DeleayTime > 0.08f)
		//{
		//	NoteDown = true;
		//	DeleayTime = 0.0f;
		//}
		
		
			
		//
		//if (NoteTime == 0 && NextNote == 0 && NoteDown)
		//{
		//	if (CountLeft < 3)
		//	{
		//		notedir = NOTE_DIR::NOTE_LEFT;
		//		CountLeft++;
		//	}
		//	else
		//	{
		//		if (CountUP < 1)
		//		{
		//			notedir = NOTE_DIR::NOTE_UP;
		//			CountUP++;
		//		}
		//		else
		//		{
		//			notedir = NOTE_DIR::NOTE_RIGHT;
		//			NextNote++;
		//		}
		//	}
		//	note->NoteDown(notedir);
		//	NoteDown = false;
		//}
		//else if (NoteTime >= 0.25 && NoteTime <= 1300 && NextNote == 1 && NoteDown)
		//{
		//	if (CountLeft < 6)
		//	{
		//		notedir = NOTE_DIR::NOTE_LEFT;
		//		CountLeft++;
		//	}
		//	else
		//	{
		//		if (CountUP < 2)
		//		{
		//			notedir = NOTE_DIR::NOTE_UP;
		//			CountUP++;
		//		}
		//		else
		//		{
		//			notedir = NOTE_DIR::NOTE_RIGHT;
		//			NextNote++;
		//		}
		//	}
		//	note->NoteDown(notedir);
		//	NoteDown = false;
		//}
		//else if (NoteTime >= 2000 && NextNote == 2 && NoteDown)
		//{
		//	if (CountLeft < 9)
		//	{
		//		notedir = NOTE_DIR::NOTE_LEFT;
		//		CountLeft++;
		//	}
		//	else
		//	{
		//		if (CountUP < 3)
		//		{
		//			notedir = NOTE_DIR::NOTE_UP;
		//			CountUP++;
		//		}
		//		else
		//		{
		//			notedir = NOTE_DIR::NOTE_RIGHT;
		//
		//		}
		//	}
		//	note->NoteDown(notedir);
		//	NoteDown = false;
		//}

		note->NotePosDown();
		note->update();
	}

	if (GameClear)
	{
		if (KEYMANAGER->isKeyDown(VK_SPACE))
		{
			SCENEMANAGER->SceneNext("Menu");
		}
	}
	if (m_boss->BulletColide(m_player->GetRect()) && !GameClear)
	{
		UINT Life = m_player->GetPlayerLife();
		Life--;
		if (Life <= 0)
		{
			if ((SOUNDMANAGER->isPlaySound("boss_2p")))SOUNDMANAGER->stop("boss_2p");
			if ((!SOUNDMANAGER->isPlaySound("GameOver"))) SOUNDMANAGER->play("GameOver");


			SCENEMANAGER->SceneNext("GameOver");
		}
		else
		{
			m_player->SetPlayerLife(Life);
		}
	}
	m_Cradit->update();
}

void BossStage::render()
{
	

	D3DXCOLOR background = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)background);

	IMGMANAGER->GetImage("BossBG_1")->Scale(WINSIZEX - 350.0f, WINSIZEY / 2.0f + 100.0f);
	IMGMANAGER->GetImage("BossBG_1")->Position(WINSIZEX / 2.0f - 150.0f, WINSIZEY / 2.0f - 110.0f);
	IMGMANAGER->Render("BossBG_1");

	IMGMANAGER->GetImage("BossBG_2")->Scale(CloudeScale.x, CloudeScale.y);
	IMGMANAGER->GetImage("BossBG_2")->Position(cloude.x, cloude.y);
	IMGMANAGER->LoofRender("BossBG_2", CloudMove, 0.0f);

	m_boss->render();
	m_player->BulletRender();
	m_player->render();

	IMGMANAGER->GetImage("Arrow3")->Scale(320.0f, 100.0f);
	IMGMANAGER->GetImage("Arrow3")->Position(WINSIZEX / 2.0f + 238.0f, 50.0f);
	IMGMANAGER->Render("Arrow3");

	IMGMANAGER->GetImage("Arrow2")->Scale(320.0f, 100.0f);
	IMGMANAGER->GetImage("Arrow2")->Position(WINSIZEX / 2.0f + 238.0f, 550.0f);
	IMGMANAGER->Render("Arrow2");
	note->render();
	IMGMANAGER->GetImage("NoteBar")->Scale(320.0f, 20.0f);
	IMGMANAGER->GetImage("NoteBar")->Position(WINSIZEX / 2.0f + 238.0f, 510.0f);
	IMGMANAGER->Render("NoteBar");

	
	

	for (int i = m_player->GetPlayerLife(); i > 0; i--)
	{
		
		IMGMANAGER->GetImage("playerLife")->Scale(50, 50);
		IMGMANAGER->GetImage("playerLife")->Position(600.0f + (i * 50.0f), 550.0f);
		IMGMANAGER->Render("playerLife");
	}

	
	m_Cradit->render();

	

	/*
	//보스방 노트충돌 대
	IMGMANAGER->AddImage("Arrow", _T("Arrow.png"), "PS2");
	IMGMANAGER->AddImage("Arrow2", _T("Arrow2.png"), "PS2");
	IMGMANAGER->AddImage("Arrow3", _T("Arrow3.png"), "PS2");

	//보스방 노트
	IMGMANAGER->AddImage("Left", _T("A_Left_A.png"), "PS2");
	IMGMANAGER->AddImage("A_Up", _T("A_Up_A.png"), "PS2");
	IMGMANAGER->AddImage("Right", _T("A_Right_A.png"), "PS2");
	IMGMANAGER->AddImage("Down", _T("A_Down_A.png"), "PS2");
	*/

}

void BossStage::autonote(float time, int max, float maxtime)
{

	if (time > maxtime && time < maxtime + 0.1f  && CountLeft < max)
	{
		notedir = NOTE_DIR::NOTE_LEFT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountLeft++;

	}

	if (time > maxtime + 0.14f && time < maxtime + 0.18f && CountUP < max)
	{
		notedir = NOTE_DIR::NOTE_UP;
		NoteDown = true;
		note->NoteDown(notedir);
		CountUP++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.22f && CountRight < max)
	{
		notedir = NOTE_DIR::NOTE_RIGHT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountRight++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.28f && CountDown < max)
	{
		notedir = NOTE_DIR::NOTE_DOWN;
		NoteDown = true;
		note->NoteDown(notedir);
		CountDown++;
	}
}
// 0.38f
void BossStage::autonote2(float time, int max, float maxtime)
{
	
	if (time > maxtime && time < maxtime + 0.1f && CountLeft < max)
	{
		notedir = NOTE_DIR::NOTE_UP;
		NoteDown = true;
		note->NoteDown(notedir);
		CountLeft++;

	}

	if (time > maxtime + 0.14f && time < maxtime + 0.18f && CountUP < max)
	{
		notedir = NOTE_DIR::NOTE_DOWN;
		NoteDown = true;
		note->NoteDown(notedir);
		CountUP++;
	}

	if (time > maxtime + 0.2f && time < maxtime + 0.22f && CountRight < max)
	{
		notedir = NOTE_DIR::NOTE_LEFT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountRight++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.28f && CountDown < max)
	{
		notedir = NOTE_DIR::NOTE_RIGHT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountDown++;
	}
}

void BossStage::autonote3(float time, int max, float maxtime)
{
	
	if (time > maxtime && time < maxtime + 0.1f && CountLeft < max)
	{
		notedir = NOTE_DIR::NOTE_RIGHT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountLeft++;

	}

	if (time > maxtime + 0.14f && time < maxtime + 0.18f && CountUP < max)
	{
		notedir = NOTE_DIR::NOTE_LEFT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountUP++;
	}

	if (time > maxtime + 0.2f && time < maxtime + 0.22f && CountRight < max)
	{
		notedir = NOTE_DIR::NOTE_DOWN;
		NoteDown = true;
		note->NoteDown(notedir);
		CountRight++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.28f && CountDown < max)
	{
		notedir = NOTE_DIR::NOTE_UP;
		NoteDown = true;
		note->NoteDown(notedir);
		CountDown++;
	}
}

void BossStage::autonote4(float time, int max, float maxtime)
{
	
	if (time > maxtime && time < maxtime + 0.1f && CountLeft < max)
	{
		notedir = NOTE_DIR::NOTE_LEFT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountLeft++;

	}

	if (time > maxtime + 0.14f && time < maxtime + 0.18f && CountUP < max)
	{
		notedir = NOTE_DIR::NOTE_RIGHT;
		NoteDown = true;
		note->NoteDown(notedir);
		CountUP++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.22f && CountRight < max)
	{
		notedir = NOTE_DIR::NOTE_UP;
		NoteDown = true;
		note->NoteDown(notedir);
		CountRight++;
	}

	if (time > maxtime + 0.2f&& time < maxtime + 0.28f && CountDown < max)
	{
		notedir = NOTE_DIR::NOTE_DOWN;
		NoteDown = true;
		note->NoteDown(notedir);
		CountDown++;
	}
}
