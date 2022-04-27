#include <SFML/Graphics.hpp>
#include "Source/Utils/InputMgr.h"
#include "Source/Utils/Utils.h"
#include "Source/Player/Player.h"
#include <iostream>
#include "Source/Utils/TextureHolder.h"
#include "Source/Player/Zombie.h"
#include "Source/PickUp/PickUp.h"

using namespace sf;
using namespace std;

int CreateBackground(VertexArray& va, IntRect arena)//버텍스, 맵사이즈
{
    const int TILE_SIZE = 50; //타일 크기
    const int TILE_TYPES = 3; //타일 타입
    const int VERTS_IN_QAUD = 4; 

    int cols = arena.width / TILE_SIZE;
    int rows = arena.height / TILE_SIZE;

    va.setPrimitiveType(Quads);
    va.resize(cols * rows * VERTS_IN_QAUD);
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int index = r * cols + c;
            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIndex = index * VERTS_IN_QAUD;

            va[vertexIndex + 0].position = Vector2f(x, y); //왼쪽점 세팅
            va[vertexIndex + 1].position = Vector2f(x+ TILE_SIZE, y);
            va[vertexIndex + 2].position = Vector2f(x+ TILE_SIZE, y+ TILE_SIZE);
            va[vertexIndex + 3].position = Vector2f(x, y+ TILE_SIZE);

            bool outline = (c == 0 || r == 0 || c == cols - 1 || r == rows - 1);
            int textIndex = outline ? TILE_TYPES : Utils::RandomRange(0, TILE_TYPES);

            float offset = textIndex * TILE_SIZE;
            va[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
            va[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
            va[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
            va[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);

            //int tileSetting = va[r + c * cols];
        }
    }
    return cols * rows;
}
///좀비의 벡터값을 만들어 포인터로 리턴
void CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena)
{
    for (auto v : zombies)
    {
        delete v;
    }

    zombies.clear();

    int offset = 25;
    int minX = arena.left + offset;
    int maxX = arena.width  - offset;
    int minY = arena.top + offset;
    int maxY = arena.height - offset;

    for (int i = 0; i < count; ++i)
    {
        int x = Utils::RandomRange(minX, maxX + 1);
        int y = Utils::RandomRange(minY, maxY + 1);
        ZombieTypes type = (ZombieTypes)Utils::RandomRange(0, (int)ZombieTypes::COUNT);

        //std::cout << (int)type << std::endl;

        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);

        zombies.push_back(zombie);
    }
}

int main()
{
    TextureHolder textureHolder;
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!!", Style::Fullscreen);
    
    //윈도우 위에서 마우스 커서 없애기
    window.setMouseCursorVisible(false);

    //마우스 포지션에 그림 넣기
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    Utils::SetOrigin(spriteCrosshair, Pivots::CC);

    //플레이어 카메라 뷰
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    View uiView(FloatRect(0, 0, resolution.x, resolution.y));


    InputMgr::Init();
   
    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    PickUp ammoPickUp(PickUpTypes::Ammo);
    PickUp healthPickUp(PickUpTypes::Health);
    ammoPickUp.SetArena(arena);
    healthPickUp.SetArena(arena);

    std::list<PickUp*> items;
    items.push_back(&ammoPickUp);
    items.push_back(&healthPickUp);

    Player player;
    player.Spawn(arena, resolution, 0.f);

    std::vector<Zombie*> zombies;
    CreateZombies(zombies, 100, arena);

    Clock clock;
    Time playTime;
    
    Texture textBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
    //textBackground.loadFromFile("graphics/background_sheet.png");

    VertexArray tileMap;
    CreateBackground(tileMap, arena);

    while (window.isOpen())
    {
        Time dt = clock.restart();
        playTime += dt;
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

        //업데이트
        InputMgr::Update(dt.asSeconds(), window, mainView);

        //메시지 찍기
        //std::cout << InputMgr::GetAxis(Axis::Horizontal) << std::endl;
        spriteCrosshair.setPosition(InputMgr::GetMouseWorldPosition());

        player.update(dt.asSeconds());
        //플레이어 카메라 위치 잡기
        mainView.setCenter(player.GetPosition());

        for (auto zombie : zombies)
        {
            zombie->Update(dt.asSeconds(), player.GetPosition());
        }

        ammoPickUp.Update(dt.asSeconds());
        healthPickUp.Update(dt.asSeconds());

        //충돌처리 Collision
        player.UpdateCollision(zombies);
        for (auto zombie : zombies)
        {
            if (zombie->UpdateCollision(playTime, player))
            {
                break;
            }
        }
        player.UpdateCollition(items);
        


        //드로우
        window.clear();
        //플레이어 뷰 넣기!
        window.setView(mainView);
        window.draw(tileMap, &textBackground);

        if (ammoPickUp.IsSpawned())
        {
            window.draw(ammoPickUp.GetSprite());
        }
        if (healthPickUp.IsSpawned())
        {
            window.draw(healthPickUp.GetSprite());
        }

        for (auto zombie : zombies)
        {
            window.draw(zombie->GetSprite());
            zombie->Draw(window);
        }
        
        //window.draw(player.GetSprite());
        player.Draw(window);

        window.draw(spriteCrosshair);
         

        window.setView(uiView);
        //Ui에 그릴 애들 


        window.display();
    }

    return 0;
}