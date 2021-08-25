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
   
    vector < vector<unsigned char> > img; 
    string inputLine = "";

    ifstream infile;    
    infile.open(name, ios::in  | ios::binary); 

    infile >> magicnumber1 >> magicnumber2;

    
    if (magicnumber1 == 'P' && magicnumber2 == '5'){ 
        getline(infile,inputLine); 
        cout << "Version : P5"<<endl; }
    
    else {        
        cout << " The File Version is Wrong" << endl;
        exit(-1);}
    
    getline(infile,inputLine); 
    strcpy(comment,inputLine.data()); 
    cout << "Comment : " << inputLine << endl;
    infile >> col >> row >> maxvalue;
    cout << "Width and Height : " << col <<" "<< row << endl;
    
    if (maxvalue == 255){
        cout << "Maximum Value : " << maxvalue << endl;}     
   
    else {
        cout <<"Maximum Value is not 255!!\nYour Maximum Value: " << maxvalue << endl;
        exit(-2);}


    vector <unsigned char> zvc(col);   


    fill(zvc.begin(),zvc.end(),0);  
    for(int i = 0; i < row; i++){   
        img.push_back(zvc);
    }


    int k = 0,l = 0; 
    long cnt = 0;  
    for(k = 0; k < row; k++){ 
        for(l = 0; l < col; l++){
            int val = 0; 
            int p = 7; 
            char c11;   
            infile.get(c11);    
            while(p >=0){      
                val += (((c11 >> p) & 1) ) * pow(2,p);
                p--; 
            }
            img[k][l] = val; 
            cnt++; 
            }    
        }
    return img;

}

void write_pgm_image(char name[], vector < vector<unsigned char> > & img){
    
    int col = 500;
    int row = 500;
    int maxvalue = 255;

    ofstream outfile;   
    outfile.open(name,ios::out |ios::binary |ios::trunc);  

    outfile << "P5" << endl;  
    outfile << "# Created by Alper BALMUMCU"<< endl;
    outfile << col << " " << row << endl;
    outfile << maxvalue << endl;
    outfile.close();

    ofstream newof;    
    newof.open(name,ios::out | ios::binary | ios::app);
    
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newof.put(img[i][j]);   
        }
    }
    
    newof.close();
}

vector < vector<unsigned char> > HistogramEqualization(vector < vector<unsigned char> > & input_img, int & row_img, int & col_img) 
{
  vector < vector<unsigned char> > output_img(row_img, vector <unsigned char> (col_img, 0));  
  int row, col, i, cumulative_distribution, min;
  int histogram [256];  
  int totalPixels = row_img * col_img;

  for (i = 0; i < 256; i++){
    histogram[i] = 0;
  }
  
  for (row = 0; row < row_img; row++) {
    for (col = 0; col < col_img; col++) {
      histogram[input_img[row][col]]++;
    }
  }
   
  cumulative_distribution = 0;  ı
  min = 0;
  for (i = 0; i < 256; i++){    
    if (min == 0){
      min = histogram[i];
    }
    cumulative_distribution += histogram[i];
    histogram[i] = cumulative_distribution;
  }
  int current;
  for (row = 0; row < row_img; row++) {
    for (col = 0; col < col_img; col++) {
      current = histogram[input_img[row][col]];
      output_img[row][col] = (uint8_t)((current-min)/double(totalPixels-min)*255);
    }    
  }
  return output_img;
}  



int main(){

char magicnumber1,magicnumber2,magicnumber3,magicnumber4,magicnumber5,magicnumber6,magicnumber7,magicnumber8;
char comment_1[500],comment_2[500],comment_3[500],comment_4[500];
int row_1,col_1,maxvalue1;    
int row_2,col_2,maxvalue2;
int row_3,col_3,maxvalue3;
int row_4,col_4,maxvalue4;

    cout<<"\nFig0320(1)(top_left)\n";
    vector < vector <unsigned char> > img_1;

    img_1 = read_pgm_image("Fig0320(1)(top_left).pgm",magicnumber1,magicnumber2,comment_1,row_1,col_1,maxvalue1); 
    vector< vector <unsigned char> > output_img_1(row_1, vector <unsigned char> (col_1, 0)); 

    output_img_1 = HistogramEqualization(img_1,row_1,col_1);

    write_pgm_image("Fig0320(1)output.pgm",output_img_1); 

 ///////////////////////////////////////////////////////////////////////////   
    cout<<"\nFig0320(2)(2nd_from_top)\n";    

    vector < vector <unsigned char> > img_2; 

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
