#include "stdafx.h"
#include "PlayerBuillet.h"


PlayerBuillet::PlayerBuillet()
{
}


PlayerBuillet::~PlayerBuillet()
{
}

void PlayerBuillet::update()
{
	float Speed = GetSpeed();
	D3DXVECTOR2 pos = GetPos();
	float Angle = GetAngle();

	pos.x += cosf((Angle * TORADIAN)) * (GetBulletSpeed()) * g_ETime;
	pos.y += sinf((Angle * TORADIAN)) * (GetBulletSpeed())* g_ETime;

	SetPos(pos);
}

HRESULT PlayerBuillet::init()
{
	Setm_CurrentFramX(2);
	m_Time = 0.0f;
	return S_OK;
}

void PlayerBuillet::release()
{
}
