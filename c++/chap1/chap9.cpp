#include<iostream>
#include<cstring>

class person{
    public:
        std::string nama;
        int usia;
        char *jurusan;
        void Inisial(std::string,int,char*);
        void print_data();
};

void person::Inisial(std::string n, int u, char *j)
{
    this->nama = n;
    this->usia = u;
    jurusan = new char[strlen(j)];
    strncpy(jurusan,j,strlen(j));
}    

void person::print_data()
{
    std::cout<<this->nama <<std::endl;
    std::cout<<this->usia <<std::endl;
    std::cout<<this->jurusan <<std::endl;
}

int main()
{
    person *p1 = new person;
    p1->Inisial("Bam Pekkaz",24,"Penelitian Kerentanan");
    p1->print_data();
    delete p1;
    delete p1->jurusan;

    return 0;
}    