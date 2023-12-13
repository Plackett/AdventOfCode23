#pragma once

#ifndef __DAYLINKERHH
#define __DAYLINKERHH 1

#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include <fstream>
#include <future>
#include <sstream>
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

// from github https://github.com/charlescochran/aoc-2023/blob/main/day13.cpp
inline unsigned hamming(const std::string& str1, const std::string& str2)
{
    // Return the Hamming distance between the input strings (the number of
    // characters that differ).
    unsigned dist = 0;
    for (unsigned i = 0; i < str1.size(); i++)
    {
        dist += (str1[i] != str2[i]);
    }
    return dist;
}

typedef struct {
    std::future<int>* outputfailstate;

    const char* stringbuffer;
} rfoutput;

inline std::string readfile_cpp(const char* filename) {
    static unsigned called{ 0 };
    std::ifstream infile(filename, std::ios::binary | std::ios::in);
    std::string buffer = "Failed to open";
    infile.seekg(0, std::ios::end);
    buffer.resize(infile.tellg());

    infile.seekg(0, std::ios::beg);
    infile.read(&buffer[0], buffer.size());

    infile.close();

    ///OPTIONAL ///
    auto outfailstate = std::async([](std::string toLog, unsigned called)->int {
        std::ostringstream fname;
        fname << "dump" << called << ".dump";

        std::ofstream out(fname.str().c_str(), std::ios::out | std::ios::binary);
        if (not out.is_open()) return -1;
        out << toLog;
        out.close();
        return 1;
        }, buffer, called++);
    ///OPTIONAL ///

    return buffer;
}

template <typename val_T>
inline bool inRange(val_T x, val_T maxx, val_T minx) {
	return x < maxx && x > minx;
}

struct vec2
{
	long long x, y;
};

inline bool operator==(const vec2& v1, const vec2& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
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