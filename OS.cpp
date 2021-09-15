#include<stdio.h>
#include<stdlib.h>
void clrscr()
{
system("@cls||clear");
}
struct proc
{
int id;
int bt;
int rem;
int wait;
int turnaround;
};
void sort(struct proc p[],int n)
{
int i=0,j=0;
struct proc temp;
for (i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
if ( p[j].bt<p[i].bt )
{
temp=p[j];
p[j]=p[i];
p[i]=temp;
}
}
}
void allocate(struct proc bt[],int n,struct proc sev1[],struct proc sev2[],struct proc sev3[])
{
int i,j;
for(j=0;j<n/3;j++)
{
sev1[j]=bt[j];
}
for (j=n/3;j<2*n/3;j++)
sev2[j-n/3]=bt[j];
for (j=2*(n/3);j<n;j++)
sev3[j-2*(n/3)]=bt[j];
}
void runSeverRR(int n,int quant,struct proc sev[])
{
int i,j,total=0,count=n;
float avgtat=0.0,avgwait=0.0;
printf("\t\nRunning processes using Round Robin");
printf("\nProcess | wait time | TurnAround Time");
while(count)
{
for (i=0;i<n;i++)
{
if (sev[i].rem!=0)
{
if (sev[i].rem-quant>0)
{
total=total+quant;
sev[i].rem=sev[i].rem-quant;
}
else
{
total=total+sev[i].rem;
sev[i].rem=0;
count--;
sev[i].turnaround=total;
sev[i].wait=total-sev[i].bt;
printf("\nP%d | %d | %d ",sev[i].id,sev[i].wait,sev[i].turnaround);
}
}
}
}
for(int i=0;i<n;i++)
{
avgtat=avgtat+1.0*sev[i].turnaround;
avgwait= avgwait +1.0*sev[i].wait;
}
avgtat=avgtat/(1.0*n);
avgwait=avgwait/(1.0*n);
printf("\n\nThe average turn around time of the processes is : %f",avgtat);
printf("\n\nThe average waiting time of the processes is : %f\n",avgwait);
}
void runSeverDRR(int n,struct proc sev[])
{
int i,j,total=0,count=n;
float avgtat=0,avgwait=0;
int quant=0;
int flag=1;
printf("\t\nRunning processes using Dynamic Round Robin");
printf("\nProcess | wait time | TurnAround Time");
while(count)
{
if (flag)
{
for (i=0;i<n;i++)
{
quant=quant+sev[i].rem;
}
quant=quant/count;
flag= 0;
}
for (i=0;i<n;i++)
{
if (sev[i].rem!=0)
{
if (sev[i].rem-quant>0)
{
total=total+quant;
sev[i].rem=sev[i].rem-quant;
}
else
{
total=total+sev[i].rem;
sev[i].rem=0;
count--;
sev[i].turnaround=total;
sev[i].wait=total-sev[i].bt;
printf("\nP%d | %d | %d ",sev[i].id,sev[i].wait,sev[i].turnaround);
flag=1;
}
}
}
}
for(int i=0;i<n;i++)
{
avgtat=avgtat+sev[i].turnaround;
avgwait= avgwait +sev[i].wait;
}
avgtat=avgtat/(1.0*n);
avgwait=avgwait/(1.0*n);
printf("\n\nThe average turn around time of the processes is : %f",avgtat);
printf("\n\nThe average waiting time of the processes is : %f\n",avgwait);
}
void compalgo(int n,struct proc sev[],float tat[],float awt[],int quant)
{
int i,j,total=0,count=n;
float avgtat=0,avgwait=0;
while(count)
{
for (i=0;i<n;i++)
{
if (sev[i].rem!=0)
{
if (sev[i].rem-quant>0)
{
total=total+quant;
sev[i].rem=sev[i].rem-quant;
}
else
{
total=total+sev[i].rem;
sev[i].rem=0;
count--;
sev[i].turnaround=total;
sev[i].wait=total-sev[i].bt;
}
}
}
}
for(int i=0;i<n;i++)
{
avgtat=avgtat+sev[i].turnaround;
avgwait= avgwait +sev[i].wait;
}
avgtat=avgtat/(1.0*n);
avgwait=avgwait/(1.0*n);
tat[0]=avgtat;
awt[0]=avgwait;
for (i=0;i<n;i++)
{
sev[i].rem=sev[i].bt;
}
avgtat=0.0;
avgwait=0.0;
total=0;
count=n;
quant=0;
int flag=1;
while(count)
{
if (flag)
{
for (i=0;i<n;i++)
{
quant=quant+sev[i].rem;
}
quant=quant/count;
flag= 0;
}
for (i=0;i<n;i++)
{
if (sev[i].rem!=0)
{
if (sev[i].rem-quant>0)
{
total=total+quant;
sev[i].rem=sev[i].rem-quant;
}
else
{
total=total+sev[i].rem;
sev[i].rem=0;
count--;
sev[i].turnaround=total;
sev[i].wait=total-sev[i].bt;
flag=1;
}
}
}
}
for(int i=0;i<n;i++)
{
avgtat=avgtat+sev[i].turnaround;
avgwait= avgwait +sev[i].wait;
}
avgtat=avgtat/(1.0*n);
avgwait=avgwait/(1.0*n);
tat[1]=avgtat;
awt[1]=avgwait;
for (i=0;i<n;i++)
{
sev[i].rem=sev[i].bt;
}
}
int main()
{
int s=0;
printf("\n \t\t\t\t ROUND ROBIN CPU SCHEDULING WITH DYNAMIC QUANTUM TIME\n ");
for(s=0;s<1000000000;s++);
clrscr();
int n,tempN,i,ip=0,tquant;
printf("\t\tWelcome to the Project on Comparison between Round Robin And Dynamic Round Robin Algorithm\n");
printf("\nEnter the number of processes you want to insert: ");
scanf("%d",&n);
clrscr();
struct proc process[n];
for (i=0;i<n;i++)
{
printf("\nEnter the Burst Time process: ");
scanf("%d",&process[i].bt);
process[i].rem=process[i].bt;
process[i].id=i;
process[i].wait=0;
process[i].turnaround=0;
}
sort(process,n);
struct proc sev1[n/3],sev2[2*(n/3)],sev3[n-2*(n/3)];
allocate(process,n,sev1,sev2,sev3);
clrscr();
while(ip!=7)
{
printf("\nEnter the operation you want to perform");
printf("\n1. Run server 1");
printf("\n2. Run server 2");
printf("\n3. Run server 3");
printf("\n4. Run All servers ");
printf("\n5. exit");
printf("\nenter you choice: ");
scanf("%d",&ip);
if (ip==1)
{
printf("\nEnter the time quantum for the server: ");
scanf("%d",&tquant);
clrscr();
printf("\nRunning server 1");
runSeverRR(n/3,tquant,sev1);
allocate(process,n,sev1,sev2,sev3);
runSeverDRR(n/3,sev1);
for(s=0;s<2000000000;s++);
clrscr();
}
else if (ip==2)
{
printf("\nEnter the time quantum for the server: ");
scanf("%d",&tquant);
clrscr();
printf("\nRunning server 2");
runSeverRR(n/3,tquant,sev2);
allocate(process,n,sev1,sev2,sev3);
runSeverDRR(n/3,sev2);
for(s=0;s<2000000000;s++);
clrscr();
}
else if (ip==3)
{
printf("\nEnter the time quantum for the server: ");
scanf("%d",&tquant);
clrscr();
printf("\nRunning server 3");
runSeverRR(n-2*(n/3),tquant,sev3);
allocate(process,n,sev1,sev2,sev3);
runSeverDRR(n-2*(n/3),sev3);
for(s=0;s<2000000000;s++);
clrscr();
}
else if (ip==4)
{
float tat[2],awt[2];
printf("\nEnter the time quantum for the server: ");
scanf("%d",&tquant);
clrscr();
compalgo(n,process,tat,awt,tquant);
printf("\n Comparison between the algorithms ");
printf("\nThe average Turn Around Time of Round robin is : %f",tat[0]);
printf("\nThe average Turn Around Time of Dynamic Round robin is : %f",tat[1]);
printf("\nThe average Waiting Time of the Round Robin is : %f",awt[0]);
printf("\nThe average Waiting Time of the Dynamic Round Robin is : %f",awt[1]);
for(s=0;s<2000000000;s++);
clrscr();
}
else
ip=7;
}
return 0;
}

