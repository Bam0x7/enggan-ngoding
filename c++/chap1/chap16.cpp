#include<iostream>

class Person{
    private:
        std::string name;
        std::string skill;
        int age;

    protected:
        void modifyTitle(const std::string &sk){
            skill = sk;
        }

    public:
        Person() = default;
        Person(const std::string &nm, const std::string sk, int ag){
            name = nm;
            skill = sk;
            age = ag;
        }
        virtual ~Person();
        const std::string &getName() const {
            return name;
        }    
        const std::string &getSkill() const {
            return skill;
        }
        const int &getAge() const {
            return age;
        }

        virtual void Print() const {
            std::cout<<"==========Person==========" <<std::endl;
            std::cout<<"Name: " <<name <<std::endl;
            std::cout<<"Skill: " <<skill <<std::endl;
            std::cout<<"Age: " <<age <<std::endl; 
            std::cout<<"==========================" <<std::endl;

        }
        virtual void Greeting(const std::string &msg){
            std::cout<<"my name is " <<name <<' ' <<msg <<std::endl;
        }
};
Person::~Person(){}
class Employee : public Person{
    private:
        std::string job;
        std::string division;
        int salary;

    public:
        Employee();
        Employee(const std::string nm, const std::string sk, const std::string jb, const std::string dv, int ag, int slr) : Person(nm,sk,ag) {
            job = jb;
            division = dv;
            salary = slr;
        }

        Employee(const Employee &E) : Person(E){
            job = E.job;
            division = E.division;
            salary = E.salary;
        }
        ~Employee() override;
        const std::string &getJob() const {
            return job;
        }
        const std::string &getdivision() const {
            return division;
        }

        const int &getSalary() const {
            return salary;
        }
        void EarnSkill(){
            modifyTitle("Vulnerability Research");
        }

        void Print() const {
            std::cout<<"========Employee========" <<std::endl;
            std::cout<<"Name: " <<getName() <<std::endl;
            std::cout<<"Skill: " <<getSkill() <<std::endl;
            std::cout<<"Age: " <<getAge() <<std::endl;
            std::cout<<"Division " <<division <<std::endl;
            std::cout<<"Job: " <<job <<std::endl;
            std::cout<<"Salary: " <<salary <<std::endl;
            std::cout<<"========================" <<std::endl;
        }

        
};

Employee::~Employee(){}

int main()
{
    Person *self[3] = {};
    self[0] = new Person("Bam Mazino","Cyber Security",24);
    self[1] = new Employee("Ibnu Ruslan","C/C++ & Python", "Vulnerability Researcher", "Cyber Security", 24, 7000000);
    self[2] = new Person("Pekkaz", "Web Programmer", 26);

    for(int i=0;i<3;i++){
        self[i]->Greeting("Upay geh");
        std::cout<<'\n';
        self[i]->Print();
    } 

    for(int i=0; i<3; i++){
        delete self[i];
    }

    return EXIT_SUCCESS;
}