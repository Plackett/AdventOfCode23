#pragma once

#ifndef __DAYLINKERHH
#define __DAYLINKERHH 1

#include <vector>
#include <string>
// for string delimiter
inline std::vector<std::string> split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

int day1(bool part);
int day2(bool part);
int day3(bool part);
int day4(bool part);

#endif