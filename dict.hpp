/*
Copyright (c) 2021, Jie Zhan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef DICT_HPP_
#define DICT_HPP_

#include <string>
#include <set>

#include "word.hpp"

class Dict {
 private:
    std::set<Word> dict_set;
    std::set<Word>::iterator current;

 public:
    // Constructor
    Dict() : dict_set(), current(dict_set.begin()) {}
    // Insert & Remove
    void insert(std::string __word);
    void remove(std::string __word);
    // List all words
    void list() const;
    // Get the number of words
    std::set<Word>::size_type size() const;
    // File reading and saving
    void read(std::string filename = "words.csv");
    void save();
    // Reviewing words
    void review_current_word();
    void show_current_word();
    void lost_current_word();
    void note_current_word(std::string __note);
    void reset_current_iter();
    void inc_current_iter();
    // Shuffle
    void shuffle();
};
#endif  // DICT_HPP_
