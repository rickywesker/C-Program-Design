#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }

    Complex &operator=(const char*s){
        char real[10],imag[10];
        int t1 = 0,t2 = 0;
        for(int i = 0;i < strlen(s);i++){
            if(s[i]=='+')
            {
                for (int j = i + 1;j < strlen(s); ++j) {
                    if(s[j]=='i')
                        break;
                    imag[t1++] = s[j];
                }
                break;
            }
            real[t2++] = s[i];
        }
        r = atoi(real);
        i = atoi(imag);
    }
// 在此处补充你的代码
};

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}