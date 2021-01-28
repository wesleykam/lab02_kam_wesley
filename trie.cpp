#include "trie.hpp"

#include <algorithm>
#include <cctype>
#include <stack>
#include <utility>

Trie::Trie():end_of_word(false){
    // TODO: There's a little more initialization to do here, but what?
}

Trie::Trie(Trie const& other):end_of_word(other.end_of_word){
    // TODO: Remember to do a deep copy of your structure!
}

Trie::~Trie(){
    // TODO: Clean up your children!
}

Trie& Trie::operator=(Trie const& other){
    // TODO: Remember to do a deep copy of your structure!

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
}

bool Trie::check(char const* const str) const{
    // Iterate through the same way as you insert.
    // What should you check to determine whether the current point
    //  is the end of the input? When you get there, of course.
    // You're trying to match the exact, entire input.

    // (Hint: This operation is easier if you use recursion.)

    // TODO: Fix this stub
    return false;
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
    return NULL;
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

    // TODO: Fix this stub.
    return Trie();
}

Trie load_trie(std::string filename){
    // Open an input stream to the file `filename`, 
    //  then pass that input stream to the other form of load_trie().

    // Should be easy!

    return Trie();
}