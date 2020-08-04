#pragma once
class GameOver :public GameNode
{
private:



public:
	GameOver();
	~GameOver();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};