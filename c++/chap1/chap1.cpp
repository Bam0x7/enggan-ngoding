#include<iostream>
#include<vector>
#include<algorithm>

int main()
{
    char name[20];
    int age;

    std::cout<<"masukan nama: ";
    std::cin>>name;

    std::cout<<"masukan usia: ";
    std::cin>>age;

    std::cout<<"hei " <<name<< ", usia anda " <<age <<std::endl;

    return 0; 
}

