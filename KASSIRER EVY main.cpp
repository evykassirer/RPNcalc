/* EVY KASSIRER     ICS4U     Mr Kroneberg
Assignment: RPN Calculator assignment*/
                                                            
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "stack.h" //class member declarations
#include "stack.cpp" //class member definitions
#define _USE_MATH_DEFINES
using namespace std;

//check to see if input is a number
bool isNum(string input) {
    bool numBool = true;
    if((input[0] < '0' || input[0] > '9') && input[0] != '-') numBool = false; //fist can be digits between 0-9 or '-'
    if(input[0] == '-' && (!input[1] || input[1] == '.') ) numBool = false; //if the string is only a subtraction sign, or '-.'
    for(int i = 1; i < input.length(); i++){
        if((input[i] < '0' || input[i] > '9') && input[i] != '.') numBool = false; //after the first, can be 0-9 or a .
    }
    return numBool;
}


//function for input - if it's a number, this function reads it back in as a float 
float getNum(string input){
    float num;
    istringstream(input) >> num;
    return num;
}


//USER INTERFACE
void displayCalc(RPN &calc){
    cout << "\t\t\t\t RPN CALCULATOR" << endl << endl; //title
    
    //display possibilities for user input
    cout << "+  :  y+x \t pi\t: 3.14159 \t\t degrees";
            if(calc.checkDegRad()) cout << " (ON)";
            cout << "\t radians";
            if(!calc.checkDegRad()) cout << " (ON)";
            cout << endl << endl << "-  :  y-x \t e\t: euler's number \t sin  cos  tan  asin  acos  atan" << endl <<
            "*  :  y*x \t sqrt\t: square root x \t recip\t: 1/x" << endl << endl <<
            "/  :  y/x \t ln\t: natural log x \t d\t: delete x" << endl << endl <<
            "^  :  y^x \t log\t: common log x \t\t switch\t: x<-->y" << endl << endl <<
            "q  :  quit program \t\t\t\t clr\t:  clear all data" << endl;
    for(int i = 0; i<78; i++) {cout << "_"; } //a line (formatting)
    cout << endl << endl;        
    
    //display stored x and y values        
    if(calc.checkTop('x'))cout << "x: " << calc.xValue() << endl;
    if(calc.checkTop('y'))cout << "y: " << calc.yValue() << endl;
    for(int i = 0; i<78; i++) {cout << "_"; } //a line (formatting)
    cout << endl << endl;
}


//MAIN

int main() {
    RPN calc; //calculator     
    string input = "";
    int error = 0; //0 is fine, 1 is bad input (doesn't exit, or doesn't work with number of arguments), 2 is undefined (divide by zero, tan 90, etc)
    
    while(input != "q"){
        system("cls");
        
        //display x and y values, and options for user
        displayCalc(calc);
        
        //display error (if applicable)
        switch(error){
            case 0: //no error
                break;
            case 1: //none of the functions were selected
                if(input != "q") {
                    cout << "ERROR: Input not recognized or not possible with the number of values entered" << endl << endl;
                }
                error = 0;
                break;
            case 2: //input recognized, but error like dividing by zero or tan90
                cout << "ERROR: undefined" << endl << endl;
                error = 0;
                break;
        }
        
        //user input
        cout << "Enter a number or valid input from above choices: ";               
        cin >> input;
        
        //INPUT ---------> FUNCTIONS
                
        //functions possible with empty stack:
        if (isNum(input)) {
            calc.push(getNum(input)); //if it is number input, change string to float
        }
        else if (input == "pi") calc.push(M_PI);
        else if (input == "e") calc.push(M_E);
        else if (input == "clr") calc.clr();
        else if (input == "degrees" || input == "radians"){ //if they enter degrees or radians
            if ((input == "degrees" && !calc.checkDegRad()) || (input == "radians" && calc.checkDegRad())) calc.degrad(); //only actually changes if needed
        }
        
        //functions possible with only one in stack:
        else if(calc.checkTop('x')){
            if(input == "d") calc.pop();
            else if (input == "sqrt")error = calc.root();
            else if (input == "log") error = calc.commonLog();
            else if (input == "ln") error = calc.ln();
            else if (input == "sin") calc.sinx();
            else if (input == "cos") calc.cosx();
            else if (input == "tan") error = calc.tanx();
            else if (input == "asin") error = calc.asinx();
            else if (input == "acos") error = calc.acosx();
            else if (input == "atan") calc.atanx();
            else if (input == "recip") error = calc.recip();                 
            
            //functions only possible with two in stack:
            else if (calc.checkTop('y')) {
                if(input == "+") calc.add();
                else if (input == "-") calc.subtract();
                else if (input == "*") calc.multiply();
                else if (input == "/") {
                    if(calc.xValue() == 0) error = 2;
                    else calc.divide();
                }
                else if(input == "^") calc.power();
                else if (input == "switch") calc.swap();
                else error = 1;
            }
            else error = 1;
        }
        else error = 1;
    }   

    return 0;
}
