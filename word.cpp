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

#include "word.hpp"

#include <ctime>

void Word::show() const {
    std::cout
        << std::left
        << std::setw(20)
        << word
        << "    ||  Views: "
        << std::setw(5)
        << view_cnt
        << "  Losts: "
        << std::setw(5)
        << lost_cnt
        << "  Last visit: "
        << std::setw(28)
        << last_visit
        << "  Note: "
        << note
        << std::endl;
}

void Word::inc_view() const {
    view_cnt++;
}

void Word::inc_lost() const {
    lost_cnt++;
}

std::string Word::get_word() const {
    return word;
}

bool Word::operator< (const Word& rhs) const {
    return word < rhs.word;
}

void Word::update_last_visit() const {
    time_t rawtime;
    time(&rawtime);
    char temp[26];
    ctime_r(&rawtime, temp);
    last_visit = temp;
    last_visit.pop_back();  // Delete the last newline char
}

void Word::update_note(const std::string& __note) const {
    note = __note;
}
