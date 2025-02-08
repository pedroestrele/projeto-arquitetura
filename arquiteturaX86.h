#include <bits/stdc++.h>
#include "tabela.h"
#include "registradores.h"

using namespace std;
#pragma once

class ArquiteturaX86{
  public:
    RegGerais gerais;
    RegSeletorSegmentos& seletores_segmento;
    RegOffsets& offset;
    TabelaDescritorSegmento tabela;
    int flag;
    map <long, string> memoria;

  	ArquiteturaX86(RegGerais gerais, RegSeletorSegmentos& seletores_segmento, RegOffsets& offset, int flag, map <long, string> memoria, TabelaDescritorSegmento tabela)
    : gerais(gerais), seletores_segmento(seletores_segmento), offset(offset), flag(flag), memoria(memoria), tabela(tabela) {}

	void add(Endereco<32>& END1, Endereco<32>& END2);
	void inc();

	void acessarMemoria(Endereco<32>& end, string retorno){
		cout<<end.end_hex<<endl;
		cout<<"-------->"<<endl;
		cout<<"BUS END"<<endl;
		cout<<endl;
		cout<<retorno<<endl;
		cout<<"<--------"<<endl;
		cout<<"BUS DATA"<<endl;
	};

	void inserirMemoria(int valor){
		cout<<valor<<endl;
		cout<<"-------->"<<endl;
		cout<<"BUS DATA"<<endl;
	};

};

void ArquiteturaX86::add(Endereco<32>& END1, Endereco<32>& END2){
	this->offset.EIP.increment(2);

	cout<<" o que estaria presente no endereço 1?";
	string valor1;
	cin>>valor1;

	cout<<"O que estaria presente no endereço 2?";
	string valor2;
	cin>>valor2;
	this->memoria[END1.end_long]=valor1;
	this->memoria[END2.end_long]=valor2;


	acessarMemoria(this->offset.EIP, "ADD");
	this->offset.EIP.increment(4);
	acessarMemoria(this->offset.EIP, END1.end_hex);
	this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END1.end_hex; 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EIP, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EDI, memoria[END1.end_long]);
	gerais.EAX=stoi(memoria[END1.end_long]);

	this->gerais.mostrar_dados();

	acessarMemoria(this->offset.ESI, memoria[END2.end_long]);
	gerais.EAX=stoi(memoria[END2.end_long]);
	this->gerais.mostrar_dados();

	gerais.EAX += stoi(memoria[END2.end_long]);
	this->gerais.mostrar_dados();

	inserirMemoria(this->gerais.EAX);
	memoria[offset.EDI.end_long]=to_string(gerais.EAX);

}
