#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<cmath>
#include<fstream>

using namespace std;


const int COLONY_SIZE=100;  //个体数目
const int Size=2;//个体的长度
const int Generation=3000;//代数
const double OVER=0.7;//杂交的概率
const double MUTATE=0.1;//变异的概率
const double UPPER=30.0;//函数的上界

struct Indival
{
	double code[Size];
	double fitness;
	double cfitness;
	double rfitness;
}Group[COLONY_SIZE];

Indival newGroup[COLONY_SIZE];

Indival bestChrom;//记录最好的个体

int GenNum=0;

double random(double, double);
void initiate();
void calvalue();
void select();
void crossOver();
void xOver(int,int);
void mutate();
double delta(int,double,double,double);
void sort();

/*****************主函数***************/
int main()
{
	ofstream output;
	srand((unsigned)time(NULL));
	initiate();
	calvalue();
	output.open("data.txt");
	while(GenNum<=Generation)
	{
		GenNum++;
		select();	
		crossOver();
		mutate();	
		calvalue();	
		sort();
		if (bestChrom.fitness<Group[0].fitness)
		{
			bestChrom.code[0]=Group[0].code[0];
			bestChrom.code[1]=Group[0].code[1];
			bestChrom.fitness=Group[0].fitness;
		}
// 		output<<"gen: "<<GenNum<<"最优解为："<<endl;
// 		output<<"x1: "<<bestChrom.code[0]<<"  x2: "<<bestChrom.code[1]<<"   函数值为： "<<(30-bestChrom.fitness)<<endl;
		output<<GenNum<<"	"<<(30-bestChrom.fitness)<<endl;
	}
	output.close();
	cout<<"运行结束！"<<endl;//提示运行结束
 	return 0;
}


/******************************函数的实现*****************************************/


double random(double start, double end){//随机产生区间内的随机数	
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}

void initiate()//初始化
{
	for(int i=0;i<COLONY_SIZE;i++)
	{
		Group[i].code[0]=random(-30,30);
		Group[i].code[1]=random(-30,30);
		Group[i].fitness=0;//适应值
		Group[i].cfitness=0;//相对适应值比例之和
		Group[i].rfitness=0;//相对适应值比例
	}
}

void calvalue()//计算适应值
{
	double x1,x2;
	double sum=0;
	double part1,part2;//将函数分成几个部分
	for(int i=0;i<COLONY_SIZE;i++)
	{
		x1=Group[i].code[0];
		x2=Group[i].code[1];
		part1=-0.2*sqrt((x1*x1+x2*x2)/Size);
		part2=(cos(2*3.1415926*x1)+cos(2*3.1415926*x2))/Size;
		Group[i].fitness=UPPER-(-20*exp(part1)-exp(part2)+20+2.71828);//适应值
		sum+=Group[i].fitness;//计算适应值之和
	}
	for(int mem=0;mem<COLONY_SIZE;mem++)//轮盘赌选择机制里所要求的几个参数
	{
		Group[mem].rfitness=Group[mem].fitness/sum;//适应值的比例
	}
	Group[0].cfitness=Group[0].rfitness;
	for(int mem=1;mem<COLONY_SIZE;mem++)
	{
		Group[mem].cfitness=Group[mem-1].cfitness+Group[mem].rfitness;//模拟轮盘
	}


}
void select()
{
	double p;
	for(int i=0;i<COLONY_SIZE;i++)//挑选出N个个体
	{
		p=random(0,1);//随机产生0到1之间的随机数
		if(p<Group[0].cfitness)
			newGroup[i]=Group[0];
		else
		{
			for(int j=1;j<COLONY_SIZE;j++)//往轮盘后走
			{
				if(p>=Group[j-1].cfitness&&p<Group[j].cfitness)
				{
					newGroup[i]=Group[j];
					break;
				}
			}
		}
	}
	for(int i=0;i<COLONY_SIZE;i++)//从newGroup复制到Group中
		Group[i]=newGroup[i];
}
void crossOver()
{
	int mem,one;
	int first=0;//记录杂交的数目
	double x;
	for(mem=0;mem<COLONY_SIZE;mem++)
	{
		x=random(0,1);
		if(x<OVER)
		{
			++first;
			if(first%2==0)//若为偶数
				xOver(one,mem);
			else 
				one=mem;
		}
	}
}
void xOver(int one,int two)
{
	double point;
	point=random(0,1);
	Group[one].code[0]=Group[one].code[0]*point+Group[two].code[0]*(1-point);
	Group[one].code[1]=Group[one].code[1]*point+Group[two].code[1]*(1-point);
	Group[two].code[0]=Group[one].code[0]*(1-point)+Group[two].code[0]*point;
	Group[two].code[1]=Group[one].code[1]*(1-point)+Group[two].code[1]*point;
}
void mutate()
{
	double x;
	for(int i=0;i<COLONY_SIZE;i++)
	{
		for(int j=0;j<Size;j++)
		{
			x=random(0,1);
			if (x<MUTATE)
			{
				Group[i].code[j]=delta(GenNum,Group[i].code[0],30,-30);
			}
		}
	}
}


double delta(int t,double x,double u,double l)
{
	double temp1;
	double temp2;
	double y;
	double r=random(0,1);
	temp1=pow((1-t/Generation),4);
	temp2=pow(r,temp1);
	int a=(int)random(0,2);
	if(a==0)
	{
		y=u-x;
		return (x+y*(1-temp2));
	}else
	{
		y=x-l;
		return (x-y*(1-temp2));
	}
}

void sort()//排序
{
	Indival temp;
	for(int i=0;i<COLONY_SIZE-1;i++)
	{
		for(int j=i+1;j<COLONY_SIZE;j++)
		{
			if(Group[i].fitness<Group[j].fitness)
			{
				temp=Group[i];
				Group[i]=Group[j];
				Group[j]=temp;
			}
		}
	}
}

