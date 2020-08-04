#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//싱글톤 해제
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
	CAMMANAGER->ReleaseSingleton();
	IMGMANAGER->DeleteAll();
	IMGMANAGER->ReleaseSingleton();
	SCENEMANAGER->ReleaseSingleton();

}

HRESULT MainGame::init()
{
	//윈도우가 시작되서 지금까지 흐른 시간을 1/1000초 단위로
	//DWORD형을 리턴하는 함수다
	srand(GetTickCount());
	////////////////////////////////////////////////////


	//루프렌더 사용시 프레임uv버퍼 사용하므로 추가할떄 프레임 갯수 넣어주기
	//IMGMANAGER->AddImage("BG", _T("배경 화면.bmp"), 1, 1, "PS2");


	//SOUNDMANAGER->addSound("BGM", "sound/bgm.wav", true);
	//SOUNDMANAGER->play("BGM");

	// 플레이어 이미지
	IMGMANAGER->AddImage("playerIdle", _T("Char/Player/idle/IdleAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerRunning", _T("Char/Player/running/RunningAni.png"), 6, 1, "PS2");
	IMGMANAGER->AddImage("playerJump", _T("Char/Player/jump/JumpAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerHit", _T("Char/Player/got hit/frame-got-hit.png"), "PS2");

	// 가드 NPC 이미지
	IMGMANAGER->AddImage("GuardNPC", _T("Char/NPC/Tutorial Night.png"), "PS2");
	// 타일 맵 이미지
	IMGMANAGER->AddImage("towerA", _T("towerA.png"), "PS2");
	IMGMANAGER->AddImage("FortressMap", _T("MapFortressTile.png"), 3, 6, "PS");
	IMGMANAGER->AddImage("FortressMap2", _T("TreeForesst.png"), 3, 3, "PS");
	IMGMANAGER->AddImage("TopDoor", _T("Map18-horz.png"), 4, 4, "PS");
	IMGMANAGER->AddImage("Top", _T("Map14-horz.png"), 10, 2, "PS");
	IMGMANAGER->AddImage("Map", _T("Map.png"), 18, 4, "PS");

	//로고
	IMGMANAGER->AddImage("Logo", _T("Logo.png"), "PS2");
	IMGMANAGER->AddImage("T_L", _T("T_L.png"), "PS2");
	IMGMANAGER->AddImage("W_L", _T("W_L.png"), "PS2");
	IMGMANAGER->AddImage("O_L", _T("O_L.png"), "PS2");
	IMGMANAGER->AddImage("P_L", _T("P_L.png"), "PS2");
	IMGMANAGER->AddImage("L_L", _T("L_L.png"), "PS2");
	IMGMANAGER->AddImage("U_L", _T("U_L.png"), "PS2");
	IMGMANAGER->AddImage("S_L", _T("S_L.png"), "PS2");


	//메뉴
	IMGMANAGER->AddImage("Button", _T("MenuButton.png"), "PS2");			//버튼

	IMGMANAGER->AddImage("Menu", _T("Menu.png"), "PS2");					//메뉴판

	IMGMANAGER->AddImage("Back", _T("Back.png"), "PS2");					//메뉴판 백그라운드


	//메뉴 이미지
	IMGMANAGER->AddImage("gamestart", _T("gamestart.png"), "PS2");
	IMGMANAGER->AddImage("option", _T("option.png"), "PS2");
	IMGMANAGER->AddImage("quit", _T("quit.png"), "PS2");
	IMGMANAGER->AddImage("o", _T("o.png"), "PS2");
	IMGMANAGER->AddImage("n", _T("n.png"), "PS2");
	IMGMANAGER->AddImage("t", _T("t.png"), "PS2");
	IMGMANAGER->AddImage("h", _T("h.png"), "PS2");
	IMGMANAGER->AddImage("e", _T("e.png"), "PS2");
	IMGMANAGER->AddImage("p", _T("p.png"), "PS2");
	IMGMANAGER->AddImage("f", _T("f.png"), "PS2");
	IMGMANAGER->AddImage("u", _T("u.png"), "PS2");
	IMGMANAGER->AddImage("l", _T("l.png"), "PS2");
	IMGMANAGER->AddImage("s", _T("s.png"), "PS2");
	IMGMANAGER->AddImage("c", _T("c.png"), "PS2");
	IMGMANAGER->AddImage("r", _T("r.png"), "PS2");
	IMGMANAGER->AddImage("b", _T("b.png"), "PS2");
	IMGMANAGER->AddImage("g", _T("g.png"), "PS2");
	IMGMANAGER->AddImage("m", _T("m.png"), "PS2");
	// 듀토리얼 배경
	IMGMANAGER->AddImage("Tutorial", _T("Background Clouds.png"), 1, 1, "PS2");

	//인트로 이미지
	IMGMANAGER->AddImage("Story", _T("Story.png"), "PS2");

	//보스 이미지
	IMGMANAGER->AddImage("talk", _T("Boss/talk.png"), "PS2");									//보스 대화 할때

	IMGMANAGER->AddImage("idle0", _T("Boss/idle0.png"), "PS2");									//보스 가만히 있을 때(왼)
	IMGMANAGER->AddImage("idle1", _T("Boss/idle1.png"), "PS2");									//보스 가만히 있을 때(중)
	IMGMANAGER->AddImage("idle2", _T("Boss/idle2.png"), "PS2");									//보스 가만히 있을 때(오)

	// 총알 이미지
	IMGMANAGER->AddImage("Bullet", _T("Boss/Bullet.png"), 4, 1, "PS2");

	//보스 맵
	IMGMANAGER->AddImage("BossBG_1", _T("Boss/BossBG_1.png"), "PS2");							//산 배경
	IMGMANAGER->AddImage("BossBG_2", _T("Boss/BossBG_2.png"), 1, 1, "PS2");							//구름 배경

	//대화창
	IMGMANAGER->AddImage("B_Talk", _T("UI/ButtonExtraWide_Black.png"), "PS2");					//보스 대화창
	IMGMANAGER->AddImage("C_Talk", _T("UI/ButtonExtraWide_Beighe.png"), "PS2");					//캐릭터들 대화창
	IMGMANAGER->AddImage("lonatier", _T("lonatier.png"), "PS2");								//로나티어 이름




	//Sound 순서대로 정렬

	SOUNDMANAGER->addSound("Logo", "sound/Logo.wav", false);									//로고 BGM
	SOUNDMANAGER->play("Logo");

	SOUNDMANAGER->addSound("Menu", "sound/Menu.wav", true);										//메뉴창 BGM
	SOUNDMANAGER->play("Menu");


	SOUNDMANAGER->addSound("Intro", "sound/Intro.wav", true);									//인트로 BGM

	SOUNDMANAGER->addSound("guard_before", "sound/guard_before.wav", true);						//가드 만나기 전 BGM

	SOUNDMANAGER->addSound("guard_tutorial", "sound/guard_tutorial.wav", true);					//가드와 대화 및 듀토리얼 BGM

	SOUNDMANAGER->addSound("Game_idle", "sound/Game_idle.wav", true);							//기본 BGM

	//가드 만날 때 BGM은 기사 모습의 보스와 만났을 때 한번 더 사용

	SOUNDMANAGER->addSound("boss", "sound/boss.wav", true);										//기사와 대화하다 보스로 변신하는 BGM

	//SOUNDMANAGER->addSound("boss_1p", "sound/boss_1p.wav", false);								//보스로 1페이즈 BGM

	//SOUNDMANAGER->addSound("boss_angry", "sound/boss_angry.wav", true);							//보스 최대 HP[200] - [100]이 되어 2p로 넘어가기 전 보스의 분노 (대화 장면 중) BGM

	SOUNDMANAGER->addSound("boss_2p", "sound/boss_2p.wav", true);								//보스로 2페이즈 BGM

	SOUNDMANAGER->addSound("Game_Over", "sound/Game_Over.wav", true);							//보스전에서 플레이어 HP[0]이 될 경우 게임오버 BGM

	SOUNDMANAGER->addSound("boss_after", "sound/boss_after.wav", true);							//보스전 클리어시 대화장면에서 나오는 BGM (보스의 모습은 기사)

	//SOUNDMANAGER->addSound("Cradit", "sound/Cradit.wav", true);									//엔딩 크레딧 BGM (출처 꼭 남기기)

	//버튼음
	SOUNDMANAGER->addSound("Button", "sound/Button.wav", false);								//버튼
	//로고
	IMGMANAGER->AddImage("Logo", _T("Logo.png"), "PS2");
	IMGMANAGER->AddImage("T_L", _T("T_L.png"), "PS2");
	IMGMANAGER->AddImage("W_L", _T("W_L.png"), "PS2");
	IMGMANAGER->AddImage("O_L", _T("O_L.png"), "PS2");
	IMGMANAGER->AddImage("P_L", _T("P_L.png"), "PS2");
	IMGMANAGER->AddImage("L_L", _T("L_L.png"), "PS2");
	IMGMANAGER->AddImage("U_L", _T("U_L.png"), "PS2");
	IMGMANAGER->AddImage("S_L", _T("S_L.png"), "PS2");


	//메뉴
	IMGMANAGER->AddImage("Button", _T("MenuButton.png"), "PS2");			//버튼

	IMGMANAGER->AddImage("Menu", _T("Menu.png"), "PS2");					//메뉴판

	IMGMANAGER->AddImage("Back", _T("Back.png"), "PS2");					//메뉴판 백그라운드


	//메뉴 이미지
	IMGMANAGER->AddImage("gamestart", _T("gamestart.png"), "PS2");
	IMGMANAGER->AddImage("option", _T("option.png"), "PS2");
	IMGMANAGER->AddImage("quit", _T("quit.png"), "PS2");
	IMGMANAGER->AddImage("o", _T("o.png"), "PS2");
	IMGMANAGER->AddImage("n", _T("n.png"), "PS2");
	IMGMANAGER->AddImage("t", _T("t.png"), "PS2");
	IMGMANAGER->AddImage("h", _T("h.png"), "PS2");
	IMGMANAGER->AddImage("e", _T("e.png"), "PS2");
	IMGMANAGER->AddImage("p", _T("p.png"), "PS2");

	//인트로 이미지
	IMGMANAGER->AddImage("Story", _T("Story.png"), "PS2");

	//보스방 노트충돌 대
	IMGMANAGER->AddImage("Arrow", _T("Arrow.png"), "PS2");
	IMGMANAGER->AddImage("Arrow3", _T("Arrow3.png"), "PS2");

	//보스방 노트
	IMGMANAGER->AddImage("Left", _T("A_Left_A.png"), "PS2");
	IMGMANAGER->AddImage("A_Up", _T("A_Up_A.png"), "PS2");
	IMGMANAGER->AddImage("Right", _T("A_Right_A.png"), "PS2");
	IMGMANAGER->AddImage("Down", _T("A_Down_A.png"), "PS2");

	//노트바
	IMGMANAGER->AddImage("NoteBar", _T("NoteBar.png"), "PS2");
	IMGMANAGER->AddImage("Arrow2", _T("Arrow2.png"), "PS2");	//노트 가리개
	IMGMANAGER->AddImage("A_Left_A", _T("A_Left_A.png"), "PS2");	//노트 L
	IMGMANAGER->AddImage("A_Up_A", _T("A_Up_A.png"), "PS2");	//노트 U
	IMGMANAGER->AddImage("A_Right_A", _T("A_Right_A.png"), "PS2");	//노트 R
	IMGMANAGER->AddImage("A_Down_A", _T("A_Down_A.png"), "PS2");	//노트 D

	//보스 HP Bar
	IMGMANAGER->AddImage("hp", _T("healthbar.png"), "PS2");	//보스 HP
	IMGMANAGER->AddImage("hp2", _T("healthbar2.png"), "PS2");	//보스 HP 틀

	//Game Over IMG
	IMGMANAGER->AddImage("gameover", _T("gameover.png"), "PS2");

	//Cradit
	IMGMANAGER->AddImage("Cradit", _T("Cradit.png"), "PS2");


	//[[Sound]]
	SOUNDMANAGER->stop("Intro");
	SOUNDMANAGER->stop("Menu");

	SOUNDMANAGER->addSound("Logo", "sound/Logo.wav", false);				//로고
	SOUNDMANAGER->play("Logo");

	SOUNDMANAGER->addSound("Menu", "sound/Menu.wav", false);				//메뉴창



	SOUNDMANAGER->addSound("Intro", "sound/Intro.wav", true);				//인트로



	SOUNDMANAGER->addSound("guard_tutorial", "sound/guard_tutorial.wav", true);				//가드 만날 때

	//버튼음
	SOUNDMANAGER->addSound("Button", "sound/Button.wav", false);				//버튼

	// 플레이어 이미지
	IMGMANAGER->AddImage("playerIdle", _T("Char/Transparent PNG/idle/IdleAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerRunning", _T("Char/Transparent PNG/running/RunningAni.png"), 6, 1, "PS2");
	IMGMANAGER->AddImage("playerJump", _T("Char/Transparent PNG/jump/JumpAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerHit", _T("Char/Transparent PNG/got hit/frame-got-hit.png"), "PS2");
	IMGMANAGER->AddImage("playerLife", _T("heart.png"), "PS2");
	m_Arka = new Arka;
	m_Arka->init();
	m_Menu = new Menu;
	SCENEMANAGER->AddScene("Menu", m_Menu);
	m_Boss = new BossStage;
	SCENEMANAGER->AddScene("Boss", m_Boss);

	m_GameOver = new GameOver;
	SCENEMANAGER->AddScene("GameOver", m_GameOver);
	m_Menu2 = new Menu2;
	SCENEMANAGER->AddScene("Menu2", m_Menu2);

	m_Cradit = new Cradit;
	SCENEMANAGER->AddScene("Cradit", m_Cradit);

	maptool = new MapTool();
	SCENEMANAGER->AddScene("MapTool", maptool);
	m_to = new Tutorial();
	SCENEMANAGER->AddScene("Tutorial", m_to);
	m_TowerUp = new TowerUp();
	SCENEMANAGER->AddScene("TowerUp", m_TowerUp);
	SCENEMANAGER->SceneNext("Menu");

	
	////////////////////////////////////////////////////

	




	ImGui::Create(g_hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();
	return S_OK;
}

void MainGame::release()
{
	////////////////////////////////////////////////////


	////////////////////////////////////////////////////
	ImGui::Delete();
}

void MainGame::update()
{
	
	////////////////////////////////////////////////////
	SCENEMANAGER->update();
	//m_Action->update();
	//m_Menu->update();




	ImGui::Update();
}

void MainGame::render()
{
	D3DXCOLOR background = D3DXCOLOR(0.85f, 0.85f, 1.0f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)background);
	CAMMANAGER->SetBuffers();
	WRITEMANAGER->GetDc()->BeginDraw();
	//TIMEMANAGER->render();
	////////////////////////////////////////////////////

	//IMGMANAGER->GetImage("BG")->Position(400.0f+g_ptCam.x, 300.0f + g_ptCam.y);
	//IMGMANAGER->LoofRender("BG", m_a, 0.0f);
	SCENEMANAGER->render();
	//m_Action->render();
	//m_Menu->render();

	////////////////////////////////////////////////////
#ifdef _DEBUG
	ImGui::Render();
#endif
	
	WRITEMANAGER->GetDc()->EndDraw();
	SwapChain->Present(0, 0);

}

