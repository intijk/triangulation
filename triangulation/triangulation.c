#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <float.h>
#include <math.h>
#define min(a,b) ((a)<(b)?(a):(b))
typedef struct vertex{
	double x,y;
	struct vertex *next;
}vertex;
vertex *vlist;
int N;
double *dpstatus;
int *dpind;
typedef struct adjNode{
	int n;
	struct adjNode *next;
}adjNode;

adjNode **adjList;

void insertEdge(int a, int b){
	adjNode *np=(adjNode*)malloc(sizeof(adjNode)), *npt;
	np->n=b;
	np->next=NULL;
	if(adjList[a]==NULL) adjList[a]=np;
	else{
		int existed=0;
		npt=adjList[a];
		while(1){
			if(npt->n==b){
			   existed=1;
			   break;
			}
			if(npt->next==NULL){
				break;
			}
			npt=npt->next;
		}
		if(!existed){
			npt->next=np;
		}else{
			free(np);
		}
	}
}
void recordEdge(int a, int b){
	if(a<0 || b<0 || a==b) return;
	if(adjList==NULL){
		adjList=(adjNode**)malloc(sizeof(adjNode*)*N);
		memset(adjList,0,sizeof(adjNode*)*N);
	}
	insertEdge(a,b);
	insertEdge(b,a);
}
double cdis(int a, int b){
	if((a+1)%N==b)return 0;
	if((b+1)%N==a)return 0;
	return sqrt((vlist[a].x-vlist[b].x)*(vlist[a].x-vlist[b].x)+(vlist[a].y-vlist[b].y)*(vlist[a].y-vlist[b].y));

}
double dps(int s, int n){
	return dpstatus[s*(N+1)+n];
}
void setdps(int s,int n,double mindis){
	if(dps(s,n)<0.1){
		dpstatus[s*(N+1)+n]=mindis;
	}else{
		printf("Status rewrite! Should not be here\n");
		exit(-1);
	}
}
void setdpind(int s, int n, int mini){
	dpind[s*(N+1)+n]=mini;
}
int getdpind(int s, int n){
	return dpind[s*(N+1)+n];
}

double dp(int s, int n){
	if(n<=3)return 0;
	double mindis=DBL_MAX;
	int mini=-1;
	if(dps(s,n)>0.0000001){
		return dps(s,n);
	}
	int k;
	for(k=1;k<=n-2;k++){
		double currentdis=cdis(s,(s+k)%N)+cdis((s+k)%N,(s+n-1)%N)+dp(s,k+1)+dp((s+k)%N,n-k);
		if(mindis>currentdis){
			mini=k;
			mindis=currentdis;
		}
	}
	setdpind(s,n,mini);
	setdps(s,n,mindis);
	return mindis;
}
void recurRecordEdge(int s,int n){
	printf("s=%d n=%d\n", s, n);
	if(n<=3)return ;
	int mini=getdpind(s,n);
	recordEdge(s, (s+mini)%N);
	recordEdge((s+mini)%N, (s+n-1)%N);

	recurRecordEdge(s,mini+1);
	recurRecordEdge((s+mini)%N, n-mini);
}
int compf(const void *p1, const void *p2){
	return (*((int*)p1))-(*((int*)p2));
}
void outputEdge()
{
	printf("%d\n", N);
	int *sortSpace=(int*)malloc(sizeof(int)*N);
	adjNode *npt;
	int i,j,c;
	for(i=0;i<N;i++){
		c=0;
		npt=adjList[i];
		while(npt!=NULL){
			sortSpace[c++]=npt->n;
			npt=npt->next;
		}
		qsort(sortSpace,c,sizeof(int),compf);
		printf("%f %f ", vlist[i].x,vlist[i].y);
		printf("%d%s",c,c==0?"\n":" ");
		for(j=0;j<c;j++){
			printf("%d%s",sortSpace[j], j==c-1?"\n":" "); 
		}
	}
}
int main(int argc, const char *argv[])
{
	double x,y;

	vertex *last;
	scanf("%lf%lf", &x,&y);
	last=vlist=(vertex*)malloc(sizeof(vertex));
	vlist->x=x;
	vlist->y=y;
	vlist->next=NULL;
	N=1;

	while(scanf("%lf%lf", &x,&y)==2){
		vertex *v=(vertex*)malloc(sizeof(vertex));
		v->x=x,v->y=y;
		v->next=NULL;
		last->next=v;
		last=v;
		N++;
	}


	last=vlist;
	vlist=(vertex*)malloc(sizeof(vertex)*N);
	memset(vlist,0,sizeof(vertex)*N);
	vertex *llast;
	int i=0;
	while(last){
		llast=last;
		vlist[i].x=last->x;
		vlist[i].y=last->y;
		last=last->next;
		free(llast);
		i++;
	}

	for(i=0;i<N;i++){
		recordEdge(i,(i+1)%N);
	}
	dpstatus=(double*)malloc(sizeof(double)*(N+1)*N);
	dpind=(int*)malloc(sizeof(int)*(N+1)*N);
	memset(dpstatus,0,sizeof(double)*(N+1)*N);
	memset(dpind,0,sizeof(int)*(N+1)*N);
	printf("%f\n",dp(0, N));

	recurRecordEdge(0,N);	

	outputEdge();

	return 0;
}
