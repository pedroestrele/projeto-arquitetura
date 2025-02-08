#include <bits/stdc++.h>
#include "endereco.h"
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
      Endereco<16> CS;
      Endereco<16> SS;
      Endereco<16> DS;

    RegSeletorSegmentos() : CS(Endereco<16>()), SS(Endereco<16>()), DS(Endereco<16>()){}
    RegSeletorSegmentos(string CS, string SS, string DS){
      this->CS = Endereco<16>(CS);
      this->SS = Endereco<16>(SS);
      this->DS = Endereco<16>(DS);
    }

    void obter_entrada(){
        string cs_value, ss_value, ds_value;
        cout<<"Digite os seletores de cada segmento:";

        cout<<"\nCS: ";
        cin>>cs_value;
        this->CS = Endereco<16>(cs_value);

        cout<<"SS: ";
        cin>>ss_value;
        this->SS = Endereco<16>(ss_value);

        cout<<"DS: ";
        cin>>ds_value;
        this->DS = Endereco<16>(ds_value);
    }

    void mostrar_dados(){
      cout  << "CS: " << this->CS.end_hex << endl;
      cout  << "SS: " << this->SS.end_hex << endl;
      cout  << "DS: " << this->DS.end_hex << endl;
    }
};

///////////OFFSET///////////
class RegOffsets{
  	public:
		Endereco<32> EIP;
		Endereco<32> EBP;
		Endereco<32> ESP;
		Endereco<32> ESI;
		Endereco<32> EDI;

    RegOffsets() : EIP(Endereco<32>()), EBP(Endereco<32>()), ESP(Endereco<32>()), ESI(Endereco<32>()), EDI(Endereco<32>()){}
	RegOffsets(string EIP, string EBP, string ESP, string ESI, string EDI){
		this->EIP = Endereco<32>(EIP);
		this->EBP = Endereco<32>(EBP);
		this->ESP = Endereco<32>(ESP);
		this->ESI = Endereco<32>(ESI);
		this->EDI = Endereco<32>(EDI);
	}

    void obter_entrada(){
        string eip_value, ebp_value;
        cout<<"Digite o endereço inicial do segmento EIP: ";
        cin>>eip_value;
        this->EIP = Endereco<32>(eip_value);

        cout<<"Digite o endereço inicial do segmento EBP: ";
        cin>>ebp_value;
        this->EBP = Endereco<32>(ebp_value);
        this->ESP = Endereco<32>(ebp_value);
    }

};

  