#pragma once
#include "GameNode.h"
#include "Object/EnemyBullet.h"

class Boss :public GameNode
{
private:
	/*조건
	BossChange[0] 보스 변신 및 대화
	BossChange[1] 1p 보스 HP[200]
	BossChange[2] boss BGM off
	BossChange[3] 보스 HP[100]이 되었을 때 화가 남(보스 빨간색 색혼합) 및 대화
	BossChange[4] 2p 보스 HP[100]
	BossChange[5] 플레이어 HP[0] 될경우 GAME OVER 렌더 후 메인 화면으로
	BossChange[6] 보스 유후 상태 및 플레이어 공격 찬스
	BossChange[7] 크레딧
	*/
	bool BossChange[7];
	D3DXVECTOR2	position;
	D3DXVECTOR2 *m_PlayerPos;
	D3DXVECTOR2	scale;
	char m_BossImgKey[255];
	vector<EnemyBullet*> m_Bullet;
	float m_UpdateDelayTime;
	float m_BossImageUpdate;
	int BossIndex;
	int m_MaxBulletCount;
	float		MinSize;
	bool		m_isFire;
	float      m_DelayReload;
	float m_DeleyTime;
	int m_CurrentBulletCount;
	FIRE_TYPE BulletPartern;
	FRECT m_Stage;
	D3DXVECTOR2 BossHp;
public:
	Boss();
	~Boss();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void LoadBullet(FIRE_TYPE Type);
	void BulletUpdate();
	void SetPlayerPos(D3DXVECTOR2 *m_Pos);
	bool GetBossChange(int index);
	void SetBossChange(int index, bool Value);
	bool BulletColide(FRECT rc);
	FIRE_TYPE BossParternUpdate();
	MAKESET(FRECT, m_Stage);
	MAKEGETSET(float, m_DeleyTime);
	MAKEGETSET(D3DXVECTOR2, position);
	MAKEGETSET(D3DXVECTOR2, scale);
	MAKEGETSET(D3DXVECTOR2, BossHp);
};

