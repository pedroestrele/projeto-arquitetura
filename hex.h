#include <bits/stdc++.h>
#include <sstream>

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

	long toLong()
	{
		long n;
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

