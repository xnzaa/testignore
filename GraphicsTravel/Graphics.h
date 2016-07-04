#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include<vector>

using namespace std;

//const int M 2
//const int N 5
//1.基类的构造函数. 多继承按照从左到右的继承顺序
//2.子对象的构造函数. 按照类中对象的声明顺序
//3.成员初始化表中的其他项.
//4.派生类构造函数的函数体.


#define MAX 10000
#define PMAX 10
#define PMIN 1
template <typename T>
class vertex
{
public:
	T data;
	int priority;//1-10
	vertex(T num,int p):data(num),priority(p){}
	void vprint(){cout<<"点：("<<data<<")的优先级为："<<priority<<endl;}
};

//有向图，用邻接矩阵的形式表示
template <typename T>
class Grap
{
public:
	int n;//图的纬度
	//邻接矩阵,也可表示2点之间的权重，
	//0表示2点之间无直接连接，非0值表示2点之间的权重
	vector<vector<int> > G;
	vector<vertex<T> > V;//端点
	vector<bool> visited;
	Grap(int m):n(m),G(m,vector<int>(m,0)),V(m,vertex<T>(m,10)),visited(m,false)//5*5 矩阵
	{
	}
	~Grap()
	{
		n=0;
	}
	void init();
	void DFS_travel();
	void BFS_travel();
	void PFS_travel();//优先级优先搜索
	void prime(int a);//最小生成树
	void dijkstra(int a);//最优路径规划
	void Tsort();

	void DFS(int v);
	void PFS(int v);
	int nextV(int self,int index);
	void updatePriority(int s,int w);
	void DUP(int s,int w);//dijkstra 最优路径规划优先级更新算法
	void PUP(int s,int w);//prime 最小生成树优先级更新算法
};




template <typename T>
void Grap<T>::DFS_travel()//深度优先搜索
{
	for(int i=0;i<this->n;i++)
		this->visited[i]=false;
	for(int j=0;j<this->n;j++)
	{
		if(!this->visited[j])
			DFS(j);
	}
}

template <typename T>
void Grap<T>::DFS(int v)
{
	this->visited[v]=true;
	this->V[v].vprint();//visited
	for(int num=nextV(v,0);num<this->n;num=nextV(v,num+1))
	{
		if(!this->visited[num])
			DFS(num);
	}
}

template <typename T>
int Grap<T>::nextV(int self,int index)//自己的索引，下一寻找节点的开始索引
{
	for(int j=index;j<this->n;j++)
	{
		if(this->G[self][j]>0)//2点之间存在有向边
			return j;
	}
	return j;
}


/*
三个点的有向图
0->1
0->2
1->2
*/
template <typename T>
void Grap<T>::init()//图初始化
{
	G[0][1]=2;
	G[0][2]=1;
	G[2][1]=2;

	for(int v=0;v<this->n;v++)
	{
		this->V[v]=vertex<T>(v,10);
	}
}




template <typename T>
void Grap<T>::BFS_travel()//宽度优先搜索
{
	for(int i=0;i<this->n;i++)
		this->visited[i]=false;//init visited
	queue<T> que;
	for(int j=0;j<this->n;j++)//防止非联通图存在
	{
		if(!this->visited[j])
		{
			this->visited[j]=true;
			this->V[j].vprint();//visited
			que.push(j);
			while(!que.empty())//一个联通图访问完毕
			{
				int v = que.front();que.pop();
				for(int num=nextV(v,0);num<this->n;num=nextV(v,num+1))
				{
					if(!this->visited[num])	
					{
						this->visited[num]=true;
						this->V[num].vprint();//visited
						que.push(num);
					}
				}
			}
		}
	}
}

template <typename T>
void Grap<T>::updatePriority(int s,int w)
{
	
	if(G[s][w]==0)
		this->V[w].priority=PMAX;
	else
		//this->V[w].priority=1;
		this->V[w].priority=G[s][w];
}



//优先级优先搜索
template <typename T>
void Grap<T>::PFS_travel()
{
	for(int i=0;i<this->n;i++)
		this->visited[i]=false;//init visited
	int s=0;
	int v=s;
	do
	{
		if(!visited[v])
			this->PFS(v);
	}while(s!=(++v)%(this->n));//这样写好处：可以从任意点开始，遍历一次所有节点
}


template <typename T>
void Grap<T>::PFS(int v)
{
	int minind=0;
	int minpri=PMAX;
	
	this->visited[v]=true;
	(this->V[v]).vprint();

	while(true)
	{

		minpri=PMAX;
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//更新所有邻接点的优先级
		{
			this->updatePriority(v,i1);
		}

		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 值越小，优先级越高
			{
				minind=i;
				minpri=this->V[i].priority;
			}
		}
		if(this->visited[minind])
			break;
		else
		{
			this->visited[minind]=true;
			(this->V[minind]).vprint();
			v=minind;
		}
	}
}



//prime 最小生成树 (不考虑非联通图)



template <typename T>
void Grap<T>::prime(int v)
{
	int minind=0;
	int minpri=PMAX;
	
	this->visited[v]=true;
	(this->V[v]).vprint();

	while(true)
	{
		minpri=PMAX;
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//更新所有邻接点的优先级
		{
			if(!this->visited[i1])
				this->PUP(v,i1);
		}
		
		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 值越小，优先级越高
			{
				minind=i;
				minpri=this->V[i].priority;
			}
		}
		if(this->visited[minind])
			break;
		else
		{
			this->visited[minind]=true;
			(this->V[minind]).vprint();
			v=minind;
		}
	}
}

template <typename T>
void Grap<T>::PUP(int s,int w)
{
	if(G[s][w]==0)
		G[s][w]=PMAX;//优先级置最大值
	else if(V[w].priority>G[s][w])
	{
		this->V[w].priority=G[s][w];//更新优先级，到最小值
	}
}

//单源最短路径问题
template <typename T>
void Grap<T>::dijkstra(int v)
{
	int minind=0;//帮助最后越界的判断
	int minpri=PMAX;
	
	this->visited[v]=true;
	(this->V[v]).vprint();

	while(true)
	{
		minpri=PMAX;//复位最大值
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//更新所有邻接点的优先级
		{
			if(!this->visited[i1])
				this->DUP(v,i1);//更新优先级
		}
		
		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 值越小，优先级越高
			{
				minind=i;
				minpri=this->V[i].priority;
			}
		}
		if(this->visited[minind])
			break;
		else
		{
			this->visited[minind]=true;
			(this->V[minind]).vprint();
			v=minind;
		}
	}
}

/*
	G[0][1]=2;
	G[0][2]=1;
	G[2][1]=2;

  */
template <typename T>
void Grap<T>::DUP(int s,int w)
{
	V[0].priority=0;
	if(G[s][w]==0)
		G[s][w]=PMAX;//优先级置最大值
	else if(V[w].priority>V[s].priority+G[s][w])
	{
		this->V[w].priority=V[s].priority+G[s][w];//更新优先级，到最小值
	}
}




#endif