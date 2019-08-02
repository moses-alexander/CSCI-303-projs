#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <queue>
#define N 10000000
#define T 100
using namespace std::chrono;

int compare(const void* a, const void* b) {
    if (*(int*)a<*(int*)b) {return -1;}
    if (*(int*)a==*(int*)b) {return 0;}
    if(*(int*)a>*(int*)b) {return 1;}
}

int check(std::vector<int> inp, int k, int n) {
  int copy[inp.size()];
  for (int i=0;i<inp.size();i++) {copy[i]=inp.at(i);}
  std::qsort(copy,inp.size(),sizeof(int),compare);
  std::cout<<'\n';
  if (n==copy[k-1]) {return 1;}
  return 0;
}

int randomized_selection(std::vector<int> inp, int k) {
  int p;
  srand(time(NULL));
  std::vector<int> l,h;
  int r=rand() % inp.size();
  std::swap(inp.at(inp.size()-1),inp.at(r));
  p=inp.at(inp.size()-1);
  inp.pop_back();
  for (int i=0;i<inp.size();i++) {
    if (inp.at(i)<p) {l.push_back(inp.at(i));}
    if (inp.at(i)>=p) {h.push_back(inp.at(i));}
  }
  if (l.size()==k-1) {return p;}
  if (l.size()>=k) {return randomized_selection(l,k);}
  if (l.size()<k-1) {return randomized_selection(h,k-l.size()-1);}
}

int quicksort(std::vector<int> inp, int k) {
  int t, p;
  std::vector<int> l, h;
  if (inp.size()<=3) {
    int arr[inp.size()];
    for (int i=0;i<inp.size();i++) {arr[i]=inp.at(i);}
    std::qsort(arr,inp.size(),sizeof(int),compare);
    return arr[k-1];
  }
  else {
    int r=rand() % inp.size();
    std::swap(inp.at(inp.size()-1),inp.at(r));
    p=inp.at(inp.size()-1);
    inp.pop_back();
    for (int i=0;i<inp.size();i++) {
      if (inp.at(i)<p) {l.push_back(inp.at(i));}
      if (inp.at(i)>=p) {h.push_back(inp.at(i));}
      }
    if (l.size()==k-1) {return p;}
    if (l.size()>=k) {return quicksort(l,k);}
    if (l.size()<k-1) {return quicksort(h,k-l.size()-1);}
    }
  }

int deterministic_selection(std::vector<int> inp, int k) {
  if (inp.size()<=10) {
    int arr[inp.size()];
    for (int i=0;i<inp.size();i++) {arr[i]=inp.at(i);}
    std::qsort(arr,inp.size(),sizeof(int),compare);
    return arr[k-1];
  }
  else {
    std::vector<std::vector<int>> x;
    std::vector<int> v, l, h, e;
    int q=0;
    for (int i=0;i<inp.size()/5;i++) {
      x.push_back(std::vector<int>());
      for (int j=0;j<5;j++) {
        x.at(i).push_back(inp.at(q));
        q++;
      }
    }
    for (int i=0;i<inp.size()/5;i++) {v.push_back(deterministic_selection(x.at(i),3));}
    int m=deterministic_selection(v,inp.size()/10);
    for (int i=0;i<inp.size();i++) {
      if (inp.at(i)<m) {l.push_back(inp.at(i));}
      if (inp.at(i)==m) {e.push_back(inp.at(i));}
      if (inp.at(i)>m) {h.push_back(inp.at(i));}
      }
    if (l.size()>=k) {return deterministic_selection(l,k);}
    else if (k>l.size()+e.size()) {return deterministic_selection(h,k-l.size()-e.size());}
    else {return m;}
  }
}

int main() {
  int r,t1,t2,t3,t4,t5,t6;
  std::vector<int> list1(N), list2(N), list3(N), test1(T), test2(T), test3(T);
  std::vector<int> a = {9, 14, 9, 5, 10, 6, 15, 6, 13, 9};
  std::vector<int> b = {9, 14, 9, 5, 10, 6, 15, 6, 13, 9};
  std::vector<int> c = {9, 14, 9, 5, 10, 6, 15, 6, 13, 9};
  std::vector<int> v1 = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
  std::vector<int> v2 = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
  std::vector<int> v3 = {7, 2, 4, 6, 9, 11, 2, 6, 10, 6, 15, 6, 14, 2, 7, 5, 13, 9, 12, 15};
  for(int i=0;i<T;i++) {
    test1.at(i)=(i+T/2)%T;
    test2.at(i)=(i+T/2)%T;
    test3.at(i)=(i+T/2)%T;
  }
  std::cout<<'\n';
  srand(time(NULL));
  for(int i=0;i<N;i++) {
    r=rand() % (N/100); //random number in range [0,n/100)
    list1.at(i)=r;
    list2.at(i)=r;
    list3.at(i)=r;
  }
  t1=randomized_selection(test1, 75);
  std::cout<<t1<<'\n';
  std::cout<<check(test1,75,t1)<<'\n';
  t2=quicksort(test2,75);
  std::cout<<'\n'<<t2<<'\n';
  std::cout<<check(test2,75,t2)<<'\n';
  t3=deterministic_selection(test3,75);
  std::cout<<'\n'<<t3<<'\n';
  std::cout<<check(test3,75,t3)<<'\n';
  std::cout<<randomized_selection(a,5)<<' '<<quicksort(b,5)<<' '<<deterministic_selection(c,5)<<'\n';
  std::cout<<"randomized selection: "<<randomized_selection(v1,10)<<" quicksort: "<<quicksort(v2,10)<<" Medians: "<<deterministic_selection(v3,10)<<'\n';
  auto s1=high_resolution_clock::now();
  int r1=randomized_selection(list1,N/2);
  auto s2=high_resolution_clock::now();
  auto d1 = duration_cast<microseconds>(s2-s1);
  auto s3=high_resolution_clock::now();
  int r2=quicksort(list2,N/2);
  auto s4=high_resolution_clock::now();
  auto d2 = duration_cast<microseconds>(s4-s3);
  auto s5=high_resolution_clock::now();
  int r3=deterministic_selection(list3,N/2);
  auto s6=high_resolution_clock::now();
  auto d3 = duration_cast<microseconds>(s6-s5);
  std::cout<<"randomized selection: "<<r1<<" quicksort: "<<r2<<" deterministic selection: "<<r3<<'\n';
  std::cout<<"randomized selection runtime: "<<d1.count()<<" ms quicksort runtime: "<<d2.count()<<" ms deterministic selection runtime: "<<d3.count()<<" ms"<<'\n';
  std::cout<<'\n';
  return 0;
}
