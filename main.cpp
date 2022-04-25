#include <SFML/Graphics.hpp>
#include "Source/Utils/InputMgr.h"
#include "Source/Utils/Utils.h"
#include "Source/Player/Player.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;



    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!!", Style::Default);
    
    InputMgr::Init();
   
    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    Player player;
    player.Spawn(arena, resolution, 0.f);

   
    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();
        Event event;
        InputMgr::ClearInput();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            InputMgr::ProcessInput(event);
        }

        //업데잉트
        player.update(dt.asSeconds());


      
       /* if (InputMgr::GetAxis(Axis::Horizontal) != 0)
        {
            shape.setFillColor(Color::Red);
        }

        if (InputMgr::GetAxis(Axis::Vertical) != 0)
        {
            shape.setFillColor(Color::Blue);
        }
        if (InputMgr::GetKeyDown(Keyboard::Space))
        {
            cout << "Down" << endl;
        }
        if (InputMgr::GetKey(Keyboard::Space))
        {
            cout << "ing" << endl;
        }
        if (InputMgr::GetKeyUp(Keyboard::Space))
        {
            cout << "Up" << endl;
        }*/


        window.clear();
        window.draw(player.GetSprite());
        window.display();
    }

    return 0;
}