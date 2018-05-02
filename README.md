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


## C:Set

***



- 总时间限制: 

  5000ms

- 内存限制: 

  100000kB


- 描述

  现有一整数集（允许有重复元素），初始为空。我们定义如下操作：add x 把x加入集合del x 把集合中所有与x相等的元素删除ask x 对集合中元素x的情况询问对每种操作，我们要求进行如下输出。add 输出操作后集合中x的个数del 输出操作前集合中x的个数ask 先输出0或1表示x是否曾被加入集合（0表示不曾加入），再输出当前集合中x的个数，中间用空格格开。

- 输入

  第一行是一个整数n，表示命令数。0<=n<=100000。后面n行命令，如Description中所述。

- 输出

  共n行，每行按要求输出。

- 样例输入

  `7add 1add 1ask 1ask 2del 2del 1ask 1`

- 样例输出

  121 20 0021 0

  ```c++
  #include <set>
  #include <algorithm>
  #include <vector>
  #include <string>
  #include <iostream>
  #include <iterator>
  using namespace std;
  typedef multiset<int> MSET;
  int main(){
      int n;
      string cmd;
      cin>>n;
      MSET m1;
      MSET log;
      while(n--){
          cin >> cmd;
          if(cmd == "add"){
              int val;
              cin>>val;
              m1.insert(val);
              log.insert(val);
              cout << m1.count(val)<<endl;
          }
          else if(cmd == "del"){
              int val;
              cin >> val;
              cout<<m1.count(val)<<endl;
              while(m1.find(val)!= m1.end()){
                  m1.erase(m1.find(val));
              }
          }
          else if(cmd == "ask"){
              int val;
              cin>>val;
              if(log.find(val)!=log.end()){
                  cout <<"1"<<" "<<m1.count(val)<<endl;
              }
              else{
                  cout <<"0 0"<<endl;
              }
          }
      }
      return 0;
  }
  ```


