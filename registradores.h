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
	RegGerais()
	    : EAX (HexNumber()), EBX (HexNumber()), ECX (HexNumber()),
	      EDX (HexNumber())
	{
	}

	RegGerais (string EAX, string EBX, string ECX, string EDX)
	{
		this->EAX.value = EAX;
		this->EBX.value = EBX;
		this->ECX.value = ECX;
		this->EDX.value = EDX;
	}

	void mostrar_dados()
	{
		int tamanho = 15;
		cout << endl << "| Registradores Gerais |" << endl;
		cout << string (tamanho + 9, '-') << endl;
		cout << "| EAX |" << setw(tamanho) << EAX.value << " |" <<  endl;
		cout << "| EBX |" << setw(tamanho) << EBX.value << " |" << endl;
		cout << "| ECX |" << setw(tamanho) << ECX.value << " |" << endl;
		cout << "| EDX |" << setw(tamanho) << EDX.value << " |" << endl;
	}

	void set_EAX (string value) { this->EAX.value = value; }
	void set_EBX (string value) { this->EBX.value = value; }
	void set_ECX (string value) { this->ECX.value = value; }
	void set_EDX (string value) { this->EDX.value = value; }
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
		int tamanho = 16;
		cout << endl << "| Seletores de Segmento |" << endl;
		cout << string (tamanho + 9, '-') << endl;
		cout << "| CS | " << setw(tamanho) << this->CS.end_hex << " |" << endl;
		cout << "| SS | " << setw(tamanho) << this->SS.end_hex << " |" << endl;
		cout << "| DS | " << setw(tamanho) << this->DS.end_hex << " |" <<endl;
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
		cout << "Digite o endereco inicial do segmento EIP: ";
		cin >> eip_value;
		this->EIP = Endereco<32> (eip_value);

		cout << "Digite o endereco inicial do segmento EBP: ";
		cin >> ebp_value;
		this->EBP = Endereco<32> (ebp_value);
		this->ESP = Endereco<32> (ebp_value);
	}

	void mostrar_dados()
	{
		int tamanho = 10;
		cout << endl << "|" << setw(tamanho) << "Offset" << setw(tamanho-2) << "|" << endl;
		cout << string (tamanho + 9, '-') << endl;
		cout << "| EIP |" << setw(tamanho) << this->EIP.end_hex << " |" << endl;
		cout << "| EBP |" << setw(tamanho) << this->EBP.end_hex << " |" << endl;
		cout << "| ESP |" << setw(tamanho) << this->ESP.end_hex << " |" << endl;
		cout << "| ESI |" << setw(tamanho) << this->ESI.end_hex << " |" << endl;
		cout << "| EDI |" << setw(tamanho) << this->EDI.end_hex << " |" << endl;
	}

	void set_ESI (string value) { this->ESI = Endereco<32> (value); }
	void set_EDI (string value) { this->EDI = Endereco<32> (value); }
};

///////////FLAG///////////
class RegFlag
{
public:
	HexNumber ZF;
	HexNumber SF;
	HexNumber OF;
	RegFlag() : ZF (HexNumber()), SF (HexNumber()), OF (HexNumber()) {}
	void set (string r)
	{
		this->ZF.value = r.substr(0, 3);
		this->SF.value = r.substr(3, 3);
		this->OF.value = r.substr(6, 2);
	}
	RegFlag (string ZF, string SF, string OF)
	{
		this->ZF.value = ZF;
		this->SF.value = SF;
		this->OF.value = OF;
	}

	void mostrar_dados()
	{
		int tamanho = 12;
		cout << endl << "| Registrador Flag |" << endl;
		cout << string (tamanho + 8, '-') << endl;
		cout << "| SF |" << setw(tamanho) << SF.value << " |" << endl;
		cout << "| OF |" << setw(tamanho) << OF.value << " |" << endl;
		cout << "| ZF |" << setw(tamanho) << ZF.value << " |" << endl;
	}
};
