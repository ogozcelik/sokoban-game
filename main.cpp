#include <iostream>
#include <fstream>
#include "stackqueue.h"

using namespace std;

class Sokoban {
private:
    char data[6][8];        //char array member
public:
    Sokoban () {}            //dummy constructor
    Sokoban (char arr[6][8]);//A constructor that initializes the class from a char array
    Sokoban (string path);   //A constructor that initializes the class from a text file
    Sokoban (const Sokoban &other);//a copy constructor
    Sokoban& operator = (const Sokoban &t);//copy assignment operator
    //METHODS
    bool move_up();
    bool move_down();
    bool move_left();
    bool move_right();
    bool is_solved();
    void print() const;
};

//Taking the elements of arr and pass them to
//the data member
Sokoban::Sokoban(char arr[6][8]){
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            data[i][j]=arr[i][j];
        }
    }
}

//Read the text file as in Assignment
Sokoban::Sokoban(string path){
    char dummy;
    ifstream file;
    file.open(path);
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            file >> noskipws >> data[i][j];
        }
        file >> noskipws >> dummy;
    }
    file.close();
}

//Creating copy constructor similar to
//main constructor whose parameter is char array
Sokoban::Sokoban(const Sokoban &other) {
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            data[i][j]=other.data[i][j];
        }
    }
}

//Creating copy assignment operator similar to copy
//constructor, in this case return the initial state
//of the class.
Sokoban&Sokoban:: operator = (const Sokoban &t){
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            data[i][j]=t.data[i][j];
        }
    }
    return *this;
}

//The move_up, move_down, move_left and move_right classes are almost
//the same.
bool Sokoban::move_up(){
    int row, col;           // First initialize row and col variables.
    //Then find the player in the array
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (data[i][j]=='@' || data[i][j]=='+'){
                row=i;
                col=j;
            }
        }
    }
    //After finding the player, figure out whether it move up
    //by searching the next blocks with if statements
    if (data[row-1][col]=='#') //if next block is # return false
        return false;
    //if next row is $ but the next after it $, # or * return false
    else if (data[row-1][col]=='$' && (data[row-2][col]=='$' || data[row-2][col]=='#' || data[row-2][col]=='*'))
        return false;
    //if next row is * but the next after it $, # or * return false
    else if (data[row-1][col]=='*' && (data[row-2][col]=='$' || data[row-2][col]=='#' || data[row-2][col]=='*'))
        return false;
    //else the player can move up
    else{
        //if the player is @
        if (data[row][col]=='@') {
            data[row][col]=' '; // make @ to ' ' after it moved up
            if (data[row-1][col]=='.') //if the next is '.'
                data[row-1][col]='+';  //make the @ to +
            else if(data[row-1][col]==' ')//if the next is ' '
                data[row-1][col]='@';     //make the @ to @
            else if(data[row-1][col]=='$'){ //if the next is $
                data[row-1][col]='@';       //make the next is @ but
                if(data[row-2][col]=='.')   //if the next after it '.'
                    data[row-2][col]='*';   // make $ to *
                else if(data[row-2][col]==' ') // if the next after it ' '
                    data[row-2][col]='$';    // make $ to $ again
            }
            else if(data[row-1][col]=='*'){ //if the next is *
                data[row-1][col]='+';       //make the next is + but
                if(data[row-2][col]=='.')   //if the next after it '.'
                    data[row-2][col]='*';   //make * to * again
                else if(data[row-2][col]==' ') //if the next after it ' '
                    data[row-2][col]='$';    //make * to $
            }
        }
        else if (data[row][col]=='+'){
            data[row][col]='.';    //make + to '.' after it moved up
            if (data[row-1][col]=='.') //if the next is '.'
                data[row-1][col]='+';  //make the + to +
            else if(data[row-1][col]==' ') // if the next is ' '
                data[row-1][col]='@';     // make the + to @
            else if(data[row-1][col]=='$'){ // if the next is $
                data[row-1][col]='@'; // make the next is @ but
                if(data[row-2][col]=='.') // if the next after it '.'
                    data[row-2][col]='*'; // make $ to *
                else if(data[row-2][col]==' ') //  if the next after it ' '
                    data[row-2][col]='$'; // make $ to $ again
            }
            else if(data[row-1][col]=='*'){ // if the next is *
                data[row-1][col]='+'; // make the next is + but
                if(data[row-2][col]=='.') //if the next after it '.'
                    data[row-2][col]='*'; //make * to *
                else if(data[row-2][col]==' ') //if the next after it ' '
                    data[row-2][col]='$'; //make * to $
            }
        }
        return true;
    }
}

//the same procedure is done like in move_up
bool Sokoban::move_down(){
    int row, col;
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (data[i][j]=='@' || data[i][j]=='+'){
                row=i;
                col=j;
            }
        }
    }
    if (data[row+1][col]=='#')
        return false;
    else if (data[row+1][col]=='$' && (data[row+2][col]=='$' || data[row+2][col]=='#' || data[row+2][col]=='*'))
        return false;
    else if (data[row+1][col]=='*' && (data[row+2][col]=='$' || data[row+2][col]=='#' || data[row+2][col]=='*'))
        return false;
    else{
        if (data[row][col]=='@') {
            data[row][col]=' ';
            if (data[row+1][col]=='.')
                data[row+1][col]='+';
            else if(data[row+1][col]==' ')
                data[row+1][col]='@';
            else if(data[row+1][col]=='$'){
                data[row+1][col]='@';
                if(data[row+2][col]=='.')
                    data[row+2][col]='*';
                else if(data[row+2][col]==' ')
                    data[row+2][col]='$';
            }
            else if(data[row+1][col]=='*'){
                data[row+1][col]='+';
                if(data[row+2][col]=='.')
                    data[row+2][col]='*';
                else if(data[row+2][col]==' ')
                    data[row+2][col]='$';
            }
        }
        else if (data[row][col]=='+'){
            data[row][col]='.';
            if (data[row+1][col]=='.')
                data[row+1][col]='+';
            else if(data[row+1][col]==' ')
                data[row+1][col]='@';
            else if(data[row+1][col]=='$'){
                data[row+1][col]='@';
                if(data[row+2][col]=='.')
                    data[row+2][col]='*';
                else if(data[row+2][col]==' ')
                    data[row+2][col]='$';
            }
            else if(data[row+1][col]=='*'){
                data[row+1][col]='+';
                if(data[row+2][col]=='.')
                    data[row+2][col]='*';
                else if(data[row+2][col]==' ')
                    data[row+2][col]='$';
            }
        }
        return true;
    }
}

//the same procedure is done like in move_up
bool Sokoban::move_left(){
    int row, col;
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (data[i][j]=='@' || data[i][j]=='+'){
                row=i;
                col=j;
            }
        }
    }
    if (data[row][col-1]=='#')
        return false;
    else if (data[row][col-1]=='$' && (data[row][col-2]=='$' || data[row][col-2]=='#' || data[row][col-2]=='*'))
        return false;
    else if (data[row][col-1]=='*' && (data[row][col-2]=='$' || data[row][col-2]=='#' || data[row][col-2]=='*'))
        return false;
    else{
        if (data[row][col]=='@') {
            data[row][col]=' ';
            if (data[row][col-1]=='.')
                data[row][col-1]='+';
            else if(data[row][col-1]==' ')
                data[row][col-1]='@';
            else if(data[row][col-1]=='$'){
                data[row][col-1]='@';
                if(data[row][col-2]=='.')
                    data[row][col-2]='*';
                else if(data[row][col-2]==' ')
                    data[row][col-2]='$';
            }
            else if(data[row][col-1]=='*'){
                data[row][col-1]='+';
                if(data[row][col-2]=='.')
                    data[row][col-2]='*';
                else if(data[row][col-2]==' ')
                    data[row][col-2]='$';
            }
        }
        else if (data[row][col]=='+'){
            data[row][col]='.';
            if (data[row][col-1]=='.')
                data[row][col-1]='+';
            else if(data[row][col-1]==' ')
                data[row][col-1]='@';
            else if(data[row][col-1]=='$'){
                data[row][col-1]='@';
                if(data[row][col-2]=='.')
                    data[row][col-2]='*';
                else if(data[row][col-2]==' ')
                    data[row][col-2]='$';
            }
            else if(data[row][col-1]=='*'){
                data[row][col-1]='+';
                if(data[row][col-2]=='.')
                    data[row][col-2]='*';
                else if(data[row][col-2]==' ')
                    data[row][col-2]='$';
            }
        }
        return true;
    }
}

//the same procedure is done like in move_up
bool Sokoban::move_right(){
    int row, col;
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (data[i][j]=='@' || data[i][j]=='+'){
                row=i;
                col=j;
            }
        }
    }
    if (data[row][col+1]=='#')
        return false;
    else if (data[row][col+1]=='$' && (data[row][col+2]=='$' || data[row][col+2]=='#' || data[row][col+2]=='*'))
        return false;
    else if (data[row][col+1]=='*' && (data[row][col+2]=='$' || data[row][col+2]=='#' || data[row][col+2]=='*'))
        return false;
    else{
        if (data[row][col]=='@') {
            data[row][col]=' ';
            if (data[row][col+1]=='.')
                data[row][col+1]='+';
            else if(data[row][col+1]==' ')
                data[row][col+1]='@';
            else if(data[row][col+1]=='$'){
                data[row][col+1]='@';
                if(data[row][col+2]=='.')
                    data[row][col+2]='*';
                else if(data[row][col+2]==' ')
                    data[row][col+2]='$';
            }
            else if(data[row][col+1]=='*'){
                data[row][col+1]='+';
                if(data[row][col+2]=='.')
                    data[row][col+2]='*';
                else if(data[row][col+2]==' ')
                    data[row][col+2]='$';
            }
        }
        else if (data[row][col]=='+'){
            data[row][col]='.';
            if (data[row][col+1]=='.')
                data[row][col+1]='+';
            else if(data[row][col+1]==' ')
                data[row][col+1]='@';
            else if(data[row][col+1]=='$'){
                data[row][col+1]='@';
                if(data[row][col+2]=='.')
                    data[row][col+2]='*';
                else if(data[row][col+2]==' ')
                    data[row][col+2]='$';
            }
            else if(data[row][col+1]=='*'){
                data[row][col+1]='+';
                if(data[row][col+2]=='.')
                    data[row][col+2]='*';
                else if(data[row][col+2]==' ')
                    data[row][col+2]='$';
            }
        }
        return true;
    }
}

//this method simply search whether there is remaining $
//in char array or not. If there is $ which means the puzzle
//is not solved yet so return false otherwise return true
bool Sokoban::is_solved() {
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (data[i][j]=='$'){
                return false;
            }
        }
     }
    return true;
}

//simply print the indexes of the char array
void Sokoban::print() const {
    cout<<"*****Map*****"<<endl;
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            if (j==7)
                cout<< data[i][j]<<'\n';
            else
                cout<< data[i][j];
        }
    }
    cout<<'\n';
}

//MAIN FUNCTION
int main()
{
    Sokoban obj("Sample_puzzle.txt"); //Prefer the text constructor
    StackQueue<Sokoban> obj2;        //create instances of StackQueue with Sokoban argument
    obj2.push__front(obj);          //initially push the puzzle once
    obj.print();                   //and print it
    char key;                     //char key will be used for w,a,s,d,z,r
    //loop until puzzle is solved
    while(!obj.is_solved()){
        cin>>key; //for each loop wait for the key
        if (key == 'w'){ //when 'w' pushed
            if(obj.move_up()) //if player can move up
                obj2.push__front(obj); //push the new puzzle to stackqueue
                obj.print();            //print it
        }
        if (key == 's'){ //when 's' pushed
            if(obj.move_down()) //if player can move down
                obj2.push__front(obj); //push the new puzzle to stackqueue
                obj.print();           //print it
        }
        if (key == 'd'){ //when 'd' pushed
            if(obj.move_right()) //if player can move right
                obj2.push__front(obj); //push the new puzzle to stackqueue
                obj.print();           //print it
        }
        if (key == 'a'){ //when 'a' pushed
            if(obj.move_left())  //if player can move left
                obj2.push__front(obj); //push the new puzzle to stackqueue
                obj.print();           //print it
        }
        if (key == 'z'){ //when 'z' pushed
                if(obj2.get__top()==0){ //if top is 0 meaning the initial state
                    obj2.pop__front();  //pop it (and it returns [top-1] which is random in this case)
                    cout<<"Program is closed"<<endl; //then close the program
                    break;  //break from program
                }
                obj2.pop__front().print(); //pop the front and return the last valid move
        }
        if (key=='r') { //when 'r' pushed
                 cout<<"------ALL MOVES------"<<endl;
                while(obj2.get__top()!=0) //until it is top==0
                {
                    obj2.pop__rear().print(); //pop first the initial state and then continue
                }
                    cout<<"Program is closed"<<endl;
                    break; //terminate the program
        }
    }

    return 0;
}
