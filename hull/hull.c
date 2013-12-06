#include <stdio.h>
#include <float.h>
#include <malloc.h>
#define max(a,b) ((a)>(b)? (a): (b))
#define min(a,b) ((a)<(b)? (a): (b))
typedef struct vertex{
	double x,y;
}vertex;
vertex *vlist;
vertex *hlist;
int N;
int p0;
int comp(const void *a, const void *b)
{
	vertex p1,p2;
	p1.x=((vertex*)a)->x-vlist[0].x;
	p1.y=((vertex*)a)->y-vlist[0].y;
	p2.x=((vertex*)b)->x-vlist[0].x;
	p2.y=((vertex*)b)->y-vlist[0].y;
	if(p1.x*p2.y-p1.y*p2.x>0)return -1;
	if(p1.x*p2.y-p1.y*p2.x==0)return 0;
	if(p1.x*p2.y-p1.y*p2.x<0)return 1;
}
int turnNonLeft(vertex p0, vertex p1, vertex p2)
{
	p1.x=p1.x-p0.x;
	p1.y=p1.y-p0.y;
	p2.x=p2.x-p0.x;
	p2.y=p2.y-p0.y;
	double res=p1.x*p2.y-p1.y*p2.x;
	if(res>0) return 0;
	if(res==0 && p2.x >=min(p0.x,p1.x) && p2.x <=max(p0.x,p1.x) &&
			p2.y>=min(p0.y,p1.y) && p2.y<=max(p0.y,p1.y)) return 0;
	return 1;
}
int main(int argc, const char *argv[])
{
	double x, y, miny=DBL_MAX, minp_x=DBL_MAX;
	vlist=(vertex*)malloc(sizeof(vertex));
	int i;
	while(scanf("%lf%lf",&x,&y)==2){
		N++;
		vlist=(vertex*)realloc(vlist, sizeof(vertex)*N);	
		vlist[N-1].x=x,vlist[N-1].y=y;
		if(y<miny || y==miny && x<minp_x)
		{
			p0=N-1;
			miny=y;
			minp_x=x;
		}
	}
	
	vertex tmp=vlist[0];
	vlist[0]=vlist[p0];
	vlist[p0]=tmp;
	/*
	for(i=0;i<N;i++){
		printf("%lf %lf\n", vlist[i].x,vlist[i].y);
	}
	*/
	qsort(vlist+1, N-1, sizeof(vertex), comp);
	/*
	for(i=0;i<N;i++){
		fprintf(stderr, "vlist[%d]=%f %f\n", i, vlist[i].x,vlist[i].y);
	}
	*/
	hlist=(vertex*)malloc(sizeof(vertex)*3);
	hlist[0]=vlist[0];
	hlist[1]=vlist[1];
	hlist[2]=vlist[2];

	int hi=2;
	for(i=3;i<N;i++){
		//fprintf(stderr, "vlist[%d]=%f %f\n", i, vlist[i].x,vlist[i].y);
		if(turnNonLeft(hlist[hi-1],hlist[hi],vlist[i])){ 
			//fprintf(stderr, "right\n");
			hlist[hi]=vlist[i];
			while(turnNonLeft(hlist[hi-2],hlist[hi-1],hlist[hi])){ 
				hi--;
				hlist[hi]=hlist[hi+1];
			}

		}else{
			//fprintf(stderr, "left\n");
			hi++;
			hlist=realloc(hlist,sizeof(vertex)*(hi+1));
			hlist[hi]=vlist[i];
		}
	}
	for(i=0;i<=hi;i++){
		printf("%f %f\n", hlist[i]);
	}

	return 0;
}
