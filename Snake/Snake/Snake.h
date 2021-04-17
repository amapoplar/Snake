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
	Snake(int height,int width);					//���캯��
	~Snake();										//��������
	void run();										//���нӿ�

private:
	sf::RenderWindow* snakewindow;					//����ָ��
	sf::RectangleShape* snakeshape;					//�߻�����״������ָ��
	void update();									//���ݸ��½ӿ�
	void events();									//��ȡ��������
	void render();									//��Ⱦͼ�ν���
	void move();									//���ƶ�����
	void newegg();
	bool eateggQ();
	bool deadsnakeQ();
	std::vector<sf::Vector2i> snakebody;
	sf::Vector2i egg;
	int height;
	int width;
	int sizeofgrid;									//�����С
	sf::Clock myClock;							
	double deltatime;								//ʱ���������������Ϸÿ֡�ƶ�
	Towards headtowards;							//ǰ������	
	double hard = 0.5;								//�Ѷ�
	bool movedQ = false;
};

