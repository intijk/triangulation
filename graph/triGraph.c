#include <stdio.h>
#include <float.h>
#include <malloc.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include <colorschema.h>
#define max(a,b) ((a) > (b)? (a) : (b))
#define min(a,b) ((a) < (b)? (a) : (b))
#define SCALE (1.2)
#define GRAPH_WIDTH (400)
#define CART_X_TO_GRAPH_X(x)  ((x-minx+(sizex-(maxx-minx))/2)*GRAPH_WIDTH/sizex)
#define CART_Y_TO_GRAPH_Y(y)  (GraphHeight-(y-miny+(sizey-(maxy-miny))/2)*GraphHeight/sizey)


int N;
typedef struct vertex{
	double x,y;
}vertex;
vertex *vlist;
cairo_surface_t *cs;
cairo_t *cr;
double sizex,sizey,GraphHeight,minx,miny,maxx,maxy;

void initDraw(){
	sizex=(maxx-minx)*SCALE;
	sizey=(maxy-miny)*SCALE;
	GraphHeight=GRAPH_WIDTH*sizey/sizex;
	cs=cairo_pdf_surface_create("triangulation.pdf", GRAPH_WIDTH, GraphHeight);
	cr=cairo_create(cs);
	int i;
	for(i=0;i<N;i++){
		vlist[i].x=CART_X_TO_GRAPH_X(vlist[i].x);
		vlist[i].y=CART_Y_TO_GRAPH_Y(vlist[i].y);
	}
}
void finishDraw(){
	cairo_show_page(cr);
	cairo_destroy(cr);
	cairo_surface_flush(cs);
	cairo_surface_destroy(cs);
}


void drawTri(int a,int b,int c){
	printf("draw triangulor on: %d %d %d (%f,%f)(%f,%f)(%f,%f)\n", 
			a,b,c,vlist[a].x,vlist[a].y,vlist[b].x,vlist[b].y,vlist[c].x,vlist[c].y);
	static int currentColor=0;
	cairo_set_source_rgb (cr, pallet[currentColor][0]/255.0, pallet[currentColor][1]/255.0, pallet[currentColor][2]/255.0); 
	currentColor=(currentColor+1)%palletSize;

	cairo_move_to(cr,vlist[a].x,vlist[a].y);
	cairo_line_to(cr,vlist[b].x,vlist[b].y);
	cairo_line_to(cr,vlist[c].x,vlist[c].y);

	cairo_close_path(cr);

	cairo_fill(cr);
}

int main(int argc, const char *argv[])
{
	FILE *fp=fopen("edgeList.txt","r");	
	fscanf(fp, "%d", &N);
	vlist=(vertex*)malloc(sizeof(vertex)*N);
	maxx=DBL_MIN, maxy=DBL_MIN, minx=DBL_MAX, miny=DBL_MAX;
	double x,y;
	int i,j,n,p;
	printf("N=%d\n", N);
	for(i=0;i<N;i++){
		fscanf(fp,"%lf%lf%d", &x, &y, &n);
		printf("x=%f y=%f n=%d\n", x , y, n);
		maxx=max(x,maxx);
		minx=min(x,minx);
		maxy=max(y,maxy);
		miny=min(y,miny);

		vlist[i].x=x;
		vlist[i].y=y;
		for(j=0;j<n;j++){
			fscanf(fp,"%d", &p);
		}
	}
	printf("minx=%f miny=%f maxx=%f maxy=%f\n", minx, miny, maxx, maxy);

	initDraw();
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
	finishDraw();
	return 0;
}
