#include<iostream>

class Child;
class Parent{
    private:
        int num;
        friend int add(Parent,Child);

    public:
        Parent() : num(5){}    
};

class Child{
    private:
        int num;
        friend int add(Parent,Child);

    public:
        Child() : num(5){}    
};


int add(Parent P, Child C)
{
    return P.num + C.num;
}

int main()
{
    Parent A;
    Child C;
    std::cout<<"result is " <<add(A,C) <<std::endl;

    return 0;
}
