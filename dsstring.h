#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>
#include <ctype.h>
#include <fstream>

using namespace std;

class DSString
{
    //overloaded insertion and extraction operators
    friend ostream& operator<<(ostream&, const DSString&);
    friend ostream& operator<<(ostream&, const DSString *);
    friend ifstream& getline(ifstream&, DSString&, char delim);

    private:
        int length;
        char * data;

    public:
        //constructors for a DSString object
        DSString();
        DSString(char *);

        //copy constructor
        DSString(const DSString&);

        //destructor
        ~DSString();

        //getter methods
        int getLength();
        char * getString();

        //setter methods
        void setLength(int newLength) { length = newLength; };
        void setString(char * newString) { data = newString; };

        //real substring methods
        DSString substring(int);
        DSString substring(int, int);

        //indexOf methods
        int indexOf(char);
        int indexOf(int, char);

        //lowercase method that makes a string all lowercase letters
        DSString toLowerCase();

        //converts string to integer
        int toInt(DSString&);

        //overloaded operators
        DSString& operator=(const DSString&);
        bool operator==(const DSString&);
        DSString& operator+(DSString&);
        DSString& operator+(char);
        bool operator<(const DSString&) const;
};
#endif
