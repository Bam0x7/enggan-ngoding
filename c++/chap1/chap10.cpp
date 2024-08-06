#include<iostream>
#include<cstring>

class Person{
    private:
        std::string nama;
        int usia;
        char *jurusan;

    public:
        void Inisialisasi();
        void Inisialisasi(std::string,int,char*);
        void cleanUp();
        void Print();    
};

void Person::Inisialisasi()
{
    this->nama.clear();
    this->usia = 0;
    this->jurusan = nullptr;
}

void Person::Inisialisasi(std::string nm, int us, char *jr)
{
    this->nama = nm;
    this->usia = us;
    this->jurusan = new char[strlen(jr)];
    strncpy(jurusan,jr,strlen(jr));
}

void Person::cleanUp()
{
    delete [] jurusan;
}

void Person::Print()
{
    std::cout<<nama <<std::endl;
    std::cout<<usia <<std::endl;
    std::cout<<jurusan <<std::endl;
}

int main()
{
    Person self1;
    self1.Inisialisasi("Bam Mazino",24,"Cyber Security");
    self1.Print();

    Person *self2 = new Person;
    self2 = &self1;
    self2->Print();

    self2->cleanUp();

    return 0;
}