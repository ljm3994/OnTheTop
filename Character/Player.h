#pragma once
#include "CharacterManager.h"
#include "Object/PlayerBuillet.h"
class Player : public CharacterManager
{
	bool m_isJump;
	bool m_isBoss;
	bool m_isFall;
	bool m_IsMove;
	float m_JumpPower;
	float m_JumpTime;
	UINT PlayerLife;
	FRECT m_Stage;
	D3DXVECTOR3 m_Rotate;
	vector<PlayerBuillet *> m_PlBullet;
	vector<PlayerBuillet *>::iterator m_PlBulletit;
	float CamSpeed;
	bool XCamMove;
	bool YCamMove;
public:
	Player(Map * map, D3DXVECTOR2 pos, D3DXVECTOR2 scale);
	Player();
	~Player() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void ImageChange(MOVE_DIR dir);
	void MakeBullet();
	void BulletFire();
	void SetTileIndex();
	bool EnemyColide(FRECT rc);
	void BulletRender();
	MAKEGETSET(string, ImgKey);
	MAKEGETSET(bool, m_isBoss);
	MAKEREFGET(D3DXVECTOR2, m_pos);
	MAKEREFGET(D3DXVECTOR2, m_TileIndex);
	MAKEGETSET(FRECT, m_Stage);
	MAKEGETSET(UINT, PlayerLife);
	MAKEGETSET(bool, XCamMove);
	MAKEGETSET(bool, YCamMove);
	MAKEGETSET(bool, m_IsMove);
	MAKEGETSET(float, m_JumpTime);
	MAKEGETSET(D3DXVECTOR2, m_Scale);
};

