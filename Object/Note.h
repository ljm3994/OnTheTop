#pragma once
#include "GameNode.h"

enum NOTE_DIR
{
	NOTE_LEFT,
	NOTE_RIGHT,
	NOTE_DOWN,
	NOTE_UP
};
struct NoteStr
{
	FRECT Note;
	UINT m_Index;
	UINT m_Time;
	float m_pos;
	bool m_Fire;
};
class Note : public GameNode
{
private:
	vector< NoteStr*>	Note_Left;
	vector< NoteStr*>	Note_Up;
	vector< NoteStr*>	Note_Right;
	vector< NoteStr*>	Note_Down;
	FRECT	Note_Bar;

	D3DXVECTOR2	Left;
	D3DXVECTOR2	Up;
	D3DXVECTOR2	Right;
	D3DXVECTOR2	Down;
	D3DXVECTOR2	Bar;

	D3DXVECTOR2	SizeLR;
	D3DXVECTOR2	SizeU;
	D3DXVECTOR2	SizeD;
	D3DXVECTOR2	SizeBar;
	
	vector< NoteStr*>::iterator LeftIndex;
	vector< NoteStr*>::iterator UpIndex;
	vector< NoteStr*>::iterator RightIndex;
	vector< NoteStr*>::iterator DownIndex;

	float BossHp = 100.0f;

	bool Note_Crush[4];

public:
	Note();
	~Note();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void NoteDown(NOTE_DIR Dir);
	void NotePosDown();
};

