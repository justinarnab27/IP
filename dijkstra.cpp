#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <functional>

using namespace std;

typedef priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > mn_heap;

class graph{
public:
	int size = gp.size();
	graph(bool);
	void addnode();
	void addedge(int,int);
	void addedge(int,int,int);
	void disp();
	void dfs();
	void bfs();
	int dijkstra(int,int);
private:
	vector<pair<int,int> > ninfo;
	bool show_weight = false;
	vector<vector<pair<int,int> > > gp;
	void dfs_aux(int,vector<int>&);
	void bfs_aux(int,queue<int>&,vector<pair<int,int> >&);
	void dijk_aux(int,int,int,mn_heap&,vector<int>&);

};

graph::graph(bool w = false){
	if(w == true) show_weight = true;
}

void graph::addnode(){
		vector<pair<int,int> > x;
		gp.push_back(x);
}

void graph::disp(){
	for(int i = 0;i!=gp.size();++i){
		cout << i << ": " ;
		for(auto j:gp[i]){
			cout << j.first << " " ;
			if(show_weight == true){
				cout << "(" << j.second << ")" << " ";
			}
		}
		cout << "\n";
	}
}

void graph::addedge(int a, int b){
	graph::addedge(a,b,0);
}

void graph::dfs_aux(int ix,vector<int>& visited){
	if(visited[ix]==1) return;
	cout << ix << endl;
	visited[ix] = 1;
	for(int i = 0;i!=gp[ix].size();++i){
		if(visited[gp[ix][i].first] == 1) continue;
		dfs_aux(gp[ix][i].first,visited);
	}
}

void graph::dfs(){
	vector<int> visited;
	visited.assign(gp.size(),0);
	for(int i = 0;i!=gp.size();++i){
		if(visited[i] == 1) continue;
		dfs_aux(i,visited);
		cout << "++++++++" << endl;
	}
}

void graph::bfs_aux(int ix,queue<int>& qu,vector<pair<int,int> >& visited){
	if(visited[ix].first == 1) return;
	qu.pop();
	visited[ix].first = 1;
	cout << ix << endl;
	for(int i = 0;i!=gp[ix].size();++i){
		if(visited[gp[ix][i].first].first != 1 && visited[gp[ix][i].first].second != 1 ){
			qu.push(gp[ix][i].first);
			visited[gp[ix][i].first].second = 1;
		}
	}
}

void graph::bfs(){
	vector<pair<int,int> > visited;
	visited.assign(gp.size(),make_pair(0,0));
	queue<int> qu;
	for(int i = 0;i!=gp.size();++i){
		if(visited[i].first == 1) continue;
		if(visited[i].second!=1){
			qu.push(i);
			visited[i].second = 1;
		}
		while(!qu.empty()){
			bfs_aux(qu.front(),qu,visited);
		}
		cout << "++++++++" << endl;
	}
}

void graph::addedge(int a,int b, int weight){
	gp[a].push_back(make_pair(b,weight));
	gp[b].push_back(make_pair(a,weight));
}

void graph::dijk_aux(int start,int end,int ix,mn_heap& pq,vector<int>& visited){
	visited[ix] = 1;
	for(int i = 0;i!=gp[ix].size();++i){
		if(visited[gp[ix][i].first]==1) continue;
		if(gp[ix][i].second+ninfo[ix].second < ninfo[gp[ix][i].first].second){
			ninfo[gp[ix][i].first].second = gp[ix][i].second+ninfo[ix].second ;
			ninfo[gp[ix][i].first].first = ix;

			pair<int,int> x = make_pair(ninfo[gp[ix][i].first].second,gp[ix][i].first);
			pq.push(x);
		}
	}
	pq.pop();
}

int graph::dijkstra(int start, int end){
	vector<int> visited;
	visited.assign(gp.size(),0);

	pair<int,int> x = make_pair(-1,INT_MAX);
	ninfo.assign(gp.size(),x);
	ninfo[start] = make_pair(-1,0);

	mn_heap pq;
	pq.push(make_pair(0,start));

	while((pq.top()).second != end){
		if(visited[(pq.top()).second]==0){
			dijk_aux(start,end,(pq.top()).second,pq,visited);
		}
		else{
			pq.pop();
		}
	}

	cout << ninfo[end].second << endl << endl;

	int z = end;

	while(1){
		cout << z << " ";
		if(z==start) break;
		z = ninfo[z].first;
	}
	cout << endl;

	return ninfo[end].second;
}



int main(){
	graph num(true);

	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();
	num.addnode();

	num.addedge(0,1,7);
	num.addedge(0,2,2);
	num.addedge(1,4,4);
	num.addedge(1,2,3);
	num.addedge(2,4,4);
	num.addedge(4,6,5);
	num.addedge(2,8,1);
	num.addedge(6,8,3);
	num.addedge(8,7,2);
	num.addedge(7,5,2);
	num.addedge(5,11,5);
	num.addedge(10,11,4);
	num.addedge(9,11,4);
	num.addedge(9,10,6);
	num.addedge(12,10,4);
	num.addedge(12,9,4);
	num.addedge(3,12,2);
	num.addedge(0,3,3);

	cout << "DISPLAY" << endl;

	num.disp();

	cout << "DFS" << endl;

	num.dfs();

	cout << "BFS" << endl;

	num.bfs();

	cout << "DIJKSTRA" << endl;

	num.dijkstra(0,1);

	return 0;
}