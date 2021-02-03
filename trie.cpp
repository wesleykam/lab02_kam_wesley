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
        this->roots[i] = new Trie;
        this->roots[i] = other.roots[i];
    }
}

Trie::~Trie(){
    // TODO: Clean up your children!
    for(int i=0; i<26; i++)
    {
        delete roots[i];
    }
}

Trie& Trie::operator=(Trie const& other){
    // TODO: Remember to do a deep copy of your structure!
    /*
    this->end_of_word = other.end_of_word;

    for(int i=0; i<26; i++)
    {
        this->roots[i] = other.roots[i];
    }

    return *this;*/
    return (Trie&)other;
}


void Trie::insert(char const* const str){
    // Skip any characters that don't pass std::islower() after
    //  being put through std::tolower; they're not letters.
    // If you encounter a '\0', what flag should be set
    //  to note this point as the end of an input?
    // For other characters, identify a position in your 
    //  roots array by which letter you were given.
    // Remember, characters are numbers in computers!
    // What could you do to have an ID of 0 for 'a'?
    // (Hint: Take a look at an ASCII table!)

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this function
    
    char p[100];
    strcpy(p, str);

    if(p[0] == '\0')
    {
        end_of_word = true;
        return;
    }

    if(islower(tolower(p[0])))
    {
        if(roots[p[0]-97] == NULL)
        {
            roots[p[0]-97] = new Trie;
        }

        roots[p[0]-97]->insert(&p[1]);
    }
    insert(&p[1]);
}

bool Trie::check(char const* const str) const{
    // Iterate through the same way as you insert.
    // What should you check to determine whether the current point
    //  is the end of the input? When you get there, of course.
    // You're trying to match the exact, entire input.

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this stub

    char *p = (char*)str;

    if(p[0] == '\0')
    {
        return true;
    }
    
    if(!islower(tolower(p[0])))
    {
        return check(&p[1]);
    }

    if(roots[p[0]-97] == NULL)
    {
        return false;
    }
    
    return roots[p[0]-97]->check(&p[1]);
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
    
    char *p = (char*)str;

    if(!check(p))
    {
        return NULL;
    }

    if(islower(tolower(p[0])))
    {
        roots[p[0]-97]->firstWithPrefix(p++, depth++);
    }
    
    if(p[0] != '\0' && !islower(tolower(p[0])))
    {
        firstWithPrefix(p++, depth);
    }


    if(p[0] == '\0')
    {
        for(int i=0; i<26; i++)
        {
            if(!end_of_word)
            {
                p[0] = i+97;
                roots[i]->firstWithPrefix((char*)'\0', depth++);
            }
        }
    }
    

    char temp[depth];
    temp[depth] = p[0];


    if(depth == 0)
    {
        return temp;
    }
        
    return p;
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
    const char *c;
    Trie temp;
    
    while( !is.eof() )
    {
        getline(is, str);
        c = str.c_str();
        temp.insert(c);
    }
    
    
    return temp;
}

Trie load_trie(std::string filename){
    // Open an input stream to the file `filename`, 
    //  then pass that input stream to the other form of load_trie().
    
    Trie temp;

    ifstream inStream;
    inStream.open(filename);

    temp = load_trie(inStream);

    inStream.close();

    return temp;

    // Should be easy!
}
