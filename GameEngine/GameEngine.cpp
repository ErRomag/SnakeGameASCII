#include "GameEngine.h"

#include <thread>
#include <iostream>

#include "Utilities/CollisionChecker.h"

GameEngine::GameEngine(const int32_t width, const int32_t height) :
    is_over(false),
    score(0),
    field_width(width),
    field_height(height)
{
    InitObjects();
}

GameEngine::~GameEngine()
{
    is_over = true;
}

void GameEngine::Run()
{
    const int64_t draw_delay = 10;

    while(!is_over)
    {
        DrawField();
        ProcessKey();
        HasCollision();
        std::this_thread::sleep_for(std::chrono::milliseconds(draw_delay));
    }
    DrawGameOverScreen();
}

void GameEngine::DrawField() const
{
    system("clear");
    bool is_space_print;
    bool is_head_print = false;
    for(int32_t h = 0; h < field_height + 2; ++h) {
        for(int32_t w = 0; w < field_width + 2; ++w) {

            is_space_print = true;
            if((w == 0) || (w == field_width + 1) ||
                    (h == 0) || (h == field_height + 1)) {
                std::cout << '#';
                continue;
            }

            if((w - 1 == eat.Coordinate().x) &&
                    (h - 1 == eat.Coordinate().y)) {
                std::cout << eat.Symbol();
                continue;
            }

//            if((w - 1 == snake.Head().x) &&
//                    (h - 1 == snake.Head().y)) {
//                std::cout << 'H';
//                is_head_print = true;
//                continue;
//            }
//            for(int i = 0; i < snake.Coordinate().size(); ++i){
//                if(is_head_print)continue;
//                if((w - 1 == snake.Coordinate().at(i).x) && (h - 1 == snake.Coordinate().at(i).y)) {
//                    std::cout << snake.Symbol();
//                    is_space_print = false;
//                }
//                continue;
//            }

            for(const Point& coord : snake.Coordinate()) {
                if((w - 1 == coord.x) && (h - 1 == coord.y)) {
                    std::cout << snake.Symbol();
                    is_space_print = false;
                }
                continue;
            }

            if(is_space_print) {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }
    //std::cout << "Snake" << std::endl;
    //PrintObjectCoordinate(snake);
    //std::cout << "Fruit" << std::endl;
    //PrintObjectCoordinate(fruit);
    std::cout << "Score: " << score << std::endl;
}

void GameEngine::DrawGameOverScreen() const
{
    system("clear");
    std::cout << "****** GAME OVER ******" << std::endl;
    std::cout << "****** SCORE " << score << " ******" << std::endl;
}

void GameEngine::InitObjects()
{
    objectGen.Init(field_width, field_height);

    objectGen.CreateObject<Coordinates>(snake);

    do{
        objectGen.CreateObject<Point>(eat);
    } while(CollisionChecker::HasObjectsCollision(snake.Coordinate(), eat.Coordinate()));
}

void GameEngine::ProcessKey()
{
    if (std::cin.peek() == '\\n') {
        return;
    }

    char input_symbol;
    std::cin >> input_symbol;

    Key pressed_key = KeyFromChar(input_symbol);

    switch (pressed_key)
    {
    case Key::Q: {is_over = true; break;}
    case Key::W:
    case Key::A:
    case Key::S:
    case Key::D: snake.Move(DirectionFromKey(pressed_key));
    }
}

void GameEngine::HasCollision()
{
    if(CollisionChecker::HasBorderCollision(snake.Head(), field_width, field_height)) {
        is_over = true;
        return;
    }

    if(CollisionChecker::HasObjectsCollision(snake.Head(), eat.Coordinate())) {
        score += 10;
        snake.Grow();
        do{
            objectGen.CreateObject<Point>(eat);
        } while(CollisionChecker::HasObjectsCollision(snake.Coordinate(), eat.Coordinate()));
    }
}
