#include "endereco.h"
#include "hex.h"
#include <bits/stdc++.h>
#include <sstream>

using namespace std;
#pragma once

///////////GERAIS///////////
class RegGerais
{
  public:
	HexNumber EAX;
	HexNumber EBX;
	HexNumber ECX;
	HexNumber EDX;
	RegGerais() : EAX (HexNumber()), EBX (HexNumber()), ECX (HexNumber()), EDX (HexNumber()) {}

	RegGerais (string EAX, string EBX, string ECX, string EDX)
	{
		this->EAX.value = EAX;
		this->EBX.value = EBX;
		this->ECX.value = ECX;
		this->EDX.value = EDX;
	}

	void mostrar_dados()
	{
		cout << "\nRegistradores Gerais: " << endl;
		cout << "EAX: " << EAX.value << endl;
		cout << "EBX: " << EBX.value << endl;
		cout << "ECX: " << ECX.value << endl;
		cout << "EDX: " << EDX.value << endl;
	}

	void set_EAX(string value){
		this->EAX.value = value;
	}
	void set_EBX(string value){
		this->EBX.value = value;
	}
	void set_ECX(string value){
		this->ECX.value = value;
	}
	void set_EDX(string value){
		this->EDX.value = value;
	}
};

///////////SELETORES DE SEGMENTO///////////
class RegSeletorSegmentos
{
  public:
	Endereco<16> CS;
	Endereco<16> SS;
	Endereco<16> DS;

	RegSeletorSegmentos()
	    : CS (Endereco<16>()), SS (Endereco<16>()), DS (Endereco<16>())
	{
	}
	RegSeletorSegmentos (string CS, string SS, string DS)
	{
		this->CS.end_hex = CS;
		this->SS.end_hex = SS;
		this->DS.end_hex = DS;
	}

	void obter_entrada()
	{
		cout << "Digite os seletores de cada segmento:";

		cout << "\nCS: ";
		cin >> this->CS.end_hex;

		cout << "SS: ";
		cin >> this->SS.end_hex;

		cout << "DS: ";
		cin >> this->DS.end_hex;
	}

	void mostrar_dados()
	{
		cout << "CS: " << this->CS.end_hex << endl;
		cout << "SS: " << this->SS.end_hex << endl;
		cout << "DS: " << this->DS.end_hex << endl;
	}
};

///////////OFFSET///////////
class RegOffsets
{
  public:
	Endereco<32> EIP;
	Endereco<32> EBP;
	Endereco<32> ESP;
	Endereco<32> ESI;
	Endereco<32> EDI;

	RegOffsets()
	    : EIP (Endereco<32>()), EBP (Endereco<32>()), ESP (Endereco<32>()),
	      ESI (Endereco<32>()), EDI (Endereco<32>())
	{
	}
	RegOffsets (string EIP, string EBP, string ESP, string ESI, string EDI)
	{
		this->EIP.end_hex = EIP;
		this->EBP.end_hex = EBP;
		this->ESP.end_hex = ESP;
		this->ESI.end_hex = ESI;
		this->EDI.end_hex = EDI;
	}

	void obter_entrada()
	{
		string eip_value, ebp_value;
		cout << "Digite o endereço inicial do segmento EIP: ";
		cin >> eip_value;
		this->EIP = Endereco<32> (eip_value);

		cout << "Digite o endereço inicial do segmento EBP: ";
		cin >> ebp_value;
		this->EBP = Endereco<32> (ebp_value);
		this->ESP = Endereco<32> (ebp_value);
	}

	void mostrar_dados()
	{
		cout << endl << "Offset: " << endl;
		cout << "EIP: " << this->EIP.end_hex << endl;
		cout << "EBP: " << this->EBP.end_hex << endl;
		cout << "ESP: " << this->ESP.end_hex << endl;
		cout << "ESI: " << this->ESI.end_hex << endl;
		cout << "EDI: " << this->EDI.end_hex << endl;
	}

	void set_ESI(string value){
		this->ESI = Endereco<32> (value);
	}
	void set_EDI(string value){
		this->EDI = Endereco<32> (value);
	}

};

///////////FLAG///////////
class RegFlag
{
  public:
	Endereco<32> ZF;
	Endereco<32> SF;
	Endereco<32> OF;
	RegFlag() : ZF (Endereco<32>()), SF (Endereco<32>()), OF (Endereco<32>()) {}
	RegFlag (string ZF, string SF, string OF)
	{
		this->ZF.end_hex = ZF;
		this->SF.end_hex = SF;
		this->OF.end_hex = OF;
	}

	void mostrar_dados()
	{
		cout << "Flags: " << endl;
		cout << "ZF: " << ZF.end_hex << endl;
		cout << "SF: " << SF.end_hex << endl;
		cout << "OF: " << OF.end_hex << endl;
	}
};
