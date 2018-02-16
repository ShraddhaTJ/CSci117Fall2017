// Shraddha Jamadade
// Student Id: 110287963
// CSci 117 Assignment 4
// Date: Oct 16, 2017
//__________________________________________________________________
//
// Assignment to implement associative arrays – unordered_map and 
// vector in C++.
// Given a data file of biological sequences in which
// each protein sequence (a string) consists of label and a string 
// of amino acids, find duplicated sequences and
// rebuild the data file with multiple labels for duplicated sequences.
//
// Input: A file containing labels and corresponding string sequences.
// Output: Data file after manipulating the duplicate sequences. List 
// of all labels and string sequences.
//
//___________________________________________________________________


#include<iostream>  //for input output stream
#include<fstream>   //for file input output
#include<string>    //to allow string manipulation
#include<unordered_map> //defines unordered map container classes
#include<vector>    //for vector creation
using namespace std;

int main()
{
	string s,s1;  	
//Variables to hold the contents from input file. s for labels and s1 for for sequences
	std::unordered_map<string, vector<string> > mapTable1;  	
                       //Creation of a map
	fstream file;    //input output operations on 'file'
	file.open("Prog4-data.txt");        //opens the file Prog4-data.txt
	if (file.is_open()) 	//If the file opened, give a result message
	{
		cout << "Successfully opened the file"<<endl;
	}
	else        //error message
	{
		cout << "File opening unsuccessful"<<endl;
	}
	file >> s >> s1;   	//Store the contents of files into the string variables
	mapTable1[s1].push_back(s); //insert string in unordered map mapTable1
	while (file >> s >> s1)
	{
		if (mapTable1[s1].empty()) 	//If a sequence is not already read. If map table is empty
		{
			mapTable1[s1].push_back(s); 
				//insert, s:labels string, s1:sequence string
		}
		else
		{
			mapTable1[s1].push_back(s); 
				//insert, s:labels string, s1:sequence string
		}
	}
  ofstream oFile;    //An output file oFile is generated
  oFile.open("Output.txt");     //open output file
  std::unordered_map<string,vector <string> >::const_iterator it=mapTable1.begin();

    oFile<<"The mappings are:\n";
      for (it=mapTable1.begin();it!=mapTable1.end(); it++)  
					//iterate through the entire map table
      {
    	  for(unsigned int i=0;i<it->second.size();i++) 
					//iterating through the vector
    	        {
    	        	cout<<","<<it->second[i]<<",";      
					//to get the vector from iterator
    	        	oFile << it->second[i]<<",";
                }
      	std::cout << " " << it->first << ":"<<endl ;   //display
      	oFile <<endl<< it->first << endl;
      }
      return 0; 			//exit at end of function
}
