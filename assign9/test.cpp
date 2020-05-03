#include <iostream>
#include <sstream>
using namespace std;

int main (void)
{
    char a = 'ff';
    char b = 't';
    int inta, intb;
    stringstream ss;
    ss << hex << a;
    ss >> inta;
    ss << hex << b;
    ss >> intb;

    inta = static_cast<int>(inta);
    intb = static_cast<int>(intb);
}
