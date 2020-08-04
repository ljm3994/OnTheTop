#pragma once
#include "BulletManager.h"
class PlayerBuillet : public BulletManager
{
	float		m_Time;
public:
	PlayerBuillet();
	~PlayerBuillet();
	void update() override;
	HRESULT init() override;
	void release() override;
};

