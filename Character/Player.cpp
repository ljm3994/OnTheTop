#include "stdafx.h"
#include "Player.h"

Player::Player(Map* map, D3DXVECTOR2 pos, D3DXVECTOR2 scale)
	:CharacterManager("playerIdle", pos, scale, map)
{
	m_isJump = false;
	m_isBoss = false;
	m_isFall = false;
	m_JumpPower = 0.0f;
	CamSpeed = 90.0f;
	PlayerLife = 3;
	XCamMove = true;
	YCamMove = true;
	m_IsMove = true;
	m_Rotate = { 0.0f, 0.0f, 0.0f };
}

Player::Player()
{
}

Player::~Player()
{
}

HRESULT Player::init()
{
	m_JumpTime = 132.0f;
	m_isJump = false;
	m_isBoss = false;
	m_isFall = false;
	m_JumpPower = 0.0f;
	CamSpeed = 90.0f;
	PlayerLife = 3;
	XCamMove = true;
	YCamMove = true;
	m_IsMove = true;
	m_Rotate = { 0.0f, 0.0f, 0.0f };
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	if (!m_isJump)
	{
		if (TileCheck(m_map, COLISION_DOWN) != ColisionDir::COLISION_DOWN)
		{
			if (!m_isFall)
			{
				m_Gravity.y = 100.0f;
				m_isFall = true;
			}
			if (YCamMove)
			{
				g_ptCam.y -= m_Gravity.y * g_ETime;
			}
			m_Gravity.y += 100 * g_ETime;
		}
		else
		{
			m_MoveDir = MOVE_IDLE;
			m_Gravity.y = 0.0f;
			m_isFall = false;
		}
		GravityApply();
	}
	if (m_IsMove)
	{
		if (m_MoveDir != MOVE_UP && !m_isFall)
		{
			if (KEYMANAGER->StayKeyDown(VK_LEFT) && (m_pos.x - (m_Scale.x / 2)) > m_Stage.left)
			{
				m_Rotate.y = PI;

				if (m_MoveDir != MOVE_LEFT)
				{
					m_MoveDir = MOVE_LEFT;
				}
				if (KEYMANAGER->StayKeyDown(VK_SHIFT))
				{
					m_Speed++;
					CamSpeed++;
					if (m_Speed >= 150.0f)
					{
						m_Speed = 150.0f;
						CamSpeed = 140.0f;
					}
				}
				else
				{
					CamSpeed = 90.0f;
					m_Speed = 100.0f;
				}
			}
			else if (KEYMANAGER->StayKeyDown(VK_RIGHT) && (m_pos.x + (m_Scale.x / 2)) < m_Stage.right + g_ptCam.x)
			{
				m_Rotate.y = 0.0f;

				if (m_MoveDir != MOVE_RIGHT)
				{
					m_MoveDir = MOVE_RIGHT;
				}
				if (KEYMANAGER->StayKeyDown(VK_SHIFT))
				{
					m_Speed++;
					CamSpeed++;
					if (m_Speed >= 150.0f)
					{
						m_Speed = 150.0f;
						CamSpeed = 140.0f;
					}
				}
				else
				{
					CamSpeed = 90.0f;
					m_Speed = 100.0f;
				}
			}
			else
			{
				if (m_MoveDir != MOVE_IDLE)
				{
					m_MoveDir = MOVE_IDLE;
				}
			}
		}
		if (KEYMANAGER->isKeyDown(VK_SPACE) && !m_isJump && !m_isFall)
		{
			m_isJump = true;
			m_JumpPower = m_JumpTime;
			m_Gravity.y = 0.0f;
			m_MoveDir = MOVE_UP;
		}


		if (XCamMove)
		{
			g_ptCam.x += m_Dir.x * CamSpeed * g_ETime;

			if (g_ptCam.x < 0)
			{
				g_ptCam.x = 0;
			}
		}
	}
	else
	{
		m_MoveDir = MOVE_IDLE;
	}

	if (m_isJump)
	{
		if ((TileCheck(m_map, COLISION_DOWN) == ColisionDir::COLISION_DOWN || TileCheck(m_map, COLISION_UP) == ColisionDir::COLISION_UP) && m_Gravity.y > 0.2f)
		{
			//m_Dir.x *= -1;
			m_Dir.y = 0.0f;
			m_Gravity.y = 0.0f;
			m_JumpPower = 0.0f;
			m_isJump = false;
		}
		else
		{
			m_Gravity.y += g_ETime;
			m_pos.y += m_JumpPower * g_ETime;
			if (YCamMove)
			{
				g_ptCam.y += m_JumpPower * g_ETime;
			}
			m_JumpPower -= m_Gravity.y;
		}
	}

	Move(m_MoveDir);
	ImageChange(m_MoveDir);
	if ((m_pos.x - (m_Scale.x / 2)) < m_Stage.left - 20.0f || (m_pos.x + (m_Scale.x / 2)) > (m_Stage.right + g_ptCam.x) + 20.0f)
	{
		m_MoveDir = MOVE_IDLE;
	}
	m_rect->Position(m_pos);
}

void Player::render()
{
	m_CharacterImage->Scale(m_Scale);
	m_CharacterImage->Position(m_pos);
	//m_rect->Render();

	switch (m_MoveDir)
	{
	case MOVE_IDLE:
		m_CharacterImage->PlayAnimation(PlayState::ANI_LOOP, true, 0.5f);
		break;
	case MOVE_LEFT:
		m_CharacterImage->PlayAnimation(PlayState::ANI_LOOP, true, 0.2f);
		break;
	case MOVE_RIGHT:
		m_CharacterImage->PlayAnimation(PlayState::ANI_LOOP, true, 0.2f);
		break;
	case MOVE_UP:
		m_CharacterImage->Render();
		break;
	}

}

void Player::ImageChange(MOVE_DIR MoveDir)
{
	switch (m_MoveDir)
	{
	case MOVE_IDLE:
		if (ImgKey != "playerIdle")
		{
			ImgKey = "playerIdle";
		}
		break;
	case MOVE_LEFT:
		if (ImgKey != "playerRunning")
		{
			ImgKey = "playerRunning";
		}
		break;
	case MOVE_RIGHT:
		if (ImgKey != "playerRunning")
		{
			ImgKey = "playerRunning";
		}
		break;
	case MOVE_UP:
		if (m_JumpPower > 130)
		{
			if (ImgKey != "playerJump")
			{
				ImgKey = "playerJump";
				m_CharacterImage->SetCurrentFrameX(0);
			}
		}
		else
		{
			m_CharacterImage->SetCurrentFrameX(1);
		}
		break;
	}
			
	m_CharacterImage = IMGMANAGER->GetImage(ImgKey);
	m_CharacterImage->Rotate(m_Rotate);
}

void Player::MakeBullet()
{
	PlayerBuillet* bulet = OBJECTPOOL(PlayerBuillet)->GetObObject();
	bulet->init();
	bulet->SetPos(m_pos);
	bulet->SetStage(m_Stage);
	bulet->SetAngle(90.0f);
	bulet->SetFireSpeed(0.23f);
	bulet->SetSpeed(500.0f);
	bulet->SetSize(10.0f);
	m_PlBullet.emplace_back(bulet);
}

void Player::BulletFire()
{
	m_PlBulletit = m_PlBullet.begin();
	while (m_PlBulletit != m_PlBullet.end())
	{
		(*m_PlBulletit)->update();
		if ((*m_PlBulletit)->OnDisplay())
		{
			OBJECTPOOL(PlayerBuillet)->PushObject((*m_PlBulletit));
			m_PlBulletit = m_PlBullet.erase(m_PlBulletit++);
		}
		else
		{
			m_PlBulletit++;
		}
	}
}

void Player::SetTileIndex()
{
	m_TileIndex = m_map->GetPositionTile(m_pos);
}

bool Player::EnemyColide(FRECT rc)
{
	m_PlBulletit = m_PlBullet.begin();

	while (m_PlBulletit != m_PlBullet.end())
	{
		if ((*m_PlBulletit)->CharColide(rc))
		{
			OBJECTPOOL(PlayerBuillet)->PushObject((*m_PlBulletit));
			m_PlBullet.erase(m_PlBulletit++);
			return true;
		}
		else
		{
			m_PlBulletit++;
		}
	}
	return false;
}

void Player::BulletRender()
{
	m_PlBulletit = m_PlBullet.begin();

	while (m_PlBulletit != m_PlBullet.end())
	{
		(*m_PlBulletit)->render();
		m_PlBulletit++;
	}
}
