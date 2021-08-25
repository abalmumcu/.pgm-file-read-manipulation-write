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

void write_pgm_image(char name[], vector < vector<unsigned char> > & img, int & row, int & col, int & maxvalue){
    

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

    for(int i = 0; i < row; i++){                            
        for(int j = 0; j < col; j++){

            padded_img[i+n][j+n] = input_img[i][j];     
        }    
    }



    for(int i = n; i < row+n; i++){                          
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


int main() {

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

    vector < vector <unsigned char> > img_negative; 

    img_negative = read_pgm_image("Fig0304(a)(breast_digital_Xray).pgm",magicnumber_1,magicnumber_2,comment_1,row_1,col_1,maxvalue_1);
    vector< vector <unsigned char> > negative_img(row_1, vector <unsigned char> (col_1, 0)); 
    
    for(int i = 0; i < row_1; i++){         
        for(int j = 0; j < col_1; j++){

            negative_img[i][j] = (255 - img_negative[i][j]);     
        }   
    }

    write_pgm_image("Fig0304(b).pgm",negative_img,row_1,col_1,maxvalue_1);

    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//                                    LOGARITHMIC TRANSFORMATION                \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
 

    vector < vector <unsigned char> > img_log_trans;

    img_log_trans = read_pgm_image("Fig0305(a)(DFT_no_log).pgm",magicnumber_3,magicnumber_4,comment_2,row_2,col_2,maxvalue_2);
    vector< vector <unsigned char> > output_log_trans(row_2, vector <unsigned char> (col_2, 0));   

    float c = 255 / log10(1 + maxvalue_2); 
    for(int i = 0; i < row_2; i++){         
        for(int j = 0; j < col_2; j++){

            output_log_trans[i][j] = c*(255*(log((img_log_trans[i][j]/255.)+1)));   
        }   
    }
    write_pgm_image("Fig0305(b).pgm",output_log_trans,row_2,col_2,maxvalue_2);

    cout << "\n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
    cout << "//              GAMMA TRANSFORMATION              C =1 , GAMMA = 0.6 , 0.4 , 0,3         \n";
    cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";

    vector <vector <unsigned char> > img_gamma_trans;
    
    img_gamma_trans = read_pgm_image("Fig0308(a)(fractured_spine).pgm",magicnumber_4,magicnumber_5,comment_3,row_3,col_3,maxvalue_3);
    vector< vector <unsigned char> > gamma_img_1(row_3, vector <unsigned char> (col_3, 0)); 
    vector< vector <unsigned char> > gamma_img_2(row_3, vector <unsigned char> (col_3, 0));
    vector< vector <unsigned char> > gamma_img_3(row_3, vector <unsigned char> (col_3, 0));


    float gamma_1 = 0.6;    
    float gamma_2 = 0.4;
    float gamma_3 = 0.3;

    for(int i = 0; i < row_3; i++){         
        for(int j = 0; j < col_3; j++){

            gamma_img_1[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_1));     
            gamma_img_2[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_2));      
            gamma_img_3[i][j] = 255*(pow(img_gamma_trans[i][j]/255.0,gamma_3));      
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

    vector <vector <unsigned char> > img_for_noise_reduction;

    img_for_noise_reduction = read_pgm_image("Fig0335(a)(ckt_board_saltpep_prob_pt05).pgm",magicnumber_8,magicnumber_9,comment_5,row_5,col_5,maxvalue_5);
    vector <vector <unsigned char> > output_3x3_average_filter_for_noise; 


    output_3x3_average_filter_for_noise = averaging_filter(mask_1,img_for_noise_reduction,row_5,col_5); 

    write_pgm_image("Fig0335(b).pgm", output_3x3_average_filter_for_noise,row_5,col_5,maxvalue_5); 


    vector <vector <unsigned char> > sample_img_for_input_median(row_5, vector <unsigned char> (col_5, 0)); 


    for(int i = 0; i < row_5; i++){                             
        for(int j = 0; j < col_5; j++){

            sample_img_for_input_median[i][j] = img_for_noise_reduction[i][j];     
        }    
    }
    unsigned char window[9]={0}; 
    unsigned char output_median[row_5][col_5];  

    for(int i =1; i <= row_5-2; i++){
        for(int j=1; j <= col_5-2; j++){
            window[0] = sample_img_for_input_median[i-1][j-1];
            window[1] = sample_img_for_input_median[i-1][j];        
            window[2] = sample_img_for_input_median[i-1][j+1];        
            window[3] = sample_img_for_input_median[i][j-1];
            window[4] = sample_img_for_input_median[i][j];
            window[5] = sample_img_for_input_median[i][j+1];
            window[6] = sample_img_for_input_median[i+1][j-1];
            window[7] = sample_img_for_input_median[i+1][j];
            window[8] = sample_img_for_input_median[i+1][j+1];

            int k, key, l; 
            for (k = 1; k < 9; k++) 
            { 
                key = window[k]; 
                l = k - 1; 
        

                while (l >= 0 && window[l] > key) 
                {                                   
                    window[l + 1] = window[l];       
                    l = l - 1; 
                } 
                window[l + 1] = key;                   
            }
            output_median[i][j]=window[4];      
        }                                        
    }

    ofstream outfile;   
    outfile.open("Fig0335(c).pgm",ios::out |ios::binary |ios::trunc);   

    outfile << "P5" << endl;    
    outfile << "# Created by Alper BALMUMCU"<< endl;
    outfile << col_5 << " " << row_5 << endl;
    outfile << maxvalue_5 << endl;
    outfile.close();

    ofstream newof;   
    newof.open("Fig0335(c).pgm",ios::out | ios::binary | ios::app);
    
    for( int i = 0; i < row_5; i++)   
    {
        for( int j = 0; j < col_5; j++)
        {
            newof.put(output_median[i][j]);
        }
    }
    
    newof.close();


    return 0;
}
