#include<iostream>
#include<algorithm>

class Parent{
    public:
        virtual void func()
        {
            std::cout<<"fungsi parent" <<std::endl;
        }
};

class Child : public Parent{
    public:
        void func()
        {
            std::cout<<"fungsi child" <<std::endl;
        }
};

int main()
{
    Child chld;
    Parent *prn = &chld;
    prn->func();

    return 0;
}