//FCFS SJF 优先级算法

#include <stdio.h>
const int N=10; //进程数

struct PCB{
    char name[10];
    float arrivalTime;
    float serviceTime;
    float startTime;
    float finishTime;
    float turnoverTime;  // 周转时间
    float turnaroundTime;  // 带权周转时间
    int pri;  //优先级
};

void input(PCB *p, int N)
{
    int i;
    for(i = 0; i <= N - 1; i++)
    {
        printf("第%d个进程：",i+1);
        scanf("%s %f %f %d", p[i].name, &p[i].arrivalTime, &p[i].serviceTime, &p[i].pri);
        p[i].startTime = 0;
        p[i].finishTime = 0;
    }
}

void output(PCB *p, int N)
{
    int k;
    printf("执行顺序：\n");
    printf("%s", p[0].name);
    for(k = 1; k < N; k++)
        printf("-->%s", p[k].name);
    printf("\n");
    printf("进程名\t到达时间\t运行时间\t完成时刻\t周转时间\t带权周转时间\n");
    for(k=0;k<N;k++)
     {
         printf("%6s\t%8.2f\t%8.2f\t%8.2f\t%8.2f\t%12.2f\t",p[k].name,p[k].arrivalTime,p[k].serviceTime,p[k].finishTime,p[k].turnoverTime,p[k].turnaroundTime);
         printf("\n");
     }
}

//计算各时间
void calc(PCB *p, int N)
{
    int k;
    for(k = 0; k < N; k++)
    {
        // 第一个进程到达
        if(k == 0)
        {
            p[k].startTime = p[k].arrivalTime;
            p[k].finishTime = p[k].arrivalTime + p[k].serviceTime;
        }
        else
        {
            p[k].startTime = p[k - 1].finishTime;
            p[k].finishTime = p[k].startTime + p[k].serviceTime;
        }
    }
    for(k = 0; k < N; k++)
    {
        // 周转时间 = 完成时间 - 到达时间
        p[k].turnoverTime = p[k].finishTime - p[k].arrivalTime;
        // 带权周转时间 = 周转时间/服务时间
        p[k].turnaroundTime = p[k].turnoverTime/p[k].serviceTime;
    }
}

//FCFS 进程到达时间排序
void FCFS(PCB *p, int N)
{
    int i,j;
    for(i = 1; i < N; i++)
    {
        PCB t = p[i];
        for(j = i - 1; j >= 0 && t.arrivalTime < p[j].arrivalTime; j--)
            p[j+1] = p[j];
        p[j+1] = t;
    }
	calc(p,N);
	printf("\n先来先服务");
	output(p,N);
}


//SJF 短进程优先排序
void SJF(PCB *p,int N)
{
    int i,j;
    for(i = 1; i < N; i++)
    {
        PCB t = p[i];
        for(j = i - 1; j >= 0 && t.serviceTime < p[j].serviceTime; j--)
            p[j+1] = p[j];
        p[j+1] = t;
    }
    calc(p,N);
    printf("\n短作业优先");
    output(p,N);
}

//优先级算法
void priority(PCB *p,int N)
{
    int i,j;
    for(i = 1; i < N; i++)
    {
        PCB t = p[i];
        for(j = i - 1; j >= 0 && t.pri < p[j].pri; j--)
            p[j+1] = p[j];
        p[j+1] = t;
    }
    calc(p,N);
    printf("\n优先级算法");
    output(p,N);
}

int main()
{
    printf("当前进程个数设置为：%d\n请分别输入进程的“名字、到达时间、服务时间、优先级”\n[注]优先级为1-%d，不采用优先级算法则全部输入0\n如:a 8.0 2.0 0\n\n",N,N);
    PCB p[N];
    input(p, N);

    if(p[0].pri==0)
    {
        FCFS(p,N);
        SJF(p,N);
    }
    else
        priority(p,N);
    return 0;
}
