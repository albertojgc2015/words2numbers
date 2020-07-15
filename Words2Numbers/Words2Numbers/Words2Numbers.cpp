//This program converts written numbers in words to digits in the middle of a paragraph. 

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp> 
#include <numeric>

using namespace std;

//Program variables
string userInput;
vector<string> vUserInput;
map<string, int> number;
string userOutput;

/*Dictionary for English Numbers (Map)*/
void englishNumbersInit()
{
    number["zero"]      = 0;
    number["one"]       = 1;
    number["two"]       = 2;
    number["three"]     = 3;
    number["four"]      = 4;
    number["five"]      = 5;
    number["six"]       = 6;
    number["seven"]     = 7;
    number["eight"]     = 8;
    number["nine"]      = 9;
    number["ten"]       = 10;
    number["eleven"]    = 11;
    number["twelve"]    = 12;
    
    //We could simplify teens by considering number + teen 
    number["thirteen"]  = 13;
    number["fourteen"]  = 14;
    number["fifteen"]   = 15;
    number["sixteen"]   = 16;
    number["seventeen"] = 17;
    number["eighteen"]  = 18;
    number["nineteen"]  = 19;
    
    //We could simplify teens multipliers by considering number * 10 module. Replace 'teen' by 'ty' ending.
    // 10^1
    number["twenty"]    = 20;
    number["thirty"]    = 30;
    number["fourty"]    = 40;
    number["fifty"]     = 50;
    number["sixty"]     = 60;
    number["seventy"]   = 70;
    number["eighty"]    = 80;
    number["ninety"]    = 90;

    //10^2
    number["hundred"]   = 100;

    //10^3
    number["thousand"]  = 1000;

    //10^6
    number["million"]   = 1000000;

    //10^9
    number["billion"]   = 1000000000;
}

void processUserInput() {

    //convert input to lower case
    boost::algorithm::to_lower(userInput);

    //split userInput by delimiter, e.g. space, and fill a vector of strings
    boost::split(vUserInput, userInput, boost::is_any_of(" "));
    
    map<string, int>::iterator it;
    int auxNumber;
    string auxWord;
    vector<int> vNumbersToSum;
    vector<int> vDetectedNumbers;
    int sum;

   
    //search if string is a number in our dictionary
    //Detect combinations of word numbers (e.g. thirty one, on thousand two hundred two, etc.) and do corresponding calculations (e.g. 1 1000 2 100 13 = 1*1000+2*100+13=1213). We can do it by recursiveness.
    
    for (int i = 0; i < vUserInput.size(); i++) {
            
        auxWord = vUserInput[i];

        it = number.find(auxWord);

        //it's a word (not a number)
        if (it == number.end()) {
            
            //build output, check first if there are numbers to sum before a new no number word
            if (!vNumbersToSum.empty()) {
            
                //Sum all elements in vector
                
                sum  = accumulate(vNumbersToSum.begin(), vNumbersToSum.end(), 0);
                              
                userOutput = userOutput.append(to_string(sum) + " ");
            }

            //empty vector before continuing writing output
            vNumbersToSum.clear();
            
            //add word
            userOutput = userOutput.append(auxWord + " ");
            
        }        
        //it's a number
        else {
                  
            auxNumber = (*it).second;
            
            vDetectedNumbers.push_back(auxNumber);
            

            // Check if number is a multiplier
            if(auxNumber == 100 || auxNumber==1000 || auxNumber == 1000000 || auxNumber == 1000000000){
                
                
                int previousNum = vDetectedNumbers.end()[-2];

                vNumbersToSum.end()[-1] = (previousNum * auxNumber);

                /*cout << "vNumbersToSum elements: " << vNumbersToSum.size() << endl;
                for (std::vector<int>::const_iterator j = vNumbersToSum.begin(); j != vNumbersToSum.end(); ++j)
                    std::cout << *j << endl;*/
            
            }
            else{
                //if the number is not a multiplier, add it to the list of consecutive numbers to sum

                vNumbersToSum.push_back(auxNumber);
               
            }
        }

    }
       
    cout << "Your processed string is: " << userOutput;

 }


/*
Assumptions:
- This program supports English "numbers in words" only.
- This program uses space as separator. Input must contain at least one space.

Corner cases:
- Different languages, different number words. 
- Different ways of writing a number (e.g. "one hundred one" vs "one hundred and one" vs " "a hundred one") -> System could learn from user entered strings to improve and expand the knowledge base (dictionary).
- Case sensitive: Lower/upper cases and mixes in the user input data.
- Different delimiters (e.g. ',' different lines, tabs, etc.)
- No delimiter between strings.
- Output keeps case sensitive chars from the input, not for the numbers because they will be converted
- test maximum allowed number
- control negative values in the input.
- Out of scope: Deal with decimal numbers (e.g. "two and a half Apples").


Alternative solving mechanisms:
- Use regular expressions (regex) to detect and convert
- Apply recursion
*/

//Tests
//test when input is one number: one
//test when input is two numbers, being one of them a multiplier (tens, hundreds, thousdands, etc.): "two hundred" 
//test when input is tens + number (e.g. twenty two, thirty three, etc.): "twenty three"
//test when input contains one number in the middle of the paragraph: "I have one apple"
//test when input contains two or more numbers in the middle of the paragraph: "I have one hundred apples"
// test when input contains two or more multipliers and number is in the middle of the paragraph: "I have seven thousand five hundred apples"
// test when input contains numbers in different parts of the string: "I have twenty four cars and two hundred fifty drivers"
//TODO: add them in a separate file

void testOneNumberOnly() {

    string testName = "testOneNumberOnly";
    //cout << testName << endl;
    userInput = "One ";
    processUserInput();
    if (userOutput == "1  ") cout << endl << testName << " passed" << endl;
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";

}

void testMultipleNumbersOnly() {
    string testName = "testMultipleNumbersOnly";
    //cout << testName << endl;
    userInput = "Two hundred ";
    processUserInput();
    if (userOutput == "200  ") cout << endl << testName << " passed" << endl;
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";
}

void testTensOnly() {
    string testName = "testTens";
    //cout << testName << endl;
    userInput = "Twenty three ";
    processUserInput();
    if (userOutput == "23  ") cout << endl << testName << " passed" << endl;
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";
}

 void testOneNumberInParagraph() {
    string testName = "testOneNumberInParagraph";
    //cout << testName << endl;
    userInput = "I have one apple";
    processUserInput();
    if (userOutput == "i have 1 apple ") cout << endl << testName << " passed" << endl; 
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";
}

void testMultipleNumbersInParagraph() {
     string testName = "testMultipleNumbersInParagraph";
     //cout << testName << endl;
     userInput = "I have one hundred apples";
     processUserInput();
     if (userOutput == "i have 100 apples ") cout << endl << testName << " passed" << endl;
     else cout << endl << testName << " failed (x)" << endl;
     userInput = "";
     userOutput = "";
}

void testMultipleNumbersAndMultipliersInParagraph() {
    string testName = "testMultipleNumbersAndMultipliersInParagraph";
    //cout << testName << endl;
    userInput = "I have seven thousand five hundred apples";
    processUserInput();
    if (userOutput == "i have 7500 apples ") cout << endl << testName << " passed" << endl;
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";
}

void testMultipleNumbersAndMultipliersInParagraphInDifferentLocations() {
    string testName = "testMultipleNumbersAndMultipliersInParagraphInDifferentLocations";
    //cout << testName << endl;
    userInput = "I have twenty four cars and two hundred fifty drivers";
    processUserInput();
    if (userOutput == "i have 24 cars and 250 drivers ") cout << endl << testName << " passed" << endl;
    else cout << endl << testName << " failed (x)" << endl;
    userInput = "";
    userOutput = "";
}

int main() {

    //start
    cout << "*** Welcome to the words 2 numbers detector & converter! *** " << endl;
    
    //init english dictionary
    cout << "*** Initializing..." << endl << endl;
    englishNumbersInit();

    cout << "*** Testing..." << endl;
    //executeTests
    testOneNumberInParagraph();
    testMultipleNumbersInParagraph();
    testMultipleNumbersAndMultipliersInParagraph();
    testMultipleNumbersAndMultipliersInParagraphInDifferentLocations();
    testOneNumberOnly();
    testMultipleNumbersOnly();
    testTensOnly();
    // TODO: return boolean for each test and determine if we can run the process or not depending on the tests passed/failed.

    //get user input
    cout << endl;
    cout << "*** Ready to start " << endl;
    cout << "*** What's your sentence? (Please, if you enter only a number in words add a space in the end before entering input): ";
    getline(cin, userInput);
    cout << "*** You introduced: " << userInput << endl;
    cout << "*** Processing... " << endl;
    
    //execute word 2 number conversion
    processUserInput();

    cout << endl << "*** GoodBye! " << endl;

              
    return 0;
}
