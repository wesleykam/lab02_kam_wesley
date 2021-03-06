#include "trie.hpp"

#include <algorithm>
#include <cctype>
#include <stack>
#include <utility>
#include <fstream>
#include <cstring>

using namespace std;

Trie::Trie():end_of_word(false){
    // TODO: There's a little more initialization to do here, but what?
    end_of_word = false; 

    for(int i=0; i<26; i++)
    {
        roots[i] = NULL;
    }
}

Trie::Trie(Trie const& other):end_of_word(other.end_of_word){
    // TODO: Remember to do a deep copy of your structure!
    this->end_of_word = other.end_of_word;
    
    for(int i=0; i<26; i++)
    {
        if(other.roots[i] != NULL)
        {
            this->roots[i] = new Trie(*other.roots[i]);
        }
    }
}

Trie::~Trie(){
    // TODO: Clean up your children!
    for(int i=0; i<26; i++)
    {
        if(roots[i] != NULL)
            delete roots[i];
    }
}

Trie& Trie::operator=(Trie const& other){
    // TODO: Remember to do a deep copy of your structure!
    
	if (this == &other)
	{
		return *this;	
	}
    

    this->end_of_word = other.end_of_word;
    
    for(int i=0; i<26; i++)
    {
        if(roots[i] != NULL)
        {
            delete roots[i];
        }
    }

    for(int i=0; i<26; i++)
    {
        if(other.roots[i] != NULL)
        {
            //p = new Trie(*other.roots[i]);
            this->roots[i] = new Trie(*other.roots[i]);
            //delete p;
        }
    }
    
    return *this;
    
}


void Trie::insert(char const* const str){
    // Skip any characters that don't pass std::islower() after
    //  being put through std::tolower; they're not letters.
    // If you encounter a '\0', what flag should be set
    //  to note this point as the end of an input?
    // For other characters, identify a position in your 
    //  roots array by which letter you were given.
    // Remember, characters are numbers in computers!
    // What could youi do to have an ID of 0 for 'a'?
    // (Hint: Take a look at an ASCII table!)

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this function
    
    //char p = *str;
    //strcpy(p, str);
    
    if(str[1] == '\0')
    {
        end_of_word = true;
    }

    if(islower(tolower(str[0])))
    {
        //cout << str[0];
        if(roots[str[0]-97] == NULL)
        {          
            roots[str[0]-97] = new Trie;
        }
        
        if(str[1] == '\0')
        {
            return;
        }
        else
        {
            roots[str[0]-97]->insert(&str[1]);  
            return;
        }
    }

    if(str[1] == '\0')
    {
        return;
    }
    else
    {
        insert(&str[1]);
        return;
    }
}

bool Trie::check(char const* const str) const{
    // Iterate through the same way as you insert.
    // What should you check to determine whether the current point
    //  is the end of the input? When you get there, of course.
    // You're trying to match the exact, entire input.

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this stub
    
    if(!islower(tolower(str[0])))
    {
        return false;
    }

    if(roots[str[0]-97] == NULL)
    {
        return false;
    }

    if(str[1] == '\0' && roots[str[0]-97] != NULL)
    {
        return true;
    }
    else
    {
        return roots[str[0]-97]->check(&str[1]);
    }
}

char* Trie::firstWithPrefix(char const* const str,unsigned depth) const{
    // You'll need two paths to solve this problem:
    
    // Case 1: You've used up all characters in str and are looking for
    //  the next stored input. Search depth-first in lexographic (a-z) order, 
    //  stopping when you encounter the first endpoint you marked in insert().

    // Case 2: You have characters left in the input. Act like check(),
    //  but when you run out of input, proceed to the other case.

    // If you can't find any matching roots to a chunk of input, return NULL.
    // If you encounter unrecognized characters in the input, skip them.
    // Increment depth on every recursion, except unrecognized characters.

    // For your return value, you can't allocate your cstring in advance 
    //  because you do not know how deep in the structure you will have to 
    //  search. Instead, increment depth on every (not-unrecognized) recursion.
    //  Then, when you reach an end of word you want to return, allocate your
    //  new char[depth+1] and fill it backward, based on your depth!

    // Remember to check whether your recursive call gave you back NULL!

    // TODO: Fix this stub.
    
    bool pass = false;
    char *temp = nullptr;
    char c = 0;

    if(!pass && !islower(tolower(str[0])))
    {
        firstWithPrefix(&str[1], depth);
    }

    if(!pass && roots[str[0]-97] == NULL)
    {
        return nullptr;
    }

    if(pass || (str[1] == '\0' && roots[str[0]-97] != NULL))
    {
        pass = true;
        
        if(!end_of_word)
        {
            for(int i=0; i<26; i++)
            {
                if(roots[i] != NULL)
                {   
                    char c = i+97;
                    roots[i]->firstWithPrefix(&str[0], depth++);
                    break;
                }
            }   
        }
    }
    else
    {
        roots[str[0]-97]->firstWithPrefix(&str[1], depth++);
    }
    
    temp = new char[depth+1];
    
    if(c != 0)
        temp[depth] = c;
    else
        temp[depth] = str[0];

    if(depth == 0)
    {
        return temp;
    }
}


Trie load_trie(std::istream& is){
    // Given an open input stream, read words on separate lines into a new Trie.
    // If no lines can be read from the input stream, return a default-constructed Trie.
    // Otherwise, return a Trie filled with all words that can be read until the
    //  first empty line.

    // Words will be placed on individual lines, like:
    //     apple
    //     application
    //     applied
    //     apply
    //
    // (The last line there was empty, indicating the end of the dictionary.)
    // You can read these easily with one of the formats of std::getline().
    // Remember, you already skip whitespace in Trie::insert(), so don't worry
    //  about stripping any whitespace here!

    // TODO: Fix this stub

    string str;
    Trie *temp = new Trie;

    while( getline(is, str) )
    {
        temp->insert(str.c_str());
        //cout << endl;
    } 
 
    return *temp;
}


Trie load_trie(std::string filename){
    // Open an input stream to the file `filename`, 
    //  then pass that input stream to the other form of load_trie().

    ifstream inStream;
    inStream.open(filename);

    Trie temp = load_trie(inStream);

    inStream.close();

    return temp;

    // Should be easy!
}









