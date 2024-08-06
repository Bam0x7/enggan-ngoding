#include<iostream>
#include<map>
#include<list>

int main()
{
    std::map<std::string,int> anggota;
    anggota["Bam"] = 90;
    anggota["Mazino"] = 89;

    std::cout<<"nilai untuk Bam: " <<anggota["Bam"] <<'\n';
    anggota["Bam"] = 100;

    for(const auto &a: anggota){
        std::cout<<a.first <<" " <<a.second <<std::endl;
    }

    return 0;
}