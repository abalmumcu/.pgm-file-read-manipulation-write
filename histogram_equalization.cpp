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

void write_pgm_image(char name[], vector < vector<unsigned char> > & img){
    
    int col = 500;
    int row = 500;
    int maxvalue = 255;

    ofstream outfile;   //Yazma işlemi başlangıcı
    outfile.open(name,ios::out |ios::binary |ios::trunc);   // yazılacak dosya açıldı

    outfile << "P5" << endl;    // PGM dosyası için parametrelerin dosyaya yazılması 
    outfile << "# Created by Alper BALMUMCU for ELM568 Image Processing Course"<< endl;
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

vector < vector<unsigned char> > HistogramEqualization(vector < vector<unsigned char> > & input_img, int & row_img, int & col_img) 
{
  vector < vector<unsigned char> > output_img(row_img, vector <unsigned char> (col_img, 0));  // girilen row ve column için output img oluşturuldu
  int row, col, i, cumulative_distribution, min; // kullanılacak parametreler tanımlandı
  int histogram [256];  // [0-255] 256 değerli histogram değişkeni tanımlandı.
  int totalPixels = row_img * col_img;  // Formulde kullanılacak toplam piksel değerleri atandı.
  // Histogram Arrayine 256 adet 0 atıldı.
  for (i = 0; i < 256; i++){
    histogram[i] = 0;
  }
  // Histogram arrayine input resmindeki değerler atandı
  for (row = 0; row < row_img; row++) {
    for (col = 0; col < col_img; col++) {
      histogram[input_img[row][col]]++;
    }
  }
  cumulative_distribution = 0;   // cumulatif distribution function tanımlandı
  min = 0;
  for (i = 0; i < 256; i++){    // bu for döngüsü içerisinde cdf hesaplandı
    //İlk döngü için min değeri histogram[0] 'a atandı.
    if (min == 0){
      min = histogram[i];
    }
    cumulative_distribution += histogram[i];
    histogram[i] = cumulative_distribution;
  }
  int current;
  //Aşağıdaki for döngüsünde girdi alınan resmin tüm pikselleri üzerinde formul kullanılarak işlem yapılıp output resme atanıyor.
  for (row = 0; row < row_img; row++) {
    for (col = 0; col < col_img; col++) {
      current = histogram[input_img[row][col]];
      output_img[row][col] = (uint8_t)((current-min)/double(totalPixels-min)*255); // 255 bitlik bir görüntü olduğu için 255 ile çarpıldı ve uint8_t kullanarak yuvarlama işlemi yapıldı.
    }    
  }
  return output_img;
}  



int main(){

char magicnumber1,magicnumber2,magicnumber3,magicnumber4,magicnumber5,magicnumber6,magicnumber7,magicnumber8; // 4 farklı input resmi P ve 5 değerleri için magicnumber tanımlandı 
char comment_1[500],comment_2[500],comment_3[500],comment_4[500]; // her bir resim için # ile başlayan yorum satırı değişkeni tanımlandı
int row_1,col_1,maxvalue1;    // her bir resim için row col ve maxvalue değerleri tanımlandı
int row_2,col_2,maxvalue2;
int row_3,col_3,maxvalue3;
int row_4,col_4,maxvalue4;

    cout<<"\nFig0320(1)(top_left)\n";
    vector < vector <unsigned char> > img_1; // ilk resim unsigned char olarak tanımlandı ve vectore atandı.

    img_1 = read_pgm_image("Fig0320(1)(top_left).pgm",magicnumber1,magicnumber2,comment_1,row_1,col_1,maxvalue1); 
    vector< vector <unsigned char> > output_img_1(row_1, vector <unsigned char> (col_1, 0));  // output resim unsigned char olarak tanımlandı ve vectore atandı.

    output_img_1 = HistogramEqualization(img_1,row_1,col_1); // tanımlanan HistogramEquation fonksiyonuna girdi görüntüsü verildi ve output_img_1 e atandı.

    write_pgm_image("Fig0320(1)output.pgm",output_img_1); //yazdırma işlemi

 ///////////////////////////////////////////////////////////////////////////   
    cout<<"\nFig0320(2)(2nd_from_top)\n";    

    vector < vector <unsigned char> > img_2; // 

    img_2 = read_pgm_image("Fig0320(2)(2nd_from_top).pgm",magicnumber3,magicnumber4,comment_2,row_2,col_2,maxvalue2);
    vector< vector <unsigned char> > output_img_2(row_2, vector <unsigned char> (col_2, 0));

    output_img_2 = HistogramEqualization(img_2,row_2,col_2);
    write_pgm_image("Fig0320(2)output.pgm", output_img_2);

 ///////////////////////////////////////////////////////////////////////////   
    cout<<"\nFig0320(3)(third_from_top)\n";    

    vector < vector <unsigned char> > img_3; // 

    img_3 = read_pgm_image("Fig0320(3)(third_from_top).pgm",magicnumber5,magicnumber6,comment_3,row_3,col_3,maxvalue3);
    vector< vector <unsigned char> > output_img_3(row_3, vector <unsigned char> (col_3, 0));

    output_img_3 = HistogramEqualization(img_3,row_3,col_3);
    write_pgm_image("Fig0320(3)output.pgm", output_img_3);


 ///////////////////////////////////////////////////////////////////////////   
    cout<<"\nFig0320(4)(bottom_left)\n";    

    vector < vector <unsigned char> > img_4; // 

    img_4 = read_pgm_image("Fig0320(4)(bottom_left).pgm",magicnumber7,magicnumber8,comment_4,row_4,col_4,maxvalue4);
    vector< vector <unsigned char> > output_img_4(row_4, vector <unsigned char> (col_4, 0));

    output_img_4 = HistogramEqualization(img_4,row_4,col_4);
    write_pgm_image("Fig0320(4)output.pgm", output_img_4);    
}