#include <bits/stdc++.h>
using namespace std;
#pragma once 

///////////GERAIS///////////
class reg_gerais{
public:
  int EAX;
  int EBX;
  int ECX;
  int EDX;
  reg_gerais() : EAX(0), EBX(0), ECX(0), EDX(0) {}
  reg_gerais(int EAX, int EBX, int ECX, int EDX){
    this->EAX = EAX;
    this->EBX = EBX;
    this->ECX = ECX;
    this->EDX = EDX;
  }

};
///////////SELETORES DE SEGMENTO///////////
class reg_seletores_segmento{
public:
  int CS;
  int SS;
  int DS;
  reg_seletores_segmento() : CS(0), SS(0), DS(0){}
  reg_seletores_segmento(int CS, int SS, int DS ){
    this->CS = CS;
    this->SS = SS;
    this->DS = DS;
    }
  void mostrar_dados(){
    cout << "CS: " << CS << endl;
    cout  << "SS: " << SS << endl;
    cout  << "DS: " << DS << endl;
    }
  };



///////////OFFSET///////////
  class reg_offset{
  public:
    int EIP;
    int EBP;
    int ESP;
    int ESI;
    int EDI;
    reg_offset() : EIP(0), EBP(0), ESP(0), ESI(0), EDI(0) {}
    reg_offset(int EIP, int EBP, int ESP, int ESI, int EDI){
      this->EIP = EIP;
      this->EBP = EBP;
      this->ESP = ESP;
      this->ESI = ESI;
      this->EDI = EDI;
    }

  };

  