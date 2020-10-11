#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;

int main() {
    
    int row = 0;
    int col = 0;
    int maxvalue = 0;
    char magicnumber_1,magicnumber_2;
    string inputLine = "";
    stringstream ss;

    ifstream infile;
    infile.open("Fig0309(a)(washed_out_aerial_image).pgm");

    infile >> magicnumber_1 >> magicnumber_2;

    
    if (magicnumber_1 == 'P' && magicnumber_2 == '5'){
        getline(infile,inputLine); 
        cout << "Version : P5"<<endl; }
    
    else {        
        cout << " The File Version is Wrong" << endl;
        exit(1); }
    
    getline(infile,inputLine);
    cout << "Comment : " << inputLine << endl;
    ss << infile.rdbuf();
    ss >> col >> row;
    cout << "Width and Height : " << col <<" "<< row << endl;
    ss >> maxvalue;
    
    if (maxvalue == 255){
        cout << "Maximum Value : " << maxvalue << endl;}
   
    else {
        cout <<"Maximum Value Error!!\nYour Maximum Value: " << maxvalue << endl;
        exit(2);}


    uint8_t array_data[row][col];
    
    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){ 
            ss >> array_data[i][j];
        }
    }

    infile.close();


    ofstream outfile;
    outfile.open("output.pgm", std::ios_base::out
                            |std::ios_base::binary
                            |std::ios_base::trunc );
    outfile << "P5" << endl;
    outfile << "# Created by Alper BALMUMCU for Image Processing Course"<< endl;
    outfile << col << " " << row << endl;
    outfile << maxvalue << endl;

    for (int i =0 ; i< row ; i++){
		for(int j=0 ; j<col ; j++){
			if(i<100 && j < 100){
				outfile << static_cast <char>(10);
			}
			else{
				outfile << static_cast <char>(array_data[i][j]);
			}
		}	
	}
    outfile.close();

    return 0;
}