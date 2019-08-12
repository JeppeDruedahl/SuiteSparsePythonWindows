//////////////
// INCLUDES //
//////////////

#include <windows.h>
#include <stdio.h>
#include <omp.h>
#include "cholmod.h"

#define EXPORT extern "C" __declspec(dllexport)


///////////////
// FUNCTIONS //
///////////////

void _example(double *diag, double *result){

	FILE* log_file;
	fopen_s(&log_file, "log.txt", "a");

	// a. start cholmod
	cholmod_common c;
	cholmod_start (&c); 

	// b. create matrix
	size_t nrow = 3;
	size_t ncol = 3;
	size_t nzmax = 5;
	int sorted = 1;
	int packed = 1;
	int stype = 1; // = symmetric
	int xtype = CHOLMOD_REAL;
	
	cholmod_sparse *A = cholmod_allocate_sparse(nrow, ncol, nzmax, sorted, packed, stype, xtype, &c);

	// c. fill matrix
	
		// column 1
		((int*)A->p)[0] = 0; // after # elements
		((int*)A->i)[0] = 0; // row 1
		((double*)A->x)[0] = diag[0]; // value 1

		// column 2
		((int*)A->p)[1] = 1; // after # elements
		((int*)A->i)[1] = 0; // row 1
		((int*)A->i)[2] = 1; // row 2
		((double*)A->x)[1] = -1.0; // value 1
		((double*)A->x)[2] = diag[1]; // value 2

		// column 2
		((int*)A->p)[2] = 3; // after # elements
		((int*)A->i)[3] = 1; // row 1
		((int*)A->i)[4] = 2; // row 2
		((double*)A->x)[3] = -1.0; // value 1
		((double*)A->x)[4] = diag[2]; // value 2
		
		((int*)A->p)[3] = 5; // total # elements

	// c. write matrix to screen
	fprintf(log_file,"\n");
	cholmod_write_sparse(log_file, A, NULL, NULL, &c);
	fprintf(log_file,"\n");

	// d. do cholesky decomposition
	cholmod_factor *L = cholmod_analyze(A, &c);
	cholmod_factorize(A, L, &c);

	// e. solve matrix equation
	cholmod_dense *b = cholmod_ones(A->nrow, 1, A->xtype, &c); 
	cholmod_dense *x = cholmod_solve(CHOLMOD_A, L, b, &c);

	// f. print solution
	fprintf(log_file,"x:\n");
	for(int i = 0; i < x->nzmax; i ++){
		fprintf(log_file,"%d: %g\n",i,((double*)x->x)[i]);
		result[i] = ((double*)x->x)[i];
	}

	// g. clean up
	cholmod_free_factor(&L, &c);
	cholmod_free_sparse(&A, &c);
	cholmod_free_dense(&x, &c);
	cholmod_free_dense(&b, &c);
	cholmod_finish(&c);
	
	fclose(log_file);

}


////////////
// EXPORT //
////////////

EXPORT void run(double *diag, double *result) {

	// a. new log-file 
	FILE* log_file;
	fopen_s(&log_file, "log.txt", "w");
    fclose(log_file);

	// b. run example
	_example(diag, result);

	// c. openmp test
	fopen_s(&log_file, "log.txt", "a");
	fprintf(log_file,"\nomp_get_num_procs() = %d\n",omp_get_num_procs());
    fclose(log_file);
	
	#pragma omp parallel
    {

		#pragma omp critical
		{
		FILE* log_file; 
		fopen_s(&log_file,"log.txt", "a");
		fprintf(log_file,"omp_get_thread_num() = %d\n",omp_get_thread_num());
		fclose(log_file);
		}

    } // omp parallel

}

EXPORT void setup_omp() {
	SetEnvironmentVariable("OMP_WAIT_POLICY", "passive");
}


//////////
// MAIN //
//////////


// when running from .exe
int main (void) { 
	
	FILE* log_file;
	fopen_s(&log_file, "log.txt", "w");
    	fclose(log_file);
	
	double *diag = new double[3];
	double *x = new double[3];

	diag[0] = 1.5;
	diag[1] = 2.5;
	diag[2] = 3.5;

	_example(diag,x);

	delete[] diag;
	delete[] x;

	return 0; 
	
}
