#include <iostream>
#include "GameEngine.h"

using namespace std;

int main(int argc, char** argv) {
    GameEngine *gameEngine = GameEngine::getInstance();
    gameEngine->init_SDL();
    gameEngine->init_IMGUI();
    
    gameEngine->Start();
    
    return 1;
}
