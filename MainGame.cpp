#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//�̱��� ����
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
	//�����찡 ���۵Ǽ� ���ݱ��� �帥 �ð��� 1/1000�� ������
	//DWORD���� �����ϴ� �Լ���
	srand(GetTickCount());
	////////////////////////////////////////////////////


	//�������� ���� ������uv���� ����ϹǷ� �߰��ҋ� ������ ���� �־��ֱ�
	//IMGMANAGER->AddImage("BG", _T("��� ȭ��.bmp"), 1, 1, "PS2");


	//SOUNDMANAGER->addSound("BGM", "sound/bgm.wav", true);
	//SOUNDMANAGER->play("BGM");

	// �÷��̾� �̹���
	IMGMANAGER->AddImage("playerIdle", _T("Char/Player/idle/IdleAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerRunning", _T("Char/Player/running/RunningAni.png"), 6, 1, "PS2");
	IMGMANAGER->AddImage("playerJump", _T("Char/Player/jump/JumpAni.png"), 2, 1, "PS2");
	IMGMANAGER->AddImage("playerHit", _T("Char/Player/got hit/frame-got-hit.png"), "PS2");

	// ���� NPC �̹���
	IMGMANAGER->AddImage("GuardNPC", _T("Char/NPC/Tutorial Night.png"), "PS2");
	// Ÿ�� �� �̹���
	IMGMANAGER->AddImage("towerA", _T("towerA.png"), "PS2");
	IMGMANAGER->AddImage("FortressMap", _T("MapFortressTile.png"), 3, 6, "PS");
	IMGMANAGER->AddImage("FortressMap2", _T("TreeForesst.png"), 3, 3, "PS");
	IMGMANAGER->AddImage("TopDoor", _T("Map18-horz.png"), 4, 4, "PS");
	IMGMANAGER->AddImage("Top", _T("Map14-horz.png"), 10, 2, "PS");
	IMGMANAGER->AddImage("Map", _T("Map.png"), 18, 4, "PS");

	//�ΰ�
	IMGMANAGER->AddImage("Logo", _T("Logo.png"), "PS2");
	IMGMANAGER->AddImage("T_L", _T("T_L.png"), "PS2");
	IMGMANAGER->AddImage("W_L", _T("W_L.png"), "PS2");
	IMGMANAGER->AddImage("O_L", _T("O_L.png"), "PS2");
	IMGMANAGER->AddImage("P_L", _T("P_L.png"), "PS2");
	IMGMANAGER->AddImage("L_L", _T("L_L.png"), "PS2");
	IMGMANAGER->AddImage("U_L", _T("U_L.png"), "PS2");
	IMGMANAGER->AddImage("S_L", _T("S_L.png"), "PS2");


	//�޴�
	IMGMANAGER->AddImage("Button", _T("MenuButton.png"), "PS2");			//��ư

	IMGMANAGER->AddImage("Menu", _T("Menu.png"), "PS2");					//�޴���

	IMGMANAGER->AddImage("Back", _T("Back.png"), "PS2");					//�޴��� ��׶���


	//�޴� �̹���
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
	// ���丮�� ���
	IMGMANAGER->AddImage("Tutorial", _T("Background Clouds.png"), 1, 1, "PS2");

	//��Ʈ�� �̹���
	IMGMANAGER->AddImage("Story", _T("Story.png"), "PS2");

	//���� �̹���
	IMGMANAGER->AddImage("talk", _T("Boss/talk.png"), "PS2");									//���� ��ȭ �Ҷ�

	IMGMANAGER->AddImage("idle0", _T("Boss/idle0.png"), "PS2");									//���� ������ ���� ��(��)
	IMGMANAGER->AddImage("idle1", _T("Boss/idle1.png"), "PS2");									//���� ������ ���� ��(��)
	IMGMANAGER->AddImage("idle2", _T("Boss/idle2.png"), "PS2");									//���� ������ ���� ��(��)

	// �Ѿ� �̹���
	IMGMANAGER->AddImage("Bullet", _T("Boss/Bullet.png"), 4, 1, "PS2");

	//���� ��
	IMGMANAGER->AddImage("BossBG_1", _T("Boss/BossBG_1.png"), "PS2");							//�� ���
	IMGMANAGER->AddImage("BossBG_2", _T("Boss/BossBG_2.png"), 1, 1, "PS2");							//���� ���

	//��ȭâ
	IMGMANAGER->AddImage("B_Talk", _T("UI/ButtonExtraWide_Black.png"), "PS2");					//���� ��ȭâ
	IMGMANAGER->AddImage("C_Talk", _T("UI/ButtonExtraWide_Beighe.png"), "PS2");					//ĳ���͵� ��ȭâ
	IMGMANAGER->AddImage("lonatier", _T("lonatier.png"), "PS2");								//�γ�Ƽ�� �̸�




	//Sound ������� ����

	SOUNDMANAGER->addSound("Logo", "sound/Logo.wav", false);									//�ΰ� BGM
	SOUNDMANAGER->play("Logo");

	SOUNDMANAGER->addSound("Menu", "sound/Menu.wav", true);										//�޴�â BGM
	SOUNDMANAGER->play("Menu");


	SOUNDMANAGER->addSound("Intro", "sound/Intro.wav", true);									//��Ʈ�� BGM

	SOUNDMANAGER->addSound("guard_before", "sound/guard_before.wav", true);						//���� ������ �� BGM

	SOUNDMANAGER->addSound("guard_tutorial", "sound/guard_tutorial.wav", true);					//����� ��ȭ �� ���丮�� BGM

	SOUNDMANAGER->addSound("Game_idle", "sound/Game_idle.wav", true);							//�⺻ BGM

	//���� ���� �� BGM�� ��� ����� ������ ������ �� �ѹ� �� ���

	SOUNDMANAGER->addSound("boss", "sound/boss.wav", true);										//���� ��ȭ�ϴ� ������ �����ϴ� BGM

	//SOUNDMANAGER->addSound("boss_1p", "sound/boss_1p.wav", false);								//������ 1������ BGM

	//SOUNDMANAGER->addSound("boss_angry", "sound/boss_angry.wav", true);							//���� �ִ� HP[200] - [100]�� �Ǿ� 2p�� �Ѿ�� �� ������ �г� (��ȭ ��� ��) BGM

	SOUNDMANAGER->addSound("boss_2p", "sound/boss_2p.wav", true);								//������ 2������ BGM

	SOUNDMANAGER->addSound("Game_Over", "sound/Game_Over.wav", true);							//���������� �÷��̾� HP[0]�� �� ��� ���ӿ��� BGM

	SOUNDMANAGER->addSound("boss_after", "sound/boss_after.wav", true);							//������ Ŭ����� ��ȭ��鿡�� ������ BGM (������ ����� ���)

	//SOUNDMANAGER->addSound("Cradit", "sound/Cradit.wav", true);									//���� ũ���� BGM (��ó �� �����)

	//��ư��
	SOUNDMANAGER->addSound("Button", "sound/Button.wav", false);								//��ư
	//�ΰ�
	IMGMANAGER->AddImage("Logo", _T("Logo.png"), "PS2");
	IMGMANAGER->AddImage("T_L", _T("T_L.png"), "PS2");
	IMGMANAGER->AddImage("W_L", _T("W_L.png"), "PS2");
	IMGMANAGER->AddImage("O_L", _T("O_L.png"), "PS2");
	IMGMANAGER->AddImage("P_L", _T("P_L.png"), "PS2");
	IMGMANAGER->AddImage("L_L", _T("L_L.png"), "PS2");
	IMGMANAGER->AddImage("U_L", _T("U_L.png"), "PS2");
	IMGMANAGER->AddImage("S_L", _T("S_L.png"), "PS2");


	//�޴�
	IMGMANAGER->AddImage("Button", _T("MenuButton.png"), "PS2");			//��ư

	IMGMANAGER->AddImage("Menu", _T("Menu.png"), "PS2");					//�޴���

	IMGMANAGER->AddImage("Back", _T("Back.png"), "PS2");					//�޴��� ��׶���


	//�޴� �̹���
	IMGMANAGER->AddImage("gamestart", _T("gamestart.png"), "PS2");
	IMGMANAGER->AddImage("option", _T("option.png"), "PS2");
	IMGMANAGER->AddImage("quit", _T("quit.png"), "PS2");
	IMGMANAGER->AddImage("o", _T("o.png"), "PS2");
	IMGMANAGER->AddImage("n", _T("n.png"), "PS2");
	IMGMANAGER->AddImage("t", _T("t.png"), "PS2");
	IMGMANAGER->AddImage("h", _T("h.png"), "PS2");
	IMGMANAGER->AddImage("e", _T("e.png"), "PS2");
	IMGMANAGER->AddImage("p", _T("p.png"), "PS2");

	//��Ʈ�� �̹���
	IMGMANAGER->AddImage("Story", _T("Story.png"), "PS2");

	//������ ��Ʈ�浹 ��
	IMGMANAGER->AddImage("Arrow", _T("Arrow.png"), "PS2");
	IMGMANAGER->AddImage("Arrow3", _T("Arrow3.png"), "PS2");

	//������ ��Ʈ
	IMGMANAGER->AddImage("Left", _T("A_Left_A.png"), "PS2");
	IMGMANAGER->AddImage("A_Up", _T("A_Up_A.png"), "PS2");
	IMGMANAGER->AddImage("Right", _T("A_Right_A.png"), "PS2");
	IMGMANAGER->AddImage("Down", _T("A_Down_A.png"), "PS2");

	//��Ʈ��
	IMGMANAGER->AddImage("NoteBar", _T("NoteBar.png"), "PS2");
	IMGMANAGER->AddImage("Arrow2", _T("Arrow2.png"), "PS2");	//��Ʈ ������
	IMGMANAGER->AddImage("A_Left_A", _T("A_Left_A.png"), "PS2");	//��Ʈ L
	IMGMANAGER->AddImage("A_Up_A", _T("A_Up_A.png"), "PS2");	//��Ʈ U
	IMGMANAGER->AddImage("A_Right_A", _T("A_Right_A.png"), "PS2");	//��Ʈ R
	IMGMANAGER->AddImage("A_Down_A", _T("A_Down_A.png"), "PS2");	//��Ʈ D

	//���� HP Bar
	IMGMANAGER->AddImage("hp", _T("healthbar.png"), "PS2");	//���� HP
	IMGMANAGER->AddImage("hp2", _T("healthbar2.png"), "PS2");	//���� HP Ʋ

	//Game Over IMG
	IMGMANAGER->AddImage("gameover", _T("gameover.png"), "PS2");

	//Cradit
	IMGMANAGER->AddImage("Cradit", _T("Cradit.png"), "PS2");


	//[[Sound]]
	SOUNDMANAGER->stop("Intro");
	SOUNDMANAGER->stop("Menu");

	SOUNDMANAGER->addSound("Logo", "sound/Logo.wav", false);				//�ΰ�
	SOUNDMANAGER->play("Logo");

	SOUNDMANAGER->addSound("Menu", "sound/Menu.wav", false);				//�޴�â



	SOUNDMANAGER->addSound("Intro", "sound/Intro.wav", true);				//��Ʈ��



	SOUNDMANAGER->addSound("guard_tutorial", "sound/guard_tutorial.wav", true);				//���� ���� ��

	//��ư��
	SOUNDMANAGER->addSound("Button", "sound/Button.wav", false);				//��ư

	// �÷��̾� �̹���
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

