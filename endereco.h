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
      unsigned n;
      ss << hex << ("0x"+end_hex);
      ss >> n;
      ss.clear();
      bitset<N> b(n);
      return b;
    }

  public:
      string end_hex; // Não altere o valor de end_hex diretamente!!! Use o método set para manter a consistência

  Endereco() : ss(stringstream()), end_hex("0") {}

  Endereco(string end_hex) : ss(stringstream()) {
      this->end_hex = end_hex;
  }

  string toBinary(){
      bitset<N> bitset = toBitset(end_hex);
      return bitset.to_string();
  }
  long toLong(){
      bitset<N> bitset = toBitset(end_hex);
      return bitset.to_ulong();
  }

  void increment(int pass){
      long end_long = toLong() + pass;
      ss << hex << end_long;
      ss >> this->end_hex;
      ss.clear();
  }
};
