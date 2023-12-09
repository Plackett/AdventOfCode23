#pragma once

#ifndef __DAYLINKERHH
#define __DAYLINKERHH 1

#include <vector>
#include <string>
#include <iostream>
#include <numeric>
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

template <typename val_T>
inline bool inRange(val_T x, val_T maxx, val_T minx) {
	return x < maxx && x > minx;
}

int day1(int part);
int day2(int part);
int day3(int part);
int day4(int part);
int day5(int part);
int day6(int part);
int day7(int part);
int day8(int part);
int day9(int part);
int day10(int part);
int day11(int part);
int day12(int part);
int day13(int part);
int day14(int part);
int day15(int part);
int day16(int part);
int day17(int part);
int day18(int part);
int day19(int part);
int day20(int part);
int day21(int part);
int day22(int part);
int day23(int part);
int day24(int part);
int day25(int part);

#endif