#include <iostream>
#include "SentimentAnalyzer.h"

int main(int argc, char** argv)
{  
    std::cout << "I will be a sentiment analyzer!" << std::endl;
    SentimentAnalyzer *test = new SentimentAnalyzer;

    test->trainingInput(argv[1]);
    test->testingInput(argv[2]);
    test->classificationResults(argv[4]);
    test->accuracyTest(argv[3], argv[5]);
    return 0;
}