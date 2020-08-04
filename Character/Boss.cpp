#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}

HRESULT Boss::init()
{
	for (int i = 0; i <= 6; i++)
	{
		BossChange[i] = false;
	}
	m_PlayerPos = nullptr;
	scale.x = 450.0f;
	scale.y = 400.0f;
	position.x = 250.0f;
	position.y = 190.0f;
	m_CurrentBulletCount = 0;
	m_MaxBulletCount = 0;
	m_UpdateDelayTime = 0.0f;
	sprintf_s(m_BossImgKey, "talk");
	BossIndex = 1;
	m_BossImageUpdate = 0.0f;
	m_isFire = false;
	m_DelayReload = 0.0f;
	m_DeleyTime = 0.0f;
	BossHp.x = 0;
	BossHp.y = 0;
	MinSize = 0;
	return S_OK;
}

void Boss::release()
{
	SAFE_DELETE(m_PlayerPos);
}

void Boss::update()
{
	if (KEYMANAGER->isKeyDown(VK_F1))
	{
		MinSize = 14.0f;
	}

	if (BossChange[0] == false)	//보스와의 대화 [나중에 true일 때 로 바꾸기]
	{
		if (KEYMANAGER->isKeyDown(VK_SPACE))
		{
			BossChange[0] = true;		//렌더 끄기
			BossChange[1] = true;		//1p 실행
		}
	}

	if (BossChange[1] == true)	//보스 크기 줄어들게 함
	{
		position.x = 250.0f;
		position.y += 19.5f * g_ETime;
		scale.x -= 16.5f * g_ETime;
		scale.y -= 14.5f * g_ETime;
		MinSize += g_ETime;
	}

	if (MinSize >= 15.0f)
	{
		m_DeleyTime += g_ETime;
		BossChange[1] = false;


		if (m_DeleyTime > 2.6f)
		{
			if ((SOUNDMANAGER->isPlaySound("boss")))SOUNDMANAGER->stop("boss");
			if (!(SOUNDMANAGER->isPlaySound("boss_2p")))SOUNDMANAGER->play("boss_2p");
			scale.x = 859.4233f;
			scale.y = 649.512f;
			position.x = 248.55f;
			position.y = 396.506f;
			sprintf_s(m_BossImgKey, "idle1");

			BossChange[2] = true;
		}
	}

	if (BossChange[2] == true)
	{
		m_UpdateDelayTime += g_ETime;
		m_BossImageUpdate += g_ETime;
		m_isFire = true;
		if (m_UpdateDelayTime > 0.02f)
		{
			if (m_MaxBulletCount == 0)
			{
				BulletPartern = BossParternUpdate();
				LoadBullet(BulletPartern);
			}
			if (m_MaxBulletCount > 0)
			{
				m_DelayReload += g_ETime;
				if (m_DelayReload > 0.5f )
				{
					LoadBullet(BulletPartern);
					m_DelayReload = 0.0f;
					m_MaxBulletCount--;
				}
			}
			m_UpdateDelayTime = 0.0f;
		}
		if(m_BossImageUpdate > 0.5f)
		{
			sprintf_s(m_BossImgKey, "idle%d", BossIndex);
			BossIndex++;
			if (BossIndex > 2)
			{
				BossIndex = 0;
			}
			m_BossImageUpdate = 0.0f;
		}
		BulletUpdate();
	}
}

void Boss::render()
{
	//Boss Talk
	if (BossChange[0] == false)	//나중에 이어질때는 기사 대화가 넘어가면 true 가 되어 사용되게 함
	{
		IMGMANAGER->GetImage("B_Talk")->Scale(420.0f, 180.0f);
		IMGMANAGER->GetImage("B_Talk")->Position(250.0f, 500.0f);
		IMGMANAGER->Render("B_Talk");

		//보스 위치 D3DXVECTOR2 로 값을 만든 후 -- 되면서 구름쪽으로 이동! 위치에 도달하면 감소를 멈추게 구현할 것!
		IMGMANAGER->GetImage("talk")->Scale(WINSIZEX - 350.0f, WINSIZEY / 2.0f + 100.0f);
		IMGMANAGER->GetImage("talk")->Position(WINSIZEX / 2.0f - 150.0f, WINSIZEY / 2.0f - 110.0f);
		IMGMANAGER->Render("talk");

		IMGMANAGER->GetImage("talk")->Scale(80.0f, 80.0f);			//보스 말풍선 캐릭터
		IMGMANAGER->GetImage("talk")->Position(115.0f, 510.0f);
		IMGMANAGER->Render("talk");

		IMGMANAGER->GetImage("lonatier")->Scale(85.0f, 35.0f);			//보스 말풍선 캐릭터
		IMGMANAGER->GetImage("lonatier")->Position(115.0f, 460.0f);
		IMGMANAGER->Render("lonatier");

		RECT rc = { 170.0f,150.0f,420.0f,82.0f };
		
		
		wstring str = L"기다리느라 목 빠지는줄 알았다고!\n여기까지 올라온 실력 좀 볼까?";
		
		WRITEMANAGER->RenderText(str, rc,15,L"궁서체",D3DXCOLOR(0,0,0,1));

	}
	IMGMANAGER->GetImage(m_BossImgKey)->Scale(scale.x, scale.y);
	IMGMANAGER->GetImage(m_BossImgKey)->Position(position.x, position.y);
	IMGMANAGER->Render(m_BossImgKey);
	//보스가 가만히 있을때
	if (BossChange[2] == true)
	{
		for (int i = 0; i < m_Bullet.size(); i++)
		{
			m_Bullet[i]->render();
		}
		
	}


}

void Boss::LoadBullet(FIRE_TYPE Type)
{
	if (m_isFire)
	{
		switch (Type)
		{
			// 탄막 종류 없음
		case NORMAL_FIRE:
			break;
			// 지향성 탄막
		case AIMED_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->SetPlayerPos(m_PlayerPos);
				TempBullet->BulletSetting(position, 12, 120.0f, 0.5f, ((360.0f / 30) * i), 90.0f, Type);
				
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 골뱅이형 탄막
		case N_WAY_FIRE:
			for (int i = 0; i < 5; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(position, 10, 120.0f, 0.05f, ((360.0f / 5) * i), 0.0f, Type);
				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 회전없이 원형으로 퍼지는 탄막
		case MULTI_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(position, 12, 120.0f, 0.5f, ((180.0f / 20)* i), 4.0f, Type);

				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
			// 원형으로 회전하며 퍼져가는 탄막
		case CIRCLE_FIRE:
			for (int i = 0; i < 20; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(position, 10, 100.0f, 0.23f, ((360.0f / 20) * i), 25.0f, Type);

				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
		case FIRE_TYPE_NUM:
			for (int i = 0; i < 10; i++)
			{
				EnemyBullet * TempBullet = ObjectPool<EnemyBullet>::GetInstance()->GetObObject();
				TempBullet->init();
				TempBullet->SetStage(m_Stage);
				TempBullet->BulletSetting(position, 10, 100.0f, 0.23f, ((180.0f / 10) * i), 30.0f, Type);

				m_DelayReload = 3.0f;
				m_Bullet.emplace_back(TempBullet);
			}
			break;
		}
	}
}

void Boss::BulletUpdate()
{
	vector<EnemyBullet*>::iterator m_BulletIt = m_Bullet.begin();

	while (m_BulletIt != m_Bullet.end())
	{
		(*m_BulletIt)->update();
		if ((*m_BulletIt)->OnDisplay())
		{
			ObjectPool<EnemyBullet>::GetInstance()->PushObject((*m_BulletIt));
			m_BulletIt = m_Bullet.erase(m_BulletIt++);
		}
		else
		{
			m_BulletIt++;
		}
	}
}

void Boss::SetPlayerPos(D3DXVECTOR2* m_Pos)
{
	m_PlayerPos = m_Pos;
}

bool Boss::GetBossChange(int index)
{
	return BossChange[index];
}

void Boss::SetBossChange(int index, bool Value)
{
	BossChange[index] = Value;
}

bool Boss::BulletColide(FRECT rc)
{
	bool ReturnValue = false;
	vector<EnemyBullet*>::iterator m_BulletIt = m_Bullet.begin();
	for (m_BulletIt; m_BulletIt != m_Bullet.end();)
	{
		if ((*m_BulletIt)->CharColide(rc))
		{
			ObjectPool<EnemyBullet>::GetInstance()->PushObject((*m_BulletIt));
			m_BulletIt = m_Bullet.erase(m_BulletIt);
			ReturnValue = true;
		}
		else
		{
			m_BulletIt++;
		}
	}

	return ReturnValue;
}

FIRE_TYPE Boss::BossParternUpdate()
{
	m_MaxBulletCount = GetFromIntTo(3, 5);
	return static_cast<FIRE_TYPE>(GetFromIntTo(1, 6));
}


