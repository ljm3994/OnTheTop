#include "stdafx.h"
#include "SceneManager.h"
#include <fstream>

SceneManager::SceneManager()
{
	m_CurrentScene = nullptr;
	m_player = new Player();
	m_boss = new Boss();

}


SceneManager::~SceneManager()
{
	m_SceneListit = m_SceneList.begin();
	for (m_SceneListit; m_SceneListit != m_SceneList.end(); ++m_SceneListit)
	{
		m_SceneListit->second->release();
		SAFE_DELETE(m_SceneListit->second);
	}

	m_SceneList.clear();
}

void SceneManager::update()
{
	if (m_CurrentScene) m_CurrentScene->update();

	if (KEYMANAGER->isKeyDown('0'))
	{
		SCENEMANAGER->SceneNext("Intro");
	}
	if (KEYMANAGER->isKeyDown('1'))
	{
		SCENEMANAGER->SceneNext("Tutorial");
	}
	if (KEYMANAGER->isKeyDown('2'))
	{
		SCENEMANAGER->SceneNext("TowerUp");
	}
	if (KEYMANAGER->isKeyDown('3'))
	{
		SCENEMANAGER->SceneNext("Boss");
	}
	if (KEYMANAGER->isKeyDown('4'))
	{
		SCENEMANAGER->SceneNext("Cradit");
	}

	if (KEYMANAGER->isKeyDown('6'))
	{
		bool Tile = MAPMANAGER->GetMap()->Getm_ViewTile();
		MAPMANAGER->GetMap()->Setm_ViewTile(!Tile);
	}

	if (KEYMANAGER->isKeyDown('7'))
	{
		bool Tile = MAPMANAGER->GetMap()->Getm_ViewPass();
		MAPMANAGER->GetMap()->Setm_ViewPass(!Tile);
	}

	if (KEYMANAGER->isKeyDown('8'))
	{
		bool Tile = MAPMANAGER->GetMap()->Getm_ViewIndex();
		MAPMANAGER->GetMap()->Setm_ViewIndex(!Tile);
	}

	if (CurrentSceneStr != "Menu" || CurrentSceneStr != "Menu2")
	{
		if (KEYMANAGER->isKeyDown('O'))
		{
			ofstream in;

			in.open("save/save1.save", ios::out | ios::trunc);

			if (in.is_open())
			{
				char str[256];
				
				in << "SceenName:" << CurrentSceneStr << endl;

				if (CurrentSceneStr == "Boss")
				{
					sprintf_s(str, "Boss_Hp:%d", m_boss->GetBossHp().x);
					in << str << endl;
					sprintf_s(str, "Boss_Change:%d", m_boss->GetBossChange(2));
					in << str << endl;
					sprintf_s(str, "Boss_Position:%f,%f", m_boss->Getposition().x, m_boss->Getposition().y);
					in << str << endl;
					sprintf_s(str, "Boss_Scale:%f,%f", m_boss->Getscale().x, m_boss->Getscale().y);
					in << str << endl;
				}

				sprintf_s(str, "Player_Hp:%d", m_player->GetPlayerLife());
				in << str << endl;
				sprintf_s(str, "Player_Position:%f,%f", m_player->GetRefm_pos().x, m_player->GetRefm_pos().y);
				in << str << endl;
				sprintf_s(str, "Cam_Pos:%f,%f", g_ptCam.x, g_ptCam.y);
				in << str << endl;

				in.flush();
				in.close();
			}
		}

		if (KEYMANAGER->isKeyDown('L'))
		{
			ifstream in;

			in.open("save/save1.save", ios::in);

			if (in.is_open())
			{
				char str[256];
				char* combination;
				char* str2;
				in.getline(str, 256);

				str2 = strtok_s(str, ":", &combination);
				SceneNext(combination);
				
				if (combination == "Boss")
				{
					in.getline(str, 256);
					str2 = strtok_s(str, ":", &combination);
					m_boss->SetBossHp({static_cast<float>(atoi(combination)), 0.0f});

					in.getline(str, 256);
					str2 = strtok_s(str, ":", &combination);
					m_boss->SetBossChange(2, atoi(combination));

					in.getline(str, 256);
					str2 = strtok_s(str, ":", &combination);
					str2 = strtok_s(NULL, ",", &combination);
					m_boss->Setposition({ static_cast<float>(atof(str)), static_cast<float>(atof(combination)) });

					in.getline(str, 256);
					str2 = strtok_s(str, ":", &combination);
					str2 = strtok_s(NULL, ",", &combination);
					m_boss->Setscale({ static_cast<float>(atof(str)), static_cast<float>(atof(combination)) });
				}

				in.getline(str, 256);
				str2 = strtok_s(str, ":", &combination);
				m_player->SetPlayerLife(atoi(combination));

				in.getline(str, 256);
				str2 = strtok_s(str, ":", &combination);
				str2 = strtok_s(NULL, ",", &combination);
				D3DXVECTOR2* Temp = &m_player->GetRefm_pos();
				Temp->x = static_cast<float>(atof(str2));;
				Temp->y = static_cast<float>(atof(combination));
				m_player->SetTileIndex();
				in.getline(str, 256);
				str2 = strtok_s(str, ":", &combination);
				str2 = strtok_s(NULL, ",", &combination);
				g_ptCam.x = atof(str2);
				g_ptCam.y = atof(combination);

				in.clear();
				in.close();
			}
		}
	}
}

void SceneManager::render()
{
	if (m_CurrentScene) m_CurrentScene->render();
}

GameNode * SceneManager::AddScene(string Keystr, GameNode * scene)
{
	GameNode * Temp = findScene(Keystr);
	if (Temp) return nullptr;

	m_SceneList.insert(make_pair(Keystr, scene));

	return scene;
}

bool SceneManager::SceneNext(string Keystr)
{
	GameNode * Temp = findScene(Keystr);

	if (!Temp) return false;

	if (Temp == m_CurrentScene) return false;

	CurrentSceneStr = Keystr;
	Temp->init();
	m_CurrentScene = Temp;
	return true;
}

GameNode * SceneManager::findScene(string Keystr)
{
	m_SceneListit = m_SceneList.find(Keystr);

	if (m_SceneListit != m_SceneList.end())
	{
		return m_SceneListit->second;
	}

	return nullptr;
}
