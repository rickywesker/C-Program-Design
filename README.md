## 作業匯總

## A:List

***



- 描述

  写一个程序完成以下命令：new id ——新建一个指定编号为id的序列(id<10000)add id num——向编号为id的序列加入整数nummerge id1 id2——合并序列id1和id2中的数，并将id2清空unique id——去掉序列id中重复的元素out id ——从小到大输出编号为id的序列中的元素，以空格隔开

- 输入

  第一行一个数n，表示有多少个命令( n＜＝２０００００)。以后n行每行一个命令。

- 输出

  按题目要求输出。

- 样例输入

  16new 1new 2add 1 1add 1 2add 1 3add 2 1add 2 2add 2 3add 2 4out 1out 2merge 1 2out 1out 2unique 1out 1

- 样例输出

  `1 2 3 1 2 3 41 1 2 2 3 3 41 2 3 4`

  ```c++
  #include <list>
  #include <algorithm>
  #include <vector>
  #include <string>
  #include <iostream>
  #include <iterator>
  using namespace std;
  int main(){
      vector<list<int>>lst;
      string cmd;
      int n;
      cin >> n;
      while(n--){
          cin >> cmd;
          if(cmd == "new"){
              int id;
              cin>>id;
              lst.push_back(list<int>());
          }
          else if(cmd == "add"){
              int id,val;
              cin>>id>>val;
              lst[id-1].push_back(val);
              lst[id-1].sort();
          }
          else if(cmd=="merge"){
              int id1,id2;
              cin >> id1 >> id2;
              lst[id1-1].merge(lst[id2-1]);
          }
          else if(cmd == "unique"){
              int id;
              cin >> id;
              lst[id-1].unique();
          }
          else if(cmd == "out"){
              int id;
              cin>> id;
              ostream_iterator<int>o(cout," ");
              copy(lst[id-1].begin(),lst[id-1].end(),o);
              cout << endl;
          }
      }
      return 0;
  }
  ```


