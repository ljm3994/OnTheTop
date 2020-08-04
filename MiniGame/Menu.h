#pragma once
#include "GameNode.h"
#include "Map/Map.h"
#include "Map/MapTool.h"
#include "Character/Player.h"
#include "Menu2.h"

class Menu :public GameNode
{
private:

	float		LogoTime = 1000.0f/600.0f;
	int			Switch;
	/*
	[0] 게임시작 버튼
	[1] 인트로 넘기기 관련
	[2] 옵션
	[3] 보스 1페이즈 소리
	[4] 기본 메뉴창
	[5] 스토리
	*/
	bool		Change[6];
	float		MoveFrame =0;

public:
	Menu();
	~Menu();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

