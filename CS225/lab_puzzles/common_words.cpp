/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    // debug use
    // for (size_t i = 0; i < file_word_maps.size(); i++){
    //   for (auto elem : file_word_maps[i])
    //     cout << elem.first << " " << elem.second << endl;
    //   cout << endl;
    // }
    init_common();
    // cout << common.size() << endl;
    // for (auto elem : common){
    //     cout << elem.first << " " << elem.second << endl;
    // }
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());
    // go through all files
    for (size_t i = 0; i < file_word_maps.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        // for each word, we need to set up a map that record the times it appears
        map<string, unsigned int> memo;
        map<string, unsigned int>::iterator lookup;
        for (size_t j = 0; j < words.size(); j++){
          lookup = memo.find(words[j]);
          if (lookup != memo.end()){
            memo[words[j]]++;
          }
          else{
            memo[words[j]] = 1;
          }
        }
        file_word_maps[i] = memo;
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    size_t number_file = file_word_maps.size();
    // loop to check strings in each file
    for (size_t i = 0; i < number_file; i++){
      for (auto elem : file_word_maps[i]){
        map<string, unsigned int>::iterator lookup = common.find(elem.first);
        if (lookup == common.end())
          common[elem.first] = 1;
        else
          common[elem.first]++;
      }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    size_t file_number = file_word_maps.size();
    for (auto elem : common){
      if (elem.second == file_number){
        size_t i;
        for (i = 0; i < file_word_maps.size(); i++){
          if (file_word_maps[i].at(elem.first) < n)
            break;
        }
        if (i == file_word_maps.size() && file_word_maps[i-1].at(elem.first) >= n)
          out.push_back(elem.first);
      }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}