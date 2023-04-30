#include <iostream>
#include <list>
#include<stack>
#include <queue>
#include "WordLadder.h"
#include <fstream>
#include <string>
#include <ostream>
#include <algorithm>

using namespace std;

WordLadder::WordLadder(const string &fileName){
ifstream inFs;
    
inFs.open(fileName);

if(!inFs.is_open()){
    std::cout << "Error Opening File" << endl;
    return ;

}
string word;

while(getline(inFs, word)){
if(word.size() != 5 ){
    std::cout << "Invalid word length" << endl;
    return ;
}

dict.push_back(word);



}

inFs.close();

}




stack<string> WordLadder::DoWordLadder(const string&firstWord, const string&secondWord){


stack<string> WordStack; //create a Stack containing just the first word in the ladder !
WordStack.push(firstWord);

queue<stack<string>> WordLadder; 
WordLadder.push(WordStack); // enqueue this Stack on to a Queue of Stacks 

if(firstWord == secondWord){
    return WordStack;
}
dict.remove(firstWord);
stack<string> copyStack;



while(!WordLadder.empty()){     // while this Queue of Stacks is not empty 
    
    
    
    string topWord = (WordLadder.front()).top(); // get the word on top of the front Stack of this Queue
    
    
    for (list<string>::iterator iterator = dict.begin(); iterator != dict.end();){  // for each word in the dictionary
            
            
            string compare2 = *(iterator); //word
            
            bool offByOne; //counting differences
            offByOne = compareStrings(topWord,compare2);
            

        
            
            if (offByOne) { 
                
                copyStack = WordLadder.front(); // create a new Stack that is a copy of the front Stack and push on this off-by-one word found
                
                copyStack.push(compare2);
                
            
                if (compare2 == secondWord && offByOne == true) { // if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder. You are done!
                    

                    return copyStack;
                }
                else { 
                    
                    WordLadder.push(copyStack); // otherwise, enqueue this new Stack and remove this word from the dictionary
                    iterator = dict.erase(iterator);
                    
                    
                }
            
            }
            else{
                ++iterator;
            }
            
        }
       
     WordLadder.pop(); 
}


    stack<string> failStack;
    
    return failStack;


// cout << "returned front" << endl; 
// return WordLadder.front(); // if the Queue is empty and you didn't find the word ladder, a word ladder does not exist for these 2 words

}


void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile){
    
    if(!exists(start) || !exists(end)){
        std::cout << "Word not in list" << endl ;
        return ;

    }
    
    stack <string> WordLadder;
    WordLadder = DoWordLadder(start,end);
    

    ofstream out ; 
    out.open(outputFile);

    if(WordLadder.empty()){
    out << "No Word Ladder Found." << endl;
    out.close();
    return;

   }
    stack<string> realLadder;
    while(!WordLadder.empty()){
        realLadder.push(WordLadder.top());
        WordLadder.pop();

    }




    
    while(!realLadder.empty()){
        out << realLadder.top() << endl ;
        realLadder.pop();
    }
    
    out.close() ;
    

}

bool WordLadder::exists(const string &word){

bool isFound = (find(dict.begin(), dict.end(), word) != dict.end());

return isFound;



}

bool WordLadder::compareStrings(const string &compare1 , const string &compare2){
int counter = 0 ;
for (int i = 0; i < 5; ++i) {  
                
        if (compare1[i] != compare2[i]) { // if the word is off by just one letter from the top word
      counter = counter + 1;          
                }
           }

if(counter == 1 ){
    return true;
}    

return false; 

}



