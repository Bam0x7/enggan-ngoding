#include<iostream>
#include<cstring>

class Pelajar{
    private:
        std::string nama;
        int usia;
        float nilai;

    public:
        Pelajar();
        Pelajar(const std::string &, int ,float);
        Pelajar(const Pelajar &);   
        void Print();
        const std::string &getName(); 
        const float &getNilai();
};

class Pekerja{
    private:
        std::string nama;
        int usia;
        int gaji;
    public:
        Pekerja();
        Pekerja(const std::string &, int, int);
        Pekerja(Pelajar &);
        void Print();
};

Pelajar::Pelajar()
{
    nama = '\0';
    usia = 0;
    nilai = 0.0;
}

Pelajar::Pelajar(const std::string &nm, int us, float nl)
{
    nama = nm;
    usia = us;
    nilai = nl;
}

Pelajar::Pelajar(const Pelajar &p)
{
    nama = p.nama;
    usia = p.usia;
}

const std::string &Pelajar::getName()
{
    return nama;
} 


const float &Pelajar::getNilai()
{
    return nilai;
}
Pekerja::Pekerja()
{
    nama = '\0';
    usia = 0;
    gaji = 0;
}

Pekerja::Pekerja(const std::string &nm, int us, int gj)
{
    nama = nm;
    usia = us;
    gaji = gj;
}

Pekerja::Pekerja(Pelajar &p)
{
    nama = p.getName();
     if(p.getNilai() >= 4.0){
        gaji = 7000000;
    }else if(p.getNilai() >=3.0){
        gaji = 6000000;
    }else{
        gaji = 5000000;
    }
}

void Pekerja::Print()
{
    std::cout<<"Nama: " <<nama <<std::endl;
    std::cout<<"gaji: " <<gaji <<std::endl;
}

void Pelajar::Print()
{
    std::cout<<"nama: " <<nama <<std::endl;
    std::cout<<"usia: " <<usia <<std::endl;
    std::cout<<"nilai: " <<nilai <<std::endl;
}

int main()
{
    Pelajar pel("Pebri subihat", 28,5.0);
    Pekerja pek(pel);
    pel.Print();
    pek.Print();

    return 0;
}