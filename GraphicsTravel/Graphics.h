#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include<vector>

using namespace std;

//const int M 2
//const int N 5
//1.����Ĺ��캯��. ��̳а��մ����ҵļ̳�˳��
//2.�Ӷ���Ĺ��캯��. �������ж��������˳��
//3.��Ա��ʼ�����е�������.
//4.�����๹�캯���ĺ�����.


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
	void vprint(){cout<<"�㣺("<<data<<")�����ȼ�Ϊ��"<<priority<<endl;}
};

//����ͼ�����ڽӾ������ʽ��ʾ
template <typename T>
class Grap
{
public:
	int n;//ͼ��γ��
	//�ڽӾ���,Ҳ�ɱ�ʾ2��֮���Ȩ�أ�
	//0��ʾ2��֮����ֱ�����ӣ���0ֵ��ʾ2��֮���Ȩ��
	vector<vector<int> > G;
	vector<vertex<T> > V;//�˵�
	vector<bool> visited;
	Grap(int m):n(m),G(m,vector<int>(m,0)),V(m,vertex<T>(m,10)),visited(m,false)//5*5 ����
	{
	}
	~Grap()
	{
		n=0;
	}
	void init();
	void DFS_travel();
	void BFS_travel();
	void PFS_travel();//���ȼ���������
	void prime(int a);//��С������
	void dijkstra(int a);//����·���滮
	void Tsort();

	void DFS(int v);
	void PFS(int v);
	int nextV(int self,int index);
	void updatePriority(int s,int w);
	void DUP(int s,int w);//dijkstra ����·���滮���ȼ������㷨
	void PUP(int s,int w);//prime ��С���������ȼ������㷨
};




template <typename T>
void Grap<T>::DFS_travel()//�����������
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
int Grap<T>::nextV(int self,int index)//�Լ�����������һѰ�ҽڵ�Ŀ�ʼ����
{
	for(int j=index;j<this->n;j++)
	{
		if(this->G[self][j]>0)//2��֮����������
			return j;
	}
	return j;
}


/*
�����������ͼ
0->1
0->2
1->2
*/
template <typename T>
void Grap<T>::init()//ͼ��ʼ��
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
void Grap<T>::BFS_travel()//�����������
{
	for(int i=0;i<this->n;i++)
		this->visited[i]=false;//init visited
	queue<T> que;
	for(int j=0;j<this->n;j++)//��ֹ����ͨͼ����
	{
		if(!this->visited[j])
		{
			this->visited[j]=true;
			this->V[j].vprint();//visited
			que.push(j);
			while(!que.empty())//һ����ͨͼ�������
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



//���ȼ���������
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
	}while(s!=(++v)%(this->n));//����д�ô������Դ�����㿪ʼ������һ�����нڵ�
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
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//���������ڽӵ�����ȼ�
		{
			this->updatePriority(v,i1);
		}

		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 ֵԽС�����ȼ�Խ��
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



//prime ��С������ (�����Ƿ���ͨͼ)



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
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//���������ڽӵ�����ȼ�
		{
			if(!this->visited[i1])
				this->PUP(v,i1);
		}
		
		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 ֵԽС�����ȼ�Խ��
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
		G[s][w]=PMAX;//���ȼ������ֵ
	else if(V[w].priority>G[s][w])
	{
		this->V[w].priority=G[s][w];//�������ȼ�������Сֵ
	}
}

//��Դ���·������
template <typename T>
void Grap<T>::dijkstra(int v)
{
	int minind=0;//�������Խ����ж�
	int minpri=PMAX;
	
	this->visited[v]=true;
	(this->V[v]).vprint();

	while(true)
	{
		minpri=PMAX;//��λ���ֵ
		for(int i1=nextV(v,0);i1<this->n;i1=nextV(v,i1+1))//���������ڽӵ�����ȼ�
		{
			if(!this->visited[i1])
				this->DUP(v,i1);//�������ȼ�
		}
		
		for(int i=0;i<this->n;i++)
		{
			if((!this->visited[i])&&(minpri>this->V[i].priority))// 1-10 ֵԽС�����ȼ�Խ��
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
		G[s][w]=PMAX;//���ȼ������ֵ
	else if(V[w].priority>V[s].priority+G[s][w])
	{
		this->V[w].priority=V[s].priority+G[s][w];//�������ȼ�������Сֵ
	}
}




#endif