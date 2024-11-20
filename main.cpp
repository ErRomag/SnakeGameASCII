#include "GameEngine/GameEngine.h"

int main()
{
    int32_t field_width = 5;
    int32_t field_height = 5;

    GameEngine engine(field_width, field_height);
    engine.Run();

    return 0;
}
