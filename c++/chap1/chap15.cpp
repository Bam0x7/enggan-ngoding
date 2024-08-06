#include<iostream>
#include<iomanip>


class Person{
    private:
        std::string name;
        std::string title;
        int age;
    protected:
        void modifyTitle(const std::string &);
    public:
        Person() = default; //default constructor adalah opsi lain ketika ingin menggunakan copy constructor;
        Person(const std::string &, const std::string &, int age);
        const std::string &getName() const { return name;}
        const std::string &getTitle() const { return title;}
        const int &getAge() const { return age;} 
};

Person::Person(const std::string &nm, const std::string &tt, int ag):name(nm),title(tt),age(ag)
{
   
}    

void Person::modifyTitle(const std::string &nt)
{
    title = nt;
}

class Student : public Person{
    private:
        float gpa;
        std::string currentCourse;
        static int numStudent;
    public:
        Student();
        Student(const std::string &, const std::string &,const std::string &, float, int);     
        ~Student();
        void earnPHD();
        void Print_data() const;
        void setCurrentCourse(const std::string &);
        static int getNumberStudents();
        const std::string &getCurrentCourse() const { return currentCourse;}
        float getGpa() const {return gpa;}
};

int Student::numStudent = 0;

inline void Student::setCurrentCourse(const std::string &c)
{
    currentCourse = c;
}

inline int Student::getNumberStudents()
{
    return numStudent;
}

Student::Student(const std::string &nm, const std::string &tt, const std::string &cr, float gp, int ag) : Person(nm,tt,ag)
{
    this->currentCourse = cr;
    this->gpa = gp;
    this->numStudent++;
}

Student::~Student()
{
    numStudent--;
}

void Student::earnPHD()
{
    modifyTitle("PhD");
}

void Student::Print_data() const
{
    std::cout<<"Name: " <<getName() <<std::endl;
    std::cout<<"title: " <<getTitle() <<std::endl;
    std::cout<<"age: " <<getAge() <<std::endl;
    std::cout<<"course: " <<getCurrentCourse() <<std::endl;
    std::cout<<"gpa: " <<getGpa() <<std::endl;
}    

int main()
{
    Student self("Bam Mazino","PhD","Cyber Security Research",4.25,24);
    self.setCurrentCourse("Vulnerabillity researcher");
    self.earnPHD();
    self.Print_data();
    std::cout<<"total student: " <<Student::getNumberStudents() <<std::endl;

    return EXIT_SUCCESS;
}
