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


vector < vector<unsigned char> > read_pgm_image(char name[], char & magicnumber1, char & magicnumber2, char comment[], int & row, int & col, int & maxvalue){   
   
    vector < vector<unsigned char> > img; // olustrulacak resim vector(konteyner)'e atandı.
    string inputLine = "";

    ifstream infile;    
    infile.open(name, ios::in  | ios::binary); // Dosyayı okuma

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
    return img;

}

void write_pgm_image(char name[], vector < vector<unsigned char> > & img, int & row, int & col, int & maxvalue){
    

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


int main() {

    // Burada farklı resimler için kullanılacak değerler tanımlandı.
    char magicnumber_1,magicnumber_2,magicnumber_3,magicnumber_4,magicnumber_5;
    char magicnumber_6,magicnumber_7,magicnumber_8,magicnumber_9,magicnumber_10;                
    char comment_1[500],comment_2[500],comment_3[500],comment_4[500],comment_5[500] = " ";
    int row_1,col_1,maxvalue_1;
    int row_2,col_2,maxvalue_2;
    int row_3,col_3,maxvalue_3;
    int row_4,col_4,maxvalue_4;
    int row_5,col_5,maxvalue_5;

    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//                                             IMAGE NEGATIVES            \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             IMAGE NEGATIVES              
////////////////////////////////////////////////////////////////////////////////////////////////////////   

    vector < vector <unsigned char> > img_negative; // negatifi alınacak resim tanımlandı

    img_negative = read_pgm_image("Fig0304(a)(breast_digital_Xray).pgm",magicnumber_1,magicnumber_2,comment_1,row_1,col_1,maxvalue_1);
    vector< vector <unsigned char> > negative_img(row_1, vector <unsigned char> (col_1, 0)); // output negatif resim  tanımı

    
    for(int i = 0; i < row_1; i++){         
        for(int j = 0; j < col_1; j++){

            negative_img[i][j] = (255 - img_negative[i][j]);      //Negative Image olusturuldu. 
        }   
    }

    write_pgm_image("Fig0304(b).pgm",negative_img,row_1,col_1,maxvalue_1); // negatif resim yazıldı

    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//                                    LOGARITHMIC TRANSFORMATION                \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    LOGARITHMIC TRANSFORMATION                
////////////////////////////////////////////////////////////////////////////////////////////////////////        

    vector < vector <unsigned char> > img_log_trans; // log transformation yapılacak resim tanımlandı

    img_log_trans = read_pgm_image("Fig0305(a)(DFT_no_log).pgm",magicnumber_3,magicnumber_4,comment_2,row_2,col_2,maxvalue_2);
    vector< vector <unsigned char> > output_log_trans(row_2, vector <unsigned char> (col_2, 0));   // output log trans

    float c = 255 / log10(1 + maxvalue_2); // Log Transformation icin c sabiti bulundu
    for(int i = 0; i < row_2; i++){         
        for(int j = 0; j < col_2; j++){

            output_log_trans[i][j] = c*(255*(log((img_log_trans[i][j]/255.)+1)));      //Log Transformation denklemi her bir bit için uygulandi.
        }   
    }
    write_pgm_image("Fig0305(b).pgm",output_log_trans,row_2,col_2,maxvalue_2);

    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//              GAMMA TRANSFORMATION              C =1 , GAMMA = 0.6 , 0.4 , 0,3         \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
////////////////////////////////////////////////////////////////////////////////////////////////////////
//              GAMMA TRANSFORMATION              C =1 , GAMMA = 0.6 , 0.4 , 0,3
////////////////////////////////////////////////////////////////////////////////////////////////////////    

    vector <vector <unsigned char> > img_gamma_trans;
    
    img_gamma_trans = read_pgm_image("Fig0308(a)(fractured_spine).pgm",magicnumber_4,magicnumber_5,comment_3,row_3,col_3,maxvalue_3);
    vector< vector <unsigned char> > gamma_img_1(row_3, vector <unsigned char> (col_3, 0)); //her bir gamma değeri için farklı resim konteynerları oluşturuldu.
    vector< vector <unsigned char> > gamma_img_2(row_3, vector <unsigned char> (col_3, 0));
    vector< vector <unsigned char> > gamma_img_3(row_3, vector <unsigned char> (col_3, 0));


    float gamma_1 = 0.6;    //gamma degerleri atandı
    float gamma_2 = 0.4;
    float gamma_3 = 0.3;

    for(int i = 0; i < row_3; i++){         
        for(int j = 0; j < col_3; j++){

            gamma_img_1[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_1));      // c = 1, gamma = 0.6
            gamma_img_2[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_2));      // c = 1, gamma = 0.4
            gamma_img_3[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_3));      // c = 1, gamma = 0.3
        }   
    }

    write_pgm_image("Fig0308(b).pgm",gamma_img_1,row_3,col_3,maxvalue_3);
    write_pgm_image("Fig0308(c).pgm",gamma_img_2,row_3,col_3,maxvalue_3);
    write_pgm_image("Fig0308(d).pgm",gamma_img_3,row_3,col_3,maxvalue_3);

    cout << "\n";
    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//               AVERAGING FILTER                3X3  ,  5X5  ,  9X9  ,  15X15  ,  35X35            \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";

////////////////////////////////////////////////////////////////////////////////////////////////////////
//               AVERAGING FILTER                3X3  ,  5X5  ,  9X9  ,  15X15  ,  35X35
////////////////////////////////////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned char> > img_for_average_filter;

    img_for_average_filter = read_pgm_image("Fig0333(a)(test_pattern_blurring_orig).pgm",magicnumber_5,magicnumber_6,comment_4,row_4,col_4,maxvalue_4);
    vector <vector <unsigned char> > output_3x3_average_filter;
    vector <vector <unsigned char> > output_5x5_average_filter;
    vector <vector <unsigned char> > output_9x9_average_filter;
    vector <vector <unsigned char> > output_15x15_average_filter;
    vector <vector <unsigned char> > output_35x35_average_filter;

    int mask_1 = 3; 
    output_3x3_average_filter = averaging_filter(mask_1,img_for_average_filter,row_4,col_4);

    int mask_2 = 5;
    output_5x5_average_filter = averaging_filter(mask_2,img_for_average_filter,row_4,col_4);



    write_pgm_image("Fig0333(b).pgm", output_3x3_average_filter,row_4,col_4,maxvalue_4);
    write_pgm_image("Fig0333(c).pgm", output_5x5_average_filter,row_4,col_4,maxvalue_4);


    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//               SALT PEPPER NOISE REDUCTION APPLICATION WITH 3X3 AVERAGE AND MEDIAN FILTER             \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
////////////////////////////////////////////////////////////////////////////////////////////////////////
//               SALT PEPPER NOISE REDUCTION APPLICATION WITH 3X3 AVERAGE AND MEDIAN FILTER               
////////////////////////////////////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned char> > img_for_noise_reduction;

    img_for_noise_reduction = read_pgm_image("Fig0335(a)(ckt_board_saltpep_prob_pt05).pgm",magicnumber_8,magicnumber_9,comment_5,row_5,col_5,maxvalue_5);
    vector <vector <unsigned char> > output_3x3_average_filter_for_noise; // 3x3luk averaging_filter outputu tanımlandı


    output_3x3_average_filter_for_noise = averaging_filter(mask_1,img_for_noise_reduction,row_5,col_5); // Fonksiyon olarak oluşturulan filtreye sokuldu

    write_pgm_image("Fig0335(b).pgm", output_3x3_average_filter_for_noise,row_5,col_5,maxvalue_5); // Yazma işlemi


    vector <vector <unsigned char> > sample_img_for_input_median(row_5, vector <unsigned char> (col_5, 0)); // 3x3luk averaging_filter outputu tanımlandı


    for(int i = 0; i < row_5; i++){                             
        for(int j = 0; j < col_5; j++){

            sample_img_for_input_median[i][j] = img_for_noise_reduction[i][j];     // okunan pgm dosyası vektor ile taşındığı için başka bir değişkene atanıp öyle işlem yapılacak.
        }    
    }
    unsigned char window[9]={0}; // pikselleri taşıması için array oluşturuldu.
    unsigned char output_median[row_5][col_5];   // Çıkış matrisi 

    for(int i =1; i <= row_5-2; i++){
        for(int j=1; j <= col_5-2; j++){
            window[0] = sample_img_for_input_median[i-1][j-1];
            window[1] = sample_img_for_input_median[i-1][j];        // Burada (i-1,j-1)'den (i+1,j+1)'e kadar olan 3x3 filtrenin her bir değeri bir 
            window[2] = sample_img_for_input_median[i-1][j+1];        // array elemanına atandı.
            window[3] = sample_img_for_input_median[i][j-1];
            window[4] = sample_img_for_input_median[i][j];
            window[5] = sample_img_for_input_median[i][j+1];
            window[6] = sample_img_for_input_median[i+1][j-1];
            window[7] = sample_img_for_input_median[i+1][j];
            window[8] = sample_img_for_input_median[i+1][j+1];

            int k, key, l; 
            for (k = 1; k < 9; k++) // Yukarıda belirtilen piksel taşıyan array elemanları için sort yani sıralama ve median değerini bulma işlemi yapılıyor.
            { 
                key = window[k]; // k. değeri atandı.
                l = k - 1; 
        

                while (l >= 0 && window[l] > key) // yukarıda l değeri k-1 olarak belirtildi. Burada l değeri 0'dan ve window'un l. değeri window[k]'dan büyük ise 
                {                                   // windowun l+1 inci de bulunan değeri l nci değerine eşitlenecek ve l hep 1 azalacak. Ve bu sayede sıralama 
                    window[l + 1] = window[l];       // işlemi yapılacak. 
                    l = l - 1; 
                } 
                window[l + 1] = key;                   
            }
            output_median[i][j]=window[4];      // sıralama bittikten sonra 0-8 'e olan arrayların medyanı artık ortadaki konuma geldi. 
        }                                          //  Ve bu değer sonuç matrisine eşitlendi.
    }

    ofstream outfile;   //Yazma işlemi başlangıcı
    outfile.open("Fig0335(c).pgm",ios::out |ios::binary |ios::trunc);   // yazılacak dosya açıldı

    outfile << "P5" << endl;    // PGM dosyası için parametrelerin dosyaya yazılması 
    outfile << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    outfile << col_5 << " " << row_5 << endl;
    outfile << maxvalue_5 << endl;
    outfile.close();

    ofstream newof;     // Olusturulan image arrayini pgm dosyasına yazdırma aşaması
    newof.open("Fig0335(c).pgm",ios::out | ios::binary | ios::app);
    
    for( int i = 0; i < row_5; i++)   
    {
        for( int j = 0; j < col_5; j++)
        {
            newof.put(output_median[i][j]);   // her bir satır sutun için img matrisi pgm dosyasına atıldı.
        }
    }
    
    newof.close();


    return 0;
}