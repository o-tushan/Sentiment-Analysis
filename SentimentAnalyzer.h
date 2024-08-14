#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include "DSString.h"

#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

class SentimentAnalyzer
{
    private:

        std::map<DSString, int> wordList;   // this is our word library   

        std::map<DSString, int> sentimentOutput;   // this holds the test IDs and the sentiment we have determined
    public:
        SentimentAnalyzer();    // constructor

    // functions for training data
        void trainingInput(char*);   // reads in a line
        
        void trainingOutput(std::vector<DSString>, bool);  // puts all of our training words in a vector with assigned sentiment

    // functions for testing data
        void testingInput(char*);    // reads in a tweet

        void testingOutput(std::vector<DSString>, DSString);   // assigns the tweet, based on the words, a positive or negative sentiment

    // functions for output files
        void classificationResults(char*);   // creates results.csv

        void accuracyTest(char*, char*);     // creates accuracy.txt

};

#endif