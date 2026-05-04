#include "dsstring.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

//this custom method allows for single characters to be added to the end of a character array
vector <DSString> getTweetContent(char * file)
{
    vector <DSString> tweets;
    //creates the ifstream object which will read in the file data
    ifstream inFS;
    inFS.open(file);

    //takes out the header of the file so we can discard it
    char * ignoreThisLine = new char[500];
    inFS >> ignoreThisLine;
    //cout << ignoreThisLine << endl; // debugging code
    delete [] ignoreThisLine;

    //iteratres through each line of the file
    while (!inFS.eof())
    {
        //create a DSString that will store each line
        DSString extractionLine;
        getline(inFS, extractionLine, '\n');
        //cout << "Extraction Line: " << extractionLine << endl; //debugging code
        //I will use these indices to use my substring method to separate out the data I need
        int firstCommaPos = extractionLine.indexOf(',');
        int secondCommaPos = extractionLine.indexOf(firstCommaPos + 1, ',');
        int thirdCommaPos = extractionLine.indexOf(secondCommaPos + 1, ',');

        //debugging code
        /*
        cout << "First: " << firstCommaPos << endl;
        cout << "Second: " << secondCommaPos << endl;
        cout << "Third: " << thirdCommaPos << endl;
        */

        DSString tweetContent = extractionLine.substring(thirdCommaPos + 1);

        //cout << "Content: " << tweetContent << endl;
        tweets.push_back(tweetContent);
    }
    inFS.close(); //close the file or else things go wrong (I've been told)
    return tweets;
}

//code to get the positive or negative connotation associated with each tweet
vector<int> getTweetConnotation(char * file) {
    vector<int> connotations;
    ifstream inFS;
    inFS.open(file);

    //takes out the header of the file so we can discard it
    char *ignoreThisLine = new char[500];
    inFS >> ignoreThisLine;
    //cout << ignoreThisLine << endl; // debugging
    delete [] ignoreThisLine;

    //iterates through each line of the training target data
    while (!inFS.eof())
    {
        //creates a DSString object that can store the line of data
        DSString extractionLine;
        getline(inFS, extractionLine, '\n');
        //cout << "Extraction Line: " << extractionLine << endl;

        //this will get us the indices of the commas that we will use in our substring method to separate out our data
        int firstCommaPos = extractionLine.indexOf(',');
        int secondCommaPos = extractionLine.indexOf(firstCommaPos + 1, ',');

        //substring method that'll give us each tweet's connotation
        extractionLine = extractionLine.substring(firstCommaPos + 1, secondCommaPos);
        //cout << "Connotation: " << extractionLine.toInt(extractionLine) << endl; //debugging code
        connotations.push_back(extractionLine.toInt(extractionLine));
    }
    inFS.close(); //close the file or else
    return connotations;
}

void wordFrequencyAnalysis(vector <DSString> tweetContent, vector<int> tweetConnotation, map <DSString, int> &positiveWords, map <DSString, int> &negativeWords)
{
    //debugging code
    /*
    for (int i = 0; i < tweetContent.size(); ++i)
    {
        cout << tweetContent.at(i) << endl;
    }

    for (int i = 0; i < tweetConnotation.size(); ++i)
    {
        cout << tweetConnotation.at(i) << endl;
    }
    */

    for (int i = 0; i < tweetContent.size() - 1; ++i)
    {
        //algorithm to pick out each word
        int counter = 0;
        int previousCounter = 0;
        DSString currentContent = tweetContent.at(i).toLowerCase();
        //cout << currentContent << endl; //debugging code
        while(counter < currentContent.getLength())
        {
            DSString newWord;
            while(isalpha(currentContent.getString()[counter]) || currentContent.getString()[counter] == '\'')
            {
                //cout << "1: " << currentContent.getString()[counter] << endl;
                ++counter;
            }
            newWord = currentContent.substring(previousCounter, counter);
            previousCounter = counter + 1;
            //cout << endl;
            while(ispunct(currentContent.getString()[counter]) || currentContent.getString()[counter] == ' ' || isdigit(currentContent.getString()[counter]))
            {
                //cout << "2: " << currentContent.getString()[counter] << endl;
                ++counter;
            }
            //cout << "Word: " << newWord << endl; //debugging code
            ++counter;

            if (tweetConnotation.at(i) == 0)
            {
                map <DSString, int> :: iterator nit = negativeWords.find(newWord);
                //cout << "nit: " << endl;
                if (nit != negativeWords.end())
                {
                    //cout << "Updating: " << newWord << endl;
                    int mapSecond = negativeWords.at(newWord);
                    mapSecond++;
                    nit->second = mapSecond;
                }
                else
                {
                    negativeWords.insert(pair<DSString, int>(newWord, 1));
                    //cout << "Inserting: " << newWord << endl;
                }
            }
            else if (tweetConnotation.at(i) == 4)
            {
                map <DSString, int> :: iterator pit = positiveWords.find(newWord);
                //cout << "pit: " << endl;
                if (pit != positiveWords.end())
                {
                    //cout << "Updating: " << newWord << endl;
                    int mapSecond = positiveWords.at(newWord);
                    mapSecond++;
                    pit->second = mapSecond;
                }
                else
                {
                    positiveWords.insert(pair<DSString, int>(newWord, 1));
                    //cout << "Inserting: " << newWord << endl;
                }
            }
            else
            {
            }
        }
    }

    //delete all words that occur only once (to improve efficiency)
    for (auto &n : negativeWords)
    {
        if (n.second <= 1)
        {
            negativeWords.erase(n.first);
        }
    }
    for (auto &p : positiveWords)
    {
        if (p.second <= 1)
        {
            negativeWords.erase(p.first);
        }
    }
}

void testTweets(char * data, char * target, char * outputFile, map <DSString, int> &positiveWords, map <DSString, int> &negativeWords)
{
    vector<DSString> tweetContent;
    vector<int> actualTweetConnotation; //stores the ACTUAL connotation of each tweet
    vector<int> predictedTweetConnotation; //stores my PREDICTIONS of the connotaiton based on word frequency analysis

    tweetContent = getTweetContent(data);
    actualTweetConnotation = getTweetConnotation(target);

    //debugging code
    /*
    for (int i = 0; i < tweetContent.size(); ++i)
    {
        cout << tweetContent.at(i) << endl;
    }

    for (int i = 0; i < actualTweetConnotation.size(); ++i)
    {
        cout << actualTweetConnotation.at(i) << endl;
    }
     */

    //code to get all the tweet ids
    ifstream inFS;
    inFS.open(data);

    vector <DSString> ids;

    while(!inFS.eof())
    {
        //create a DSString that will store each line
        DSString extractionLine;
        getline(inFS, extractionLine, '\n');
        //cout << "Extraction Line: " << extractionLine << endl; //debugging code

        //I will use these indices to use my substring method to separate out the data I need
        int firstCommaPos = extractionLine.indexOf(',');
        int secondCommaPos = extractionLine.indexOf(firstCommaPos + 1, ',');

        extractionLine = extractionLine.substring(firstCommaPos + 1, secondCommaPos);
        //cout << "Extraction: " << extractionLine << endl; //debugging code
        ids.push_back(extractionLine);
    }
    inFS.close();


    for (int i = 0; i < tweetContent.size(); ++i)
    {
        int counter = 0;
        int previousCounter = 0;
        int positiveCounter = 0;
        int negativeCounter = 0;
        DSString currentTweet = tweetContent.at(i);
        while(counter < currentTweet.getLength())
        {
            DSString newWord;
            while (isalpha(currentTweet.getString()[counter]) || currentTweet.getString()[counter] == '\'')
            {
                //cout << "1: " << currentContent.getString()[counter] << endl;
                ++counter;
            }
            newWord = currentTweet.substring(previousCounter, counter);
            previousCounter = counter + 1;
            //cout << endl;

            while (ispunct(currentTweet.getString()[counter]) || currentTweet.getString()[counter] == ' ' ||
                   isdigit(currentTweet.getString()[counter]) || currentTweet.getString()[counter] == '.')
            {
                //cout << "2: " << currentContent.getString()[counter] << endl;
                ++counter;
            }
            //cout << "Word: " << newWord << endl; //debugging code
            ++counter;

            positiveCounter += positiveWords[newWord];
            negativeCounter += negativeWords[newWord];
        }

        if (positiveCounter > negativeCounter)
        {
            predictedTweetConnotation.push_back(4);
        }
        else if (positiveCounter == negativeCounter)
        {
            predictedTweetConnotation.push_back(4);
        }
        else
        {
            predictedTweetConnotation.push_back(0);
        }

    }

    int TOTAL_NUM_OF_TWEETS = tweetContent.size();
    int totalGuessedRight = 0;
    int totalGuessedWrong = 0;

    for (int i = 0; i < actualTweetConnotation.size() - 2; ++i)
    {
        if (actualTweetConnotation.at(i) == predictedTweetConnotation.at(i))
        {
            totalGuessedRight++;
        }
        else
        {
            totalGuessedWrong++;
        }
    }

    cout << "Accuracy: " << (double) totalGuessedRight / (double) TOTAL_NUM_OF_TWEETS << endl;
    ofstream outFS;
    outFS.open(outputFile);
    outFS << (double) totalGuessedRight / (double) TOTAL_NUM_OF_TWEETS << endl;
    for (int i = 0; i < ids.size() - 1; ++i)
    {
        if (predictedTweetConnotation.at(i) != actualTweetConnotation.at(i))
        {
            outFS << ids.at(i) << endl;
        }
    }
    outFS.close();
}

void catchtest()
{
    Catch::Session().run();
}

//method that analyzes the number of times a word occurs in a positive/negative sense
int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        catchtest();
        exit(69);
    }

    char * file1 = argv[1];
    char * file2 = argv[2];
    char * file3 = argv[3];
    char * file4 = argv[4];
    char * output = argv[5];

    vector<DSString> tweets = getTweetContent(file1);
    tweets.reserve(500000);
    vector<int> tweetConnotation = getTweetConnotation(file2);
    tweetConnotation.reserve(500000);
    map <DSString, int> posOccurences; //int is number of occurences
    map <DSString, int> negOccurences; //int is number of occurences

    wordFrequencyAnalysis(tweets, tweetConnotation, posOccurences, negOccurences);

    //debugging code
    //positive
    /*
    cout << "Positive words: " << endl;
    for (auto &p : posOccurences)
    {
        cout << "first: " << p.first << endl;
        cout << "Second: " << p.second << endl;
    }
    cout << endl;

    //negative
    cout << "Negative words: " << endl;
    for (auto &n : negOccurences)
    {
        cout << "First: " << n.first << endl;
        cout << "Second: " << n.second << endl;
    }
     */

    testTweets(file3, file4, output, posOccurences, negOccurences);

    return 0;
}