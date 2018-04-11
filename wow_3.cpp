#include <iostream>
using namespace std;
const int spawnOrder[2][5] = {(2,3,4,1,0),(3,0,1,2,4)};
string WarriorType[5] = {"dragon","ninja","iceman","lion","wolf"};
string color[2] = {"red","blue"};
string WeaponType[3] = {"sword","bomb","arrow"};
const int MAXWPNUM=10;
int hour;
class Weapon{
protected:
    int id;
    int atk;
    string name = "NULL";
public:
    Weapon(int,int);
    Weapon();
    virtual void printName(Weapon& wp){
        cout << name;
    };
    friend class Warrior;

};
Weapon::Weapon(int _id, int _atk) {
    id = _id;
    atk = _atk;
}

Weapon::Weapon() {
    id = 0;
    atk = 0;
}
class sword:public Weapon{
private:
    string name = "sword";
public:
    sword(int atk):Weapon(0,atk){}
    sword();
    void printName(){
        cout << name;
    };
};

class bomb:public Weapon{
private:
    string name = "bomb";
public:
    bomb(int atk):Weapon(1,atk){}
    bomb();
    void printName(){
        cout << name;
    };
};

class arrow:public Weapon{
private:
    string name = "arrow";
    int usingTime = 2;
public:
    arrow(int atk):Weapon(2,atk){}
    arrow();
    void printName(){
        cout << name;
    };
};

class City{
private:
    int id;
    City* pWest;
    City* pEast;
};

class Warrior{
protected:
    int hp;
    int id;
    int atk;
    string color;
    int weaponCount[3] = {0};
    Weapon _weapon[10];
    sword* _sword;
    arrow* _arrow;
    bomb* _bomb;
    bool ninjaBuff;
    int wpNum = 0;
public:
    Warrior();
    //~Warrior();
    Warrior(int,int,int,int,string);
    virtual void printWpInfo(char str){
        switch (str){
            case 's':
                _sword->printName();
                break;
            case 'b':
                _bomb->printName();
                break;
            case 'a':
                _arrow->printName();
                break;
        }
    }
};

Warrior::Warrior(int _id, int _hp, int _atk,int _type,string _color) {
    printf("%.3d:00 ",hour);
    cout << _color << " "<<WarriorType[_type] << " " << _id << " " << "born\n";
    id = _id;
    hp = _hp;
    atk = _atk;
    color = _color;
}


class dragon:public Warrior {
private:
    string name = "dragon";
    int type = 0;
public:
    dragon(int _id, int _hp, int _atk, string color) : Warrior(_id, _hp, _atk,type, color) {
        switch (id%3){
            case 0:
                _sword = new sword((int)(atk*0.2));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                _bomb = new bomb((int)(atk*0.4));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                _arrow = new arrow((int)(atk*0.3));
                weaponCount[2]++;wpNum++;
        }
    }//constructor
    ~dragon();//destructor
};
dragon::~dragon() {
    cout << "dragon"<<id<<" died.\n";
}

class ninja:public Warrior{
private:
    string name = "ninja";
    int type = 1;
public:
    ninja(int _id, int _hp, int _atk, string color) : Warrior(_id, _hp, _atk,type,color){
        switch (id%3){
            case 0:
                _sword = new sword((int)(atk*0.2));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                _bomb = new bomb((int)(atk*0.4));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                _arrow = new arrow((int)(atk*0.3));
                weaponCount[2]++;wpNum++;
                break;
        }

        switch ((id+1)%3){
            case 0:
                _sword = new sword((int)(atk*0.2));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                _bomb = new bomb((int)(atk*0.4));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                _arrow = new arrow((int)(atk*0.3));
                weaponCount[2]++;wpNum++;
        }
    }
};

class iceman:public Warrior{
private:
    string name = "iceman";
    int type = 2;
public:
    iceman(int _id, int _hp, int _atk, string color) : Warrior(_id, _hp, _atk,type, color) {
        switch (id%3){
            case 0:
                _sword = new sword((int)(atk*0.2));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                _bomb = new bomb((int)(atk*0.4));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                _arrow = new arrow((int)(atk*0.3));
                weaponCount[2]++;wpNum++;
        }
    }
    void stepForward();
};
void iceman::stepForward(){
    hp-=hp*0.1;
}

class lion:public Warrior{
private:
    int loyalty;
    string name = "lion";
    int type = 3;
public:
    lion(int _id, int _hp, int _atk,int _loyalty,string color) : Warrior(_id, _hp, _atk,type, color) {
        loyalty = _loyalty;
        switch (id%3){
            case 0:
                _sword = new sword((int)(atk*0.2));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                _bomb = new bomb((int)(atk*0.4));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                _arrow = new arrow((int)(atk*0.3));
                weaponCount[2]++;wpNum++;
        }
    }
};

int main(){
    return 0;
}