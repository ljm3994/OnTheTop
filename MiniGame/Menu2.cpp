#include "stdafx.h"
#include "Menu2.h"


Menu2::Menu2()
{
}


Menu2::~Menu2()
{
}

HRESULT Menu2::init()
{
	return S_OK;
}

void Menu2::release()
{
}

void Menu2::update()
{

	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		if (option == false && PtInRect(RectMakeCenter(399.0f, 152.0f, 75.0f, 50.0f), g_ptMouse))
		{
			option = true;
		}
	}
	if(option == true)	//옵션창
	{ 
	SCENEMANAGER->SceneNext("Menu");
	option = false;		//메뉴창으로 다시 돌아감
	}



	
	//BGM OFF 때 사용
	//SOUNDMANAGER->stop("Logo");
	//SOUNDMANAGER->stop("Menu");
	//SOUNDMANAGER->stop("Intro");
	//SOUNDMANAGER->stop("guard_before");
	//SOUNDMANAGER->stop("guard_tutorial");
	//SOUNDMANAGER->stop("Game_idle");
	//SOUNDMANAGER->stop("boss");
	//SOUNDMANAGER->stop("boss_1p");
	//SOUNDMANAGER->stop("boss_angry");
	//SOUNDMANAGER->stop("boss_2p");
	//SOUNDMANAGER->stop("Game_Over");
	//SOUNDMANAGER->stop("boss_after");
	//SOUNDMANAGER->stop("Cradit");
	//SOUNDMANAGER->stop("Button");




}




void Menu2::render()
{
	//메뉴 백그라운드
	IMGMANAGER->GetImage("Back")->Scale(1200.0f, 1200.0f);
	IMGMANAGER->GetImage("Back")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
	IMGMANAGER->Render("Back");

	if (option == false) //옵션 창으로 들어왔을 때
	{
	
		IMGMANAGER->GetImage("Menu")->Scale(800.0f - 100.0f, 550.0f);
		IMGMANAGER->GetImage("Menu")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		IMGMANAGER->Render("Menu");

		//Option 이미지
		IMGMANAGER->GetImage("option")->Scale(230.0f, 100.0f);
		IMGMANAGER->GetImage("option")->Position(WINSIZEX / 2.0f, WINSIZEY - 150.0f);
		IMGMANAGER->Render("option");

		//Quit 이미지
		IMGMANAGER->GetImage("quit")->Scale(75.0f, 50.0f);
		IMGMANAGER->GetImage("quit")->Position(WINSIZEX / 2.0f, 150.0f);
		IMGMANAGER->Render("quit");
	
		//Full Screen
		IMGMANAGER->GetImage("f")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("f")->Position(186.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("f");

		IMGMANAGER->GetImage("u")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("u")->Position(216.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("u");

		IMGMANAGER->GetImage("l")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("l")->Position(246.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("l");

		IMGMANAGER->GetImage("l")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("l")->Position(276.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("l");

		IMGMANAGER->GetImage("s")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("s")->Position(326.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("s");

		IMGMANAGER->GetImage("c")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("c")->Position(356.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("c");

		IMGMANAGER->GetImage("r")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("r")->Position(386.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("r");

		IMGMANAGER->GetImage("e")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("e")->Position(416.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("e");

		IMGMANAGER->GetImage("e")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("e")->Position(446.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("e");

		IMGMANAGER->GetImage("n")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("n")->Position(476.0f + 80.0f, 351.0f - 10.0f);
		IMGMANAGER->Render("n");

		//BGM
		IMGMANAGER->GetImage("b")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("b")->Position(186.0f + 80.0f, 351.0f - 120.0f);
		IMGMANAGER->Render("b");

		IMGMANAGER->GetImage("g")->Scale(30.0f, 40.0f);
		IMGMANAGER->GetImage("g")->Position(216.0f + 80.0f, 351.0f - 120.0f);
		IMGMANAGER->Render("g");

		IMGMANAGER->GetImage("m")->Scale(40.0f, 40.0f);
		IMGMANAGER->GetImage("m")->Position(246.0f + 90.0f, 351.0f - 120.0f);
		IMGMANAGER->Render("m");

		//BGM Button
		IMGMANAGER->GetImage("Button")->Scale(60.0f, 60.0f);
		IMGMANAGER->GetImage("Button")->Position(200.0f, 240.0f-12.0f);
		IMGMANAGER->Render("Button");

		//Full Screen Button
		IMGMANAGER->GetImage("Button")->Scale(60.0f, 60.0f);
		IMGMANAGER->GetImage("Button")->Position(200.0f, 330.0f+7.0f);
		IMGMANAGER->Render("Button");

	}

	
}
