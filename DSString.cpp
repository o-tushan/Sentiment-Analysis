#include "DSString.h"

DSString::DSString()
{
    len = 0;
    data = new char[1];
    data[0] = '\0';
}
DSString::DSString(const char *val)
{                                                               // constructor that converts a cstring
    len = strlen(val);
    data = new char[len + 1];
    strcpy(data, val);
    data[len] = '\0';
}

DSString::DSString(const DSString &original)
{                                                               // copy constructor
    len = original.len;
    data = new char[len + 1];

    strcpy(data, original.data);
}

DSString::~DSString()
{                                                               // destructor
    delete[] data;
}

DSString &DSString::operator=(const DSString &original)
{                                                               // assignment operator

    if (this != &original)
    {
        delete[] data;

        len = original.len;
        data = new char[len + 1];

        strcpy(data, original.data);
    }

    return *this;
}

size_t DSString::length() const
{                                                               // returns the length of the string
    return len;
}

char &DSString::operator[](size_t x)
{                                                               // returns a reference to the character at the given index

    return *(data + x);
}

/**
 * Overloaded operator+ which appends the string in the argument to this string
 */
DSString DSString::operator+(const DSString &original) const 
{

    char *temp;
    temp = new char[original.len + len + 1];                    // size of temp is original len + our len

    int i = 0;
    int tempVal = 0;
    while (data[i] != '\0')
    {                                                           // adds the characters from data to temp

        temp[tempVal] = data[i];
        i++;
        tempVal++;
    }
    i = 0;
    while (original.data[i] != '\0')
    {

        temp[tempVal] = original.data[i];                       // adds the characters from original to temp
        i++;
        tempVal++;
    }

    DSString fullVal(temp);                                     // create DSString object and delete temp
    delete[] temp;

    return fullVal;
}

/**
 * Standard relational operators to compare and order your strings.
 * Feel free to add additional.
 **/
bool DSString::operator==(const DSString &original) const
{
    if (original.len != len)
    {                                                           // check to make sure the length of both strings are equal
        return false;
    }

    for (size_t i = 0; i < len; i++)
    {                                                           // go letter by letter. If any are different, return false
        if (original.data[i] != data[i])
        {
            return false;
        }
    }
    return true;
}
bool DSString::operator<(const DSString &original) const
{

    for (size_t i = 0; i < std::min(len, original.len); i++)
    {
        if (data[i] < original.data[i])
        {                                                       // if data is smaller than original, then the letter comes first
            return true;
        }
        if (data[i] > original.data[i])
        {                                                       // if data is larger, then the letter comes after
            return false;
        }
    }

    if (len < original.len)                                     // check the size of len and original.len
    { 
        return true;
    }
    else if (len >= original.len)
    {
        return false;
    }
}

/**
 * The substring method returns a new string object that contains a
 * sequence of characters from this string object.
 *
 * param start - the index of where to start
 * param numChars - the number (count) of characters to copy into
 *    the substring
 * @return a DSString object containing the requested substring
 **/
DSString DSString::substring(size_t start, size_t numChars) const
{
    char *temp;                                                  // create the temporary pointer
    temp = new char[numChars + 1];

    int x = 0;
    for (size_t i = start; i < (start + numChars); i++)
    {                                                            // start the for loop at start and have it run until it reaches numChars length
        temp[x] = data[i];

        x++;
    }
    temp[numChars] = '\0';

    DSString sub(temp);                                          // create DSString object and delete temp
    delete[] temp;

    return sub;
}

/**
 * @brief Returns a new string object with all characters in lowercase
 *
 * @return DSString
 */

// look at the ASCII table for this!
DSString DSString::toLower() const
{
    char *temp; // create temp and set its length
    temp = new char[len + 1];

    int i = 0;
    while (data[i] != '\0')
    {

        //std::cout << data[i] << std::endl;
        
        if (int(data[i]) <= 90 && int(data[i]) >= 65)           // makes sure data[i] is upper case
        {                           
            temp[i] = (int(data[i]) + 32);                      // turns the char into an int and adds 32, getting the lower case version of the char
        
        }  
        else
        {
            temp[i] = data[i];
        }  
        i++;                                               
    }
    temp[len] = '\0';

    DSString lower(temp);                                       // create DSString object and delete temp
    delete[] temp;

    return lower;
}

/**
 * the c_str function returns a pointer a null-terminated c-string holding the
 * contents of this object. Since data already has a `\0`
 * at the end of the string in DSString so you can just return a pointer to data.
 **/
char* DSString::c_str() const
{

    return data;                                                // return data
}

// a conversion to std::string would also be nice: string string() const;

/**
 * Overloaded stream insertion operator to print the contents of this
 * string to the output stream in the first argument. Remember:
 * This operator needs to be implemented outside of the class as
 * a friend because it operates on the stream and not the DSString object.
 **/

std::ostream &operator<<(std::ostream &temporary, const DSString &original)
{

    temporary << original.c_str();                              // temporary acts as std::cout

    return temporary;                                           // since temporary is type ostream, return it
}

// You are free to add more functionality to the class.  For example,
// you may want to add a find(...) function that will search for a
// substring within a string or a function that breaks a string into words.
// You will need a split or tokenize function.

std::vector<DSString> tokenize(DSString val)                           
{        
    DSString original;                                          
    original = val.toLower();                            

    int i = 0;                                                  // tracks where we are in the tweet
    int j = 0;                                                  // tracks the size of each word
    std::vector<DSString> toReturn;
    char temp[original.len + 1];
    while (original.data[i] != '\0')
    {
        if (j != 0 && isspace(original.data[i]))               // if j is a space, then the word is done
        {
            temp[j] = '\0';

            toReturn.push_back(DSString(temp));                // adds the word to the vector. reset j
            j = 0;
            i++;
        }
        else if (isalpha(original.data[i]))                    // checks to see if j is a character
        {
            temp[j] = original.data[i];
            j++;
            i++;
        }
        else                                                  // j has to be a special character, so just increment i
        {
            i++;
        }
    }
    if(j != 0) {                                             // only used for the last word (no spaces after)
        temp[j] = '\0';
        toReturn.push_back(DSString(temp));
    }

    return toReturn;

    
}
