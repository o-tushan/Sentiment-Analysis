#include "SentimentAnalyzer.h"


SentimentAnalyzer::SentimentAnalyzer()
{
    wordList = std::map<DSString, int>();
}

//functions for training data

void SentimentAnalyzer::trainingInput(char* fileName){        // reads in the training file, getting the sentiment and tweet from each line

    std::ifstream fileStream;

    fileStream.open(fileName);

    if(!fileStream.is_open()){
        std::cout << "error opening training dataset" << std::endl;
    }

    char temp[10000];
    bool sentiment;
    fileStream.getline(temp, 10000);    // this should be the first line of train file, which is just the format, so we need to skip it

    while(!fileStream.eof()){

        fileStream.getline(temp, 10000, ',');                // this should get sentiment on the first real line
        sentiment = (temp[0] == '4');
        fileStream.getline(temp, 10000, ',');                // these 4 bypass the ID, date, query, and user
        fileStream.getline(temp, 10000, ',');
        fileStream.getline(temp, 10000, ',');
        fileStream.getline(temp, 10000, ',');

        fileStream.getline(temp, 10000, '\n');               // gets the tweet

        DSString tweet = DSString(temp);
        
        std::vector<DSString> tokenized = tokenize(tweet);   // vector that will be passed in to trainingOutput
        
        this->trainingOutput(tokenized, sentiment);

    }
    
    //TOTAL WORDCOUNT | positive: 18101 | negative: 13982 |
    fileStream.close();

}

void SentimentAnalyzer::trainingOutput(std::vector<DSString> singleTweet, bool sentiment){    // creates our word library with sentiment

    // checks to see if any new words need to be added to our word list

    for(size_t i = 0; i < singleTweet.size(); i++){
        if(wordList.find(singleTweet.at(i)) == wordList.end()){      // word is not found
            wordList[singleTweet.at(i)] = (sentiment) ? 1 : -1;

        }
        else {                                                      // word is found, and sentiment needs +/-
            wordList[singleTweet.at(i)] += (sentiment) ? 1 : -1;
        }
    }

}

//functions for test data

void SentimentAnalyzer::testingInput(char* fileName){         // reads in the testing file, getting the ID and the tweet from each line

    std::ifstream fileStream;

    fileStream.open(fileName);

    if(!fileStream.is_open()){
        std::cout << "error opening training dataset" << std::endl;
    }
     
    char temp[10000];
    fileStream.getline(temp, 10000);  // this should be the first line of test file, which we don't need
    while(!fileStream.eof()){
        
        
        fileStream.getline(temp, 10000, ',');                        // this should get us the ID
        DSString ID = DSString(temp);

        fileStream.getline(temp, 10000, ',');                        // skips the date, user, and query
        fileStream.getline(temp, 10000, ',');
        fileStream.getline(temp, 10000, ',');

        fileStream.getline(temp, 10000, '\n');                       // gets us the tweet    

        DSString tweet = DSString(temp);                             // puts the tweet into a DSString
        
        std::vector<DSString> tokenized = tokenize(tweet);           // vector that will be passed in to testingOutput

        this->testingOutput(tokenized, ID);

    }

    fileStream.close();
}   

void SentimentAnalyzer::testingOutput(std::vector<DSString> singleTweet, DSString ID){        // finds the sentiment of each word and determines if each tweet is positive or negative 

    int totalSentiment = 0;
    for(size_t i = 0; i < singleTweet.size(); i++){            // iterates through all of the words in the tweet
        
        if(wordList[singleTweet.at(i)] >= 0){                  // if the word's sentiment is positive: totalSentiment + 1
                 
            totalSentiment++;                   
        }
        else if(wordList[singleTweet.at(i)] < 0){              // if the word's sentiment is negative:: totalSentiment -1
            
            totalSentiment--;   
        }
    }

    if(totalSentiment >= 0){        // if the total tweet sentiment = positive

        sentimentOutput[ID] = 4;                           // put the ID into sentimentOutput map with the sentiment "4"
    }
    else{                           // the total tweet sentiment has to = negative 
        
        sentimentOutput[ID] = 0;                           // put the ID into sentimentOutput map with the sentiment "0"
    }
}

//functions for output files

void SentimentAnalyzer::classificationResults(char* fileName){        // generates file 1, which holds the tweet IDs and the the sentiment we determined  

    std::ofstream results;

    results.open(fileName);

    
    for(const auto& elem: sentimentOutput){
        results << elem.second << ", " << elem.first << std::endl;
    }
    
    
    results.close();
}

void SentimentAnalyzer::accuracyTest(char* readFile, char* writeFile){                 // generates file 2, which holds our accuracy and incorrect tweets

    std::ifstream fileStream;               // read/write
    std::ofstream accuracy;

    fileStream.open(readFile);
    accuracy.open(writeFile);

    char temp[10000];                       // all of the variables needed
    int sentiment;
    double amountTotal = 0.0;
    double amountCorrect = 0.0;
    std::vector<DSString> incorrectTweets;                  

    fileStream.getline(temp, 10000);  // skips over the first line
    while(!fileStream.eof()){
        
        fileStream.getline(temp, 10000, ',');                        // gets us the sentiment
        sentiment = int(temp[0] - '0');

        fileStream.getline(temp, 10000, '\n');                       // gets us the ID
        DSString ID = DSString(temp);

        if(sentimentOutput[ID] != sentiment){     // if the ID's sentiment isn't equal to the one we got
            incorrectTweets.push_back(ID);
            amountTotal++;
        }
        else{                                               // if ID's sentiment is equal
            amountCorrect++;
            amountTotal++;
        }

    }

    double tweetAcc = amountCorrect / amountTotal;
    accuracy << std::setprecision(3) << tweetAcc << std::endl;

    for(size_t i = 0; i < incorrectTweets.size(); i++){
        accuracy << sentimentOutput[incorrectTweets.at(i)] << ", ";     // first, print out the sentiment we got for incorrect ID

        if(sentimentOutput[incorrectTweets.at(i)] == 4){                // then print out the opposite sentiment since it's incorrect
            accuracy << "0, ";
        }
        else{
            accuracy << "4,";
        }
        accuracy << incorrectTweets.at(i) << std::endl;                 // finally, print out the ID of the incorrect one
    }


    fileStream.close();
    accuracy.close();

}