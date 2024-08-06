#include<iostream>

namespace DataType
{
    int total;
}

int main()
{
    using namespace DataType;
    DataType::total = 10;

    std::cout<<DataType::total <<std::endl;

    return 0;
}