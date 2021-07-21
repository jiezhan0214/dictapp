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

#ifndef WORD_HPP_
#define WORD_HPP_

#include <iostream>
#include <iomanip>
#include <string>

class Word {
 private:
    std::string word;
    mutable unsigned view_cnt;
    mutable unsigned lost_cnt;
    mutable std::string last_visit;
    mutable std::string note;
 public:
    Word() = delete;
    explicit Word(std::string __word) : word(__word),
        view_cnt(0), lost_cnt(0) {}
    void show() const;
    void inc_view() const;  // To allow modifying 'mutable' with const interator in set
    void inc_lost() const;  // To allow modifying 'mutable' with const interator in set
    std::string get_word() const;
    bool operator< (const Word& rhs) const;
    void update_last_visit() const;     // To allow modifying 'mutable' with const interator in set
    void update_note(const std::string& __note) const;  // To allow modifying 'mutable' with const interator in set
    friend class Dict;
};
#endif  // WORD_HPP_
