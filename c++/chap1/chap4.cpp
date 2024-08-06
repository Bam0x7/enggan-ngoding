#include<iostream>
#include<algorithm>

namespace Math{
    int tambah(int a, int b)
    {
        return a + b;
    }
    int kurang(int a, int b)
    {
        return a - b;
    }
}

int main()
{
    std::cout<<"hasil tambah: " <<Math::tambah(10,10) <<std::endl;
    std::cout<<"hasil kurang: " <<Math::kurang(10,5) <<std::endl;
    
    return 0;
}