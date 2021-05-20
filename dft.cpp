#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <array>
#include <algorithm>
#include <functional>
#include <complex>

using namespace std;


int main() {
    vector <vector <double>> given_array = {    
        {3,2,1},
        {6,5,4},
        {9,8,7}};
    
    double output_array[3][3];      
    int width=3;    
    int height=3;

    complex <double> **dft_array = new complex <double>*[width];   
    for (int b=0;b<width;b++){                      
        dft_array[b]= new complex <double>[height];    
    }

    complex<double> sum=0; 
    complex<double> sum2=0; 
    double pi = 3.141592653589793;

    for (int i=0; i<3; i++){    
        for (int j=0; j<3; j++){
            complex<double> cplx(given_array[i][j], 0);
            dft_array[i][j]=cplx;   
        }   
    }
    cout << "\nOut of the 1D DFT of Row\n";

    for (int x=0; x<3; x++){    
        sum=0;
        for (int y=0; y<3; y++){
            sum+=(dft_array[x][y].real())*cos((2*pi*x*y)/3)-(dft_array[x][y].imag())*sin((2*pi*x*y)/3);
            cout<<sum<<" ";
            dft_array[x][y]=sum;
        }
    }
    
    cout << "\n\nOut of the 1D DFT of Column\n";
    
    for (int x=0; x<3; x++){   
        sum2=0;
        for (int y=0; y<3; y++){
            sum2+=(dft_array[y][x].real())*cos((2*pi*x*y)/3)-(dft_array[y][x].imag())*sin((2*pi*x*y)/3);
            cout<<sum2<<" ";
            dft_array[y][x]=sum2;
        }
    }
    
    cout << "\n\nResults:\n";

    for (int i=0; i<3; i++){   
        for (int j=0; j<3; j++){
        output_array[i][j]=dft_array[i][j].real();
        }
    }    
   
    for ( int i = 0; i < 3; i++ ){ 
        for ( int j = 0; j < 3; j++ ) {      
        cout << "output_array[" << i << "][" << j << "]: ";
        cout << output_array[i][j]<< endl;
        }
    }

}
