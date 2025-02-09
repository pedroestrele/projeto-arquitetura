#include <bits/stdc++.h>
#include "tabela.h"
#include "registradores.h"

using namespace std;
#pragma once

class ArquiteturaX86{
  public:
    RegGerais gerais;
    RegSeletorSegmentos &seletores_segmento;
    RegOffsets &offset;
    TabelaDescritorSegmento &tabela;
    int flag;
    map <long, string> memoria;

	ArquiteturaX86(RegGerais gerais, RegSeletorSegmentos &seletores_segmento, RegOffsets &offset, int flag, map <long, string> memoria, TabelaDescritorSegmento &tabela)
		: gerais(gerais), seletores_segmento(seletores_segmento), offset(offset), flag(flag), memoria(memoria), tabela(tabela) {
			seletores_segmento.mostrar_dados();
		}

	void add(Endereco<32>& END1, Endereco<32>& END2);
	void inc();
	void mov(Endereco<32>& END1, Endereco<32>& END2);
	void push(Endereco<32>& END1);
	void pop(Endereco<32>& END1);

	void acessarMemoria(Endereco<32>& end, string retorno){
		cout<<endl<<end.end_hex<<endl;
		cout<<"-------->"<<endl;
		cout<<"BUS END"<<endl;
		cout<<endl;
		cout<<retorno<<endl;
		cout<<"<--------"<<endl;
		cout<<"BUS DATA"<<endl;
	};

	void inserirMemoria(Endereco<32>& end, int valor){
		cout<<endl<<end.end_hex<<endl;
		cout<<"-------->"<<endl;
		cout<<"BUS END"<<endl;
		cout<<valor<<endl;
		cout<<"-------->"<<endl;
		cout<<"BUS DATA"<<endl;
	};

	string obterValorEnd(int n){
		string valor;
		cout << "O que estaria presente no endereço " << n << "? ";
		cin >> valor;
		return valor;
	}

	Endereco<32> obterEnderecoLinear(DescritorSegmento& descritor, Endereco<32>& end){
		Endereco<32> end_linear(descritor.end_base.end_hex);
		end_linear.increment(end.toLong());
		
		if(descritor.ehGPF(end_linear)){
			cout << endl << "GPF!" << endl;
		}

		return end_linear;
	}
};

void ArquiteturaX86::add(Endereco<32>& END1, Endereco<32>& END2){
	END1 = obterEnderecoLinear(tabela.code_segm, END1);
	END2 = obterEnderecoLinear(tabela.code_segm, END2);

	this->memoria[END1.toLong()] = obterValorEnd(1);
	this->memoria[END2.toLong()] = obterValorEnd(2);

	acessarMemoria(this->offset.EIP, "ADD");
	this->offset.EIP.increment(4);
	acessarMemoria(this->offset.EIP, END1.end_hex);
	this->offset.mostrar_dados();

	this->offset.EDI = (END1.end_hex); 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EIP, END2.end_hex);
	this->offset.ESI = (END2.end_hex);
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EDI, memoria[END1.toLong()]);
	gerais.EAX=stoi(memoria[END1.toLong()]);

	this->gerais.mostrar_dados();

	acessarMemoria(this->offset.ESI, memoria[END2.toLong()]);
	gerais.EAX += stoi(memoria[END2.toLong()]);
	this->gerais.mostrar_dados();

	inserirMemoria(this->offset.EDI, this->gerais.EAX);
	memoria[offset.EDI.toLong()]=to_string(gerais.EAX);

}

void ArquiteturaX86::mov(Endereco<32>& END1, Endereco<32>& END2){
	END1 = obterEnderecoLinear(tabela.code_segm, END1);
	END2 = obterEnderecoLinear(tabela.code_segm, END2);


	this->memoria[END1.toLong()] = obterValorEnd(1);
	this->memoria[END2.toLong()] = obterValorEnd(2);

	acessarMemoria(this->offset.EIP, "MOV"); // Obtém MOV
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EIP, END1.end_hex); // Obtém END1
	this->offset.EDI = (END1.end_hex); 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EIP, END2.end_hex); // Obtém END2
	this->offset.ESI = (END2.end_hex); 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.ESI, memoria[END2.toLong()]); // Obtém valor apontado por END2
	this->gerais.EAX=stoi(memoria[END2.toLong()]);
	this->gerais.mostrar_dados();

	inserirMemoria(this->offset.EDI, this->gerais.EAX); // Insere valor apontado por END2 na posição apontada por END1
}

void ArquiteturaX86::push(Endereco<32>& END1){
	END1 = obterEnderecoLinear(tabela.code_segm, END1);
	this->memoria[END1.toLong()] = obterValorEnd(1);
	
	Endereco<32> endAux = obterEnderecoLinear(tabela.code_segm, offset.EIP);
	acessarMemoria(endAux, "PUSH"); // Obtém PUSH
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	endAux = obterEnderecoLinear(tabela.code_segm, offset.EIP);
	acessarMemoria(endAux, END1.end_hex); // Obtém END1
	this->offset.ESI.end_hex = (END1.end_hex); 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	endAux = obterEnderecoLinear(tabela.data_segm, offset.ESI);
	acessarMemoria(endAux, memoria[END1.toLong()]); // Obtém valor apontado por END1
	this->gerais.EAX=stoi(memoria[END1.toLong()]);
	this->gerais.mostrar_dados();

	this->offset.ESP.increment(-4);
	endAux = obterEnderecoLinear(tabela.stack_segm, offset.ESP);
	inserirMemoria(endAux, this->gerais.EAX); // Insere valor apontado por END1 no topo da pilha
	this->offset.mostrar_dados();
}

void ArquiteturaX86::pop(Endereco<32>& END1){
	this->memoria[END1.toLong()] = obterValorEnd(1);

	acessarMemoria(this->offset.EIP, "POP"); // Obtém POP
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.EIP, END1.end_hex); // Obtém END1
	this->offset.EDI.end_hex = (END1.end_hex); 
	this->offset.EIP.increment(4);
	this->offset.mostrar_dados();

	acessarMemoria(this->offset.ESP, memoria[this->offset.ESP.toLong()]); // Obtém valor do topo da pilha
	this->gerais.EAX=stoi(memoria[this->offset.ESP.toLong()]);
	this->offset.ESP.increment(4);
	this->gerais.mostrar_dados();
	this->offset.mostrar_dados();

	inserirMemoria(this->offset.EDI, this->gerais.EAX); // Insere valor do topo da pilha na posição apontada por END1
}