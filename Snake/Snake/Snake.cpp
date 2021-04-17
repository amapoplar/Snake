#include "Snake.h"

Snake::Snake(int _height,int _width):height(_height),width(_width)
{
	snakewindow = new sf::RenderWindow(sf::VideoMode(width, height), "SNAKE EATS EGGS !!!!");
    sizeofgrid = 40;
	snakeshape = new sf::RectangleShape(sf::Vector2f(sizeofgrid-2, sizeofgrid-2));
    
    snakebody.push_back(sf::Vector2i(10, 6));
    snakebody.push_back(sf::Vector2i(10, 5));
    newegg();
    deltatime = 0.0;
    headtowards = Towards::Up;
}

Snake::~Snake()
{
    delete snakewindow;
    delete snakeshape;
}

void Snake::run()
{

    while (snakewindow->isOpen())
    {
        if (!deadsnakeQ())
        {
            update();
            sf::Event event;
            events();
            render();
            snakewindow->clear();
            deltatime += myClock.getElapsedTime().asSeconds();
            myClock.restart();
        }
        else
        {
            std::cout << "YOU ARE A LOSER!!!!!!!!!!!!!" << std::endl;
            events();
        }

    }
}



void Snake::update()
{
    move();
    eateggQ();
}

void Snake::events()
{
    sf::Event event;
    snakewindow->pollEvent(event);
    if (event.type ==  sf::Event::KeyPressed)
    {
        if ((event.key.code == sf::Keyboard::Up|| event.key.code == sf::Keyboard::W)
            &&headtowards!=Towards::Down && movedQ)
        {
            headtowards = Towards::Up;
            movedQ = false;
        }
        if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
            && headtowards != Towards::Up && movedQ)
        {
            headtowards = Towards::Down;
            movedQ = false;
        }
        if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
            && headtowards != Towards::Left && movedQ)
        {
            headtowards = Towards::Right;
            movedQ = false;
        }
        if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
            && headtowards != Towards::Right && movedQ)
        {
            headtowards = Towards::Left;
            movedQ = false;
        }
    }
    if (event.type == sf::Event::Closed)
        snakewindow->close();
}

void Snake::render()
{

    /*渲染蛇身体*/

    snakeshape->setFillColor(sf::Color(20, 20, 220, 225));
    for (std::vector<sf::Vector2i>::iterator iter = snakebody.begin(); iter != snakebody.end(); iter++)
    {

        snakeshape->setPosition((iter->x)*sizeofgrid,(iter->y) * sizeofgrid);
        snakewindow->draw(*snakeshape);
        snakeshape->setFillColor(sf::Color(0, 120, 220, 225));
    }

    /*渲染蛋*/
    if (deltatime > hard/2)
    {
        snakeshape->setFillColor(sf::Color(140, 125, 0, 225));
        snakeshape->setPosition((egg.x) * sizeofgrid, (egg.y) * sizeofgrid);
        snakewindow->draw(*snakeshape);
    }


    /*渲染地图*/



    snakewindow->display();
}

void Snake::move()
{
    /*当间隔时间大于hard，移动蛇身*/
    if (deltatime>hard)
    {
        /*蛇向前蠕动，先移动后部分，每个节点等于前一个节点位置*/
        for (size_t i = snakebody.size() - 1; i > 0; i--)
        {
            snakebody[i].x = snakebody[i - 1].x;
            snakebody[i].y = snakebody[i - 1].y;
        
        }

        switch (headtowards)
        {
        case Towards::Up:
        {
            snakebody[0].y = snakebody[0].y - 1>=0? snakebody[0].y-1:height/sizeofgrid;
            break;
        }
            
        case Towards::Down:
        {
            snakebody[0].y = snakebody[0].y + 1< height / sizeofgrid? snakebody[0].y + 1:0;
            break;
        }
        case Towards::Right:
        {
            snakebody[0].x = snakebody[0].x + 1< width/sizeofgrid? snakebody[0].x + 1:0;
            break;
        }
        case Towards::Left:
        {
            snakebody[0].x = snakebody[0].x - 1>=0?snakebody[0].x-1:width/sizeofgrid;
            break;
        }
        default:
            break;
        }
        movedQ = true;
        deltatime = 0.0;
    }

}

void Snake::newegg()
{
  bool flag = false;
  int eggx,eggy;

  do
  {
     eggx = rand() %( width /sizeofgrid);
     eggy = rand() %( height/sizeofgrid);
     for (std::vector<sf::Vector2i>::iterator iter = snakebody.begin(); iter != snakebody.end(); iter++)
     {
         if (eggx==iter->x && eggy == iter->y)
         {
             flag == true;
             break;
         }
     }
  } while (flag);
  egg = sf::Vector2i(eggx, eggy);
 
}

bool Snake::eateggQ()
{
    if (egg.x==snakebody[0].x&& egg.y == snakebody[0].y)
    {
        snakebody.push_back(snakebody[snakebody.size() - 1]);
        newegg();
        return true;
    }
    return false;
}

bool Snake::deadsnakeQ()
{
    for (std::vector<sf::Vector2i>::iterator iter = snakebody.begin()+1; iter != snakebody.end(); iter++)
    {
        if (snakebody[0].x == iter->x && snakebody[0].y == iter->y)
        {
            return true;
        }
    }
    return false;
}
