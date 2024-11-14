#include <stdint.h>
#include "GameEngine/GameEngine.h"

int main()
{
    int32_t field_width = 10;
    int32_t field_height = 10;

    GameEngine engine(field_width, field_height);
    engine.Run();

    return 0;
}
