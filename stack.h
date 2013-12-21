//header declares classes 

#ifndef STACK_H //checks to make sure this header hasn't been run already to avoid double declarations
#define STACK_H

//STACK CLASS
class stack {
    private:
        struct NODE{ 
            float value;
            NODE *next;
        };
        NODE *head;
    public:
        stack(); //constructor
        ~stack(); //desctructor
        void push(float f);
        float pop();
        bool checkTop (char check); //checks if there is an x or y value in the stack
        //accessors
        float xValue();
        float yValue(); 
};

class RPN:public stack{
    private:
        bool degradBool; //stores if the program is currently using radians or degrees                                                        
    public:
        RPN(); //constructor
        //destructor not required because no dynamic memory used
        
        //accessors
        bool checkDegRad(); //returns value of degradBool
        
        //basic math
        void add(); 
        void subtract();
        void multiply();
        void divide();
        
        int root();
        void clr();
        int recip();
        void swap() ;
        
        //trig
        void degrad();  //modifier
        void sinx(); 
        void cosx();
        int tanx();
        int asinx(); 
        int acosx();
        void atanx();
        
        void power();
        int ln();
        int commonLog();
};

#endif
