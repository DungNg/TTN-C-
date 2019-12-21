#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <iomanip>
#include <time.h>
using namespace std;


struct node{
	int n;
	int count;
	int node[100000];
};

void NhapDs(node &ds,int max)
{
	for(int i=0;i<max;i++)
	{
		ds.node[i] = i+1;
		ds.n++;
	}
	cout<<"Nhap xong"<<endl;
}

void InDs(node &ds)
{
	for(int i=0;i<ds.n;i++)
	{
		cout<<ds.node[i]<<endl;
	}
}

int rd(int max,int min)
{
	return min + rand()%(max + 1-min);
}

void Swap(int &a,int &b)
{
	int temp = a;
	a=b; b=temp;
}

void randomID(node &ds,int max)
{
	int pos,id;
	while(ds.count<max)
	{
		pos = rd(max-1,ds.count); //random tu 0 -> 1999
		//id = ds.node[pos].data; //lay gia tri cua phan tu tai vi tri pos
		ds.count++; //cac so random da dc lay ra
		Swap(ds.node[pos],ds.node[ds.count-1]);
	}	
}

int search(node &ds,int x)
{
	for(int i=0;i<ds.n;i++)
	{
		if(ds.node[i]==x)
		{
			return i;
		}
	}
}

int main()
{
	int max = 100000;
	srand(time(0));
	node ds;
	ds.n=0;
	ds.count=0;
	NhapDs(ds,max);
	randomID(ds,max);
	//InDs(ds);
	cout<<"Vi tri chua so 1: "<<search(ds,1);
	return 0;
}
