#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <sstream>

namespace ch1 {

    /*******************************************************************************************************************
     * 1: Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you cannot use
     * data structures?
     * // TODO: should ask if this will be a unicode or ascii string
     ******************************************************************************************************************/
    bool is_unique(const std::string &str) {
        // solution 1: bool array with each index representing a char O(n)
        // * solution 2: no data structs - loop through n characters and compare with the others O(n ^ 2)
        // solution 3: sort and compare adjacent characters O(n log n)
        if (str.empty() || str.size() > 128) // 128 possible characters in ascii
            return true;

        for (std::size_t i = 0; i < str.size() - 1; ++i) {
            const char current_char = str[i];
            for (std::size_t k = i + 1; k < str.size(); ++k) {
                if (current_char == str[k])
                    return false;
            }
        }
        return true;
    }


    /*******************************************************************************************************************
     * 2: Check Permutation: Given 2 strings, write a method to decide if one is a permutation of the other.
     * // TODO: can I modify? What's the char set? Does whitespace matter? Does letter case matter?
     ******************************************************************************************************************/
    bool is_permutation(const std::string &str1, const std::string &str2) {
        // solution 1: sort both strings and compare each char in both O(n log n) - use if I can modify string
        // * solution 2: use a map to count char occurrences O(n)
        // solution 3: linear search and try to find each char in the other string O(n ^ n)

        // assuming whitespace and letter case matter

        if (str1.size() != str2.size())
            return false;

        std::unordered_map<char, int> char_count{};
        for (std::size_t i = 0; i < str1.size(); ++i) {
            ++char_count[str1[i]];
            --char_count[str2[i]];
        }

        for (const auto &pair : char_count) {
            if (pair.second != 0)
                return false;
        }

        return true;
    }

    /*******************************************************************************************************************
     * 3: URLify: Write a method to replace all spaces in a string with '%20'. Assume string has sufficient space at end
     * to hold additional characters, and that you are given the true length of the string. Please use character array.
     * // TODO: ask what is true size? Should it account for other replacement strings?
     ******************************************************************************************************************/
    void urlify(char *const str) {
        // solution 1: iterate through each char until space, replace char and move rest - NO
        // solution 2: string stream - works if not in place
        // * solution 3: iterate backwards O(n)

        constexpr char SEARCH_CHAR = ' '; // the char to be searched for and replaced
        const std::string REPLACEMENT_STRING = "%20"; // replaces search char
        const auto size_difference = REPLACEMENT_STRING.size() - 1;
        const auto size = strlen(str) + 1; // account for null char

        // get number of spaces
        std::size_t space_count = 0;
        for (std::size_t i = 0; i < size; ++i) {
            if (str[i] == SEARCH_CHAR)
                ++space_count;
        }

        std::size_t swap_index = size + (space_count * size_difference) - 1;

        str[swap_index--] = '\0';

        for (long i = size - size_difference; i >= 0; --i) {
            if (str[i] == SEARCH_CHAR) {
                for (long k = size_difference; k >= 0; --k)
                    str[swap_index--] = REPLACEMENT_STRING[k];
            } else {
                str[swap_index--] = str[i];
            }
        }
    }

    /*******************************************************************************************************************
     * 4: Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
     * A permutation does not need to be limited to just dictionary words.
     * TODO: Are we dealing with ascii? How do non-letters affect 'palindromeness'? How does case affect it?
     ******************************************************************************************************************/
    bool is_palindrome_permutation(const std::string &str) {
        std::unordered_map<char, std::size_t> char_map{};
        for (const auto &character : str) {
            if (isalpha(static_cast<int>(character)))
                ++char_map[character];
        }

        // number of chars that can have an odd count
        const long odd_count = std::count_if(char_map.begin(), char_map.end(), [](const auto &pair) {
            return pair.second % 2 == 1; // count if odd
        });

        return odd_count <= 1;
    }

    bool is_equal(const std::string &short_str, const std::string &long_str,
                  const std::size_t short_start_index, const std::size_t long_start_index) {
        for (std::size_t k = short_start_index, j = long_start_index; k < short_str.size(); ++k, ++j) {
            if (short_str[k] != long_str[j])
                return false;
        }

        return true;
    }

    /*******************************************************************************************************************
     * 5: One Away: There are three types of edits that can be performed on strings; insert a character, remove a
     * character, or replace a character. Given two strings, write a function to check if they are one edit
     * (or zero edits away)
     ******************************************************************************************************************/
    bool is_one_away(const std::string &str, const std::string &modified_str) {
        const std::string &short_string = (str.size() <= modified_str.size()) ? str : modified_str;
        const std::string &long_string = (str.size() > modified_str.size()) ? str : modified_str;

        if (long_string.size() - short_string.size() > 1)
            return false;

        for (std::size_t i = 0, j = 0; i < short_string.size(); ++i, ++j) {
            if (str[i] != modified_str[i]) {
                if (long_string.size() == short_string.size()) // replacement or equals
                    return is_equal(short_string, long_string, i + 1, i + 1);
                else // insertion or deletion
                    return is_equal(short_string, long_string, i, i + 1);
            }
        }

        return true;
    }

    /*******************************************************************************************************************
     * 6: String Compression: Implement a method to perform basic string compression that counts repeated characters.
     * You can assume the string has only uppercase and lowercase letters (a-z).
     * TODO: an optimization would be to check the compressed size in advance.
     ******************************************************************************************************************/
    std::string compress(const std::string &str) {
        if (str.empty())
            return str;

        char curr_char = str[0];
        std::size_t count = 1;
        std::ostringstream ss;

        for (std::size_t i = 1; i < str.size(); ++i) {
            if (str[i] == curr_char) {
                ++count;
            } else {
                ss << curr_char << count;
                curr_char = str[i];
                count = 1;
            }
        }

        ss << curr_char << count;

        const auto result = ss.str();

        return (str.size() > result.size()) ? result : str;
    }

    using matrix = std::vector<std::vector<int>>;

    /**
     * 7: Rotate Matrix: Given an image of NxN matrix where each pixel is image of 4 bytes, write method to rotate image
     * by 90 degrees. Can you do this in place?
     */
    void rotate_matrix(matrix &the_matrix) {
        if (the_matrix.empty() || the_matrix.size() != the_matrix[0].size())
            return;

        const auto n = the_matrix.size();

        for (std::size_t row = 0; row < (n / 2); ++row) {
            const std::size_t last_column = n - row - 1;
            for (std::size_t column = row; column < last_column; ++column) {
                int *buffer = &the_matrix[row][column];
                std::swap(*buffer, the_matrix[column][last_column]);                     // swap with right column
                std::swap(*buffer, the_matrix[last_column][last_column + row - column]); // swap with bottom row
                std::swap(*buffer, the_matrix[last_column + row - column][row]);         // swap with left column
            }
        }
    }

    /**
     * 8: Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column are
     * set to 0.
     */
    void zero_matrix(matrix &matrix) {
        if (matrix.empty()) return;

        const auto total_rows = matrix.size();
        const auto total_columns = matrix[0].size();

        std::vector<std::size_t> marked_rows{};
        std::vector<std::size_t> marked_columns{};

        // mark rows and columns to be zeroed
        for (std::size_t row = 0; row < total_rows; ++row) {
            for (std::size_t column = 0; column < total_columns; ++column) {
                if (matrix[row][column] == 0) {
                    marked_rows.push_back( row );
                    marked_columns.push_back( column );
                }
            }
        }

        // zero out rows
        for ( const auto& row : marked_rows ) {
            for ( std::size_t i = 0; i < total_columns; ++i )
                matrix[row][i] = 0;
        }

        // zero out columns
        for ( const auto& column : marked_columns ) {
            for ( std::size_t i = 0; i < total_rows; ++i )
                matrix[i][column] = 0;
        }
    }

    /**
     * 9: String Rotation: Assume you have a method isSubstring which checks if one word is a substring
     * of another. Given two strings, s1 and s2, write code to check if s1 is a rotation of s1 using only
     * one call to isSubstring.
     */
    bool is_rotation( const std::string& str1, const std::string& str2 ) {
        if ( str1.size() != str2.size() ) { return false; }
        const std::string copy = str2 + str2;
        return std::search(copy.begin(), copy.end(), str1.begin(), str1.end()) != copy.end();
    }

} // end of ch1 namespace
