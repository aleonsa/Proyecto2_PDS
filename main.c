#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define N_VI        30
#define VI_MIN      0.0
#define VI_MAX      10.0
#define PI 	        3.14159265358979

#define N           2000
#define MIN_CYCLES  5
#define MAX_CYCLES  30

// #define f       10
// #define fs      1000

void Goertzel(float *x, int len_x, double *y, int klim){
	double vk0,vk1,vk2,AI, AR;
	int k,n;
	for(k=0; k<klim; k++){
		vk0=0;
		vk1=0;
		vk2=0;
		for(n=0;n<len_x;n++){	
			vk0=x[n]+2*cos(2*PI*k/len_x)*vk1-vk2;
			vk2=vk1;
			vk1=vk0;
		}
		AR=vk0+vk1*cos(2*PI*k/len_x);
		AI=vk1*sin(2*PI*k/len_x);
		y[k]= sqrt(AR*AR+AI*AI);
	}
	
}
void normalizeArray(float arr[], int size) {
    // Encontrar el valor absoluto máximo en el arreglo
    int i;
    int j;
    float maxAbsValue = 0.0;
    for (i = 0; i < size; i++) {
        float absValue = fabs(arr[i]);
        if (absValue > maxAbsValue) {
            maxAbsValue = absValue;
        }
    }

    // Normalizar los demás valores en proporción al máximo
    for ( i = 0; i < size; i++) {
        arr[i] /= maxAbsValue;
    }
}

int main()
{
    // Initialize required variables
    int i, j, n;
    float vi[N_VI], w[N_VI], a1[N_VI], k;
    float a2 = 1.0;

    /* *********************Define File Pointers for plotting in GNUPlot*****************/
    FILE *fvco, *fspec, *fvi, *fw;
        fvco = fopen("vco.dat", "w");
        fspec = fopen("spec.dat", "w");
        fvi = fopen("vi.dat", "w");
        fw = fopen("w.dat","w");
    /*************************************************************************************/

    /* **********************Generate Random number for Vi**************************** */
    // Initialize random seed
    srand(time(NULL));

    for (i = 0; i < N_VI; i++)
    {
        vi[i] = ((float)rand() / RAND_MAX) * (VI_MAX - VI_MIN) + VI_MIN;
        fprintf(fvi, "%f\n", vi[i]);
    }
    /* **************************************************************************** */

    /*****************Calculate the frequencies in function of the Vi **********************/
    for (i = 0; i < N_VI; i++)
    {   
        k = (vi[i]/VI_MAX)*(MAX_CYCLES-MIN_CYCLES) + MIN_CYCLES;
        w[i] = (2*PI*k) / N;
        a1[i] = -2*cos(w[i]);
        fprintf(fw, "%f\n", w[i]);
    
    }
    /* **********************Generate VCO using IIR Oscilator**************************** */
    float vco[N_VI*N]; // Array to store VCO values

    // Define IIR coefficients for the "first sine"
    // Generate "first" sinewave
    vco[0] = 0;
    vco[1] = sin(w[0]);
    float vco_temp[N];

    for (n = 2; n < N; n++)
    {
        vco[n] = -a1[0]*vco[n-1] - a2*vco[n-2];
        fprintf(fvco, "%f\n", vco[n]);
    }
    // Generate consequent sinewaves
    for (i = 1; i < N_VI; i++)
    {
        for (j = 0; j < N; j++)
        {
            vco_temp[j] = -a1[i]*vco[(i*N) + j-1] - a2*vco[(i*N) + j-2];
            //fprintf(fspec,"%f\n",vco_temp[j]);
            vco[(i*N) + j] = -a1[i]*vco[(i*N) + j-1] - a2*vco[(i*N) + j-2];
            //fprintf(fvco, "%f\n", vco[(i*N) + j]);
        }
        normalizeArray(vco_temp,N);
        for (j = 0; j < N; j++)
        {
            vco[(i*N)+j] = vco_temp[j];
            fprintf(fvco, "%f\n", vco[(i*N) + j]);
        }
        
        
    }
   double espectro[6000];
    Goertzel(vco,N_VI*N,espectro,6000);
    for (i = 0; i < 6000; i++)
        {
            fprintf(fspec, "%f\n", espectro[i]);
        }

    /***************************************************************************************/

    // Close the file pointers
    fclose(fvco);
    fclose(fspec);
    fclose(fvi);
    fclose(fw);

    system("gnuplot -p main.gp");

    return 0;
}
