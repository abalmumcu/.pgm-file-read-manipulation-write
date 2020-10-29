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

using namespace std;

void write_pgm_image(char name[], vector < vector<unsigned char> > & img){
    
    int col = 500;
    int row = 800;
    int maxvalue = 255;

    ofstream outfile;   //Yazma işlemi başlangıcı
    outfile.open(name,ios::out |ios::binary |ios::trunc);   // yazılacak dosya açıldı

    outfile << "P5" << endl;    // PGM dosyası için parametrelerin dosyaya yazılması 
    outfile << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    outfile << col << " " << row << endl;
    outfile << maxvalue << endl;
    outfile.close();

    ofstream newof;     // Olusturulan image arrayini pgm dosyasına yazdırma aşaması
    newof.open(name,ios::out | ios::binary | ios::app);
    
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newof.put(img[i][j]);   // her bir satır sutun için img matrisi pgm dosyasına atıldı.
        }
    }
    
    newof.close();
}


vector < vector<unsigned char> > averaging_filter(int & mask_size, vector<vector<unsigned char>> & input_img, int & row, int & col){
    vector< vector <unsigned char> > padded_img(row +mask_size-1, vector <unsigned char> (col+mask_size-1, 0));
    vector< vector <unsigned char> > output_img(row, vector <unsigned char> (col, 0)); //  averaging filter sonucu oluşacak resim.

    int n;

    n = (mask_size-1)/2;        // buradaki n parametresi filtrenin (i,j) kısmından max ne kadar az veya çok olacağını belirliyor.

    for(int i = 0; i < row; i++){                               //zero padding
        for(int j = 0; j < col; j++){

            padded_img[i+n][j+n] = input_img[i][j];     
        }    
    }



    for(int i = n; i < row+n; i++){                            // averaging filter
        for(int j = n; j < col+n; j++){
            for(int k = 0; k < mask_size; k++){
                for(int l = 0; l < mask_size; l++){
                    output_img[i-n][j-n] +=  (padded_img[i-n+k][j-n+l])/pow(mask_size,2); // Burada filtrenin her elemanı (1/mask size^2) ile 
                }                                                                          // carpılarak toplandı. Teorideki önce toplanıp sonra
            }                                                                                // çarpılması ile aynı işlem oluyor.             
         
        }       
    }
    return output_img;
}


int main(){


    int row,col,maxvalue;
    char magicnumber1,magicnumber2;
    char comment[500]= " ";


    string inputLine = "";

    ifstream infile;    
    infile.open("Fig0343(a)(skeleton_orig).pgm", ios::in  | ios::binary); // Dosyayı okuma

    infile >> magicnumber1 >> magicnumber2; // P ve 5 ayrı ayrı cekildi

        
    if (magicnumber1 == 'P' && magicnumber2 == '5'){ // Eger P5 degilse hata oluştur ve çıkıs yap.
        getline(infile,inputLine); 
        cout << "Version : P5"<<endl; }
        
    else {        
        cout << " The File Version is Wrong" << endl;
        exit(-1);}
        
    getline(infile,inputLine);  // '#' satırı okuma islemi
    strcpy(comment,inputLine.data()); 
    cout << "Comment : " << inputLine << endl; // '#' satı yazdırma
    infile >> col >> row >> maxvalue; // row col ve maxvalue degerleri okuma
    cout << "Width and Height : " << col <<" "<< row << endl;
        
    if (maxvalue == 255){
        cout << "Maximum Value : " << maxvalue << endl;}        //  Maxvalue 255 degilse hata ver ve çıkış yap.
    
    else {
        cout <<"Maximum Value is not 255!!\nYour Maximum Value: " << maxvalue << endl;
        exit(-2);}


    vector <unsigned char> zvc(col);  // zvc column ile olusturuldu  
    vector < vector<unsigned char> > img; // olustrulacak resim vector(konteyner)'e atandı.


    fill(zvc.begin(),zvc.end(),0);  // bütün noktalara 0 atandı

    for(int i = 0; i < row; i++){   
        img.push_back(zvc); //img parametresi ile atama yapıldı
    }


    int k = 0,l = 0; 
    long cnt = 0;  // Counter tanımladık
    for(k = 0; k < row; k++){ 
        for(l = 0; l < col; l++){
            int val = 0; // Görüntü matrisinden alınacak değerler için atanan değişken
            int p = 7; 
            char c11;   // matrisin (1,1) değeri
            infile.get(c11);       // Değeri al         
            while(p >=0){      
                val += (((c11 >> p) & 1) ) * pow(2,p); //Matrisin ilk değerinden başlayarak alınan değeri p ye gönder ve 256 ile çarp
                p--; 
            }
            img[k][l] = val;  // Okunan val değerlerini image'e ata
            cnt++; // counter 
        }    
    }

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART B ///////////////////////////
////////////////////////////////////////////////////////////////////////
 
    int laplace_mask[9] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };       // Laplace maskeyi oluşturuldu.
    int tmp = 0;                    // Döngü içerisinde kullanılacak bir template değişken tanımlandı.    
    int counter = 0;                // For döngüsü içerisinde laplace mask için kullanılacak counter tanımlandı.
    float laplaceImage[row][col];       // Çıktı görüntüsü oluşturuldu.

    for (int i = 1; i < row - 1; i++){
        for (int j = 1; j < col - 1; j++){
            for (int k = i - 1; k < i + 2; k++){
                for (int l = j - 1; l < j + 2; l++){
                    tmp += laplace_mask[counter] * static_cast<int>(img[k][l]);  // Burada Laplace mask arrayi içerisindeki her bir eleman
                    counter++;                                                   // giriş görüntüsü ile row ve column boyunca çarpılıp toplanıyor.  
                }
            }

        laplaceImage[i - 1][ j - 1] = tmp;          // template her maske döngüsü sonrasında o anki piksel numarası atanıyor.    
        if (laplaceImage[i - 1][j-1] < 0) {           // [-1020,1020] aralığından ötürü piksel değerlerini 0-255 aralığında tutmak için
            laplaceImage[i-1][j-1] = 0;}                // eğer 255'den büyükse = 255
        else if (laplaceImage[i-1][j-1] > 255) {        // eğer 0'dan küçükse = 0 yap diyerek görüntü matrisini oluşturuyoruz.
            laplaceImage[i-1][j-1] = 255;
        } 
  
        tmp = 0;
        counter = 0;
        }
    }


    ofstream outfile;   //Yazma işlemi başlangıcı
    outfile.open("Fig0343(b).pgm",ios::out |ios::binary |ios::trunc);   // yazılacak dosya açıldı

    outfile << "P5" << endl;    // PGM dosyası için parametrelerin dosyaya yazılması 
    outfile << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    outfile << col << " " << row << endl;
    outfile << maxvalue << endl;
    outfile.close();

    ofstream newof;     // Olusturulan image arrayini pgm dosyasına yazdırma aşaması
    newof.open("Fig0343(b).pgm",ios::out | ios::binary | ios::app);
        
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newof.put(laplaceImage[i][j]);   // her bir satır sutun için img matrisi pgm dosyasına atıldı.
        }
    }
        
    newof.close();
////////////////////////////////////////////////////////////////////////
    ////////////////////// PART C ///////////////////////////
////////////////////////////////////////////////////////////////////////
    vector< vector <unsigned char> > output_sharpened(row, vector <unsigned char> (col, 0)); // output sharpened resim  tanımı

    int templat;        // template oluşturuldu
    for (int i =0; i < row; i++){   
        for(int j =0; j < col; j++){
            templat = img[i][j] + laplaceImage[i][j];   // orjinal görüntü ile partB de oluşturulan laplace görüntüsü toplanarak
            if (templat< 0) {                           // yeni görüntüye kaydedildi.
                templat = 0;}
            else if (templat > 255) {
                templat = 255;} 

            output_sharpened[i][j] = templat;
            
        }
    } 

    cout << "Fig0343(b).pgm saved successfully to the directory\n\n";


    write_pgm_image("Fig0343(c).pgm",output_sharpened);     // Oluştrulan görüntü kaydedildi.
    cout << "Fig0343(c).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART D ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > sobel_grad(row, vector <unsigned char> (col, 0)); // output sobel grad görüntü  tanımı

    int Gx;    
    int Gy;

    float sobel_x[3][3] =       // X ve Y gradiantleri tanımlandı
    { { -1, 0, 1 },
      { -2, 0, 2 },
      { -1, 0, 1 } };

    float sobel_y[3][3] =
    { { -1, -2, -1 },
      { 0,  0,  0 },
      { 1,  2,  1 } };

    for (int i=1; i < row-1; i++){
        for (int j=1; j < col-1; j++){

            Gx =     (sobel_x[0][0] * img[i-1][j-1])    // sobel_x ve sobel_y matrisleri için maskenin her bir piksel
                    + (sobel_x[0][1] * img[i-1][j])      // bloğuna karşılık gelecek şekilde orjinal görüntünün kordinatları
                    + (sobel_x[0][2] * img[i-1][j+1])  // belirlenip çarpımları yapıldı. Ve bütün row ve column boyunca döngüsü sağlandı.
                    + (sobel_x[1][0] * img[i][j-1])
                    + (sobel_x[1][1] * img[i][j])
                    + (sobel_x[1][2] * img[i][j+1])
                    + (sobel_x[2][0] * img[i+1][j-1])
                    + (sobel_x[2][1] * img[i+1][j])
                    + (sobel_x[2][2] * img[i+1][j+1]);

            Gy =    (sobel_y[0][0] * img[i-1][j-1])
                    + (sobel_y[0][1] * img[i-1][j])
                    + (sobel_y[0][2] * img[i-1][j+1])
                    + (sobel_y[1][0] * img[i][j-1])
                    + (sobel_y[1][1] * img[i][j])
                    + (sobel_y[1][2] * img[i][j+1])
                    + (sobel_y[2][0] * img[i+1][j-1])
                    + (sobel_y[2][1] * img[i+1][j])
                    + (sobel_y[2][2] * img[i+1][j+1]);

            int val = (int)sqrt((Gx * Gx) + (Gy * Gy));     //genlik hesaplandı

            if(val < 0) val = 0;        // 0-255 aralığında kalması için if else döngüleri tanımlandı.
            if(val > 255) val = 255;

            sobel_grad[i][j]= val;  // her bir piksel koordinatı için genlik değerleri atandı.
        }
    }

    write_pgm_image("Fig0343(d).pgm",sobel_grad);   // Pgm dosyası olarak yazdırılması.
    cout << "Fig0343(d).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART E ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned char> > output_sobel_grad_with_5x5_averaging;     // 5x5 averaging filtre uygulanmış görüntünün outputu için görüntü oluşturuldu.

    int mask_1 = 5;     // 5x5 olduğu için mask_1 = 5 olarak seçildi.
    output_sobel_grad_with_5x5_averaging = averaging_filter(mask_1,sobel_grad,row,col); // yukarıda oluşturulan averaging_filter fonksiyonuna sokuldu.
    write_pgm_image("Fig0343(e).pgm",output_sobel_grad_with_5x5_averaging); // Çıktı işlemi yazıdırıldı.
    cout << "Fig0343(e).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART F ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned int> > product_of_sharpen_and_averaged_sobel_grad(row, vector <unsigned int> (col, 0)); // belirli row ve column değerlerinde output tanımlandı.
    int temmp;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
        temmp = (output_sharpened[i][j] * output_sobel_grad_with_5x5_averaging[i][j])/255.; // Part e ve part c de oluşturulan çıktı görüntüleri ayrı ayrı her bir piksel değerleri
            if (temmp< 0) {                                                                  // çarpılararak template değişkenine atandı.
                temmp = 0;}                                                                     // atanan değer 0-255 aralığında kalması sağlandı.
            else if (temmp > 255) {
                temmp = 255;} 
            product_of_sharpen_and_averaged_sobel_grad[i][j] = temmp;                   // her bir temmp değişkeni o anki i,j piksel kordinatlarına piksel değeri olarak atandı.
        }
    }

    ofstream outfile_part_e;   //Yazma işlemi başlangıcı
    outfile_part_e.open("Fig0343(f).pgm",ios::out |ios::binary |ios::trunc);   // yazılacak dosya açıldı

    outfile_part_e << "P5" << endl;    // PGM dosyası için parametrelerin dosyaya yazılması 
    outfile_part_e << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    outfile_part_e << col << " " << row << endl;
    outfile_part_e << maxvalue << endl;
    outfile_part_e.close();

    ofstream newofile_part_e;     // Olusturulan image arrayini pgm dosyasına yazdırma aşaması
    newofile_part_e.open("Fig0343(f).pgm",ios::out | ios::binary | ios::app);
        
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newofile_part_e.put(product_of_sharpen_and_averaged_sobel_grad[i][j]);   // her bir satır sutun için img matrisi pgm dosyasına atıldı.
        }
    }
        
    newofile_part_e.close();
    cout << "Fig0343(f).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART G ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > output_sharpened_img_sum_of_part_a_and_f(row, vector <unsigned char> (col, 0)); // output part G görüntüsünün tanımı

    int temp_for_part_g;            // G partında kullanılacak değerleri döndürecek template oluşturuldu. 
    for(int i=0; i< row; i++){
        for(int j=0; j< col; j++){
            temp_for_part_g = product_of_sharpen_and_averaged_sobel_grad[i][j] + img[i][j]; //orjinal görüntü piksel değerleri ve  part F'de oluşturulan görüntünün
            if (temp_for_part_g< 0) {                                                       // piksel değerleri toplanarak temp_for_part_g değişkenine atandı
                temp_for_part_g = 0;}                                                       // Bu toplanan piksel değerlerinin 0-255 aralığında kalması sağlandı.
            else if (temp_for_part_g > 255) {
                temp_for_part_g = 255;} 
            output_sharpened_img_sum_of_part_a_and_f[i][j] = temp_for_part_g;           // döndürülen her bir piksel değeri output görüntü matrisine atandı.
        }
    }

    write_pgm_image("Fig0343(g).pgm", output_sharpened_img_sum_of_part_a_and_f);    
    cout << "Fig0343(g).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART H ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > gamma_of_part_g(row, vector <unsigned char> (col, 0));
    float gamma = 0.5;    //gamma degeri atandı

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            gamma_of_part_g[i][j] = 255*(pow(output_sharpened_img_sum_of_part_a_and_f[i][j]/255.,gamma));   //Gamma transformation işlemi her bir piksel değeri için yapıldı.

        }
    }

    write_pgm_image("Fig0343(h).pgm", gamma_of_part_g);
    cout << "Fig0343(h).pgm saved successfully to the directory";


}  

