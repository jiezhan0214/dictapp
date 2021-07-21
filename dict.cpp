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

#include <utility>
#include <fstream>
#include <sstream>

#include "dict.hpp"

void Dict::insert(std::string __word) {
    Word temp(__word);
    temp.update_last_visit();
    dict_set.insert(temp);
}

void Dict::remove(std::string __word) {
    Word temp(__word);
    dict_set.erase(temp);
}

void Dict::list() const {
    for (auto it = dict_set.begin(); it != dict_set.end(); ++it) {
        it->show();
    }
    std::cout << "Number of words: " << dict_set.size() << std::endl;
}

std::set<Word>::size_type Dict::size() const {
    return dict_set.size();
}

void Dict::read(std::string filename) {
    std::fstream words_file;
    words_file.open(filename);
    std::string line;
    if (words_file.is_open()) {
        while (std::getline(words_file, line)) {
            std::stringstream line_stream(line);
            std::string buf;
            std::getline(line_stream, buf, ',');    // Get word
            Word temp(buf);
            std::getline(line_stream, buf, ',');    // Get view_cnt
            temp.view_cnt = std::stoi(buf);
            std::getline(line_stream, buf, ',');    // Get lost_cnt
            temp.lost_cnt = std::stoi(buf);
            std::getline(line_stream, buf, ',');    // Get last_visit
            temp.last_visit = buf;
            std::getline(line_stream, buf, ',');    // Get note
            temp.note = buf;
            dict_set.insert(std::move(temp));
        }
    } else {
        std::cout << "Unable to open file.\n";
    }
    current = dict_set.begin();
}

void Dict::save() {
    std::fstream words_file;
    words_file.open("words.csv");
    if (words_file.is_open()) {
        for (auto it = dict_set.begin(); it != dict_set.end(); ++it) {
            words_file << it->word
                << ',' << it->view_cnt
                << ',' << it->lost_cnt
                << ',' << it->last_visit
                << ',' << it->note
                << ',' << std::endl;
        }
    } else {
        std::cout << "Unable to open file.\n";
    }
}

void Dict::review_current_word() {
    current->inc_view();
    current->show();
    current->update_last_visit();
}

void Dict::show_current_word() {
    current->show();
}

void Dict::lost_current_word() {
    current->inc_lost();
}

void Dict::note_current_word(std::string __note) {
    current->update_note(__note);
}

void Dict::reset_current_iter() {
    current = dict_set.end();
    --current;
}

void Dict::inc_current_iter() {
    if (++current == dict_set.end()) {
        current = dict_set.begin();
    }
}
