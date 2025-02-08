#include <bits/stdc++.h>
using namespace std;
#pragma once 

///////////GERAIS///////////
class RegGerais{
    public:
        int EAX;
        int EBX;
        int ECX;
        int EDX;
    RegGerais() : EAX(0), EBX(0), ECX(0), EDX(0) {}
    RegGerais(int EAX, int EBX, int ECX, int EDX){
    this->EAX = EAX;
    this->EBX = EBX;
    this->ECX = ECX;
    this->EDX = EDX;
    }

};

///////////SELETORES DE SEGMENTO///////////
class RegSeletorSegmentos{
  	public:
		int CS;
		int SS;
		int DS;

    RegSeletorSegmentos() : CS(0), SS(0), DS(0){}

    RegSeletorSegmentos(int CS, int SS, int DS ){
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
class RegOffsets{
  	public:
		int EIP;
		int EBP;
		int ESP;
		int ESI;
		int EDI;

    RegOffsets() : EIP(0), EBP(0), ESP(0), ESI(0), EDI(0) {}

	RegOffsets(int EIP, int EBP, int ESP, int ESI, int EDI){
		this->EIP = EIP;
		this->EBP = EBP;
		this->ESP = ESP;
		this->ESI = ESI;
		this->EDI = EDI;
	}

  };

  