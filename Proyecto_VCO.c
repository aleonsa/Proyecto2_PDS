#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 5000
#define N 10
#define pi 3.14159265
#define A 50

void main(){
	int i,j, rango = 10, f;
	int x[N] = {};
	float vco[M] = {};
	float wo ;
	float a1 ;
	float ang,ang2,wn;
	int a2 = 1;
	float b0 = sin(wo);
	for (i = 0; i < N; i++)
	{
		x[i]= (int)(rand()%rango+1);
		//printf("%d \n",x[i]);
	}
	
	wo = (2*pi*x[0])/M;
	a1 = 2*cos(wo);
	
	FILE *fiir;
	fiir = fopen("vco.dat", "w");
	
	/*
	vco[0] = a1*(A*sin(wo)); //y[-2]=0 y[-1] = (-A*sin(wo))
	fprintf(fiir, "%6.4f\n", vco[0]);
	vco[1] = a1*vco[0] - a2*(A*sin(wo));
	fprintf(fiir, "%6.4f\n", vco[1]);
	f = 2;
	for (i = 0; i < N; i++){
		wo = (2*pi*x[i])/M;
		a1 = 2*cos(wo);
		vco[f-1] = A*sin(wo*(f-1));
		vco[f-2] = A*sin(wo*(f-2));
		for(j=0; j<M/N; j++){
		vco[f] = a1*vco[f-1] - a2*vco[f-2];
		fprintf(fiir, "%6.4f\n", vco[f]);
		f++;
		}
	}
	*/
	vco[0] = A*sin(wo);
	f = 1;
	wn = wo;
	for (i = 0; i < N; i++){
		wo = (2*pi*x[i])/M;
		a1 = 2*cos(wo);
		vco[f] = vco[f-1]*cos(wo)+A*cos(wn)*sin(wo);
		fprintf(fiir, "%6.4f\n", vco[f]);
		wn = wn + wo;
		f++;
		for(j=0; j<M/N; j++){
		wn = wn + wo;
		vco[f] = a1*vco[f-1] - vco[f-2];
		fprintf(fiir, "%6.4f\n", vco[f]);
		f++;
		}
	}
	
	
	fclose(fiir);
	//system("gnuplot -p graf_senal.gp");
	
}
