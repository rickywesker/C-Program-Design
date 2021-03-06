#include <iostream>
using namespace std;
string WarriorType[6] = {"NULL","dragon","ninja","iceman","lion","wolf"};//dragon,ninja,iceman,lion,wolf
int redOrder[6] = {0,3,4,5,2,1};
int blueOrder[6] = {0,4,1,2,3,5};
int _i = 1,_j = 1;
int minHp;
int time = 0;
int warriorHP[6];

class Warrior{
protected:

    int side;//0red,1blue
    string weapon[2];
public:
    int hp;
    int id;
    Warrior(){}
    Warrior(int _hp,int _id):hp(_hp),id(_id){}
    //virtual void Attack(Warrior *pWarrior);
    //virtual void Hurted(int nPower);
    //virtual void FightBack(Warrior *pWarrior);
    //virtual void printSpawnInfo(Warrior *pWarrior);
};

class Dragon:public Warrior{
public:
    int type = 1;
    string strName = WarriorType[1];

    Dragon(int _hp,int _id):Warrior(_hp,_id){}
    //virtual void Attack(Warrior *pWarrior);
   // virtual void Hurted(int nPower);
    //virtual void FightBack(Warrior *pWarrior);

};

class Ninja:public Warrior{
public:
    int type = 2;

    string strName = WarriorType[2];
    Ninja(int _hp,int _id):Warrior(_hp,_id){}
    //virtual void Attack(Warrior *pWarrior);
    //virtual void Hurted(int nPower);
   // virtual void FightBack(Warrior *pWarrior);
};

class Iceman:public Warrior{
public:
    int type = 3;
    string strName = WarriorType[3];
    Iceman(int _hp,int _id):Warrior(_hp,_id){}
    //virtual void Attack(Warrior *pWarrior);
   // virtual void Hurted(int nPower);
   // virtual void FightBack(Warrior *pWarrior);
};

class Lion:public Warrior{
public:
    int type = 4;
    string strName = WarriorType[4];
    Lion(int _hp,int _id):Warrior(_hp,_id){}
    //virtual void Attack(Warrior *pWarrior);
    //virtual void Hurted(int nPower);
    //virtual void FightBack(Warrior *pWarrior);
};

class Wolf:public Warrior{
public:
    int type = 5;
    string strName = WarriorType[5];
    Wolf(int _hp,int _id):Warrior(_hp,_id){}
   // virtual void Attack(Warrior *pWarrior);
    //virtual void Hurted(int nPower);
    //virtual void FightBack(Warrior *pWarrior);
};

class HeadQuarter{
public:
    int mana;
    bool isOver= 0;
    HeadQuarter(){};
    HeadQuarter(int _mana):mana(_mana){}
    virtual void spawnFunc(){};
};

class RedHQ:public HeadQuarter{
private:
    int no = 0;
    int warriorCount[6] = {0};
public:

    virtual void spawnFunc(){
        if(isOver)return;
        if(mana<minHp){
            isOver = true;
            printf("%03d",time);
            cout << "red headquarter stops making warriors\n";
            return;
        }
        while(true){
            int i = _i;
            if(i >5){
                i%=5;
                if(i==0)i=5;
            }
            if(warriorHP[redOrder[i]]>mana) {
                ++_i;
                continue;
            }
            else{
                switch(redOrder[i]){
                    case 1:{Dragon dg(warriorHP[1],++no);
                        printf("%03d red dragon %d born with strength %d,%d dragon in red headquarter\n",time,no,
                               dg.hp,++warriorCount[1]);
                        mana-=dg.hp;
                        ++_i;
                        return;}

                    case 2:{Ninja nj(warriorHP[2],++no);
                        printf("%03d red ninja %d born with strength %d,%d ninja in red headquarter\n",time,no,
                               nj.hp,++warriorCount[2]);
                        mana-=nj.hp;
                        ++_i;
                        return;}

                    case 3:{Iceman im(warriorHP[3],++no);
                        printf("%03d red iceman %d born with strength %d,%d iceman in red headquarter\n",time,no,
                               im.hp,++warriorCount[3]);
                        mana-=im.hp;
                        ++_i;
                        return;}

                    case 4:{Lion lion(warriorHP[4],++no);
                        printf("%03d red lion %d born with strength %d,%d lion in red headquarter\n",time,no,
                               lion.hp,++warriorCount[4]);
                        mana-=lion.hp;
                        ++_i;
                        return;}

                    case 5:{Wolf wolf(warriorHP[5],++no);
                        printf("%03d red wolf %d born with strength %d,%d wolf in red headquarter\n",time,no,
                               wolf.hp,++warriorCount[5]);
                        mana-=wolf.hp;
                        ++_i;
                        return;}

                }
            }
        }
    }
};

class BlueHQ:public HeadQuarter{
private:
    int no = 0;
    int warriorCount[6] = {0};
public:
    virtual void spawnFunc(){
        if(isOver)return;
        if(mana<minHp){
            isOver = true;
            printf("%03d",time);
            cout << "blue headquarter stops making warriors\n";
            return;
        }

        while(true){
            int j = _j;
            if(j >5){
                j%=5;
                if(j==0)j=5;
            }
            if(warriorHP[blueOrder[j]]>mana){
                ++_j;
                continue;
            }
            else{
                switch(blueOrder[j]){
                    case 1:{Dragon bdg(warriorHP[1],++no);
                        printf("%03d blue dragon %d born with strength %d,%d dragon in blue headquarter\n",time,no,
                               bdg.hp,++warriorCount[1]);
                        mana-=bdg.hp;
                        ++_j;
                        return;}

                    case 2:{Ninja bnj(warriorHP[2],++no);
                        printf("%03d blue ninja %d born with strength %d,%d ninja in blue headquarter\n",time,no,
                               bnj.hp,++warriorCount[2]);
                        mana-=bnj.hp;
                        ++_j;
                        return;}

                    case 3:{Iceman bim(warriorHP[3],++no);
                        printf("%03d blue iceman %d born with strength %d,%d iceman in blue headquarter\n",time,no,
                               bim.hp,++warriorCount[3]);
                        mana-=bim.hp;
                        ++_j;
                        return;}

                    case 4:{Lion blion(warriorHP[4],++no);
                        printf("%03d blue lion %d born with strength %d,%d lion in blue headquarter\n",time,no,
                               blion.hp,++warriorCount[4]);
                        mana-=blion.hp;
                        ++_j;
                        return;}

                    case 5:{Wolf bwolf(warriorHP[5],++no);
                        printf("%03d blue wolf %d born with strength %d,%d wolf in blue headquarter\n",time,no,
                               bwolf.hp,++warriorCount[5]);
                        mana-=bwolf.hp;
                        ++_j;
                        return;}

                }
            }
        }
    }
};

class Game{
public:
    int M;
    RedHQ RHQ;
    BlueHQ BHQ;
    void reset(){
        _i = _j =1;
        time = 0;
    }
    void GameStart(){
        while(true){
            if(RHQ.isOver&&BHQ.isOver)break;
            RHQ.spawnFunc();
            BHQ.spawnFunc();
            time++;
        }
    }
    void initHQ(){
        cin>>M;
        RHQ.mana = BHQ.mana = M;
    }
    void initWarrior(){
        for(int i = 1;i<=5;i++){
            cin>>warriorHP[i];
        }
        for(int i = 1,minHp = warriorHP[1];i<=5;i++){
            if(warriorHP[i]<minHp){
                minHp = warriorHP[i];
            }
        }
    }

};

int main(){

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        Game game;
        game.reset();
        cout<<"Case:"<<i+1<<endl;
        game.initHQ();
        game.initWarrior();
        game.GameStart();
    }
    return  0;
}