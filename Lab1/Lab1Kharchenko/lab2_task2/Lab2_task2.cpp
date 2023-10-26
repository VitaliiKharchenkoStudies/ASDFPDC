#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <math.h>

const double k = 3.0;
const int nsteps = 40000000;

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

double run_serial() {
	double t = omp_get_wtime();
	double res = integrate_trapezoidal(func, -k, k, nsteps);
	t = omp_get_wtime() - t;
	std::cout << "Result (serial): " << res << " analytical value: " << (k / (k + 1)) * (pow(3, k + 1) - pow(-3, k + 1)) << " error: " << res - ((k / (k + 1)) * (pow(3, k + 1) - pow(-3, k + 1))) << std::endl;
	return t;
}

int main(int argc, char** argv) {
	printf("Integration y(x) = k * x^k on [-3.00, 3.00], nsteps = %d\n", nsteps);
	double tserial = run_serial();
	printf("Execution time (serial): %.6f\n", tserial);
	return 0;
}
