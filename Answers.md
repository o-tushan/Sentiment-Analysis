# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Owen Tushan

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[x] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > To train the model, you first give it the training data, which tells us the sentiment for the words. Using this given sentiment, we then analyze the test data set, which is done by looking at each individual word in each tweet. Using the sentiment of each word that we derived from the training set, we then add this sentiment to the tweet, and compare all of the "positive" words to all of the "negative" ones.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > The training has complexity O(N)^2. Because tokenize uses a loop and is called within another loop, there is complexity of O(N) within O(N), resulting in O(N)^2. The code took 0.838568 seconds to run. 

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The classification algorithm is O(N)^2 because similarly to the training algorithm, the most complex implementation is tokenize being called within another loop. The code took 0.320107 seconds to run. 


4. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > By using Valgrind, we can see if there are any bytes of data leaked. By implementing our code and then running Valgrind, we can make sure our data has no leaks and therefore runs optimally. 

5. What was the most challenging part of the assignment?

   > The most challenging part was understanding what was needed to classify tweets. It was difficult trying to visualize what's needed in order to make it all work. 