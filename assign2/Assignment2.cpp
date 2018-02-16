


// Shraddha Jamadade
// Student Id: 110287963
// CSci 117 Assignment 2
//_________________________________________________________________________________________________________________________________
//
// Interpreter for simplified infix expression with +,-,*,/,(),^ operations
// Keyboard input, single digit numbers only and no spaces are allowed.
// compile:  $>g++ Assignment2.cpp
// run with: >./a.out filename
//_________________________________________________________________________________________________________________________________


#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream> //for file input output
#include<math.h> //for mathematical operators (power)
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Fact2(int), Num();
string prog, s1; //string for reading 1-line input program
int indexx = 0; //global index for program string
ifstream fin; //to read data from file


//Main function

int main(int argc, const char **argv)
{ 
	string path1=argv[1]; //data file is read from the argument line and stored in variable
	fin.open(path1.c_str());
	getline(fin,s1);
	while(!fin.eof()) //continue reading file till end of file
	{
		prog+=s1;
		getline(fin,s1);
	}
	cout<<"result= "<<Exp()<<endl; //Function Exp() called to evaluate expression and display result
}

//Exp() function calls the Exp2() function for solving addition and subtraction operations

int Exp()
{ 
	return Exp2(Term()); //Result of Term() function is passed as parameter to Exp2()
}

//Term() function calls the Term2() function for solving multiplication and division operations

int Term()
{
	 return Term2(Fact()); //Result of Fact() function is passed as parameter to Term2()
}

//Exp2() recursive function where the parameter passed is the result of multiplication and division operations
//checks whether it is end of expression
//gets one character from input expression
//skips blank spaces if any
//checks for addition'+' and subtraction'-' operations
//performs operation
//returns result

int Exp2(int inp)
{
	int result = inp;
	if (indexx < prog.length())   //if not the end of program string
	{ 
		char a = prog.at(indexx++); //get one chr from program string
		while (a==' ' && indexx < prog.length())
			a= prog.at(indexx++);
		if (a == '+')
		result = Exp2(result + Term());  //handles T+T
		else if (a == '-')
		result = Exp2(result - Term());  //handles T-T
	}
	return result;
}

//Term2() recursive function where the parameter passed is the result of the power operation
//checks whether it is end of expression
//gets one character from input expression
//skips blank spaces if any
//checks for multiplication'*' and division'/' operations
//performs operation
//returns result

int Term2(int inp)
{
	int result = inp;
	if (indexx < prog.length())   //if not the end of program string
	{
		char a = prog.at(indexx++); //get one chr from program string
		while (a==' ' && indexx < prog.length())
			a= prog.at(indexx++);
		if (a == '*')
		result = Term2(result * Fact()); //handles consecutive * operators
		else if (a == '/')
		result = Term2(result / Fact()); //handles consecutive / operators
		else if (a == '+' || a == '-' || a == ')')     //if + or -, get back one position
		indexx--;
	}
	return result;
}

//Fact() function calls the Fact2() function for performing power operations

int Fact()
{
	return Fact2(Num()); //Result of Num() function is passed as parameter to Fact2()
}

//Fact2() recursive function where the parameter passed is a numeric value
//checks whether it is end of expression
//gets one character from input expression
//skips blank spaces if any
//checks for power'^' operations
//performs operation
//returns result

int Fact2(int inp)
{
	int result = inp;
	if (indexx < prog.length())
	{
		char a = prog.at(indexx++); //get one chr from program string  
		while (a == ' ' && indexx < prog.length())
			a = prog.at(indexx++);
		if (a == '^')
			result = Fact2(pow(result,Fact()));
		else
			indexx--;
	}
	return result;
}

//Num() recursive function 
//gets one character from input expression
//skips blank spaces if any
//checks for () operations
//converts each character into numeric number
//returns result

int Num()
{
	char a = prog.at(indexx++); //get one chr from program string  	
	while (a == ' ' && indexx < prog.length())
		a = prog.at(indexx++);
	if (a == '(')
		return Exp();
	else 
		return atoi(&a); //converts a char to a numeric number and return
}
