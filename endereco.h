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

  bitset<N> toBitset(string end_hex){
    ss << hex << ("0x"+end_hex);
    unsigned n;
    ss >> n;
    return n;
  }

  public:
    string end_hex; // Não altere o valor de end_hex diretamente!!! Use o método set para manter a consistência
    string end_bin;
    long end_long;
    
  
  Endereco() {
    this->set("0");
  }

  Endereco(string end_hex) {
    this->set(end_hex);
  }

  void set(string end_hex){
    this->end_hex = end_hex;
    bitset<N> bitset = toBitset(end_hex);
    this->end_bin = bitset.to_string();
    this->end_long = bitset.to_ulong();
  }

  void increment(int pass){
    unsigned n;
    this->end_long += pass;
    ss << hex << this->end_long;
    ss >> this->end_hex;

    bitset<N> bitset(this->end_long);
    this->end_bin = bitset.to_string();
  }
};