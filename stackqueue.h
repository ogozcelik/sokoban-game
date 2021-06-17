#ifndef STACKQUEUE
#define STACKQUEUE

#include <iostream>
#include <stdlib.h>

using namespace std;
const int MaxStackSize=150;
/*
I use Stack logic to compose StackQueue
class. LIFO structure is considered.
*/
template <class T>
class StackQueue {
private:
    T stacklist[MaxStackSize]; // An array will holds Sokoban objects later
    int top;                   // Top can show front
public:
    StackQueue();              // Dummy constructor
    //METHODS
    void push__front(const T& item);
    T pop__front();
    T pop__rear();
    int StackQueueFull() const;
    int StackQueueEmpty() const;
    int get__top() const;      // This get "int top" which is need in Sokoban class
    void display() const;      // Display the stack
} ;

template <class T>
StackQueue<T>::StackQueue():top(-1) {}  //Initialize the StackQueue with top -1
                                        //As in Stacks

//If StackQueue is full return true
template <class T>
int StackQueue<T>::StackQueueFull() const {
    return top==(MaxStackSize-1);
}

//If StackQueue is empty return false
template <class T>
int StackQueue<T>::StackQueueEmpty() const {
    return top==-1;
}

//Push StackQueue as in Stacks
template <class T>
void StackQueue<T>::push__front(const T& item){
    if (StackQueueFull()){
        cerr<<"Overflow"<<endl;
        exit(1);
    }
    top++;
    stacklist[top]=item;
}

//This will a bit tricky. Normally it should be top instead of top-1
//However we will undo the last valid move and it should be printed
//so I return the last valid move by [top-1], that may cause error
//when undo the initial position, so I put an checking if statement
//when top==0 in the main part of the Sokoban.
template <class T>
T StackQueue<T>::pop__front() {
    T temp;
    if (StackQueueEmpty()){
        cerr<<"Empty"<<endl;
        exit(1);
    }
    temp=stacklist[top-1];
    top--;
    return temp;
}


template <class T>
T StackQueue<T>::pop__rear(){
    T temp = stacklist[0];            //hold rear element
    T templist[MaxStackSize-1];       //temp list with one index decrease
    for (int i=(MaxStackSize-1);i>0;i--){
        templist[i-1] = stacklist[i]; //store elements in temp array except rear element
    }
    for (int i=0;i<MaxStackSize-2;i++){
        stacklist[i]=templist[i];     //restore elements in main array
    }
    top--;                            //decrease top
    return temp;                      //return the rear element
}

//This method is to get private member
template <class T>
int StackQueue<T>::get__top() const {
    return top;
}

//Just display the StackQueue
template <class T>
void StackQueue<T>::display() const{
    for (int i = MaxStackSize-1;i>=0;i--){
        cout<<stacklist[i]<<" ";
    }
}

#endif  //STACKQUEUE
