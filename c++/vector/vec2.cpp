#include<iostream>
#include<vector>

int main()
{
    std::vector<std::string> name = {"bam","mazino"};

    for(std::string nm : name){
        std::cout<<nm <<" ";
    }
    std::cout<<"\n" <<std::endl;

    return 0;
}