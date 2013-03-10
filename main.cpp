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
    cout << "Please enter the length of time delay you would like between each operation of the Turing machine simulator (in seconds): ";
    float N = 0;
    cin >> N;
    int W = N*1000000;
    
    string toSquare = "";
    
    cout << "Please enter the number that you would like to square in 0 form (e.g. for 4, type 0000): ";
    cin >> toSquare;

    square(toSquare, W);
    
    return 0;
}

string square(string& s, int W)
{
    string squared = "B" + s + blankCreator(s.length());
    cout << squared << endl;
    usleep(W);
    
    squared = replaceChar(squared, s.length()+1, "#");
    cout << squared << endl;
    usleep(W);
    
    zeroCopy(s.length(), squared, W);
    
    squared = replaceChar(squared, s.length()*2+2, "#");
    cout << squared << endl;
    usleep(W);
    
    wholeSquare(s.length(), squared, W);
    cleanup(s.length(), squared, W);
    
    return squared;
}

string blankCreator(int n)
{
    string blanks = "";
    
    for(int i = 0; i < (n*n + n + 3); i++)
        blanks += "B";
    
    return blanks;
}

string replaceChar(string str, int i, string ch)
{
    str[i] = ch[0];
    
    return str;
}

void zeroCopy(int n, string& s, int W)
{
    for(int i = 0; i < n; i++)
    {
        s = replaceChar(s, n+2+i, "0");
        cout << s << endl;
        usleep(W);
    }
}

void wholeSquare(int n, string& s, int W)
{
    for(int i = 0; i < n; i++)
    {
        s = replaceChar(s, 1+i, "1");
        cout << s << endl;
        usleep(W);
        soloMultiply(n, i, s, W);
    }
}

void soloMultiply(int n, int i, string& s, int W)
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

void cleanup(int n, string& s, int W)
{
    for(int i = 2*n+2; i > 0; i--)
    {
        s = replaceChar(s, i, "B");
        cout << s << endl;
        usleep(W);
    }
}
