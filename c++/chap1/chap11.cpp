#include<iostream>
#include<cstring>

class Person{
    private:
        std::string nama;
        int usia;
    public:
        Person(); //constructor
        Person(const std::string &, int);
        void Print();
   
};

Person::Person()
{
    usia = 0;
}    

Person::Person(const std::string &nm, int us)
{
    this->nama = nm;
    this->usia = us;
}

void Person::Print()
{
    std::cout<<"Nama: " <<nama <<", usia: " <<usia <<std::endl;
}

int main()
{
    Person p1;
    Person p2("Bam Mazino",24);
    p2.Print();

    Person *p3 = new Person("Pekkaz" ,23);
    p3->Print();
    delete p3;

    return 0;
}