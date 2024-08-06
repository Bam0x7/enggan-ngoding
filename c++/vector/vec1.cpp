#include<iostream>
#include<vector>
#include<algorithm>

int main()
{
    std::vector<int> vec = {1,2,3,4,5};
 
    //vec.assign(0,10);
    vec.push_back(7);
    for(int a: vec){
        std::cout<<a <<" ";
    }
    std::cout<<"\n" <<std::endl;
}    