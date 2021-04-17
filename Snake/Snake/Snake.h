#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<random>

enum class Towards
{
	Up,
	Down,
	Right,
	Left
};

class Snake
{
public:
	Snake(int height,int width);					//构造函数
	~Snake();										//析构函数
	void run();										//运行接口

private:
	sf::RenderWindow* snakewindow;					//窗体指针
	sf::RectangleShape* snakeshape;					//蛇基本形状（方格）指针
	void update();									//数据更新接口
	void events();									//读取控制命令
	void render();									//渲染图形界面
	void move();									//蛇移动函数
	void newegg();
	bool eateggQ();
	bool deadsnakeQ();
	std::vector<sf::Vector2i> snakebody;
	sf::Vector2i egg;
	int height;
	int width;
	int sizeofgrid;									//蛇身大小
	sf::Clock myClock;							
	double deltatime;								//时间戳，用来计算游戏每帧移动
	Towards headtowards;							//前进方向	
	double hard = 0.5;								//难度
	bool movedQ = false;
};

