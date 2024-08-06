#include<iostream>
#include<algorithm>

template <class type1, class type2> type2 ChooseFirst(type1,type2);
template <class type1, class type2>
type2 ChooseFirst(type1 x, type2 y)
{
    if(x<y){
        return static_cast<type2>(x);
    }else{
        return y;
    }
}   

int main()
{
    int value1 = 4, value2 = 3;
    std::cout<<ChooseFirst(value1,value2) <<std::endl;

    return EXIT_SUCCESS;
}

