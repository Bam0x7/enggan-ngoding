#include<iostream>
#include<vector>
#include<algorithm>

namespace myClass{
    class Person{
        private:
            std::string name;
            std::string title;
            int age;
        public:
            const std::string &getName() const { return name;}
            const std::string &getTitle() const { return title;}
            const int &getAge() const { return age;}
            void reTitle(const std::string &);
    };
}

int main()
{
    std::vector<int> vec = {10,20,300,40};
    std::vector<std::string> name;
}