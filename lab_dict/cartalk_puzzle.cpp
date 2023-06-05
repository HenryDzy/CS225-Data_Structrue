/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if(wordsFile.is_open()){
        while (getline(wordsFile, word)){
            string word1 = word.substr(1);
            string word2;
            if(word.length()<=2){
                word2 = word.substr(0,1);
            }
            else{
                word2 = word.front() + word.substr(2);
            }

            if(d.homophones(word1, word) && d.homophones(word2, word)){
                ret.push_back({word,word1,word2});
            }
        }
    }
    return ret;
}
