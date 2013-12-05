#include <stdio.h>
#include <float.h>
#include <malloc.h>
#define max(a,b) ((a) > (b)? (a) : (b))
#define min(a,b) ((a) < (b)? (a) : (b))
int N;
typedef struct vertex{
	double x,y;
}vertex;


cairo_surface_t *cs;
void createSurface(double maxx,double maxy,double minx,double miny){
	cs=cairo_pdf_surface_create("triangulation.pdf", SIZEX, SIZEY);
}
void finishPaint(){
	cairo_surface_flush(cs);
	cairo_surface_destroy(cs);
}

void drawTri(int a,int b,int c){
	printf("%d %d %d\n", a,b,c);	
}

int main(int argc, const char *argv[])
{
	FILE *fp=fopen("edgeList.txt","r");	
	fscanf(fp, "%d", &N);
	vertex *vlist=(vertex*)malloc(sizeof(vertex)*N);
	double maxx=DBL_MAX, maxy=DBL_MAX, minx=DBL_MIN, miny=DBL_MIN,x,y;
	int i,j,n,p;
	for(i=0;i<N;i++){
		fscanf(fp,"%lf%lf%d", &x, &y, &n);
		maxx=max(x,maxx);
		minx=min(x,minx);
		maxy=max(y,maxy);
		miny=min(y,miny);

		vlist[i].x=x;
		vlist[i].y=y;
		for(i=0;i<n;i++){
			fscanf(fp,"%d", &p);
		}
	}
	createSurface(maxx,maxy,minx,miny);	
	fseek(fp,0,SEEK_SET);
	fscanf(fp,"%d",&N);
	for(i=0;i<N;i++){
		fscanf(fp,"%lf%lf%d", &x, &y, &n);
		int p1=-1,p2=-1;
		for(j=0;j<n;j++){
			fscanf(fp,"%d",&p);
			if(p>i){
				p1=p2;
				p2=p;
			}
			if(p1>i){
				drawTri(i,p1,p2);
			}
		}
	}
	return 0;
}
