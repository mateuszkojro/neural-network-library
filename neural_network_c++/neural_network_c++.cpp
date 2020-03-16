#include <iostream>
#include "matrix.h"

int n = 0;

double test(double x) {
    n++;
    return n;
}

int main()
{
    
    double** tab1;
    double** tab2;
    
    int size = 3;
    
    //przygotowanie tablic testowych
    
        

        tab1 = new double* [size];
        tab2 = new double* [size];

        for (int i = 0; i < size; i++)
        {
            tab1[i] = new double[size];
            tab2[i] = new double[size];
        }

/*
        tab1[0][0] = 1; tab1[0][1] = 2; tab1[0][2] = 3;
        tab1[1][0] = 4; tab1[1][1] = 5; tab1[1][2] = 6;
        tab1[2][0] = 7; tab1[2][1] = 8; tab1[2][2] = 9;

        tab2[0][0] = 2;
        tab2[1][0] = 1;
        tab2[2][0] = 3;
*/

        

        tab1[0][0] = 1; tab1[0][1] = 2; tab1[0][2] = 3;
        tab1[1][0] = 1; tab1[1][1] = 2; tab1[1][2] = 3;
        tab1[2][0] = 1; tab1[2][1] = 2; tab1[2][2] = 3;

        tab2[0][0] = 1; tab2[0][1] = 1; tab2[0][2] = 1;
        tab2[1][0] = 2; tab2[1][1] = 1; tab2[1][2] = 2;
        tab2[2][0] = 3; tab2[2][1] = 2; tab2[2][2] = 1;




    

    std::cout << "Hello World!\n";
    // (rozmiar_w_x,rozmiar_w_y)
    matrix x1(size,size),x2(3,size),x3(3,size);

    x1.fill_table(tab1);
    x2.fill_table(tab2);

    x1.show();
    printf("\n");
    x2.show();
    printf("\n");
    x3 = x1 * x2;
    x3.show();

}

//WARRNINGS 
//- nie czyszcze danych z heap