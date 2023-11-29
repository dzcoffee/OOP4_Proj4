#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

using namespace std;
using namespace sf;

int main()
{

    RenderWindow window(VideoMode(1600, 900), "OOPMon! "); //화면크기 설정 & 캡션 이름 설정
    window.setFramerateLimit(60);//최대프레임 제한

    Map map(30, 20);

    // 전체를 grass로 채우기
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height; ++j) {
            map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }
    }

    // 주어진 범위를 concrete으로 채우기
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 3; ++j) {
            delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
            map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        // 그리드 그리기
        map.draw(window);

        window.display();
    }
    
    // 메모리 해제
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height; ++j) {
            delete map.grid[i][j];
        }
    }

    return 0;
}

