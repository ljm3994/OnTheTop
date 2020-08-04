#pragma once
class Cradit :public GameNode
{
private:

	bool cradit = false;

public:
	Cradit();
	~Cradit();
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

};

