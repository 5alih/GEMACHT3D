#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <bits/stdc++.h>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <variant>
#include "raylib.h"

inline const char *to_const_char(std::string str){
	const char *text= str.c_str();
	return text;
}

inline std::string to_string(int value){
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

inline std::vector<std::string> split_string(const std::string str, const char ch){
	std::stringstream stream(str);
	std::vector<std::string> parts;
	std::string s;
	while(std::getline(stream, s, ch)){
		parts.push_back(s);
	}
	return parts;
}

inline std::string cat_string(std::vector<std::string> parts, char ch){
	std::ostringstream stream;
	for(std::string str : parts){
		stream << str;
		if(ch!= '\0')
			stream << ch;
	}
	return stream.str();
}

inline std::string cat_2string(std::string s1, std::string s2){
	std::ostringstream stream;
	stream<< s1 << s2;
	return stream.str();
}

inline bool is_number(const std::string& s){
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

#endif // MY_FUNCTIONS_H