#pragma once
#include "Character/Player.h"
#include "Character/Boss.h"
#include "Object/Note.h"
#include "Map/Cradit.h"
class BossStage : public GameNode
{
	D3DXVECTOR2	cloude;
	D3DXVECTOR2	CloudeScale;
	D3DXVECTOR4	Cloud_WIndows;
	FRECT m_Stage;
	Player* m_player;
	Boss* m_boss;
	Note * note;
	UINT NoteTime;
	NOTE_DIR notedir;
	UINT CountLeft;
	UINT CountUP;
	UINT CountDown;
	UINT CountRight;
	float DeleayTime;
	Cradit*	m_Cradit;
	bool NoteDown;
	UINT NextNote;
	float MaxTime;
	float		CloudMove = 0;
	float		JSKILL = 0;
	bool BossChange;
	bool m_FirstSound;
	bool m_isBossAttack;
	bool m_IsNote;
	bool GameClear;
	int Count = 0;
	float time;
public:
	BossStage();
	~BossStage();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void autonote(float time, int max, float MaxTime);
	void autonote2(float time, int max, float MaxTime);
	void autonote3(float time, int max, float MaxTime);
	void autonote4(float time, int max, float MaxTime);
};

