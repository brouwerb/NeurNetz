#include <stdio.h>

void printmatrix(int len, double mat[len][len]){
    for(int i = 0; i<len; i++){
        printf("| ");
        for (int j = 0; j < len; j++)
        {
            printf("%6.2f ", mat[i][j]);
        }
        printf(" |\n");
    }
    printf("\n");
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

void decomp(int len, double lu[len][len]){
    for (int k = 0; k < len; k++)
    {
        for (int i = k + 1; i < len; i++)
        {
            double temp = lu[i][k] /= lu[k][k];
            for (int j = k+1; j < len; j++)
            {
                lu[i][j] -= temp*lu[k][j];
                // printf("%6.2f \n", temp);
            }
            
        }
        
    }
    
}

void extract(int len, double LU[len][len], double L[len][len], double U[len][len]){
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            L[i][j] = LU[i][j];
        }
        L[i][i] = 1;
        for (int j = i; j < len; j++)
        {
            U[i][j] = LU[i][j];
        }
        
        
    }

    
}

void solve(int len, double L[len][len], double U[len][len], double b[len], double x[len]){
    double y[len];
    for (int i = 0; i < len; i++)
    {
        double sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += L[i][j]*y[j];
        }
        y[i] = b[i] - sum;
    }
    for (int i = len-1; i >= 0; i--)
    {
        double sum = 0;
        for (int j = i+1; j < len; j++)
        {
            sum += U[i][j]*x[j];
        }
        x[i] = (y[i] - sum)/U[i][i];
    }
    
}

void copy(int len, double A[len][len], double B[len][len]){
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            B[i][j] = A[i][j];
        }
        
    }
    
}

int check(int len, double A[len][len], double L[len][len], double U[len][len]){
    double res[len][len];
    multiply(len, L, U, res);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (res[i][j] != A[i][j])
            {
                return 0;
            }
            
        }
        
    }
    return 1;
    
}
void fillzero(int len, double A[len][len]){
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            A[i][j] = 0;
        }
        
    }
    
}

void calculate(int len, double A[len][len], double b[len], double x[len]){
    printf("Matrix: \n");
    printmatrix(len, A);
    double LU[len][len];
    copy(len, A, LU);
    decomp(len, LU);
    double L[len][len];
    double U[len][len];
    double D[len][len];
    fillzero(len, D);
    fillzero(len, L);
    fillzero(len, U);
    extract(len, LU, L, U);
    printf("L: \n");
    printmatrix(len, L);
    printf("U: \n");
    printmatrix(len, U);
    multiply(len, L, U, D);
    printf("D: \n");
    printmatrix(len, D);
    printf("%i", check(len, A, L, U));
    if(check(len, A, L, U)){
        printf("L:\n");
        printmatrix(len, L);
        printf("U:\n");
        printmatrix(len, U);
        solve(len, L, U, b, x);
        printVector(len, x);
    }
    else{
        printf("Error");
    }

}


int main(){

	double x[3];

	double A[3][3] = {{4, 3, -2}, {-1, -1, 3}, {2, -1, 5}};

	double b[] = {9, -4, 6};
    calculate(3, A, b, x);

	double B[3][3] = {{0, 3, -2}, {-1, -1, 3}, {2, -1, 5}};
	double c[3] = {-7, -4, 6};
    calculate(3, B, c, x);

	return 0;
}
