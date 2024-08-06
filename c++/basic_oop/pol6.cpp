#include<iostream>

class Child;
class Parent{
    private:
        int num;
        friend class Child;

    public:
        Parent() : num(5) {}    
};

class Child{
    private:
        int num;

    public:
        Child() : num(10){}

    int add(){
        Parent P;
        return P.num + num;
    }    

};

int main(){
    Child C;
    std::cout<<"result " <<C.add() <<std::endl;

    return 0;
}