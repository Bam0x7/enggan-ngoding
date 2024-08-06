#include<iostream>
#include<cstring>

class Person{
    private:
        std::string nama;
        int usia;

    public:
        Person();
        Person(const std::string &, int usia);
        Person(const Person &);
        void Print();
        void setName(const std::string &); //setter   
};

Person::Person()
{
    this->nama = '\0';
    this->usia = 0;
} 

Person::Person(const std::string &nm, int us)
{
    this->nama = nm;
    this->usia = us;
}

Person::Person(const Person &p) //copy constructor
{
    this->nama = p.nama;
    this->usia = p.usia;
}

void Person::Print()
{
    std::cout<<"nama: " <<this->nama <<", usia: " <<this->usia <<std::endl;

}

void Person::setName(const std::string &nm)
{
    nama = nm;
}

int main()
{
    Person per1("Bam",24);
    Person per2("Mazino", 22);

    Person per3(per1);
    Person per4 = per2;

    per3.setName("Ibnu");
    per4.setName("Pekkaz");

    per1.Print();
    per2.Print();
    per3.Print();
    per4.Print();

    return 0;
}