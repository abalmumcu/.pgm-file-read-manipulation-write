#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

int main() {
    
    const int rows = 400;
    const int columns = 300;
    const int maxval = 255;
    string filename;

    uint8_t k = 0;
    uint8_t txbuf[256];

    fstream dosya;
    dosya.open("output2.pgm", std::ios_base::out
                            |std::ios_base::binary
                            |std::ios_base::trunc );
    
    dosya << "P5" << endl;
    dosya << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    dosya << columns << " " << rows << endl;
    dosya << maxval << endl;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns ; j++){                       
            do
            {
            txbuf[k] = k;
            dosya << static_cast<char>(k);
            } while (k++ != 255);    
        }
    }
    dosya.close();
}
