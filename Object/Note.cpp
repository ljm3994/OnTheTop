#include "stdafx.h"
#include "Note.h"


Note::Note()
{
}


Note::~Note()
{
}

HRESULT Note::init()
{
	
	//사이즈
	SizeLR.x = 75.0f;
	SizeLR.y = 91.0f;
	SizeU.x = 75.0f;
	SizeU.y = 98.0f;
	SizeD.x = 77.0f;
	SizeD.y = 98.0f;
	SizeBar.x = 320.0f;
	SizeBar.y = 100.0f;
	
	//좌표
	Left.x = 518.0f;
	Left.y = 550.0f;
	Up.x = 598.0f;
	Up.y = 550.0f;
	Right.x = 678.0f;
	Right.y = 550.0f;
	Down.x = 757.0f;
	Down.y = 550.0f;
	Bar.x = 638.0f;
	Bar.y = 550.0f;

	RectMakeCenter(Left.x, Left.y, SizeLR.x, SizeLR.y);
	RectMakeCenter(Up.x, Up.y, SizeU.x, SizeU.y);
	RectMakeCenter(Right.x, Right.y, SizeLR.x, SizeLR.y);
	RectMakeCenter(Down.x, Down.y, SizeD.x, SizeD.y);
	RectMakeCenter(Bar.x, Bar.y, SizeBar.x, SizeBar.y);

	for (int i = 0; i < 114; i++)
	{
		NoteStr *Temp = OBJECTPOOL(NoteStr)->GetObObject();
		Temp->Note = RectMakeCenter(Left.x, Left.y, SizeLR.x, SizeLR.y);
		Temp->m_pos = 0;
		Temp->m_Index = i;
		Temp->m_Fire = false;
		Note_Left.emplace_back(Temp);
	}

	for (int i = 0; i < 49; i++)
	{
		NoteStr *Temp = OBJECTPOOL(NoteStr)->GetObObject();
		Temp->Note = RectMakeCenter(Up.x, Up.y, SizeU.x, SizeU.y);
		Temp->m_pos = 0;
		Temp->m_Index = i;
		Temp->m_Fire = false;
		Note_Up.emplace_back(Temp);
	}
	for (int i = 0; i < 79; i++)
	{
		NoteStr *Temp = OBJECTPOOL(NoteStr)->GetObObject();
		Temp->Note = RectMakeCenter(Right.x, Right.y, SizeLR.x, SizeLR.y);
		Temp->m_pos = 0;
		Temp->m_Index = i;
		Temp->m_Fire = false;
		Note_Right.emplace_back(Temp);
	}
	for (int i = 0; i < 28; i++)
	{
		NoteStr *Temp = OBJECTPOOL(NoteStr)->GetObObject();
		Temp->Note = RectMakeCenter(Down.x, Down.y, SizeD.x, SizeD.y);
		Temp->m_Index = i;
		Temp->m_pos = 0;
		Temp->m_Fire = false;
		Note_Down.emplace_back(Temp);
	}

	LeftIndex = Note_Left.begin();
	RightIndex = Note_Right.begin();
	DownIndex = Note_Down.begin();
	UpIndex = Note_Up.begin();
	return S_OK;
}

void Note::release()
{
}

void Note::update()
{

	
	/*if (KEYMANAGER->isKeyDown(VK_LEFT) && IntersectRect(Note_Bar, Note_Left[i]))
	{
		BossHp -= g_ETime;
	}
	

	
	if (KEYMANAGER->isKeyDown(VK_UP) && IntersectRect(Note_Bar, Note_Up[i]))
	{
		BossHp -= g_ETime;
	}

	
	if (KEYMANAGER->isKeyDown(VK_RIGHT) && IntersectRect(Note_Bar, Note_Right[i]))
	{
		BossHp -= g_ETime;
	}
	

	if (KEYMANAGER->isKeyDown(VK_DOWN) && IntersectRect(Note_Bar, Note_Down[i]))
	{
		BossHp -= g_ETime;
	}*/

}

void Note::render()
{
	//노트
	IMGMANAGER->GetImage("A_Left_A")->Scale(SizeLR.x, SizeLR.y);
	IMGMANAGER->GetImage("A_Left_A")->Position(Left.x, Left.y);
	IMGMANAGER->Render("A_Left_A");

	IMGMANAGER->GetImage("A_Up_A")->Scale(SizeU.x, SizeU.y);
	IMGMANAGER->GetImage("A_Up_A")->Position(Up.x, Up.y);
	IMGMANAGER->Render("A_Up_A");

	IMGMANAGER->GetImage("A_Right_A")->Scale(SizeLR.x, SizeLR.y);
	IMGMANAGER->GetImage("A_Right_A")->Position(Right.x, Right.y);
	IMGMANAGER->Render("A_Right_A");

	IMGMANAGER->GetImage("A_Down_A")->Scale(SizeD.x, SizeD.y);
	IMGMANAGER->GetImage("A_Down_A")->Position(Down.x, Down.y);
	IMGMANAGER->Render("A_Down_A");

	//노트 받이
	IMGMANAGER->GetImage("Arrow2")->Scale(SizeBar.x, SizeBar.y);
	IMGMANAGER->GetImage("Arrow2")->Position(Bar.x, Bar.y);
	IMGMANAGER->Render("Arrow2");

	//Hp 창과 알파 창

	for (int i = 0; i < Note_Left.size(); i++)
	{
		if (Note_Left[i]->m_Fire)
		{
			IMGMANAGER->GetImage("A_Left_A")->Scale(SizeLR.x, SizeLR.y);
			IMGMANAGER->GetImage("A_Left_A")->Position(Note_Left[i]->Note.left + (SizeLR.x / 2), Note_Left[i]->Note.bottom + (SizeLR.y / 2));
			IMGMANAGER->Render("A_Left_A");
			//IMGMANAGER->Getrect()->Scale(SizeLR.x, SizeLR.y);
			//IMGMANAGER->Getrect()->Position(Note_Left[i]->Note.left + (SizeLR.x / 2), Note_Left[i]->Note.bottom + (SizeLR.y / 2));
			//IMGMANAGER->RectRender();
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < Note_Up.size(); i++)
	{
		if (Note_Up[i]->m_Fire)
		{
			IMGMANAGER->GetImage("A_Up_A")->Scale(SizeU.x, SizeU.y);
			IMGMANAGER->GetImage("A_Up_A")->Position(Note_Up[i]->Note.left + (SizeU.x / 2), Note_Up[i]->Note.bottom + (SizeU.y / 2));
			IMGMANAGER->Render("A_Up_A");
			//IMGMANAGER->Getrect()->Color({ 0.0f, 1.0f, 0.0f, 1.0f });
			//IMGMANAGER->Getrect()->Scale(SizeU.x, SizeU.y);
			//IMGMANAGER->Getrect()->Position(Note_Up[i]->Note.left + (SizeU.x / 2), Note_Up[i]->Note.bottom + (SizeU.y / 2));
			//IMGMANAGER->RectRender();
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < Note_Right.size(); i++)
	{
		if (Note_Right[i]->m_Fire)
		{
			IMGMANAGER->GetImage("A_Right_A")->Scale(SizeLR.x, SizeLR.y);
			IMGMANAGER->GetImage("A_Right_A")->Position(Note_Right[i]->Note.left + (SizeLR.x / 2), Note_Right[i]->Note.bottom + (SizeLR.y / 2));
			IMGMANAGER->Render("A_Right_A");
			//IMGMANAGER->Getrect()->Color({ 1.0f, 0.0f, 0.0f, 1.0f });
			//IMGMANAGER->Getrect()->Scale(SizeLR.x, SizeLR.y);
			//IMGMANAGER->Getrect()->Position(Note_Right[i]->Note.left + (SizeLR.x / 2), Note_Right[i]->Note.bottom + (SizeLR.y / 2));
			//IMGMANAGER->RectRender();
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < Note_Down.size(); i++)
	{
		if (Note_Down[i]->m_Fire)
		{
			IMGMANAGER->GetImage("A_Down_A")->Scale(SizeD.x, SizeD.y);
			IMGMANAGER->GetImage("A_Down_A")->Position(Note_Down[i]->Note.left + (SizeD.x / 2), Note_Down[i]->Note.bottom + (SizeD.y / 2));
			IMGMANAGER->Render("A_Down_A");
			//IMGMANAGER->Getrect()->Color({ 1.0f, 0.0f, 1.0f, 1.0f });
			//IMGMANAGER->Getrect()->Scale(SizeD.x, SizeD.y);
			//IMGMANAGER->Getrect()->Position(Note_Down[i]->Note.left + (SizeD.x / 2), Note_Down[i]->Note.bottom + (SizeD.y / 2));
			//IMGMANAGER->RectRender();
		}
		else
		{
			break;
		}
	}
}

void Note::NoteDown(NOTE_DIR Dir)
{
	UINT msPlay = SOUNDMANAGER->GetPosition("boss_2p");

	switch (Dir)
	{
	case NOTE_LEFT:
		if (LeftIndex != Note_Left.end())
		{
			(*LeftIndex)->m_Fire = true;
			(*LeftIndex)->m_pos = 210.0f;
			LeftIndex++;
		}
		break;
	case NOTE_UP:
		if (UpIndex != Note_Up.end())
		{
			(*UpIndex)->m_Fire = true;
			(*UpIndex)->m_pos = 210.0f;
			UpIndex++;
		}
		break;
	case NOTE_RIGHT:
		if (RightIndex != Note_Right.end())
		{
			(*RightIndex)->m_Fire = true;
			(*RightIndex)->m_pos = 210.0f;
			RightIndex++;
		}
		break;
	case NOTE_DOWN:
		if (DownIndex != Note_Down.end())
		{
			(*DownIndex)->m_Fire = true;
			(*DownIndex)->m_pos = 210.0f;
			DownIndex++;
		}
		break;
	}

}

void Note::NotePosDown()
{
	for (int i = 0; i < Note_Left.size(); i++)
	{
		if (Note_Left[i]->m_Fire)
		{
			Note_Left[i]->Note.bottom -= Note_Left[i]->m_pos * g_ETime;
			Note_Left[i]->Note.top -= Note_Left[i]->m_pos * g_ETime;
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < Note_Up.size(); i++)
	{
		if (Note_Up[i]->m_Fire)
		{
			Note_Up[i]->Note.bottom -= Note_Up[i]->m_pos * g_ETime;
			Note_Up[i]->Note.top -= Note_Up[i]->m_pos * g_ETime;
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < Note_Right.size(); i++)
	{
		if (Note_Right[i]->m_Fire)
		{
			Note_Right[i]->Note.bottom -= Note_Right[i]->m_pos * g_ETime;
			Note_Right[i]->Note.top -= Note_Right[i]->m_pos * g_ETime;
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < Note_Down.size(); i++)
	{
		if (Note_Down[i]->m_Fire)
		{
			Note_Down[i]->Note.bottom -= Note_Down[i]->m_pos * g_ETime;
			Note_Down[i]->Note.top -= Note_Down[i]->m_pos * g_ETime;
		}
		else
		{
			break;
		}
	}
}
