#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#pragma once

using namespace std;

template<int N>
class Endereco {
  private:
    stringstream  ss;
    bitset<N> bitset;
  public:
    string end_hex;
  
  Endereco() :end_hex("0x0") {
    ss << hex << end_hex;
    unsigned n;
    ss >> n;
    bitset = n;
  }

  Endereco(string end_hex) {
    this->end_hex = "0x" + end_hex;
    ss << hex << this->end_hex;
    unsigned n;
    ss >> n;
    bitset = n;
  }

  string toBinary(){
    return bitset.to_string();
  }

  long toLong(){
    return bitset.to_ulong();
  }

  void increment(int pass){
    ss << hex << end_hex;
    unsigned n;
    ss >> n;
    bitset = n + pass;
  }
};