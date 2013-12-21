//this document defines the functions declared in the header

#ifndef STACK_CPP
#define STACK_CPP
#include <math.h>
#define _USE_MATH_DEFINES
//STACK CLASS
//constructor
stack::stack() {
    head = NULL;
}

//destructor - deletes list
stack::~stack(){ 
    while(head){
        NODE *temp = head; 
        head = head->next;
        delete temp;
    }
}

//pushes new value at head of list
void stack::push (float f) { 
    NODE *temp = new NODE;
    temp->value = f;
    temp->next = head;
    head = temp;
}

//pops value from the list
float stack::pop (){ 
    float f = head->value;
    NODE *temp = head;
    head = head->next;
    delete temp;
    return f;
}

//checks if x and y values exist in the stack
bool stack::checkTop (char check){
    if(check == 'x') return head;
    if(check == 'y') {
        if(head){
            return head->next;
        }
        else return false;
    }
}

//accessors to x and y values
float stack::xValue() {
    return head->value;
}
float stack::yValue() {
    return head->next->value;
}

//RPN CLASS
//constructor
RPN::RPN(){
    degradBool = true; //true is deg, false is rad, initialized to degrees
}

//accessor to degradBool
bool RPN::checkDegRad(){
    return degradBool;
}

//basic math functions
void RPN::add(){
    push(pop() + pop());
}
void RPN::subtract(){
    float temp = pop();
    push(pop()-temp);
}
void RPN::multiply(){
    push(pop() * pop());
}
void RPN::divide(){
    float temp = pop();
    push(pop()/temp);
}

//root function - returns error if x is less than zero
int RPN::root(){
    if(xValue() < 0) return 2;
    push(sqrt(pop()));
    return 0;
}

//empties the whole stack, 
void RPN::clr(){
    while(checkTop('x')) pop(); //while x exists, delete it
}

//reciprocal, as long as x isn't 0
int RPN::recip() {
    if(xValue() == 0) return 2; //divide by zero - undefined error
    else push(1/pop());
    return 0;
}

//switch x and y values
void RPN::swap() {
    float temp1 = pop();
    float temp2 = pop();
    push(temp1);
    push(temp2);
}

//bool modifier
void RPN::degrad(){
    degradBool = !degradBool;
}

//sine, cosine, and tan functions
void RPN::sinx(){
    if(degradBool) push((pop()*M_PI)/180); //if entered as degrees, convert to radians
    push(sin(pop()));
    if(xValue() <= 0.00000265358 && xValue() >= (0-0.00000265358)) { //this the range of sin(pi) and sin(2pi) where it's very close to 0, but should be 0
        pop();                                                       //because of the approximated values of pi provided
        push(0); //pop the old value, and push 0 instead as it should be
    }
}       
void RPN::cosx(){
    if(degradBool) push((pop()*M_PI)/180); //if entered as degrees, convert to radians
    push(cos(pop()));
    if(xValue() <= 0.00000265358 && xValue() >= (0-0.00000265358)) { //the range of cos(3pi/2) and cos(pi/2) where it's very close to 0, but should be 0
        pop();                                                       //because of the approximated values of pi provided
        push(0); //pop the old value, and push 0 instead as it should be
    }
}       
int RPN::tanx(){
    float temp = xValue(); //to check if would be undefined
    if(degradBool) temp = ((temp*M_PI)/180); //convert to radians if in degrees
    if(tan(temp) > 753695 || tan(temp) < -753695) return 2; //the range of tan(pi/2) and tan(3pi/2) where it's very large, but should be undefined
    pop();                                                  //because of the approximated values of pi provided - return error
    push(tan(temp)); //otherwise, pop and push the tangent of temp (has already been converted to radians so we just use it instead of the popped value)
    return 0;
}    
int RPN::asinx(){ 
    if(xValue() > 1 || xValue() < -1) return 2; //arcsin is undefined for this domain
    push(asin(pop())); 
    if(degradBool) push((pop()*180)/M_PI); //if use wants degrees, convert from radians
    return 0;
}
int RPN::acosx(){ 
    if(xValue() > 1 || xValue() < -1) return 2; //arccos is undefined for this domain
    push(acos(pop()));
    if(degradBool) push((pop()*180)/M_PI); //if use wants degrees, convert from radians
    return 0;
}
void RPN::atanx(){ 
    if(degradBool) push((pop()*180)/M_PI); //if use wants degrees, convert from radians
    push(atan(pop()));
}
        
//power, y^x
void RPN::power(){
    push(pow(pop(), pop()));
}

//logs are undefined when x is less than 1
int RPN::ln(){
    if(xValue() < 1) return 2;
    push(log(pop()));
    return 0;
}
int RPN::commonLog(){
    if(xValue() < 1) return 2;
    push(log10(pop()));
    return 0;
}

#endif
