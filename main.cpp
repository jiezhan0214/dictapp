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

#include <iostream>

#include "word.hpp"
#include "dict.hpp"

void tui(Dict* dict) {
    // TUI based on a state machine
    std::cout << "Welcome to \"dictapp\"!" << std::endl;
    unsigned state = 1;     // integer states
    std::string in_buf;
    for (;;) {
        switch (state) {
            case 0: {   // Quit
                std::cout << "Thanks for playing me. " << std::endl;
                return;
            }
            case 1: {   // Initial state, main menu
                std::cout << "Main menu: \n"
                    << "    1. Read vocabulary (words.csv by default)\n"
                    << "    2. Review words\n"
                    << "    3. List all words\n"
                    << "    4. Insert a new word\n"
                    << "    5. Delete a word\n"
                    << "    6. Save & Quit\n";
                std::cin >> in_buf;
                int temp = std::stoi(in_buf);
                if (temp == 1) {
                    std::cout << "Reading \"words.csv\"..." << std::endl;
                    dict->read();
                    std::cout << "Finished!" << std::endl;
                } else if (temp == 2) {
                    std::cout << "Reviewing words...\n"
                        << "Press 'Enter' to see the next word;\n"
                        << "Enter '1' if you forget this word;\n"
                        << "Enter '2' to write notes;\n"
                        << "Enter '3' to return to Main menu.\n";
                    std::getline(std::cin, in_buf);     // Get rid of a newline
                    dict->reset_current_iter();
                    state = 2;
                } else if (temp == 3) {
                    std::cout << "Listing all words..." << std::endl;
                    dict->list();
                } else if (temp == 4) {
                    std::cout << "Enter a new word to be inserted..." << std::endl;
                    std::getline(std::cin, in_buf);     // Get rid of a newline
                    std::getline(std::cin, in_buf);
                    if (in_buf == "") {
                        std::cout << "Empty input, returning to Main menu..." << std::endl;
                    } else {
                        dict->insert(in_buf);
                        std::cout << in_buf << ", inserted." << std::endl;
                    }
                } else if (temp == 5) {
                    std::cout << "Enter the word to be deleted..." << std::endl;
                    std::getline(std::cin, in_buf);     // Get rid of a newline
                    std::getline(std::cin, in_buf);
                    if (in_buf == "") {
                        std::cout << "Empty input, returning to Main menu..." << std::endl;
                    } else {
                        dict->remove(in_buf);
                        std::cout << in_buf << ", deleted." << std::endl;
                    }
                } else if (temp == 6) {
                    std::cout << "Saving data to \"words.csv\"..." << std::endl;
                    dict->save();
                    std::cout << "Finished!" << std::endl;
                    std::cout << "Quiting..." << std::endl;
                    state = 0;
                } else {
                    std::cout << "Unknown input, returning to Main menu..." << std::endl;
                }
                break;
            }
            case 2: {   // Reviewing words
                std::getline(std::cin, in_buf);
                if (in_buf == "") {
                    dict->inc_current_iter();
                    dict->review_current_word();
                } else {
                    int temp = std::stoi(in_buf);
                    if (temp == 1) {
                        std::cout << "Hope you will recognize it next time!" << std::endl;
                        dict->lost_current_word();
                        dict->show_current_word();
                    } else if (temp == 2) {
                        std::cout << "Writing a new note..." << std::endl;
                        std::cin >> in_buf;
                        dict->note_current_word(in_buf);
                        std::getline(std::cin, in_buf);     // Get rid of a newline
                        dict->show_current_word();
                    } else if (temp == 3) {
                        std::cout << "Returning to Main menu..." << std::endl;
                        state = 1;
                    } else {
                        std::cout << "Unknown input." << std::endl;
                    }
                }
                break;
            }
        }
    }
}

int main() {
    Dict dict;
    tui(&dict);

    return 0;
}
