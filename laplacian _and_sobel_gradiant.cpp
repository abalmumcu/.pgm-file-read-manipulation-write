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


vector < vector<unsigned char> > averaging_filter(int & mask_size, vector<vector<unsigned char>> & input_img, int & row, int & col){
    vector< vector <unsigned char> > padded_img(row +mask_size-1, vector <unsigned char> (col+mask_size-1, 0));
    vector< vector <unsigned char> > output_img(row, vector <unsigned char> (col, 0)); 

    int n;

    n = (mask_size-1)/2;        

    for(int i = 0; i < row; i++){                               //zero padding
        for(int j = 0; j < col; j++){

            padded_img[i+n][j+n] = input_img[i][j];     
        }    
    }



    for(int i = n; i < row+n; i++){                            // averaging filter
        for(int j = n; j < col+n; j++){
            for(int k = 0; k < mask_size; k++){
                for(int l = 0; l < mask_size; l++){
                    output_img[i-n][j-n] +=  (padded_img[i-n+k][j-n+l])/pow(mask_size,2); 
                }                                                                          
            }                                                                                            
         
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
    infile.open("Fig0343(a)(skeleton_orig).pgm", ios::in  | ios::binary);

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
    vector < vector<unsigned char> > img; 


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
            cnt++; // counter 
        }    
    }

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART B ///////////////////////////
////////////////////////////////////////////////////////////////////////
 
    int laplace_mask[9] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };     
    int tmp = 0;                      
    int counter = 0;               
    float laplaceImage[row][col];     

    for (int i = 1; i < row - 1; i++){
        for (int j = 1; j < col - 1; j++){
            for (int k = i - 1; k < i + 2; k++){
                for (int l = j - 1; l < j + 2; l++){
                    tmp += laplace_mask[counter] * static_cast<int>(img[k][l]);  
                    counter++;                                                     
                }
            }

        laplaceImage[i - 1][ j - 1] = tmp;             
        if (laplaceImage[i - 1][j-1] < 0) {           
            laplaceImage[i-1][j-1] = 0;}                
        else if (laplaceImage[i-1][j-1] > 255) {        
            laplaceImage[i-1][j-1] = 255;
        } 
  
        tmp = 0;
        counter = 0;
        }
    }


    ofstream outfile; 
    outfile.open("Fig0343(b).pgm",ios::out |ios::binary |ios::trunc);  

    outfile << "P5" << endl;    
    outfile << "# Created by Alper BALMUMCU"<< endl;
    outfile << col << " " << row << endl;
    outfile << maxvalue << endl;
    outfile.close();

    ofstream newof;    
    newof.open("Fig0343(b).pgm",ios::out | ios::binary | ios::app);
        
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newof.put(laplaceImage[i][j]);  
        }
    }
        
    newof.close();
////////////////////////////////////////////////////////////////////////
    ////////////////////// PART C ///////////////////////////
////////////////////////////////////////////////////////////////////////
    vector< vector <unsigned char> > output_sharpened(row, vector <unsigned char> (col, 0));

    int templat;       
    for (int i =0; i < row; i++){   
        for(int j =0; j < col; j++){
            templat = img[i][j] + laplaceImage[i][j];   
            if (templat< 0) {                           
                templat = 0;}
            else if (templat > 255) {
                templat = 255;} 

            output_sharpened[i][j] = templat;
            
        }
    } 

    cout << "Fig0343(b).pgm saved successfully to the directory\n\n";


    write_pgm_image("Fig0343(c).pgm",output_sharpened);    
    cout << "Fig0343(c).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART D ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > sobel_grad(row, vector <unsigned char> (col, 0)); 

    int Gx;    
    int Gy;

    float sobel_x[3][3] =      
    { { -1, 0, 1 },
      { -2, 0, 2 },
      { -1, 0, 1 } };

    float sobel_y[3][3] =
    { { -1, -2, -1 },
      { 0,  0,  0 },
      { 1,  2,  1 } };

    for (int i=1; i < row-1; i++){
        for (int j=1; j < col-1; j++){

            Gx =     (sobel_x[0][0] * img[i-1][j-1])   
                    + (sobel_x[0][1] * img[i-1][j])      
                    + (sobel_x[0][2] * img[i-1][j+1])  
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

            int val = (int)sqrt((Gx * Gx) + (Gy * Gy));   

            if(val < 0) val = 0;        
            if(val > 255) val = 255;

            sobel_grad[i][j]= val; 
        }
    }

    write_pgm_image("Fig0343(d).pgm",sobel_grad);   
    cout << "Fig0343(d).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART E ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned char> > output_sobel_grad_with_5x5_averaging;     

    int mask_1 = 5;  
    output_sobel_grad_with_5x5_averaging = averaging_filter(mask_1,sobel_grad,row,col);
    write_pgm_image("Fig0343(e).pgm",output_sobel_grad_with_5x5_averaging); 
    cout << "Fig0343(e).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART F ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector <vector <unsigned int> > product_of_sharpen_and_averaged_sobel_grad(row, vector <unsigned int> (col, 0)); 
    int temmp;
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
        temmp = (output_sharpened[i][j] * output_sobel_grad_with_5x5_averaging[i][j])/255.;
            if (temmp< 0) {                                                                  
                temmp = 0;}                                                                     
            else if (temmp > 255) {
                temmp = 255;} 
            product_of_sharpen_and_averaged_sobel_grad[i][j] = temmp;                   
        }
    }

    ofstream outfile_part_e;  
    outfile_part_e.open("Fig0343(f).pgm",ios::out |ios::binary |ios::trunc);  

    outfile_part_e << "P5" << endl;     
    outfile_part_e << "# Created by Alper BALMUMCU"<< endl;
    outfile_part_e << col << " " << row << endl;
    outfile_part_e << maxvalue << endl;
    outfile_part_e.close();

    ofstream newofile_part_e;     
    newofile_part_e.open("Fig0343(f).pgm",ios::out | ios::binary | ios::app);
        
    for( int i = 0; i < row; i++)   
    {
        for( int j = 0; j < col; j++)
        {
            newofile_part_e.put(product_of_sharpen_and_averaged_sobel_grad[i][j]);  
        }
    }
        
    newofile_part_e.close();
    cout << "Fig0343(f).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART G ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > output_sharpened_img_sum_of_part_a_and_f(row, vector <unsigned char> (col, 0)); 

    int temp_for_part_g;            
    for(int i=0; i< row; i++){
        for(int j=0; j< col; j++){
            temp_for_part_g = product_of_sharpen_and_averaged_sobel_grad[i][j] + img[i][j];
            if (temp_for_part_g< 0) {                                                      
                temp_for_part_g = 0;}                                                      
            else if (temp_for_part_g > 255) {
                temp_for_part_g = 255;} 
            output_sharpened_img_sum_of_part_a_and_f[i][j] = temp_for_part_g;          
        }
    }

    write_pgm_image("Fig0343(g).pgm", output_sharpened_img_sum_of_part_a_and_f);    
    cout << "Fig0343(g).pgm saved successfully to the directory\n\n";

////////////////////////////////////////////////////////////////////////
    ////////////////////// PART H ///////////////////////////
////////////////////////////////////////////////////////////////////////

    vector< vector <unsigned char> > gamma_of_part_g(row, vector <unsigned char> (col, 0));
    float gamma = 0.5;    

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            gamma_of_part_g[i][j] = 255*(pow(output_sharpened_img_sum_of_part_a_and_f[i][j]/255.,gamma)); 
        }
    }

    write_pgm_image("Fig0343(h).pgm", gamma_of_part_g);
    cout << "Fig0343(h).pgm saved successfully to the directory";


}  

