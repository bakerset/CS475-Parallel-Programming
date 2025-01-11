#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

unsigned int seed = 0;

// Constants
const float GRAIN_GROWS_PER_MONTH = 12.0;
const float ONE_DEER_EATS_PER_MONTH = 1.0;
const float ONE_PREDATOR_EATS_PER_MONTH = 0.5;

const float AVG_PRECIP_PER_MONTH = 7.0;   // average
const float AMP_PRECIP_PER_MONTH = 6.0;   // plus or minus
const float RANDOM_PRECIP = 2.0;          // plus or minus noise

const float AVG_TEMP = 60.0;              // average
const float AMP_TEMP = 20.0;              // plus or minus
const float RANDOM_TEMP = 10.0;           // plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

// Global state variables
int NowYear = 2024;
int NowMonth = 0;
float NowPrecip = 0.0;
float NowTemp = 0.0;
float NowHeight = 5.0;  // initial grain height
int NowNumDeer = 2;     // initial number of deer
int NowNumPredators = 1; // initial number of predators

// Barrier variables
omp_lock_t Lock;
volatile int NumInThreadTeam;
volatile int NumAtBarrier;
volatile int NumGone;

// Function prototypes
void InitBarrier(int n);
void WaitBarrier();
float Ranf(float low, float high);
float SQR(float x);
float TempFactor();
float PrecipFactor();
float ComputeNextHeight();
int ComputeNextNumDeer();
int ComputeNextNumPredators();

// Initialize barrier
void InitBarrier(int n) {
    NumInThreadTeam = n;
    NumAtBarrier = 0;
    omp_init_lock(&Lock);
}

// Wait at barrier
void WaitBarrier() {
    omp_set_lock(&Lock);
    {
        NumAtBarrier++;
        if (NumAtBarrier == NumInThreadTeam) {
            NumGone = 0;
            NumAtBarrier = 0;
            while (NumGone != NumInThreadTeam - 1);
            omp_unset_lock(&Lock);
            return;
        }
    }
    omp_unset_lock(&Lock);

    while (NumAtBarrier != 0);
    #pragma omp atomic
    NumGone++;
}

// Generate random number in range [low, high]
float Ranf(float low, float high) {
    float r = (float)rand_r(&seed);  // rand_r() is thread-safe random number generator
    return (low + r * (high - low) / (float)RAND_MAX);
}

// Square function
float SQR(float x) {
    return x * x;
}

// Temperature factor calculation
float TempFactor() {
    return exp(-SQR((NowTemp - MIDTEMP) / 10.0));
}

// Precipitation factor calculation
float PrecipFactor() {
    return exp(-SQR((NowPrecip - MIDPRECIP) / 10.0));
}

// Compute next grain height based on current state
float ComputeNextHeight() {
    float tempFactor = TempFactor();
    float precipFactor = PrecipFactor();
    float nextHeight = NowHeight + tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
    nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
    if (nextHeight < 0.0)
        nextHeight = 0.0;
    return nextHeight;
}

// Compute next number of deer based on current state
int ComputeNextNumDeer() {
    int nextNumDeer = NowNumDeer;
    int carryingCapacity = (int)(NowHeight);
    if (nextNumDeer < carryingCapacity)
        nextNumDeer++;
    else if (nextNumDeer > carryingCapacity)
        nextNumDeer--;
    if (nextNumDeer < 0)
        nextNumDeer = 0;
    return nextNumDeer;
}

// Compute next number of predators based on current state
int ComputeNextNumPredators() {
    int nextNumPredators = NowNumPredators;

    // Determine predator growth based on the deer population
    if (NowNumDeer > 0) {
        nextNumPredators += (NowNumDeer / 5);
    }

    // Decrease predator population based on the available food (grain height)
    if (NowHeight > 0.0) {
        nextNumPredators -= static_cast<int>(ONE_PREDATOR_EATS_PER_MONTH * NowHeight);
    }
    if (nextNumPredators < 0) {
        nextNumPredators = 0;
    }

    return nextNumPredators;
}

int main() {
    omp_set_num_threads(4);
    InitBarrier(4);

    #ifdef _OPENMP
        fprintf(stderr, "OpenMP is supported -- version = %d\n", _OPENMP);
    #else
        fprintf(stderr, "No OpenMP support!\n");
        return 1;
    #endif

    // Set initial number of predators to 1
    NowNumPredators = 1;

    while (NowYear < 2030) {        
        // Compute new temperature and precipitation
        float ang = (30.0 * (float)NowMonth + 15.0) * (M_PI / 180.0);
        float temp = AVG_TEMP - AMP_TEMP * cos(ang);
        NowTemp = temp + Ranf(-RANDOM_TEMP, RANDOM_TEMP);

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
        NowPrecip = precip + Ranf(-RANDOM_PRECIP, RANDOM_PRECIP);
        if (NowPrecip < 0.0)
            NowPrecip = 0.0;

        // Parallel sections
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                // Compute next grain height
                float nextHeight = ComputeNextHeight();
                WaitBarrier();  // DoneComputing barrier
                NowHeight = nextHeight;
                WaitBarrier();  // DoneAssigning barrier
            }

            #pragma omp section
            {
                // Compute next number of deer
                int nextNumDeer = ComputeNextNumDeer();
                WaitBarrier();  // DoneComputing barrier
                NowNumDeer = nextNumDeer;
                WaitBarrier();  // DoneAssigning barrier
            }

            #pragma omp section
            {
                // Compute next number of predators
                int nextNumPredators = ComputeNextNumPredators();
                WaitBarrier();  // DoneComputing barrier
                NowNumPredators = nextNumPredators;
                WaitBarrier();  // DoneAssigning barrier
            }

            #pragma omp section
            {
                // Watcher function to print and increment month
                WaitBarrier();  // DoneComputing barrier
                cout << "Year: " << NowYear << ", Month: " << NowMonth << endl;
                cout << "Temperature: " << ((NowTemp - 32.0) * 5.0 / 9.0) << "°C, Precipitation: " << (NowPrecip * 2.54) << " cm" << endl;
                cout << "Grain Height: " << (NowHeight * 2.54) << " cm, Number of Deer: " << NowNumDeer << ", Number of Predators: " << NowNumPredators << endl;
                NowMonth++;
                if (NowMonth == 12) {
                    NowMonth = 0;
                    NowYear++;
                }
                WaitBarrier();  // DonePrinting barrier
            }
        }
    }

    return 0;
}
