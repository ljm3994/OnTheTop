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
	[0] ���ӽ��� ��ư
	[1] ��Ʈ�� �ѱ�� ����
	[2] �ɼ�
	[3] ���� 1������ �Ҹ�
	[4] �⺻ �޴�â
	[5] ���丮
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

