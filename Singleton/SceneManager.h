#pragma once
#include "Character/Player.h"
#include "Character/Boss.h"
#include "GameNode.h"
class SceneManager : public SingletonBase<SceneManager>
{
	map<string, GameNode*> m_SceneList;	
	map<string, GameNode*>::iterator m_SceneListit;
	string CurrentSceneStr;
	GameNode* m_CurrentScene;	
	Player * m_player;
	Boss * m_boss;

public:
	SceneManager();
	~SceneManager();
	void update();
	void render();
	GameNode * AddScene(string Keystr, GameNode* scene);
	void SceneInit(string Keystr);
	bool SceneNext(string Keystr);
	Player& Getm_player() { return *m_player; };
	Boss& Getm_boss() { return *m_boss; };
	GameNode * findScene(string Keystr);
};

