#include <stdio.h>
#include <float.h>
#include <malloc.h>
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
	p1.x=((vertex*)a)->x-vlist[p0].x;
	p1.y=((vertex*)a)->y-vlist[p0].y;
	p2.x=((vertex*)b)->x-vlist[p0].x;
	p2.y=((vertex*)b)->y-vlist[p0].y;
	return  p1.x*p2.y-p1.y*p2.x;
}
int turnNonLeft(vertex p0, vertex p1, vertex p2)
{
	p1.x=p1.x-p0.x;
	p1.y=p1.y-p0.y;
	p2.x=p2.x-p0.x;
	p2.y=p2.y-p0.y;
	double res=p1.x*p2.y-p1.y*p2.x;
	if(res>0) return 1;
	if(res==0 && p2.x>p1.x || p2.y>p1.y) return 1;
	return 0;
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
	hlist=(vertex*)malloc(sizeof(vertex)*3);
	hlist[0]=vlist[0];	
	hlist[1]=vlist[1];	
	hlist[2]=vlist[2];	

	int hi=2;
	for(i=3;i<N;i++){
		if(turnNonLeft(hlist[hi-1],hlist[hi],vlist[i])){ 
			hlist[hi]=vlist[i];
		}else{
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
