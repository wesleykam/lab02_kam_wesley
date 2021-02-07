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
    
    Trie *p = nullptr;
    
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
    // What could you do to have an ID of 0 for 'a'?
    // (Hint: Take a look at an ASCII table!)

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this function
    
    char p[1000];
    strcpy(p, str);
    
    if(p[1] == '\0')
    {
        end_of_word = true;
    }

    if(islower(tolower(p[0])))
    {
        cout << p[0];
        if(roots[p[0]-97] == NULL)
        {          
            roots[p[0]-97] = new Trie;
        }
        
        if(end_of_word)
        {
            return;
        }
        else
        {
            roots[p[0]-97]->insert(&p[1]);  
            return;
        }
    }

    if(end_of_word)
    {
        return;
    }
    else
    {
        insert(&p[1]);
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

    char p[1000];
    strcpy(p, str);
    /*
    bool b = (roots[p[0]-97] == NULL);
    cout << p[0] << endl;
    cout << b << endl;
    cout << p[0]-97 << endl;
    cout << b << endl;
    cout << "hi" << endl;
    */
    
    if(!islower(tolower(p[0])))
    {
        return false;
    }

    if(roots[p[0]-97] == NULL)
    {
        return false;
    }

    if(p[1] == '\0' && roots[p[0]-97] != NULL)
    {
        return true;
    }
    else
    {
        return roots[p[0]-97]->check(&p[1]);
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
    
    char p[100];
    strcpy(p, str);
    bool pass = false;

    if(!pass && !islower(tolower(p[0])))
    {
        firstWithPrefix(&p[1], depth);
    }

    if(!pass && roots[p[0]-97] == NULL)
    {
        return NULL;
    }

    if(pass || p[0] == '\0')   //(pass || (p[1] == '\0' && roots[p[0]-97] != NULL))
    {
        pass = true;
        
        if(!end_of_word)
        {
            for(int i=0; i<26; i++)
            {
                if(roots[i] != NULL)
                { 
                    char c[1] = {i+97};
                    roots[i]->firstWithPrefix(c, depth++);
                }
            }   
        }
    }
    else
    {
        cout << p[0];
        roots[p[0]-97]->firstWithPrefix(&p[1], depth++);
    }
    
    char *temp[depth+1];
    
    temp[depth] = &p[0];

    if(depth == 0)
    {
        return *temp;
    }
}

/*
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
    char c[100];
    Trie *temp = new Trie;
    getline(is, str); 

    while( str != "" )
    {
        strcpy(c, str.c_str());
        temp->insert(c);
        cout << endl;
        getline(is, str);
    } 
    
    return *temp;
}
*/

Trie load_trie(std::istream& is){
    Trie* loading = new Trie;
    string str;
    while (std::getline(is, str)) {
        loading->insert(str.c_str());
    }
    return *loading;
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









