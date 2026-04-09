#pragma once

class GameManager {

public:
	static GameManager* instance;

	static GameManager* GetInstance();

	void PrintHi();
protected:
	GameManager() = default;
	~GameManager() = default;
};