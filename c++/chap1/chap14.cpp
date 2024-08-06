#include<iostream>
#include<cstring>
#include<cstdlib>

class Person{
    private:
        std::string name;
        int age;

    public:
        Person();
        Person(const std::string &, int);
        Person(const Person &);
        ~Person();
        void Print_data();   
        void setName(const std::string &);
        const std::string &getName();
        const int &getAge(); 
};

class Employee{
    private:
        std::string name;
        std::string job;
        int age;
        int salary;

    public:
        Employee();
        Employee(const std::string &, const std::string &, int, int);
        Employee(Person &);
        ~Employee();
        void Print_data();
        void Position();
        void setName(const std::string &);
        void setJob(const std::string &);
        const std::string &getJob();
        const std::string &getName();
        const int &getAge();
        const int &getSalary();
};

Person::Person(): age(0)
{

}

Person::Person(const std::string &nm, int ag)
{
    name = nm;
    age = ag;
}

Person::Person(const Person &p)
{
    name = p.name;
    age = p.age;
}

void Person::setName(const std::string &nm)
{
    name = nm;
}

const std::string &Person::getName()
{
    return name;
}

const int &Person::getAge()
{
    return age;
}

void Person::Print_data()
{
    std::cout<<"====data pelajar====" <<std::endl;
    std::cout<<"Name: " <<name <<std::endl;
    std::cout<<"Age: " <<age <<std::endl;
    std::cout<<"====================" <<std::endl;
}

Person::~Person()
{
    
}

Employee::Employee() : age(0),salary(0)
{

} 

Employee::Employee(const std::string &nm, const std::string &jb, int ag, int slr)
{
    name = nm;
    job = jb;
    age = ag;
    salary = slr;
}

Employee::Employee(Person &p)
{
    name = p.getName();
    age = p.getAge();

    if(p.getAge() >=24){
        salary = 10000000;
    }else{
        7000000;
    }
}

void Employee::setName(const std::string &nm)
{
    name = nm;
}

void Employee::setJob(const std::string &jb)
{
    job = jb;
}

const std::string &Employee::getName()
{
    return name;
}

const std::string &Employee::getJob()
{
    return job;
}

const int &Employee::getAge()
{
    return age;
}

const int &Employee::getSalary()
{
    return salary;
}

void Employee::Position()
{
    if(age>=24){
        std::cout<<name <<" adalah senior dalam bidang " <<job <<std::endl;
    }else{
        std::cout<<name <<" masih pemula dalam bidang " <<job <<std::endl;
    }
}

void Employee::Print_data()
{
    std::cout<<"=======data pekerja=======" <<std::endl;
    std::cout<<"Name: " <<name <<std::endl;
    std::cout<<"Age: " <<age <<std::endl;
    std::cout<<"Job: " <<job <<std::endl;
    std::cout<<"salary: " <<salary <<std::endl;
    std::cout<<"==========================" <<std::endl;
}

Employee::~Employee()
{
    
}
int main()
{
    Person p1("Bam Mazino",24);
    Employee e1(p1);
    e1.setJob("Vulnerabillity Research");
    p1.Print_data();
    e1.Print_data();
    e1.Position();

    std::cout<<"gaji " <<p1.getName() <<" adalah: " <<e1.getSalary() <<std::endl;

    return EXIT_SUCCESS; 
}