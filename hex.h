#include <bits/stdc++.h>
#include <sstream>
#include <cstdint>
using namespace std;
#pragma once

class HexNumber
{
  private:
  stringstream ss;

  public:
  string value;
  HexNumber() : value ("0") {}
  HexNumber (string value) : value (value) {}

  HexNumber(int32_t value_in_long, bool t) : value (longToHex(value_in_long)) {}

  static string longToHex(long binary) {

    stringstream ss;
      ss << hex << binary;
      return ss.str();
  }

  int32_t toLong()
  {
    int32_t n;
    ss << hex << value;
    ss >> n;
    ss.clear();

    return n;
  }
  void add (HexNumber other)
  {
    ss << hex << toLong() + other.toLong();
    ss >> value;
    ss.clear();
  }

  void sub (HexNumber other)
  {
    ss << hex << toLong() - other.toLong();
    ss >> value;
    ss.clear();
  }

  void mul (HexNumber other)
  {
    ss << hex << toLong() * other.toLong();
    ss >> value;
    ss.clear();
  }

  void inc(){
    ss << hex << toLong() + 1;
    ss >> value;
    ss.clear();
  }
  void dec(){
    ss << hex << toLong() - 1;
    ss >> value;
    ss.clear();
  }

  bool equals(HexNumber& other){
    return toLong() == other.toLong();
  }

  bool isNegative(){
    return toLong() < 0;
  }
};