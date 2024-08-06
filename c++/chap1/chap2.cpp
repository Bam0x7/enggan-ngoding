#include<iostream>
#include<algorithm>

using namespace std;

class student{
    public:
    string name;
    float smester[2];
    float gpa;
};

int main()
{
    student s1;
    s1.name = "bam mazino";
    s1.gpa = 3.5;
    s1.smester[0] = 3.4;

    cout<<s1.name <<" dengan nilai: " <<s1.gpa <<endl;

    return 0;
}