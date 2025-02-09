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

    void mostrar_dados(){
        cout<<"Registradores Gerais: "<<endl;
        cout<<"EAX: "<<EAX<<endl;
        cout<<"EBX: "<<EBX<<endl;
        cout<<"ECX: "<<ECX<<endl;
        cout<<"EDX: "<<EDX<<endl;
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
      this->CS.end_hex = CS;
      this->SS.end_hex = SS;
      this->DS.end_hex = DS;
    }


    void obter_entrada(){
        cout<<"Digite os seletores de cada segmento:";

        cout<<"\nCS: ";
        cin>>this->CS.end_hex;

        cout<<"SS: ";
        cin>>this->SS.end_hex;

        cout<<"DS: ";
        cin>>this->DS.end_hex;
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
		this->EIP.end_hex = EIP;
		this->EBP.end_hex = EBP;
		this->ESP.end_hex = ESP;
		this->ESI.end_hex = ESI;
		this->EDI.end_hex = EDI;
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

    void mostrar_dados(){
        cout<<endl<<"Offset: "<<endl;
        cout  << "EIP: " << this->EIP.end_hex << endl;
        cout  << "EBP: " << this->EBP.end_hex << endl;
        cout  << "ESP: " << this->ESP.end_hex << endl;
        cout  << "ESI: " << this->ESI.end_hex << endl;
        cout  << "EDI: " << this->EDI.end_hex << endl;
    }

};
