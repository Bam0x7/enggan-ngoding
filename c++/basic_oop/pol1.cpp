#include<iostream>
#include<algorithm>

class Count{
    private:
        int value;

    public: 
        Count() : value(5){}

    void operator ++(){
        value = value+1;
    }

    void Print(){
        std::cout<<value <<std::endl;
    }
};

int main()
{
    Count cnt;
    ++cnt;
    cnt.Print();

    return 0;
}