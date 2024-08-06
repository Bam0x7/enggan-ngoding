#include<iostream>

using namespace std;

class Distance{
    private:
        int meter;
        friend int addFive(Distance);

    public:
        Distance() : meter(0) {}   
};

int addFive(Distance D)
{
    D.meter += 5;

    return D.meter;
}

int main()
{
    Distance D;
    std::cout<<"Distance " <<addFive(D) <<std::endl;

    return 0; 
}