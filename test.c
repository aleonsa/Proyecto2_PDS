#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define N_VI        1
#define VI_MIN      0.0
#define VI_MAX      10.0
#define PI          3.14159265358979

#define N           400
#define MIN_CYCLES   5
#define MAX_CYCLES   30

int main()
{
    // Initialize required variables
    uint8_t i, j, n;
    float a1 = 0;
    float a2 = 1.0;

    /* *********************Define File Pointers for plotting in GNUPlot*****************/
    FILE *fvco, *fspec, *fvi, *fw;
    fvco = fopen("vco.dat", "w");
    fspec = fopen("spec.dat", "w");
    fvi = fopen("vi.dat", "w");
    fw = fopen("w.dat","w");
    /*************************************************************************************/

    /* **********************Generate VCO using IIR Oscilator**************************** */
    float vco[400]; // Array to store VCO values

    // Define IIR coefficients

    float w1 = 0.8077;
    vco[0] = 0;
    vco[1] = sin(w1);
    a1 = -2*cos(w1);

    for (n = 2; n < 200; n++)
    {
        vco[n] = -a1*vco[n-1] - a2*vco[n-2];
        fprintf(fvco, "%f\n", vco[n]);
    }

    float w2 = 0.0968;
    a1 = -2*cos(w2);
    for (n = 0; n < 200; n++)
    {
        vco[n+200] = -a1*vco[n+200-1] - a2*vco[n+200-2];
        fprintf(fvco, "%f\n", vco[n+200]);
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
