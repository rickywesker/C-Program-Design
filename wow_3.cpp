#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int redSpawnOrder[5] = {2,3,4,1,0};
int blueSpawnOrder[5] = {3,0,1,2,4};
int redNo = 0;
int blueNo = 0;
int _red = 0;
int _blue = 0;
int WarriorHP[5] = {1,2,3,4,5};
int Warrioratk[5] = {3,3,4,5,6};
int WarriorTypeno[5] = {0,1,2,3,4};
int lionCost;
int cityNum;



string WarriorType[5] = {"dragon","ninja","iceman","lion","wolf"};
string color[2] = {"red","blue"};
string WeaponType[3] = {"sword","bomb","arrow"};

const int MAXWPNUM=10;
int hour,min;

int minVal(int* array){
    int tmp = *array;
    int len = sizeof(array);
    for(int i = 0;i < len;i++){
        if(*(array+i)<tmp)tmp = *(array+i);
    }
    return tmp;
}
class Warrior;
class City{
public:
    int id;
    City* pWest;
    City* pEast;
    bool isTie = 0;
    bool redP = 0;
    bool blueP = 0;
    bool redwin = 0;
    bool bluewin = 0;
    bool bothDead = 0;
    Warrior* redPos;
    Warrior* bluePos;
    City(int _id,City* _pWest,City* _pEast):id(_id),pWest(_pWest),pEast(_pEast){}
    City(int _id){
        id = _id;
        pWest = NULL;
        pEast = NULL;

    }
    void battle(Warrior*,Warrior*);
};
vector<City>cities;
class Weapon{
protected:
    int id;
    int atk;
    string name = "NULL";
public:
    int usingTime = 2;
    Weapon(int,int);
    Weapon();
    string getName(){
        return name;
    }
    int getID(){return id;}
    int getatk(){return atk;}
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
public:
    sword(int atk):Weapon(0,atk){name = "sword";}
    sword();
    void printName(){
        cout << name;
    };
};

class bomb:public Weapon{
public:
    bomb(int atk):Weapon(1,atk){name = "bomb";}
    bomb();
    void printName(){
        cout << name;
    };
};

class arrow:public Weapon{
public:
    arrow(int atk):Weapon(2,atk){name = "arrow";}
    arrow();
    void printName(){
        cout << name;
    };
};

class Warrior{
protected:
    int hp;
    int id;
    int atk;
    int type;

    int weaponCount[3] = {0};
    bool ninjaBuff;

    int wpNum = 0;
    City* currCity;
    Weapon* currWeapon;
public:
    int colorno;
    vector<Weapon*>weaponlist;
    bool fleed = 0;
    bool arriveHQ = 0;
    Warrior();
    //~Warrior();
    Warrior(int,int,int,int,int);
    bool isDead();
    bool canYell = 0;
    virtual void needToFlee(){}
    int getType()const{return type;}
    virtual void Attack(Warrior* troops,Weapon*){};
    virtual void Hurted(int _val){};
    void equipWp(Weapon*);
    virtual void MarchToCity(Warrior*a,City *pCity){};
    City* getCurrCity(){return currCity;}
    void reportWpInfo();
    int getID(){return id;}
    void setCurrCity(City*pcity){currCity = pcity;}
    int getHP(){return hp;}
    int getATK(){return atk;}
    virtual void Yell(Warrior*){};
};

void Warrior::reportWpInfo() {
    printf("%.3d:55 ",hour);
    cout <<color[colorno]<< " "<<WarriorType[type]<<" "<<id<<" has "<<weaponCount[0]<<" sword "<<weaponCount[1] <<" bomb "<<weaponCount[2]<<" arrow and "<<hp<<" elements\n";
}
void Warrior::equipWp(Weapon *pWeapon) {
    *currWeapon = *pWeapon;
}

bool Warrior::isDead(){
    return hp<=0;
}
Warrior::Warrior(int _id, int _hp, int _atk,int _type,int _colorno) {
    colorno = _colorno;
    printf("%.3d:00 ",hour);
    cout << color[_colorno] << " "<<WarriorType[_type] << " " << _id << " " << "born\n";
    id = _id;
    hp = _hp;
    atk = _atk;
    if(color[colorno]=="red"){
        currCity = &cities[0];
    }
    else{
        currCity = &cities[cityNum+1];
    }

}


class dragon:public Warrior {
private:
    string name = "dragon";
public:
    dragon(int _id, int _hp, int _atk, int _colorno) : Warrior(_id, _hp, _atk,WarriorTypeno[0], _colorno) {
        type = 0;
        switch (id%3){
            case 0:
                weaponlist.push_back(new sword(atk*2/10));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                weaponlist.push_back(new bomb(atk*4/10));
                weaponCount[1]++;wpNum++;
                break;
            case 2:weaponlist.push_back(new arrow(atk*3/10));
                weaponCount[2]++;wpNum++;
        }
    }//constructor
    ~dragon(){};//destructor

    virtual void MarchToCity(Warrior*a,City*);
    void Yell(Warrior*pWari);
    virtual void Attack(Warrior* p,Weapon*);
    virtual void Hurted(int _val);
};

void dragon::Yell(Warrior*pWari) {
        printf("%.3d:40 ",hour);
        cout <<color[colorno]<<" dragon "<<id<<" yelled in city "<<currCity->id<<endl;
}
void dragon::MarchToCity(Warrior*a,City *pCity){
    currCity = pCity;
    /*printf("%.3d:10 ",hour);
    if(pCity == cities+cityNum+1){
        cout <<color[colorno]<<" dragon "<<id<<" "<<"reached "<<(color[colorno]=="red"?"blue":"red")<<" headquarter "<<" with "<<hp<<" elements and force "<<atk<<endl;
        arriveHQ = 1;
        return;
    }
    cout <<color[colorno]<<" dragon "<<id<<" "<<"marched to city "<<pCity->id<<" with "<<hp<<" elements and force "<<atk<<endl;*/
}

void dragon::Attack(Warrior* p,Weapon* pWp){
    p->Hurted(pWp->getatk());
    if(pWp->getName()=="arrow"){
        pWp->usingTime-=1;
    }
    if(pWp->getName()=="bomb"){
        pWp->usingTime=0;
        this->Hurted(p->getATK()/2);
    }
}

void dragon::Hurted(int _val){
    hp-=_val;
}

/*dragon::~dragon() {
    cout << "dragon"<<id<<" died.\n";
}*/

class ninja:public Warrior{
private:
    string name = "ninja";
public:
    ninja(int _id, int _hp, int _atk, int _colorno) : Warrior(_id, _hp, _atk,WarriorTypeno[1],_colorno){
        type = 1;

        switch (id%3){
            case 0:
                weaponlist.push_back(new sword(atk*2/10));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                weaponlist.push_back(new bomb(atk*4/10));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                weaponlist.push_back(new arrow(atk*3/10));
                weaponCount[2]++;wpNum++;
                break;
        }

        switch ((id+1)%3){
            case 0:
                weaponlist.push_back(new sword(atk*2/10));
                break;
            case 1:
                weaponlist.push_back(new bomb(atk*4/10));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                weaponlist.push_back(new arrow(atk*3/10));
                weaponCount[2]++;wpNum++;
        }
    }
    virtual void MarchToCity(Warrior*a,City*);
    virtual void Attack(Warrior* p,Weapon* pWp){
        p->Hurted(pWp->getatk());
        if(pWp->getName()=="arrow"){
            pWp->usingTime-=1;
        }
        if(pWp->getName()=="bomb"){
            pWp->usingTime=0;
        }
    }

    virtual void Hurted(int _val){
        hp-=_val;
    }

};
void ninja::MarchToCity(Warrior*a,City*pCity){
    currCity = pCity;
    /*printf("%.3d:10 ",hour);
    if(pCity == cities+cityNum+1){
        cout <<color[colorno]<<" ninja "<<id<<" "<<"reached "<<(color[colorno]=="red"?"blue":"red")<<" headquarter "<<" with "<<hp<<" elements and force "<<atk<<endl;
        arriveHQ =1;
        return;
    }
    cout <<color[colorno]<<" ninja "<<id<<" "<<"marched to city "<<pCity->id<<" with "<<hp<<" elements and force "<<atk<<endl;*/
}
class iceman:public Warrior{
private:
    string name = "iceman";
public:
    iceman(int _id, int _hp, int _atk, int _colorno) : Warrior(_id, _hp, _atk,WarriorTypeno[2], _colorno) {
        type = 2;
        switch (id%3){
            case 0:
                weaponlist.push_back(new sword(atk*2/10));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                weaponlist.push_back(new bomb(atk*4/10));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                weaponlist.push_back(new arrow(atk*3/10));
                weaponCount[2]++;wpNum++;
        }
    }

    virtual void MarchToCity(Warrior*a,City*);
    virtual void Attack(Warrior* p,Weapon* pWp){
        p->Hurted(pWp->getatk());
        if(pWp->getName()=="arrow"){
            pWp->usingTime-=1;
        }
        if(pWp->getName()=="bomb"){
            pWp->usingTime=0;
            this->Hurted(p->getATK()/2);
        }
    }

    virtual void Hurted(int _val){
        hp-=_val;
    }


};
void iceman::MarchToCity(Warrior*a,City*pCity){
    currCity = pCity;
    hp-=hp/10;
    /*printf("%.3d:10 ",hour);
    if(pCity == cities+cityNum+1){
        cout <<color[colorno]<<" iceman "<<id<<" "<<"reached "<<(color[colorno]=="red"?"blue":"red")<<" headquarter "<<" with "<<hp<<" elements and force "<<atk<<endl;
        arriveHQ = 1;
        return;
    }
    cout <<color[colorno]<<" iceman "<<id<<" "<<"marched to city "<<pCity->id<<" with "<<hp<<" elements and force "<<atk<<endl;*/
}

class lion:public Warrior{
private:
    int loyalty;
    string name = "lion";
public:
    lion(int _id, int _hp, int _atk,int _loyalty,int _colorno) : Warrior(_id, _hp, _atk,WarriorTypeno[3], _colorno) {
        type = 3;
        loyalty = _loyalty;
        cout << "Its loyalty is "<<loyalty<<endl;
        switch (id%3){
            case 0:
                weaponlist.push_back(new sword(atk*2/10));
                weaponCount[0]++;wpNum++;
                break;
            case 1:
                weaponlist.push_back(new bomb(atk*4/10));
                weaponCount[1]++;wpNum++;
                break;
            case 2:
                weaponlist.push_back(new arrow(atk*3/10));
                weaponCount[2]++;wpNum++;

        }
    }
    void MarchToCity(Warrior*a,City*);
    virtual void needToFlee();
    void setLoyalty(int _loyalty){
        loyalty = _loyalty;
    }
    virtual void Attack(Warrior* p,Weapon* pWp){
        p->Hurted(pWp->getatk());
        if(pWp->getName()=="arrow"){
            pWp->usingTime-=1;
        }
        if(pWp->getName()=="bomb"){
            pWp->usingTime=0;
            this->Hurted(p->getATK()/2);
        }
    }

    virtual void Hurted(int _val){
        hp-=_val;
    }

};

void lion::MarchToCity(Warrior*a,City* pCity){
    currCity = pCity;
    loyalty-=lionCost;
    /*printf("%.3d:10 ",hour);
    if(pCity == cities+cityNum+1){
        cout <<color[colorno]<<" lion "<<id<<" "<<"reached "<<(color[colorno]=="red"?"blue":"red")<<" headquarter "<<" with "<<hp<<" elements and force "<<atk<<endl;
        arriveHQ  =1;
        return;
    }
    cout <<color[colorno]<<" lion "<<id<<" "<<"marched to city "<<pCity->id<<" with "<<hp<<" elements and force "<<atk<<endl;*/
    return;
}
void lion::needToFlee(){
    if(color[colorno]=="red"){
    if(currCity->id == cityNum +1){
        cout << "Arrived HQ\n";
        return ;}
    if(loyalty<=0){
        printf("%.3d:05 ",hour);
        cout << color[colorno]<<" lion "<< id<< " ran away\n";
        fleed = true;
        return;
    }}
    else{
        if(currCity->id == 0){
            cout << "Arrived HQ\n";
            return ;}
        if(loyalty<=0){
            printf("%.3d:05 ",hour);
            cout << color[colorno]<<" lion "<< id<< " ran away\n";
            fleed = true;
            return;
        }
    }
}
class wolf:public Warrior{
private:
    string name="wolf";
public:
    wolf(int _id,int _hp, int _atk,int _colorno):Warrior(_id,_hp,_atk,WarriorTypeno[4],_colorno){
        type = 4;
    }
    virtual void MarchToCity(Warrior*a,City*);
    virtual void Attack(Warrior* p,Weapon* pWp){
        p->Hurted(pWp->getatk());
        if(pWp->getName()=="arrow"){
            pWp->usingTime-=1;
        }
        if(pWp->getName()=="bomb"){
            pWp->usingTime=0;
            this->Hurted(p->getATK()/2);
        }
    }

    virtual void Hurted(int _val){
        hp-=_val;
    }

};

void wolf::MarchToCity(Warrior*a,City* pCity){
    currCity = pCity;
    /*printf("%.3d:10 ",hour);
    if(pCity == cities+cityNum+1){
        cout <<color[colorno]<<" wolf "<<id<<" "<<"reached "<<(color[colorno]=="red"?"blue":"red")<<" headquarter "<<" with "<<hp<<" elements and force "<<atk<<endl;
        arriveHQ = 1;
        return;
    }
    cout <<color[colorno]<<" wolf "<<id<<" "<<"marched to city "<<pCity->id<<" with "<<hp<<" elements and force "<<atk<<endl;*/
}
bool mySort(Weapon* a,Weapon* b){
    if(a->getName()=="arrow"&&b->getName()=="arrow"){
        if(a->usingTime < b->usingTime){
            return 1;
        }
    }
    return (a->getID())<(b->getID());
}
void sortWeapon(Warrior* solider){
    sort(solider->weaponlist.begin(),solider->weaponlist.end(),mySort);
}


vector<Warrior*>redSolider;
vector<Warrior*>blueSolider;
class HeadQuarter{
private:
    int element;
    string color;
    Warrior* troops;
    int warriorCount[5] = {0};
public:
    HeadQuarter(int _element,string _color){
        element = _element;
        color = _color;
    };
    HeadQuarter(){
        element = 0;
        color = "NULL";
    }
    void spawnMinion(int);
    void initWariors();
    bool isStop();
    void printElmInfo();
    int getElm(){return element;}

};
void HeadQuarter::spawnMinion(int _no){
    int tmpNo = _no;
    bool type = color == "blue";
    if(tmpNo>=5)tmpNo%=5;
    switch (type?blueSpawnOrder[tmpNo]:redSpawnOrder[tmpNo]){
        case 0:
            if(element<WarriorHP[0])return;
            troops = new dragon(type?++blueNo:++redNo,WarriorHP[0],Warrioratk[0],type?1:0);
            element-=WarriorHP[0];
            ++warriorCount[0];
            break;
        case 1:
            if(element<WarriorHP[1])return;
            troops = new ninja(type?++blueNo:++redNo,WarriorHP[1],Warrioratk[1],type?1:0);
            element-=WarriorHP[1];
            ++warriorCount[1];
            break;
        case 2:
            if(element<WarriorHP[2])return;
            troops = new iceman(type?++blueNo:++redNo,WarriorHP[2],Warrioratk[2],type?1:0);
            element-=WarriorHP[2];
            ++warriorCount[2];
            break;
        case 3:
            if(element<WarriorHP[3])return;
            element-=WarriorHP[3];
            troops = new lion(type?++blueNo:++redNo,WarriorHP[3],Warrioratk[3],element,type?1:0);
            ++warriorCount[3];
            break;
        case 4:
            if(element<WarriorHP[4])return;
            troops = new wolf(type?++blueNo:++redNo,WarriorHP[4],Warrioratk[4],type?1:0);
            element-=WarriorHP[4];
            ++warriorCount[4];
            break;
    }
    if(type){
        blueSolider.push_back(troops);
        _blue++;
    }
    else{
        redSolider.push_back(troops);
        _red++;
    }

}
void HeadQuarter::initWariors() {
    for(int i = 0;i< 5;i++){
        cin >> WarriorHP[i];
    }
}
bool HeadQuarter::isStop(){
    return (element<minVal(WarriorHP));
}
void HeadQuarter::printElmInfo() {
    printf("%.3d:50 ",hour);
    cout <<element<<" elements in "<<color<<" headquarter\n";
}


void creatCityList(int num){
    for (int i = 0;i <= num+2;i++) {
        cities.push_back(num);
    }
    cities[0].id = 0;
    cities[num+1].id = num+1;
    for(int i = 1;i <= num;i++){//init no
        cities[i].id = i;
    }
    for(int i = 1;i <= num;i++){//init pointer
        cities[i].pWest = &cities[i-1];
        cities[i].pEast = &cities[i+1];
        /*cout << "City"<<" "<<cities[i].id<<" is created,";
        cout << "it's western city is 'city:"<<" "<<cities[i].pWest->id<<endl;
        cout << "it's eastern city is 'city:"<<" "<<cities[i].pEast->id<<endl;*testing data*/
    }
}

class Game{
private:
    bool blueisOver = 0;
    bool redisOver = 0;
public:
    Game(){};
    void gameStart();

};

void City::battle(Warrior *redWari, Warrior *blueWari) {
    if(redP&&blueP){
        sortWeapon(redWari);
        sortWeapon(blueWari);//sorting weapons
        //battle begins
        int _rorder = 0;
        int _border = 0;
        while(!(redWari->isDead()||blueWari->isDead())) {
            //tie?
            if(redWari->isDead()==0&&blueWari->isDead()==0&&(redWari->weaponlist.size()==0)&&(blueWari->weaponlist.size()==0)){
                isTie = true;
                break;
            }

            if((redWari->weaponlist.size()==0)&&(blueWari->weaponlist.size()==0)){
                isTie = true;
                break;
            }


            //check and delete weapons....
            for(vector<Weapon*>::iterator iter=redWari->weaponlist.begin(); iter!=redWari->weaponlist.end(); )
            {
                if((*iter)->usingTime==0)
                    iter = redWari->weaponlist.erase(iter);
                else
                    iter ++ ;
            }

            for(vector<Weapon*>::iterator iter=blueWari->weaponlist.begin(); iter!=blueWari->weaponlist.end(); )
            {
                if((*iter)->usingTime==0)
                    iter = blueWari->weaponlist.erase(iter);
                else
                    iter ++ ;
            }
            //delete complete...

            if(_rorder==redWari->weaponlist.size()-1)_rorder=0;
            if(_border==blueWari->weaponlist.size()-1)_border=0;
            if (id % 2 != 0) {
                if(redWari->weaponlist.size()){
                    redWari->Attack(blueWari, redWari->weaponlist[_rorder]);
                    _rorder++;
                }
                if(blueWari->weaponlist.size()){
                    blueWari->Attack(redWari, blueWari->weaponlist[_border]);
                    _border++;
                }

            }

            else {
                if(blueWari->weaponlist.size()){
                    blueWari->Attack(redWari, blueWari->weaponlist[_border]);
                    _border++;
                }
                if(redWari->weaponlist.size()){
                    redWari->Attack(blueWari, redWari->weaponlist[_rorder]);
                    _rorder++;
                }
            }
        }
        if(redWari->isDead()&&blueWari->isDead()){
            isTie = true;
            bothDead = true;
        }
        if(redWari->isDead()==1&&blueWari->isDead()==0){
            bluewin = 1;
            blueWari->Yell(blueWari);
        }
        if(redWari->isDead()==0&&blueWari->isDead()==1){
            redwin = 1;
            redWari->Yell(redWari);
        }
    }
    else{return;}
}
void Game::gameStart() {
    int M,N,K,T;
    cin >> M >> N >> K >> T;
    for(int i = 0; i < 5;i++){
        cin >> WarriorHP[i];
    }
    for(int i = 0; i < 5;i++){
        cin >> Warrioratk[i];
    }
    int maxHour;
    cityNum = N;
    lionCost = K;
    maxHour = T/60;
    HeadQuarter RedHQ(M,"red");
    HeadQuarter BlueHQ(M,"blue");
    creatCityList(cityNum);
    while(true){
        if(hour>=maxHour)break;
        if(RedHQ.isStop()&&BlueHQ.isStop())break;

        RedHQ.spawnMinion(_red);
        BlueHQ.spawnMinion(_blue);



        //check if it is fleed
        for(int i = 0;i<redSolider.size();i++){
            redSolider[i]->needToFlee();
        }
        for(vector<Warrior*>::iterator iter=redSolider.begin(); iter!=redSolider.end(); )
        {
            if((*iter)->fleed)
                iter = redSolider.erase(iter);
            else
                iter ++ ;
        }
        for(int i = 0;i<blueSolider.size();i++){
            blueSolider[i]->needToFlee();
        }
        for(vector<Warrior*>::iterator iter=blueSolider.begin(); iter!=blueSolider.end(); )
        {
            if((*iter)->fleed)
                iter = blueSolider.erase(iter);
            else
                iter ++ ;
        }
        //Marching of the soliders...
        for(int i = 0;i<redSolider.size();i++){
            if(blueisOver)break;
            cities[(redSolider[i]->getCurrCity()+1)->id].redPos = redSolider[i];
            cities[(redSolider[i]->getCurrCity()+1)->id].redP= 1;
            cities[(redSolider[i]->getCurrCity())->id].redP = 0;
            //redSolider[i]->setCurrCity(redSolider[i]->getCurrCity()+1);
            redSolider[i]->MarchToCity(redSolider[i],redSolider[i]->getCurrCity()+1);
            if(redSolider[i]->getCurrCity()->id==cityNum+1)
                blueisOver = 1;
        }
        for(int i = 0;i<blueSolider.size();i++){
            if(redisOver)break;
            cities[(blueSolider[i]->getCurrCity()-1)->id].bluePos = blueSolider[i];
            cities[(blueSolider[i]->getCurrCity()-1)->id].blueP= 1;
            cities[(blueSolider[i]->getCurrCity())->id].blueP = 0;
            //blueSolider[i]->setCurrCity(blueSolider[i]->getCurrCity()-1);
            blueSolider[i]->MarchToCity(blueSolider[i],blueSolider[i]->getCurrCity()- 1);
            if(blueSolider[i]->getCurrCity()->id==0)redisOver=1;
        }

        for(int i = 1;i<=cityNum;i++){
            if(cities[i].redP){
                printf("%.3d:10 ",hour);
                if(cities[i].id == cityNum+1){
                    cout <<"red "<<WarriorType[cities[i].redPos->getType()]<<" "<<cities[i].redPos->getID()<<" "<<"reached "<<"blue"<<" headquarter "<<" with "<<cities[i].redPos->getHP()<<" elements and force "<<cities[i].redPos->getATK()<<endl;
                    cities[i].redPos->arriveHQ = 1;
                }
                else {
                    cout << "red " << WarriorType[cities[i].redPos->getType()] << " " << cities[i].redPos->getID()
                         << " marched to city " << cities[i].id << " with " << cities[i].redPos->getHP()
                         << " elements and force " << cities[i].redPos->getATK() << endl;
                }
                }

            if(cities[i].blueP){
                printf("%.3d:10 ",hour);
                if(cities[i].id == 0){
                    cout <<"blue "<<WarriorType[cities[i].bluePos->getType()]<<" "<<cities[i].bluePos->getID()<<" "<<"reached "<<"red"<<" headquarter "<<" with "<<cities[i].bluePos->getHP()<<" elements and force "<<cities[i].bluePos->getATK()<<endl;
                    cities[i].bluePos->arriveHQ = 1;
                }
                else {
                    cout << "blue " << WarriorType[cities[i].bluePos->getType()] << " " << cities[i].bluePos->getID()
                         << " marched to city " << cities[i].id << " with " << cities[i].bluePos->getHP()
                         << " elements and force " << cities[i].bluePos->getATK() << endl;
                }
                }
        }
        if(blueisOver||redisOver){
            printf("%.3d:10 ",hour);
            cout <<(blueisOver?"blue":"red")<<" headquarter was taken\n";
            break;
        }
        /*//wolf is gonna take the oppo.'s weapon...
        for(int i = 1; i <= cityNum;i++){
            if(cities[i].redP&&cities[i].blueP){

                if(cities[i].redPos->getType()==4 && cities[i].bluePos->getType()==4){
                    continue;
                }
                if(cities[i].redPos->getType()==4){
                    if(cities[i].bluePos->weaponlist.size()==0)continue;
                    if(cities[i].redPos->weaponlist.size()==10)continue;
                    int mintmp=cities[i].bluePos->weaponlist[0]->getID();
                    for(int j = 0;j < cities[i].bluePos->weaponlist.size();j++){
                        if(cities[i].bluePos->weaponlist[j]->getID()<mintmp)mintmp = cities[i].bluePos->weaponlist[j]->getID();
                    }
                    int getWpcount = 0;
                    for(int j = 0;j < cities[i].bluePos->weaponlist.size();j++){
                        if(cities[i].bluePos->weaponlist[j]->getID()==mintmp){

                            cities[i].redPos->weaponlist.push_back(cities[i].bluePos->weaponlist[j]);
                            getWpcount++;
                        }
                    }
                    printf("%.3d:35 ",hour);
                    cout <<"red wolf "<<cities[i].redPos->getID()<<"took "<<getWpcount<<" " <<cities[i].bluePos->weaponlist[mintmp]->getName()<< "from blue "<<WarriorType[cities[i].bluePos->getType()]<<cities[i].bluePos->getID()<<" in city "<<cities[i].id<<endl;
                    for(vector<Weapon*>::iterator iter=cities[i].bluePos->weaponlist.begin(); iter!=cities[i].bluePos->weaponlist.end(); )
                    {
                        if((*iter)->getID()==mintmp)
                            iter=cities[i].bluePos->weaponlist.erase(iter);
                        else
                            iter ++ ;
                    }

                }
                else{
                    if(cities[i].redPos->weaponlist.size()==0)continue;
                    if(cities[i].bluePos->weaponlist.size()==10)continue;
                    int mintmp=cities[i].redPos->weaponlist[0]->getID();
                    for(int j = 0;j < cities[i].redPos->weaponlist.size();j++){
                        if(cities[i].redPos->weaponlist[j]->getID()<mintmp)mintmp = cities[i].redPos->weaponlist[j]->getID();
                    }
                    int getWpcount = 0;
                    for(int j = 0;j < cities[i].redPos->weaponlist.size();j++){
                        if(cities[i].redPos->weaponlist[j]->getID()==mintmp){
                            cities[i].bluePos->weaponlist.push_back(cities[i].redPos->weaponlist[j]);
                            getWpcount++;
                        }

                    }
                    printf("%.3d:35 ",hour);
                    cout <<"blue wolf "<<cities[i].bluePos->getID()<<"took "<<getWpcount<<" " <<cities[i].redPos->weaponlist[mintmp]->getName()<< "from red "<<WarriorType[cities[i].redPos->getType()]<<cities[i].redPos->getID()<<" in city "<<cities[i].id<<endl;

                    for(vector<Weapon*>::iterator iter=cities[i].redPos->weaponlist.begin(); iter!=cities[i].redPos->weaponlist.end(); )
                    {
                        if((*iter)->getID()==mintmp)
                            iter=cities[i].redPos->weaponlist.erase(iter);
                        else
                            iter ++ ;
                    }
                }
            }
        }*/
        //Battle starts where the city have 2 soliders...
        for(int i = 1;i<=cityNum;i++){
            if(cities[i].redPos&&cities[i].bluePos){
                cities[i].battle(cities[i].redPos,cities[i].bluePos);
            }
        }

        //report the elements..
        RedHQ.printElmInfo();
        BlueHQ.printElmInfo();

        //report the weapon and hp
        for(int i = 1;i<=cityNum;i++){
            if(cities[i].redP){
                cities[i].redPos->reportWpInfo();
                           }
            if(cities[i].blueP)cities[i].bluePos->reportWpInfo();

        }

        hour++;

}
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":\n";
        Game game;
        game.gameStart();
    }

    return 0;
}
