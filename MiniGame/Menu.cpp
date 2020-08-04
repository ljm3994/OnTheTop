#include "stdafx.h"
#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

HRESULT Menu::init()
{

	for (int i = 0; i < 5; i++)
	{
		Change[i] = false;
	}

	return S_OK;
}

void Menu::release()
{
}

void Menu::update()
{

	LogoTime-= g_ETime;

	if (LogoTime <= 100.0f / 600.0f && Change[1] == false)	//메인메뉴 렌더
	{
		SOUNDMANAGER->play("Menu");
		Change[4] = true;

		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{

			if (PtInRect(RectMakeCenter(189.0f, 330.0f, 60.0f, 60.0f), g_ptMouse))	//게임 시작 버튼
			{
				Change[1] = true;
				SOUNDMANAGER->stop("Menu");
				SOUNDMANAGER->play("Button");
				SOUNDMANAGER->play("Intro");
			}
			if (PtInRect(RectMakeCenter(189.0f, 241.0f, 60.0f, 60.0f), g_ptMouse))	//옵션 버튼
			{
				SCENEMANAGER->SceneNext("Menu2");
			}
			if (Change[2] == false && PtInRect(RectMakeCenter(197.0f, 151.0f, 60.0f, 60.0f), g_ptMouse))	//나가기 버튼
			{
				Change[2] = true;
				exit(0);
			}
			
		}
		
	}

	if (Change[1] == true && MoveFrame < 5120.0f)
	{
		MoveFrame += 100.0f*g_ETime;
		Change[0] = false;
	}
	if (MoveFrame > 5120.0f && KEYMANAGER->isKeyDown(VK_SPACE))
	{
		
		SCENEMANAGER->SceneNext("Tutorial");
		SOUNDMANAGER->stop("Intro");
	}
	if (KEYMANAGER->isKeyDown(VK_F1))
	{
		SCENEMANAGER->SceneNext("MapTool");
		SOUNDMANAGER->stop("Intro");
	}

	if ((SOUNDMANAGER->isPlaySound("Game_Over")))SOUNDMANAGER->stop("Game_Over");
}

void Menu::render()
{

	if (LogoTime <= 1000.0f / 600.0f)
	{
		IMGMANAGER->GetImage("Logo")->Scale(230.0f, 230.0f);
		IMGMANAGER->GetImage("Logo")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f + 60.0f);
		IMGMANAGER->Render("Logo");
	}
	if (LogoTime <= 950.0f / 600.0f)
	{
		IMGMANAGER->GetImage("T_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("T_L")->Position(WINSIZEX / 2.0f - 140.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("T_L");
	}
	if (LogoTime <= 900.0f / 600.0f)
	{
		IMGMANAGER->GetImage("W_L")->Scale(55.0f, 50.0f);
		IMGMANAGER->GetImage("W_L")->Position(WINSIZEX / 2.0f - 87.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("W_L");
	}
	if (LogoTime <= 880.0f / 600.0f)
	{
		IMGMANAGER->GetImage("O_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("O_L")->Position(WINSIZEX / 2.0f - 40.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("O_L");
	}
	if (LogoTime <= 850.0f / 600.0f)
	{
		IMGMANAGER->GetImage("P_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("P_L")->Position(WINSIZEX / 2.0f + 20.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("P_L");
	}
	if (LogoTime <= 740.0f / 600.0f)
	{
		IMGMANAGER->GetImage("L_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("L_L")->Position(WINSIZEX / 2.0f + 65.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("L_L");
	}
	if (LogoTime <= 700.0f / 600.0f)
	{
		IMGMANAGER->GetImage("U_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("U_L")->Position(WINSIZEX / 2.0f + 110.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("U_L");
	}
	if (LogoTime <= 620.0f / 600.0f)
	{
		IMGMANAGER->GetImage("S_L")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("S_L")->Position(WINSIZEX / 2.0f + 155.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("S_L");
	}

	if (Change[4] == true)
	{
		//메인메뉴


		//메뉴 백그라운드
		IMGMANAGER->GetImage("Back")->Scale(1200.0f, 1200.0f);
		IMGMANAGER->GetImage("Back")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Back");

		//메뉴판
		IMGMANAGER->GetImage("Menu")->Scale(800.0f - 100.0f, 550.0f);
		IMGMANAGER->GetImage("Menu")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Menu");

		//게임 이름
		IMGMANAGER->GetImage("o")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("o")->Position(200.0f - 15.0f, 435.0f);
		IMGMANAGER->Render("o");

		IMGMANAGER->GetImage("n")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("n")->Position(255.0f - 15.0f, 435.0f);
		IMGMANAGER->Render("n");

		IMGMANAGER->GetImage("t")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("t")->Position(220.0f + (55.0f * 2) - 15.0f, 435.0f);
		IMGMANAGER->Render("t");

		IMGMANAGER->GetImage("h")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("h")->Position(220.0f + (55.0f * 3) - 15.0f, 435.0f);
		IMGMANAGER->Render("h");

		IMGMANAGER->GetImage("e")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("e")->Position(220.0f + (55.0f * 4) - 15.0f, 435.0f);
		IMGMANAGER->Render("e");

		IMGMANAGER->GetImage("t")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("t")->Position(220.0f + 75.0f + (55.0f * 4) - 15.0f, 435.0f);
		IMGMANAGER->Render("t");

		IMGMANAGER->GetImage("o")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("o")->Position(220.0f + 75.0f + (55.0f * 5) - 15.0f, 435.0f);
		IMGMANAGER->Render("o");

		IMGMANAGER->GetImage("p")->Scale(50.0f, 50.0f);
		IMGMANAGER->GetImage("p")->Position(220.0f + 75.0f + (55.0f * 6) - 15.0f, 435.0f);
		IMGMANAGER->Render("p");

		//게임 시작 버튼
		IMGMANAGER->GetImage("Button")->Scale(60.0f, 60.0f);
		IMGMANAGER->GetImage("Button")->Position(200.0f, 240.0f);
		IMGMANAGER->Render("Button");

		//옵션 버튼
		IMGMANAGER->GetImage("Button")->Scale(60.0f, 60.0f);
		IMGMANAGER->GetImage("Button")->Position(200.0f, 330.0f);
		IMGMANAGER->Render("Button");

		//나가기 버튼
		IMGMANAGER->GetImage("Button")->Scale(60.0f, 60.0f);
		IMGMANAGER->GetImage("Button")->Position(200.0f, 330.0f - 180.0f);
		IMGMANAGER->Render("Button");

		//Game Start
		IMGMANAGER->GetImage("gamestart")->Scale(250.0f, 50.0f);
		IMGMANAGER->GetImage("gamestart")->Position(380.0f, 330.0f);
		IMGMANAGER->Render("gamestart");

		//Option
		IMGMANAGER->GetImage("option")->Scale(115.0f, 50.0f);
		IMGMANAGER->GetImage("option")->Position(310.0f, 245.0f);
		IMGMANAGER->Render("option");

		//Quit
		IMGMANAGER->GetImage("quit")->Scale(75.0f, 50.0f);
		IMGMANAGER->GetImage("quit")->Position(290.0f, 150.0f);
		IMGMANAGER->Render("quit");
	}

	if (Change[1] == true)
	{
		D3DXCOLOR background = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1);
		DeviceContext->ClearRenderTargetView(RTV, (float *)background);
		IMGMANAGER->GetImage("Story")->Scale(WINSIZEX, 5272.0f);
		IMGMANAGER->GetImage("Story")->Position(WINSIZEX / 2.0f, -2500.0f+MoveFrame);
		IMGMANAGER->Render("Story");
	}

	
	
}
