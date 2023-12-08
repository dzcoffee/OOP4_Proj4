#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "SideWindow.h"
#include "Player.h"
#include "Gamecontroller.h"
#include "InfoWindow.h"

using namespace std;
using namespace sf;

int main()
{

    RenderWindow window(VideoMode(1600, 900), "OOPMon! "); //화면크기 설정 & 캡션 이름 설정
    window.setFramerateLimit(60);//최대프레임 제한
    Player player("name","Puang",oopmon::montype::fire);
    gamecontroller controller(player);
    MapManager mapManager(player, controller);
    InfoWindow *InfoWindow1 = nullptr;
    
    bool isSideWindowVisible = false; // SideWindow의 가시성 여부를 저장하는 변수
    bool isInfoWindowVisible = false; // SideWindow의 가시성 여부를 저장하는 변수

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            //1204 윤도경 추가
            // 키보드인풋
            if (event.type == Event::KeyPressed) {
                if (controller.isActivate()) { //사이드 윈도우가 켜졌을 떄만
                    switch (event.key.code) {
                    case Keyboard::Left:
                        //아마 화살표 움직이고 어떤 함수를 실행시킬 id값을 설정하게 하면 될 듯
                        controller.selectionLeft();
                        break;
                    case Keyboard::Right:
                        //Left와 동일
                        controller.selectionRight();
                        break;
                    case Keyboard::Up:
                        //Left와 동일
                        controller.selectionUp();
                        break;
                    case Keyboard::Down:
                        //Left와 동일
                        controller.selectionDown();
                        break;
                    case Keyboard::X:
                        
                        break;
                    case Keyboard::Z:
                        //해당 위치에 있는 함수 실행
                        break;
                    case Keyboard::Enter:
                        controller.enter();
                        break;
                    }

                }
                else {
                    if (!isInfoWindowVisible) {
                        switch (event.key.code) {
                        case Keyboard::Left:
                            mapManager.movePlayer(-1, 0);
                            break;
                        case Keyboard::Right:
                            mapManager.movePlayer(1, 0);
                            break;
                        case Keyboard::Up:
                            mapManager.movePlayer(0, -1);
                            break;
                        case Keyboard::Down:
                            mapManager.movePlayer(0, 1);
                            break;
                        case Keyboard::X:
                            isInfoWindowVisible = !isInfoWindowVisible;
                            
                            break;
                        }
                    }
                    else {
                        switch (event.key.code) {
                        case Keyboard::X:
                            isInfoWindowVisible = !isInfoWindowVisible;
                            
                            break;
                        }
                    }
                }
            }

            window.clear(Color::White);

            // 그리드 그리기
            mapManager.draw(window);
            //1204 윤도경 추가
            if (controller.isActivate()) // X키를 누른 상태에서만 켜짐
            {
                //sidewindow1.draw(window); // SideWindow 그리기
                controller.draw(window);
            }
            else {
                if (!player.curmon().getAlive()) {
                    mapManager.onPlayerDied();
                }
            }
            if (isInfoWindowVisible) {
                if (InfoWindow1 == nullptr) {
                    InfoWindow1 = new InfoWindow(player, mapManager);
                }
                InfoWindow1->draw(window);
            }
            else {
                delete InfoWindow1;
                InfoWindow1 = nullptr;
            }

            window.display();
        }
    }

    return 0;
}
