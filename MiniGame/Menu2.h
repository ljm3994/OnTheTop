#pragma once
#include "GameNode.h"
#include "Menu.h"
class Menu2 :public GameNode
{
private:
	bool option = false;
	bool fullscreen = false;
	bool bgm = false;
public:
	Menu2();
	~Menu2();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

