#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#ifndef DEBUG
#define DEBUG	false
#endif

#ifndef NUMT
#define NUMT	2
#endif

#ifndef NUMTRIALS
#define NUMTRIALS	50000
#endif

#define NUMTIMES	1
#define GRAVITY		32.2f

const float BEFOREY = 80.f;
const float AFTERY = 20.f;
const float DISTX = 70.f;
const float RADIUS = 3.f;

const float BEFOREYDY = 5.f;
const float AFTERYDY = 1.f;
const float DISTXDX = 5.f;

float BeforeY[NUMTRIALS];
float AfterY[NUMTRIALS];
float DistX[NUMTRIALS];

float Ranf(float low, float high) {
    float r = (float)rand();               // 0 - RAND_MAX
    float t = r / (float)RAND_MAX;         // 0. - 1.

    return low + t * (high - low);
}

void TimeOfDaySeed() {
    struct tm y2k = { 0 };
    y2k.tm_hour = 0; y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time_t timer;
    time(&timer);
    double seconds = difftime(timer, mktime(&y2k));
    unsigned int seed = (unsigned int)(1000. * seconds);    // milliseconds
    srand(seed);
}

int main(int argc, char* argv[]) {

#ifdef _OPENMP
    fprintf(stderr, "OpenMP is supported -- version = %d\n", _OPENMP);
#else
    fprintf(stderr, "No OpenMP support!\n");
    return 1;
#endif

    TimeOfDaySeed();               // seed the random number generator

    omp_set_num_threads(NUMT);    // set the number of threads to use in parallelizing the for-loop

    FILE* outFile = fopen("results.csv", "a"); // Open CSV file for appending
    if (outFile == NULL) {
        perror("Error: Unable to open output file");
        return 1;
    }

    // Lock file to ensure only one thread writes the header
    #pragma omp critical
    {
        // Check if the file is empty (assuming fseek works)
        fseek(outFile, 0, SEEK_END);
        long fileSize = ftell(outFile);

        if (fileSize == 0) {
            fprintf(outFile, "NUMT,NUMTRIALS,Probability (%),MegaTrials/sec\n");
        }
    }

    for( int n = 0; n < NUMTRIALS; n++ )
    {
        BeforeY[n] = Ranf(  BEFOREY - BEFOREYDY, BEFOREY + BEFOREYDY );
        AfterY[n]  = Ranf(  AFTERY - AFTERYDY, AFTERY + AFTERYDY );
        DistX[n]   = Ranf(  DISTX - DISTXDX, DISTX + DISTXDX );
    }

    double maxPerformance = 0.;
    int numSuccesses;


    for (int times = 0; times < NUMTIMES; times++) {
        double time0 = omp_get_wtime();

        numSuccesses = 0;

    #pragma omp parallel for default(none) shared(BeforeY, AfterY, DistX) reduction(+:numSuccesses)
        for (int n = 0; n < NUMTRIALS; n++) {
            float beforey = BeforeY[n];
            float aftery = AfterY[n];
            float distx = DistX[n];

            // Calculate vx (horizontal velocity)
            //(distx / aftery) *
            float vx =  sqrtf(2.0 * GRAVITY * (beforey - aftery));

            // Calculate t (time to reach the ground)
            //beforey - 
            float t = sqrtf(2.0 * (aftery) / GRAVITY);

            // Calculate dx (horizontal distance traveled)
            float dx = vx * t;

            // Check if the ball lands in the cup
            if (fabsf(dx - distx) <= RADIUS)
                numSuccesses++;
        }

        double time1 = omp_get_wtime();
        double megaTrialsPerSecond = (double)NUMTRIALS / (time1 - time0) / 1000000.;

        if (megaTrialsPerSecond > maxPerformance)
            maxPerformance = megaTrialsPerSecond;

        float probability = (float)numSuccesses / (float)NUMTRIALS;

        // Append results to CSV file
        fprintf(outFile, "%d,%d,%.2f,%.2f\n", NUMT, NUMTRIALS, 100.0 * probability, maxPerformance);
    }

    fclose(outFile); // Close CSV file

    //Speedup = (Peak performance for 8 threads) / (Peak performance for 1 thread)
    double speedup = (107.27/51.7);
    printf("Speedup: %lf\n", speedup);

    //Parallel Function
    float Fp = (4. / 3.) * (1. - (1. / speedup));
    printf("Parallel Function: %lf\n", Fp);

    return 0;
}
