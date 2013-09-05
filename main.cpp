#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

string blankCreator(int);
string square(string&, int);
string replaceChar(string, int, string);
void zeroCopy(int, string&, int);
void wholeSquare(int, string&, int);
void soloMultiply(int, int, string&, int);
void cleanup(int, string&, int);

int main()
{
    /* The user needs to enter a series of 0s as though they were inputting 0 symbols on to a Turing machine tape. This means entering just a single 0 if you wish to have the number one squared and then represented by 0s on the tape at the end. The code just below is to calculate a time delay between printing each stage of the Turing machine's process, should the user wish to use one.*/
    
    cout << "Please enter the length of time delay you would like between each operation of the Turing machine simulator, in seconds (if you wish to have no delay then enter 0): ";
    float N = 0;
    cin >> N;
    int W = N*1000000;
    
    string toSquare = "";      // initialising the Turing machine tape
    
    cout << "Please enter the number that you would like to square in 0 form, e.g. for 4, type 0000 (the final output will show a representation of the tape of a Turing machine with all blank symbols, B, other than the final result, which will displayed as 0s): ";
    cin >> toSquare;

    square(toSquare, W);      // calls the main function for the Turing machine
    
    return 0;
}

string square(string& s, int W)
{
    string squared = "B" + s + blankCreator(s.length());
    cout << squared << endl;
    usleep(W);
    
    squared = replaceChar(squared, s.length()+1, "#");      // prints a # symbol so that the Turing machine can distinguish between different sections of the tape
    cout << squared << endl;
    usleep(W);
    
    zeroCopy(s.length(), squared, W);
    
    squared = replaceChar(squared, s.length()*2+2, "#");      // prints a # symbol so that the Turing machine can distinguish between different sections of the tape
    cout << squared << endl;
    usleep(W);
    
    wholeSquare(s.length(), squared, W);
    cleanup(s.length(), squared, W);
    
    return squared;
}

string blankCreator(int n)      // adds an appropriate number of blank symbols to the tape string
{
    string blanks = "";
    
    for(int i = 0; i < (n*n + n + 3); i++)
        blanks += "B";
    
    return blanks;
}

string replaceChar(string str, int i, string ch)      // funciton for replacing characters in strings
{
    str[i] = ch[0];
    
    return str;
}

void zeroCopy(int n, string& s, int W)      // funciton for doing an initial copy of the number of 0s, and represents states q3-q7 on the transition diagram
{
    for(int i = 0; i < n; i++)
    {
        s = replaceChar(s, 1+i, "1");
        cout << s << endl;
        usleep(W);
        s = replaceChar(s, n+2+i, "0");
        cout << s << endl;
        usleep(W);
    }
}

void wholeSquare(int n, string& s, int W)      // function for printing the appropriate number of 0s to the tape so that the original number of 0s is squared and represents states q11-q20 on the transition diagram
{
    for(int i = 0; i < n; i++)
    {
        s = replaceChar(s, 1+i, "0");
        cout << s << endl;
        usleep(W);
        soloMultiply(n, i, s, W);
    }
}

void soloMultiply(int n, int i, string& s, int W)      // function for printing the appropriate number of 0s to the tape for each individual 0 in the section of the tape created from the original copy and represents states q14-q17 on the transition diagram
{
    for(int j = n; j > 0; j--)
    {
        s = replaceChar(s, n+1+j, "1");
        cout << s << endl;
        usleep(W);
        s = replaceChar(s, 2*n+3+n*i+(n-j), "0");
        cout << s << endl;
        usleep(W);
    }
    for(int q = 0; q < n; q++)
    {
        s = replaceChar(s, n+2+q, "0");
        cout << s << endl;
        usleep(W);
    }
}

void cleanup(int n, string& s, int W)      // function that writes blank symbols over all squares of the tape otehr than the result and represents states q21-q22 on the transition diagram
{
    for(int i = 2*n+2; i > 0; i--)
    {
        s = replaceChar(s, i, "B");
        cout << s << endl;
        usleep(W);
    }
}
