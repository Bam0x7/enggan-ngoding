#include<iostream>
#include<vector>
#include<typeinfo>

using namespace std;

class usedByAuto{
    string name;

    public:
        usedByAuto(string newName) : name(newName) {} 

        string getName() const {
            return name;
        }
};

template<class T>
class Auto{
    T anything;

    public:
        Auto(T anthg) : anything(anthg) {}
        auto echo() -> decltype(auto){
            for(auto element: anything){
                cout<<element ;
            }
            cout<<endl;
        }
};

int main()
{
    vector<int> numbers = {1,2,3,4,5};
    Auto<vector<int>> v(numbers); 
    v.echo();

    string myString("bamMazino");
    Auto<string> String(myString);
    String.echo();

    vector<string> names = {"bam","mazino","alice"};
    for(auto name: names){
        usedByAuto beUsed(name);
        Auto<string> last(beUsed.getName());
        last.echo();
    }

    return EXIT_SUCCESS;
    
}