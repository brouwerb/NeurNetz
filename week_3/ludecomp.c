#include <stdio.h>

void printmatrix(int len, double mat[len][len]){
    for(int i = 0; i<len; i++){
        for (int j = 0; j < len; j++)
        {
            printf("%6.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

void multiply(int len, double mat1[len][len], double mat2[len][len], double res[len][len]){
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            double sum = 0;
            for (int k = 0; k < len; k++)
            {
                sum += mat1[i][k]*mat2[k][j];
            }
            res[i][j] = sum;
        }
        
    }
}

void printVector(const int N, double x[]){
	int i;
	printf("(");
	for(i=0; i<N; ++i){
		printf(" % 8.4f", x[i]);
		if(i != N-1) printf(",");
	}
	printf(" )\n\n");
}

void decomp(int len, double mat[len][len], double lu[len][len]){
    double temp;
    for (int k = 0; k < len; k++)
    {
        for (int i = 0; i < len; i++)
        {
            temp = lu[i][k] /= lu[k][k];
            for (int j = 0; j < len; j++)
            {
                lu[i][j] -= temp*lu[k][j];
            }
            
        }
        
    }
    
}

int main(){

	double x[3];

	double A[][3] = {{4, 3, -2}, {-1, -1, 3}, {2, -1, 5}};
    double LU[3][3];
	const double b[] = {9, -4, 6};
	decomp(3, A, LU);
	printmatrix(3, LU);
	// printVector(3, x);

	// double B[][3] = {{0, 3, -2}, {-1, -1, 3}, {2, -1, 5}};
	// const double c[] = {-7, -4, 6};
	// // TODO: implement your solver
	// printmatrix(3, 3, B);
	// printVector(3, x);


	return 0;
}
