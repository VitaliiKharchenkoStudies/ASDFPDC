#include <stdio.h>
#include <omp.h>
#include <math.h>

const double k = 3.0; 
const int max_threads = 12; // Maximum number of threads to test
const int nsteps_values[] = { 40000000, 80000000 }; // Values of nsteps to test
const double analytical_integral = (k / (k + 1)) * (pow(k, k + 1) - pow(-k, k + 1));

double func(double x) {
    return k * pow(x, k);
}

double integrate_trapezoidal(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += func(x);
    }
    sum *= h;
    return sum;
}

double run_parallel(int num_threads, int nsteps) {
    omp_set_num_threads(num_threads); // Set the number of threads
    double t = omp_get_wtime();
    double res = integrate_trapezoidal(func, -k, k, nsteps);
    t = omp_get_wtime() - t;
    return t;
}

int main(int argc, char** argv) {
    printf("Number of Threads\tNsteps\tExecution Time (s)\tSpeedup\n");

    for (int nsteps_index = 0; nsteps_index < 2; nsteps_index++) {
        int nsteps = nsteps_values[nsteps_index];

        double tserial = run_parallel(1, nsteps); // Serial execution time

        for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
            double tparallel = run_parallel(num_threads, nsteps);
            double speedup = tserial / tparallel;
            printf("%d\t\t\t%d\t%.6f\t%.2f\n", num_threads, nsteps, tparallel, speedup);
        }
    }

    return 0;
}
