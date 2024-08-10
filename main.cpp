#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <exception>
#include <vector>
#include <chrono>
#include <thread>

struct Coordinate {
    Coordinate() : x(0), y(0) {}
    Coordinate(const int32_t new_x, const int32_t new_y) :
        x(new_x), y(new_y) {}

    int32_t x;
    int32_t y;
};

class GameObject
{
public:
    GameObject(const char symbol,
               const int32_t x, const int32_t y,
               const uint32_t body_count = 1) :
        object_symbol(symbol)
    {
        Coordinate coord(x, y);
        for(uint32_t c = 0; c < body_count; ++c) {
            position.push_back(coord);
            coord.y++;
        }
    }

     char Symbol() const {
        return object_symbol;
    }

    void SetPosition(const std::vector<Coordinate>& new_position) {
        position = new_position;
    }

    virtual const std::vector<Coordinate>& Position() const
    {
        if(position.empty()) {
            throw std::range_error("Object position not set");
        }
        return position;
    }

    Coordinate& operator[](const size_t index) {
        return position[index];
    }

    const Coordinate& operator[](const size_t index) const {
        return position.at(index);
    }

protected:
    char object_symbol;
    std::vector<Coordinate> position;
};

void PrintObjectCoordinate(const GameObject& obj) {
    for(const Coordinate& coord : obj.Position()) {
        std::cout << "x: " << coord.x << " y: " << coord.y << std::endl;
    }
}

class StaticObject : public GameObject
{
public:
    StaticObject(const char symbol,
                 const int32_t x, const int32_t y) :
        GameObject(symbol, x, y) {}
};

enum Actions {Unknown, Stop, Up, Down, Left, Right};

Actions DirectionFromChar(const char c)
{
    switch(c)
    {
    case 'q':
        return Stop;
    case 'w':
        return Up;
    case 's':
        return Down;
    case 'a':
        return Left;
    case 'd':
        return Right;
    default:
        std::cout << "Error convert from input symbol to enum" << std::endl;
    }
    return Unknown;
}

class MovableObject : public GameObject
{
public:
    MovableObject(const char symbol,
                  const int32_t x, const int32_t y, const uint32_t body_count) :
        GameObject(symbol, x, y, body_count) {}

    MovableObject(const char symbol,
                  const int32_t x, const int32_t y) :
        GameObject(symbol, x, y) {}

    virtual void Move(const Actions dir) = 0;
};

class Snake : public MovableObject
{
public:
    Snake(const int32_t x, const int32_t y, const uint32_t body_count) :
        MovableObject('S', x, y, body_count) {}

    void Move(const Actions direction)
    {
        last_action = direction;

        for(size_t i = position.size() - 1; i > 0; --i) {
            position[i] = position[i - 1];
        }

        switch (direction)
        {
        case Up:
        {
            Head().y--;
            break;
        }
        case Down:
        {
            Head().y++;
            break;
        }
        case Left:
        {
            Head().x--;
            if(last_action != Left) {
                Head().y--;
            }
            break;
        }
        case Right:
        {
            Head().x++;
            if(last_action != Right) {
                Head().y++;
            }
            break;
        }
        default:
            throw std::runtime_error("Unknown move direction for Snake");
        }
    }

    const Coordinate& Head() const {
        return position[0];
    }
    Coordinate& Head() {
        return position[0];
    }

    void AddPart(const Coordinate& new_head)
    {
        std::cout << "new_head " <<new_head.x<<new_head.y<<std::endl;
        position.push_back(Coordinate());
        for(size_t i = position.size() - 1; i > 0; --i) {
            position[i] = position[i - 1];
        }
        position[0] = new_head;
    }

private:
    Actions last_action;
};

class OneDimensionObject : public MovableObject
{
public:
    OneDimensionObject() : MovableObject('M', 0, 0) {}
    OneDimensionObject(const int32_t x, const int32_t y) :
        MovableObject('M', x, y) {}

    void Move(const Actions direction)
    {
        switch (direction)
        {
        case Up:
        {
            position[0].y--;
            break;
        }
        case Down:
        {
            position[0].y++;
            break;
        }
        case Left:
        {
            position[0].x--;
            break;
        }
        case Right:
        {
            position[0].x++;
            break;
        }
        default:
            throw std::runtime_error("Unknown move direction for OneDimensionObject");
        }
    }
};

class Eat : public StaticObject
{
public:
    Eat() : StaticObject('E', 0, 0) {}
    Eat(const int32_t x, const int32_t y) :
        StaticObject('E', x, y) {}
};

class GameEngine
{
public:
    GameEngine(const uint32_t new_width, const uint32_t new_height) :
        is_over(false),
        width(new_width),
        height(new_height),
        fruit(1, 4),
        snake(1, 5, 2),
        score(0)
    {   /*
           do {
               SetRandomPosition(fruit);
           } while(HasObjectsCollision(fruit, snake));
           */
    }

    ~GameEngine() {
        is_over = true;
    }

    void Run()
    {
        while(!is_over)
        {
            Draw();
            ProcessAction(Input());
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        DrawGameOverScreen();
    }

    Actions Input() const
    {
        if (std::cin.peek() != '\\n') {
            char input_symbol;
            std::cin >> input_symbol;
            return DirectionFromChar(input_symbol);
        }
        return Unknown;
    }

    void ProcessAction(const Actions action)
    {
        if(action == Unknown){
            return;
        }

        if(action == Actions::Stop) {
            is_over = true;
            return;
        }

        snake.Move(action);
        if(HasBorderCollision(snake)) {
            is_over = true;
            return;
        }

        if(HasObjectsCollision(snake, fruit)) {
            score += 10;
            snake.AddPart(fruit.Position().at(0));
            do {
                SetRandomPosition(fruit);
            } while(HasObjectsCollision(fruit, snake));
        }
    }

    bool HasBorderCollision(const Coordinate& coord) const
    {
        if(coord.x < 0 || coord. x > static_cast<int32_t>(width - 1) ||
                coord.y < 0 || coord.y > static_cast<int32_t>(height - 1)) {
            return true;
        }
        return false;
    }

    bool HasBorderCollision(const GameObject& obj) const
    {
        for(const Coordinate& coord : obj.Position()) {
            if(HasBorderCollision(coord)){
                return true;
            }
        }
        return false;
    }

    bool HasObjectsCollision(const Coordinate& lhs, const Coordinate& rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y ? true : false;
    }

    bool HasObjectsCollision(const GameObject& obj_1, const GameObject& obj_2) const
    {
        for(const Coordinate& coord_obj_1 : obj_1.Position()) {
            for(const Coordinate& coord_obj_2 : obj_2.Position()) {
                if(HasObjectsCollision(coord_obj_1, coord_obj_2)) {
                    return true;
                }
            }
        }
        return false;
    }

    void Draw()
    {
        system("clear");
        bool is_space_print;
        for(uint32_t h = 0; h < height + 2; ++h) {
            for(uint32_t w = 0; w < width + 2; ++w) {
                is_space_print = true;
                if((w == 0) || (w == width + 1) ||
                        (h == 0) || (h == height + 1)) {
                    std::cout << '#';
                    continue;
                }
                /*
                // вывод на экран объекта one_dim_obj
                if((w - 1 == one_dim_obj.Position().at(0).x) &&
                        (h - 1 == one_dim_obj.Position().at(0).y)) {
                    std::cout << one_dim_obj.Symbol();
                    continue;
                }
                */
                if((w - 1 == fruit.Position().at(0).x) &&
                        (h - 1 == fruit.Position().at(0).y)) {
                    std::cout << fruit.Symbol();
                    continue;
                }

                for(const Coordinate& coord : snake.Position()) {
                    if((w - 1 == coord.x) && (h - 1 == coord.y)) {
                        std::cout << snake.Symbol();
                        is_space_print = false;
                    }
                }

                if(is_space_print) {
                    std::cout << ' ';
                }
            }
            std::cout << "\n";
        }
        std::cout << "Snake" << std::endl;
        PrintObjectCoordinate(snake);
        std::cout << "Fruit" << std::endl;
        PrintObjectCoordinate(fruit);
        std::cout << "Score: " << score << std::endl;
    }

    void DrawGameOverScreen() const
    {
        system("clear");
        std::cout << "****** GAME OVER ******" << std::endl;
        std::cout << "****** SCORE " << score << " ******" << std::endl;
    }

private:
    bool is_over;
    uint32_t width, height;
    OneDimensionObject one_dim_obj;
    Eat fruit;
    Snake snake;
    uint32_t score;

    void SetRandomPosition(GameObject& obj)
    {
        std::srand(static_cast<unsigned int>(time(0)));
        std::vector<Coordinate> new_position;
        new_position.push_back(Coordinate(std::rand() % width,
                                          std::rand() % height));
        obj.SetPosition(new_position);
    }
};

int main()
{
    GameEngine game(10, 10);
    game.Run();

    return 0;
}
