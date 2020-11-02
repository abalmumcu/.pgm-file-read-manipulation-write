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
    vector <vector <double>> given_array = {    // Verilen görüntü matrisi
        {3,2,1},
        {6,5,4},
        {9,8,7}};
    
    double output_array[3][3];      // çıktı olarak kullanılacak görüntü
    int width=3;    // görüntünün genişlik ve yükseklik değerleri
    int height=3;

    complex <double> **dft_array = new complex <double>*[width];    // complex olarak işlem yapılacak dft_array tanımlandı.
    for (int b=0;b<width;b++){                      
        dft_array[b]= new complex <double>[height];     // dft_array değişkeni [3][3] olarak tanımlandı.
    }

    complex<double> sum=0;  // Satırların fourieri alındığında kullanılacak temp.
    complex<double> sum2=0; // Sütunların fourieri alındığında kullanılacak temp.
    double pi = 3.141592653589793;  // Pi sayısı tanımlandı

    for (int i=0; i<3; i++){    // Buradaki for düngüsü ile given_array matrisi, complex dft_array değişkenine atandı.
        for (int j=0; j<3; j++){
            complex<double> cplx(given_array[i][j], 0);
            dft_array[i][j]=cplx;   
        }   
    }
    cout << "\nOut of the 1D DFT of Row\n";

    for (int x=0; x<3; x++){    // Bu bölümde Satırların fourier dönüşümü yapıldı.
        sum=0;
        for (int y=0; y<3; y++){
            sum+=(dft_array[x][y].real())*cos((2*pi*x*y)/3)-(dft_array[x][y].imag())*sin((2*pi*x*y)/3);
            cout<<sum<<" ";
            dft_array[x][y]=sum;
        }
    }
    
    cout << "\n\nOut of the 1D DFT of Column\n";
    
    for (int x=0; x<3; x++){    // Bu bölümde yukarıda Fourier dönüşümü yapılan Satırların, Sütünlar için fourier dönüşümü yapıldı.
        sum2=0;
        for (int y=0; y<3; y++){
            sum2+=(dft_array[y][x].real())*cos((2*pi*x*y)/3)-(dft_array[y][x].imag())*sin((2*pi*x*y)/3);
            cout<<sum2<<" ";
            dft_array[y][x]=sum2;
        }
    }
    
    cout << "\n\nResults:\n";

    for (int i=0; i<3; i++){    // En son olarak ayrı ayrı satır ve sütun için 1D DFT işleminden sonra değerlerin reel kısımları output_arraya atandı.
        for (int j=0; j<3; j++){
        output_array[i][j]=dft_array[i][j].real();
        }
    }    
   
    for ( int i = 0; i < 3; i++ ){  // Sonuç değerlerini yazdırma kısmı
        for ( int j = 0; j < 3; j++ ) {      
        cout << "output_array[" << i << "][" << j << "]: ";
        cout << output_array[i][j]<< endl;
        }
    }

}