#include "langtons_ant.h"
#include <iostream>

int main()
{
    int a;
    std::cin >> a;
    LangtonsAnt ant(800, 800);
    ant.run();
    return 0;
}
