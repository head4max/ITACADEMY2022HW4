#pragma once

#include <vector>
#include <string>
#include <system_error>
#include <iostream>

template<typename T>
bool split_str(std::vector<T>& vector, std::string& str4split, int& start_pos, int& count)
{
    if(count == 0)
        return true;

    auto pos = str4split.find_first_of(' ', start_pos);

    if(pos == std::string::npos and str4split.size() - start_pos > 1 and count == 1)
        pos = str4split.size();

    if(pos > start_pos) {
        try {
            T numb = std::stoi(str4split.substr(start_pos, pos - start_pos));
            vector.push_back(numb);
        }catch(const std::bad_cast& e){
            std::cout << "badcast" << std::endl;
            return false;
        }
        ++pos;
        --count;
        return split_str(vector, str4split, pos, count);
    }else
        vector.clear();

    return false;
}

void getNumberInMatrixRow();
void getValuesInMatrixRow();