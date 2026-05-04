#include "dsstring.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <stdlib.h>

using namespace std;
//constructors
DSString::DSString()
{
    data = nullptr;
    length = 0;
}

DSString::DSString(char * stringData)
{
    data = new char[strlen(stringData) + 1];
    strcpy(data, stringData);

    length = strlen(stringData);
}

//destructor
DSString::~DSString()
{
    //cout << "I am in the destructor right now..." << endl; //debugging code
    delete []data;
}

//copy constructor
DSString::DSString(const DSString& string)
{
    this->length = strlen(string.data);

    this->data = new char[strlen(string.data) + 1];
    strcpy(this->data, string.data);
}

//returns the length of the DSString object
int DSString::getLength()
{
    int lengthCounter = 0;
    char currentChar = 'a'; //default value because why not
    //loops through the char * and for each character adds 1 to the counter to get the length
    while (currentChar != '\0')
    {
        lengthCounter++;
        currentChar = data[lengthCounter];
    }
    length = lengthCounter;
    return length;
}

//returns the actual content in the DSString
char * DSString::getString()
{
    return data;
}

//potential new substring methods?
DSString DSString::substring(int startIndex)
{
    char * stringData = this->data;
    int stringLength = this->getLength();
    char * substring = new char[stringLength + 1];
    int counter = 0;
    for (int i = startIndex; i < stringLength; ++i)
    {
        substring[counter] = stringData[i];
        counter++;
    }
    substring[counter] = '\0';
    DSString newSubstring(substring);
    //cout << "Substring data: " << newSubstring->data << endl;
    return newSubstring;
}

DSString DSString::substring(int startIndex, int endIndex)
{
    char * stringData = this->data;
    int stringLength = this->getLength();
    char * substring = new char[stringLength + 1];
    int counter = 0;
    for (int i = startIndex; i < endIndex; ++i)
    {
        substring[counter] = stringData[i];
        counter++;
    }
    substring[counter] = '\0';
    DSString newSubstring(substring);
    //cout << "Substring data: " << newSubstring->data << endl;
    return newSubstring;
}

DSString DSString::toLowerCase()
{
    char * tempData = this->data;
    int stringLength = this->getLength();
    char * lowerCaseData = new char[stringLength + 1];
    int counter = 0;
    for (int i = 0; i < stringLength; ++i)
    {
        lowerCaseData[counter] = tolower(tempData[counter]);
        ++counter;
    }
    lowerCaseData[counter] = '\0';
    DSString lowerCase(lowerCaseData);
    //cout << "LowerCase: " << lowerCaseData << endl;
    return lowerCase;
}

int DSString::indexOf(char character)
{
    //cout << "Character: " << character << endl;
    int stringLength = this->length;
    //cout <<  "String length: " << stringLength << endl;
    int index = -1;
    char * tempData = this->data;
    for (int i = 0; i < stringLength; ++i)
    {
        //cout << "i: " << i << endl;
        //cout << "tempData[i]" << tempData[i] << endl;
        if (tempData[i] == character)
        {
            //cout << "Made it here!" << endl;
            index = i;
            break;
        }
    }
    return index;
}

int DSString::indexOf(int startingIndex, char character)
{
    //cout << "Character: " << character << endl;
    int stringLength = this->length;
    //cout <<  "String length: " << stringLength << endl;
    int index = -1;
    char * tempData = this->data;
    for (int i = startingIndex; i < stringLength; ++i)
    {
        //cout << "i: " << i << endl;
        //cout << "tempData[i]" << tempData[i] << endl;
        if (character == tempData[i])
        {
            //cout << "Made it here!" << endl;
            index = i;
            break;
        }
    }
    return index;
}

int DSString::toInt(DSString& string)
{
    char * stringData = string.data;
    int stringNum;
    stringNum = atoi(stringData);
    return stringNum;

}

//overloaded insertion operator so you can directly print out DSStrings
ostream& operator<<(ostream& output, const DSString& string)
{
    output << string.data;
    return output;
}

ostream& operator<<(ostream& output, const DSString * string)
{
    output << string->data;
    return output;
}

//overloaded extraction operator so you can directly extract DSStrings
istream& operator>>(istream& input, DSString &string)
{
    //initialize a character array to store the data that we will put in a string object
    char * stringData = new char[281];
    input >> stringData;
    string = DSString(stringData);
    delete [] stringData;
    return input;
}

//overloaded getline function
ifstream& getline(ifstream& input, DSString& currentString, char delim)
{
    char * content = new char[2048];
    char currentChar;
    input >> currentChar;
    int counter = 0;
    while (currentChar != delim && !input.eof())
    {
        //cout << "Current Char: " << currentChar << endl; //debugging code
        content[counter] = currentChar;
        content[counter + 1] = '\0';
        //cout << "Content: " << content << endl; // debugging code
        input.get(currentChar);
        counter++;
    }
    content[counter] = '\0';
    currentString.setString(content);
    //cout << "Current String: " << currentString << endl; //debugging code
    currentString.setLength(counter);
    return input;
}

//checks whether or not two DSString objects are equal (based on the "string" in them)
bool DSString::operator==(const DSString& string)
{
    if (strcmp(this->data, string.data) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DSString::operator<(const DSString& string) const
{
    if (strcmp(this->data, string.data) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//adds one string onto the end of another via overloaded + operator
DSString& DSString::operator+(DSString& string)
{
    int newLength = this->getLength() + string.getLength();
    char * newString = new char[newLength];

    for (int i = 0; i < this->getLength(); ++i)
    {
        newString[i] = this->data[i];
    }

    for (int j = 0; j < string.getLength(); ++j)
    {
        newString[length + j] = string.data[j];
    }
    delete this->data;
    this->length = newLength;
    this->data = newString;
    return *this;
}
DSString& DSString::operator+(char newChar)
{
    int newLength = this->getLength() + 2;
    char * newString = new char[newLength];
    for (int i = 0; i < this->getLength(); ++i)
    {
        newString[i] = this->data[i];
    }
    newString[newLength - 2] = newChar;
    newString[newLength - 1] = '\0';
    delete this->data;
    this->length = newLength;
    this->data = newString;
    return *this;

}

//overloaded assignment operator - assigns one DSString object to another
DSString& DSString::operator=(const DSString& string)
{
    if (this->data != nullptr)
        delete[] this->data;
    this->length = string.length;
    this->data = new char[strlen(string.data) + 1];
    strcpy(this->data, string.data);
    return *this;
}
