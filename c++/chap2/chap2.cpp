#include<iostream>
#include<algorithm>
#include<typeinfo>

using namespace std;

template<class T1, class T2>
class Math_{
    private:
        T1 x;
        T2 y;
        Math_() : x(0), y(0){}

    public:
        Math_(T1 xx, T2 yy) : x(xx),y(yy){}   
        ~Math_(){}
        Math_(const Math_<T1, T2> &math) : x(math.x),y(math.y){}
        int add(){
            return x + y;
        }

        int sub(){
            return x - y;
        } 

        int div(){
            return x / y;
        }

        int mul(){
            return x * y;
        }
};

int main()
{
    Math_<int, int> mth(10,5);
    cout<<mth.add() <<endl;
    cout<<mth.sub() <<endl;
    cout<<mth.div() <<endl;
    cout<<mth.mul() <<endl;

    return EXIT_SUCCESS;
}
