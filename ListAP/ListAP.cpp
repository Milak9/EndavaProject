#include <iostream>
#include "../WlanWrapper/WlanWrapper.h"

int main()
{
    std::cout << "Hello World!\n";
    WlanWrapper ww;
    ww.WlanOpenHandleToServer(0, NULL, 0, NULL);
    return 0;
}