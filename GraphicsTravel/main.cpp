#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include "Graphics.h"

//0xcccc лл
//0xcdcd мм


using namespace std;

void main()
{

	vector<int> v(5,-5);
	for(vector<int>::iterator ite=v.begin();ite<v.end();ite++)
	{
		cout<<"Test: "<<*ite<<endl;
	}
	Grap<int> grap(3);
	grap.init();
//	grap.PFS_travel();
//	grap.prime(0);
	grap.dijkstra(0);

}
