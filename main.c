#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define N_VI        2
#define VI_MIN      0.0
#define VI_MAX      10.0
#define PI 	        3.14159265358979

#define N           200
#define MIN_CYCLES  5
#define MAX_CYCLES  30

// #define f       10
// #define fs      1000

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

    for (n = 2; n < N; n++)
    {
        vco[n] = -a1[0]*vco[n-1] - a2*vco[n-2];
        fprintf(fvco, "%f\n", vco[n]);
    }
    // Generate consequent sinewaves
    for (int i = 1; i < N_VI; i++)
    {
        for (int j = 0; j < N; j++)
        {
            vco[(i*N) + j] = -a1[i]*vco[(i*N) + j-1] - a2*vco[(i*N) + j-2];
            fprintf(fvco, "%f\n", vco[(i*N) + j]);
        }
        
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