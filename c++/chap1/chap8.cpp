#include<iostream>
#include<algorithm>

struct Student{
    std::string name;
    float gpa;
    void Initialize(std::string,float);
    void print();
};

class University{
    public:
        std::string name;
        int Num;
        void Initialize(std::string, int);
        void print();
};

void Student::Initialize(std::string n, float afg)
{
    name = n;
    gpa = afg;
}

void Student::print()
{
    std::cout<<name <<" gpa: " <<gpa <<std::endl;
}

void University::Initialize(std::string n, int num)
{
    name = n;
    Num = num;
}

void University::print()
{
    std::cout<<"name: " <<name <<std::endl;
    std::cout<<"enrollment: " <<Num <<std::endl;
}

int main()
{
    Student student;
    student.Initialize("Bam Mazino",5.00);
    student.print();

    University s1,*s2;
    s1.Initialize("azam zamora",8881123);
    s1.print();

    s2 = new University();
    s2->Initialize("born asborn", 999123);
    s2->print();
    delete s2;
}