#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

std::vector<std::vector<int>> generate_random_graph(int n, double p) {
  std::cout<<'\n';
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  double q;
  srand(time(NULL));
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      q=((double) rand()/RAND_MAX);
      if(q<p && j<i) {matrix.at(i).at(j)=1;}
      else {matrix.at(i).at(j)=0;}
      if(i==j) {matrix.at(i).at(j)=0;}
      matrix.at(j).at(i)=matrix.at(i).at(j);
    }
  }
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      std::cout<<matrix.at(i).at(j)<<' ';
    }
    std::cout<<'\n';
  }
  std::cout<<'\n';
  return matrix;
}

int bfs_count(std::vector<std::vector<int>> g, int s) {
  int c=1, visited[g.size()];
  std::queue<int> q;
  for(int i=0;i<g.size();i++) {visited[i]=0;}
  visited[s]=1;
  q.push(s);
  while (!q.empty()) {
    int next=q.front();
    q.pop();
    for(int i=0;i<g.size();i++) {
      if(g[next][i]==1 && visited[i]==0) {
        q.push(i);
        visited[i]=1;
        c++;
        // std::cout<<"visited:"<<i<<'\n';
      }
    }
  }
  // std::cout<<s<<' '<<c<<'\n';
  return c;
}

int contains_connected_component(std::vector<std::vector<int>> g, int t) {
  for(int i=0;i<g.size();i++) {
    if(bfs_count(g,i)>=t) {return 1;}
  }
  return 0;
}

int main() {

  //tests:
  // for(int i=1;i<4;i++) {generate_random_graph(4,0.5/i);}
  // std::vector<std::vector<int>> g1=generate_random_graph(5,0.5);
  // std::cout<<contains_connected_component(g1,4)<<'\n';
  // std::vector<std::vector<int>> g2=generate_random_graph(10,0);
  // std::cout<<contains_connected_component(g2,4)<<'\n';
  // std::vector<std::vector<int>> g3=generate_random_graph(3,0.95);
  // std::cout<<contains_connected_component(g3,3)<<'\n';
  // std::vector<std::vector<int>> g4=generate_random_graph(3,0.05);
  // std::cout<<contains_connected_component(g4,3)<<'\n';
  // std::vector<std::vector<int>> g5=generate_random_graph(5,0.5);
  // std::cout<<contains_connected_component(g5,6)<<'\n';
  // std::vector<std::vector<int>> g6=generate_random_graph(10,0.2);
  // std::cout<<contains_connected_component(g6,4)<<'\n';
  // std::vector<std::vector<int>> g7=generate_random_graph(10,1);
  // std::cout<<contains_connected_component(g7,9)<<'\n';
  // std::vector<std::vector<int>> g8=generate_random_graph(8,0.25);
  // std::cout<<contains_connected_component(g8,6)<<'\n';
  // std::vector<std::vector<int>> g9=generate_random_graph(8,0.75);
  // std::cout<<contains_connected_component(g9,6)<<'\n';
  // std::cout<<'\n';

  //main:
  double p, final[15];
  std::vector<std::vector<int>> g;
  int n=40, check=0, index=0, connected[15];
  for(double i=0.2;i<3.2;i+=0.2){
    p=i/n;
    for(int j=0;j<500;j++) {
      g=generate_random_graph(n,p);
      if(contains_connected_component(g,30)==1) {check++;}
    }
    connected[index]=check;
    index++;
    check=0;
  }
    for(int i=0;i<15;i++) {
      final[i]=((double) (connected[i]))/500;
      std::cout<<final[i]<<' ';
    }
  std::cout<<'\n';
  return 0;
}

//results:
//trial #01. [0.000 0.000 0.000 0.000 0.000 0.000 0.150 0.192 0.430 0.694 0.900 0.976 1.000 1.000 0.974]
//trial #02. [0.000 0.000 0.000 0.000 0.000 0.000 0.098 0.174 0.468 0.796 0.808 0.950 0.974 0.974 1.000]
//trial #03. [n/a]
//trial #04. [0.000 0.000 0.000 0.000 0.000 0.000 0.106 0.214 0.472 0.724 0.778 1.000 1.000 1.000 1.000]
//trial #05. [0.000 0.000 0.000 0.000 0.000 0.000 0.102 0.254 0.442 0.516 0.822 0.878 0.920 0.972 1.000] ***
//trial #06. [0.000 0.000 0.000 0.000 0.024 0.024 0.126 0.388 0.494 0.596 0.872 0.976 1.000 1.000 1.000]
//trial #07. [0.000 0.000 0.000 0.000 0.000 0.054 0.090 0.388 0.468 0.644 0.902 0.924 0.976 1.000 1.000]
//trial #08. [0.000 0.000 0.000 0.000 0.000 0.000 0.076 0.242 0.472 0.652 0.850 0.974 1.000 1.000 1.000]
//trial #09. [0.000 0.000 0.000 0.000 0.012 0.040 0.104 0.224 0.484 0.778 0.904 0.950 0.974 0.974 1.000]
//trial #10. [0.000 0.000 0.000 0.000 0.000 0.000 0.128 0.232 0.484 0.820 0.794 0.850 1.000 1.000 1.000]
//trial #11. [0.000 0.000 0.000 0.000 0.000 0.028 0.076 0.378 0.494 0.662 0.764 0.854 1.000 1.000 1.000]
//trial #12. [0.000 0.000 0.000 0.000 0.000 0.050 0.088 0.340 0.592 0.698 0.848 0.874 0.976 1.000 1.000]
