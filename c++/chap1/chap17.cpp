#include<iostream>
#include<iomanip>
#include<algorithm>

class Person{
    private:
        std::string name;
        std::string skill;
        int age;

    public:
        Person() = default;
        Person(const std::string &nm, const std::string sk, int ag){
            name = nm;
            skill = sk;
            age = ag;            
        }    
        Person(const Person &P){
            name = P.name;
            skill = P.skill;
            age = P.age;
        }

        virtual ~Person(){}
        const std::string &getName() const {
            return name;
        }

        const std::string &getSkill() const {
            return skill;
        }

        const int &getAge() const {
            return age;
        }
};

class Wallet{
    private:
        float invoice;

    public:
        Wallet() = default;
        Wallet(float amt) : invoice(amt){}
        Wallet(const Wallet &w){
            invoice = w.invoice;
        }
        virtual ~Wallet(){}
        void Pay(float amt){
            invoice -= amt;
        }
        float getBalance() const {
            return invoice;
        }
        void Balance() const {
            if(invoice){
                std::cout<<"Owed amount: Rp." <<invoice <<std::endl;
            }else{
                std::cout<<"Credit: Rp." <<0.0 - invoice <<std::endl;
            }
        }
};

class Employee: public Person, public Wallet{
    private:
        std::string job;
        int salary;
        int exp;

    public:
        Employee();
        Employee(const std::string &nm, const std::string &sk, const std::string &jb, int ag, int ex
        , int slr,float mnt) : Person(nm,sk,ag),Wallet(mnt){
            job = jb;
            salary = slr;
            exp = ex;
        }    
        Employee(const Employee &E){
            job = E.job;
            salary = E.salary;
            exp = E.salary;
        }

        const std::string &getJob() const {
            return job;
        }
        
        int &getSalary() {
            if(exp>5){
                salary = 10000000;
                salaryPromotion(salary);
            }
            return salary;
        }

        const int &getExp() const {
            return exp;
        }
        void salaryPromotion(int slrPromot){
            salary = slrPromot;
        }



        void Print();

};


void Employee::Print(){
    std::cout<<"========Employee========" <<std::endl;
    std::cout<<"Name: " <<getName() <<std::endl;
    std::cout<<"Age: " <<getAge() <<std::endl;
    std::cout<<"Skill: " <<getSkill() <<std::endl;
    std::cout<<"Job: " <<job <<std::endl;
    std::cout<<"Experience: " <<exp <<std::endl;
    std::cout<<"Salary: Rp." <<getSalary() <<std::endl;
    std::cout<<"Amount balance: Rp." <<getBalance() <<std::endl;
}

int main()
{
    Employee emp1("Bam Mazino","C++","Game Programmer",24,5,8000000,100000.00);
    emp1.Print();
    std::cout<<emp1.getSalary() <<std::endl;
    emp1.Pay(10000.00);
    emp1.Balance();
}