#include "endereco.h"
#include "hex.h"
#include "registradores.h"
#include "tabela.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
#pragma once

class ArquiteturaX86
{
public:
	RegGerais &gerais;
	RegSeletorSegmentos &seletores_segmento;
	RegOffsets &offset;
	RegFlag &flag;
	TabelaDescritorSegmento &tabela;
	// int flag;
	map<long, string> memoria;

	ArquiteturaX86 (
	    RegGerais &gerais, RegSeletorSegmentos &seletores_segmento,
	    RegOffsets &offset, map<long, string> memoria,
	    TabelaDescritorSegmento &tabela, RegFlag &flag)
	    : gerais (gerais), seletores_segmento (seletores_segmento),
	      offset (offset), flag (flag), tabela (tabela), memoria (memoria)
	{
		seletores_segmento.mostrar_dados();
	}

	void add (Endereco<32> &END1, Endereco<32> &END2);
	void inc (Endereco<32> &END);
	void dec (Endereco<32> &END);
	void mov (Endereco<32> &END1, Endereco<32> &END2);
	void xchg (Endereco<32> &END1, Endereco<32> &END2);
	void push (Endereco<32> &END1);
	void pop (Endereco<32> &END1);
	void cmp (Endereco<32> &END1, Endereco<32> &END2);
	void jmp (Endereco<32> &END);
	void mul (Endereco<32> &END1, Endereco<32> &END2);
	void sub (Endereco<32> &END1, Endereco<32> &END2);
  	void neg (Endereco<32> &END);
	void AND (Endereco<32> &DST, Endereco<32> &SRC);
	void OR (Endereco<32> &DST, Endereco<32> &SRC);
	void XOR (Endereco<32> &DST, Endereco<32> &SRC);
  
	void acessarMemoria (Endereco<32> &end, string retorno)
	{
		cout << endl << end.end_hex << endl;
		cout << "-------->" << endl;
		cout << "BUS END" << endl;
		cout << endl;
		cout << retorno << endl;
		cout << "<--------" << endl;
		cout << "BUS DATA" << endl;
	};
	void inserirMemoria (Endereco<32> &end, HexNumber &num)
	{
		cout << endl << end.end_hex << endl;
		cout << "-------->" << endl;
		cout << "BUS END" << endl;
		cout << num.value << endl;
		cout << "-------->" << endl;
		cout << "BUS DATA" << endl;
	};

	string obterValorAlocado (int n)
	{
		string valor;
		cout << "O que estaria presente no endereço " << n << "? ";
		cin >> valor;
		return valor;
	}

	Endereco<32>
	obterEnderecoLinear (DescritorSegmento &descritor, Endereco<32> &end)
	{
		Endereco<32> end_linear (descritor.end_base.end_hex);
		end_linear.increment (end.toLong());

		if (descritor.ehGPF (end_linear)) {
			cout << endl << "GPF!" << endl;
			exit (4);
		}

		return end_linear;
	}
};

void ArquiteturaX86::add (Endereco<32> &END1, Endereco<32> &END2)
{
Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "ADD");
	this->offset.EIP.increment (2);

	offset.mostrar_dados();
	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END1.end_hex);

	this->offset.EDI.end_hex = END1.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	acessarMemoria (end_linear, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
	acessarMemoria (end_linear, memoria[END2.toLong()]);
	gerais.EAX.add (memoria[end_linear.toLong()]);
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (end_linear, gerais.EAX);
	memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::mov (Endereco<32> &END1, Endereco<32> &END2)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear;
	end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, "MOV"); // Obtém MOV
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, END1.end_hex); // Obtém END1
	this->offset.EDI = (END1.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, END2.end_hex); // Obtém END2
	this->offset.ESI = (END2.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, offset.ESI);
	acessarMemoria (
	    end_linear,
	    memoria[end_linear.toLong()]); // Obtém valor apontado por END2
	this->gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, offset.EDI);
	inserirMemoria (
	    end_linear,
	    this->gerais
	        .EAX); // Insere valor apontado por END2 na posição apontada por END1
	memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::push (Endereco<32> &END1)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear = obterEnderecoLinear (tabela.code_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, "PUSH"); // Obtém PUSH
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, END1.end_hex); // Obtém END1
	this->offset.ESI.end_hex = (END1.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, offset.ESI);
	acessarMemoria (
	    end_linear,
	    memoria[end_linear.toLong()]); // Obtém valor apontado por END1
	this->gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	this->offset.ESP.increment (-4);
	end_linear = obterEnderecoLinear (tabela.stack_segm, offset.ESP);
	inserirMemoria (
	    end_linear,
	    this->gerais.EAX); // Insere valor apontado por END1 no topo da pilha
	memoria[end_linear.toLong()] = gerais.EAX.value;
	this->offset.mostrar_dados();
}

void ArquiteturaX86::pop (Endereco<32> &END1)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear;
	end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "POP"); // Obtém POP
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END1.end_hex); // Obtém END1
	this->offset.EDI.end_hex = (END1.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.stack_segm, this->offset.ESP);
	acessarMemoria (
	    end_linear,
	    memoria[this->offset.ESP.toLong()]); // Obtém valor do topo da pilha
	this->gerais.EAX.value = memoria[this->offset.ESP.toLong()];
	this->offset.ESP.increment (4);
	this->gerais.mostrar_dados();
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (
	    end_linear,
	    this->gerais
	        .EAX); // Insere valor do topo da pilha na posição apontada por END1
	memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::inc (Endereco<32> &END)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "INC");
	this->offset.EIP.increment (4);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END.end_hex);
	// this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END.end_hex;
	this->offset.EIP.increment (4);
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, END);
	acessarMemoria (this->offset.EDI, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	// this->gerais.mostrar_dados();

	gerais.EAX.inc();
	// this->gerais.mostrar_dados();

	inserirMemoria (end_linear, this->gerais.EAX);
	memoria[offset.EDI.toLong()] = gerais.EAX.value;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::dec (Endereco<32> &END)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "DEC");
	this->offset.EIP.increment (4);
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END.end_hex);
	// this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END.end_hex;
	this->offset.EIP.increment (4);
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, END);
	acessarMemoria (this->offset.EDI, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	// this->gerais.mostrar_dados();

	gerais.EAX.dec();
	// this->gerais.mostrar_dados();

	inserirMemoria (end_linear, this->gerais.EAX);
	memoria[end_linear.toLong()] = gerais.EAX.value;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::cmp (Endereco<32> &END1, Endereco<32> &END2)
{
	this->offset.EIP.increment (2);

	cout << "O que estaria presente no endereço 1? ";
	string valor1;
	cin >> valor1;

	cout << "O que estaria presente no endereço 2? ";
	string valor2;
	cin >> valor2;

	this->memoria[END1.toLong()] = valor1;
	this->memoria[END2.toLong()] = valor2;

	acessarMemoria (this->offset.EIP, "CMP");
	this->offset.EIP.increment (4);
	acessarMemoria (this->offset.EIP, END1.end_hex);
	this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END1.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	acessarMemoria (this->offset.EIP, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	acessarMemoria (this->offset.EDI, memoria[END1.toLong()]);
	HexNumber valorReg1 (memoria[END1.toLong()]);

	acessarMemoria (this->offset.ESI, memoria[END2.toLong()]);
	HexNumber valorReg2 (memoria[END2.toLong()]);

	HexNumber resultado (valorReg1.value);
	resultado.sub (valorReg2.value);

	if (valorReg1.equals (valorReg2)) {
		this->flag.ZF.end_hex = "1"; // ZF = 1 se os valores forem iguais
	} else {
		this->flag.ZF.end_hex = "0";
	}

	if (resultado.isNegative()) {
		this->flag.SF.end_hex = "1"; // SF = 1 se o resultado for negativo
	} else {
		this->flag.SF.end_hex = "0";
	}

	// Pega o bit de sinal para fazer a comparação
	bool sinalOperando1 = (valorReg1.toLong() >> 31) & 1;
	bool sinalOperando2 = (valorReg2.toLong() >> 31) & 1;
	bool sinalResultado = (resultado.toLong() >> 31) & 1;

	// OF = (sinalOperando1 == sinalOperando2) && (sinalResultado !=
	// sinalOperando1)
	if ((sinalOperando1 == sinalOperando2) &&
	    (sinalResultado != sinalOperando1)) {
		this->flag.OF.end_hex = "1"; // OF = 1 se ocorreu overflow
	} else {
		this->flag.OF.end_hex = "0";
	}

	cout << "Resultado da comparação (valorReg1 - valorReg2): " << resultado.value
	     << endl;
	this->flag.mostrar_dados();

	gerais.EAX.value = valorReg1.value;
	gerais.EBX.value = valorReg2.value;

	this->gerais.mostrar_dados();
}

void ArquiteturaX86::jmp (Endereco<32> &END)
{
	this->offset.EIP.increment (2);

	// Exibe a instrução JMP
	cout << "Executando JMP para o endereço: " << END.end_hex << endl;

	acessarMemoria (this->offset.EIP, "JMP");
	this->offset.EIP.increment (4);
	acessarMemoria (this->offset.EIP, END.end_hex);
	// this->offset.mostrar_dados();

	// Atualiza EIP para endereço de destino
	this->offset.EIP = END.end_hex;

	acessarMemoria (this->offset.EIP, memoria[END.toLong()]);

	cout << "Novo valor do EIP: " << this->offset.EIP.end_hex;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::xchg (Endereco<32> &END1, Endereco<32> &END2)
{
	this->offset.EIP.increment (2);
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "XCHG"); // Obtém XCHG
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END1.end_hex); // Obtém END1
	this->offset.EIP.increment (4);
	this->offset.EDI.end_hex = END1.end_hex;
	this->offset.ESI.end_hex = END1.end_hex;
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	acessarMemoria (
	    end_linear,
	    memoria[end_linear.toLong()]); // Obtém valor apontado por END1
	this->gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END2.end_hex); // Obtém END2
	this->offset.EIP.increment (4);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
	acessarMemoria (
	    this->offset.ESI,
	    memoria[end_linear.toLong()]); // Obtém valor apontado por END2
	this->gerais.EBX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (
	    end_linear, this->gerais.EBX); // Salvando valor apontado por END2 na
	                                   // posição apontada por END1
	memoria[end_linear.toLong()] = gerais.EBX.value;
	this->offset.EDI.end_hex = this->offset.ESI.end_hex;
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (
	    end_linear, this->gerais.EAX); // Salvando valor apontado por END1 na
	                                   // posição apontada por END2
	memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::sub (Endereco<32> &END1, Endereco<32> &END2)
{
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "SUB");
	this->offset.EIP.increment (2);

	offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END1.end_hex);

	this->offset.EDI.end_hex = END1.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	acessarMemoria (end_linear, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
	acessarMemoria (end_linear, memoria[end_linear.toLong()]);
	gerais.EAX.sub (memoria[end_linear.toLong()]);

	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (end_linear, this->gerais.EAX);
	memoria[offset.EDI.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::mul (Endereco<32> &END1, Endereco<32> &END2)
{
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "MUL");
	this->offset.EIP.increment (2);

	offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END1.end_hex);

	this->offset.EDI.end_hex = END1.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	acessarMemoria (end_linear, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
	acessarMemoria (end_linear, memoria[end_linear.toLong()]);
	gerais.EAX.mul (memoria[end_linear.toLong()]);
	this->gerais.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
	inserirMemoria (this->offset.EDI, this->gerais.EAX);
	memoria[offset.EDI.toLong()] = gerais.EAX.value;
}
void ArquiteturaX86::neg(Endereco<32> &END){
    Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
    this->memoria[end_linear.toLong()] = obterValorAlocado (1);

    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_linear, "NEG");
    this->offset.EIP.increment (2);
    offset.mostrar_dados();

    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_linear, END.end_hex);
    this->offset.EDI.end_hex = END.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    acessarMemoria(end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.value="0";
    gerais.EAX.sub(memoria[end_linear.toLong()]);
    this->gerais.mostrar_dados();

    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    inserirMemoria (end_linear, this->gerais.EAX);
    memoria[offset.EDI.toLong()] = gerais.EAX.value;

}

void ArquiteturaX86::AND (Endereco<32> &DST,Endereco<32> &SRC){
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 
	string valor_dst = obterValorAlocado(1);
	string valor_src = obterValorAlocado(2);

	acessarMemoria(end_lin, "AND");
	this->offset.EIP.increment(2);
  
	this->offset.mostrar_dados();

	//CALCULANDO E ACESSANDO OS NOVOS ENDEREÇOS LINEARES
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,DST.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_EDI(DST.end_hex);
	this->offset.set_ESI(DST.end_hex);
  
	this->offset.mostrar_dados();

	//acessando o endereço destino em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_dst);
	this->gerais.set_EAX(valor_dst);
  
	this->gerais.mostrar_dados();

	//repetindo processo para segundo endereço
	end_lin= obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,SRC.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_ESI(SRC.end_hex);

	this->offset.mostrar_dados();

	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_src);
	this->gerais.set_EBX(valor_src);
  
	this->gerais.mostrar_dados(); 	

	//fazendo a operação AND
	long resultado = (this->gerais.EAX.toLong() & this->gerais.EBX.toLong());
	this->gerais.EAX = HexNumber(resultado,true);
	//armazenando
	this->gerais.mostrar_dados();

	//movendo eax para destino
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.EDI);
	inserirMemoria(end_lin,this->gerais.EAX);


};

void ArquiteturaX86::OR (Endereco<32> &DST,Endereco<32> &SRC){
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 
	string valor_dst = obterValorAlocado(1);
	string valor_src = obterValorAlocado(2);

	acessarMemoria(end_lin, "OR");
	this->offset.EIP.increment(2);
  
	this->offset.mostrar_dados();

	//CALCULANDO E ACESSANDO OS NOVOS ENDEREÇOS LINEARES
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,DST.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_EDI(DST.end_hex);
	this->offset.set_ESI(DST.end_hex);
  
	this->offset.mostrar_dados();

	//acessando o endereço destino em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_dst);
	this->gerais.set_EAX(valor_dst);
  
	this->gerais.mostrar_dados();

	//repetindo processo para segundo endereço
	end_lin= obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,SRC.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_ESI(SRC.end_hex);

	this->offset.mostrar_dados();

	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_src);
	this->gerais.set_EBX(valor_src);
  
	this->gerais.mostrar_dados(); 
	
	//fazendo a operação OR
	long resultado = (this->gerais.EAX.toLong() || this->gerais.EBX.toLong());
	this->gerais.EAX = HexNumber(resultado,true);
	//armazenando
	this->gerais.mostrar_dados();

	//movendo eax para destino
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.EDI);
	inserirMemoria(end_lin,this->gerais.EAX);

};


void ArquiteturaX86::XOR (Endereco<32> &DST,Endereco<32> &SRC){
Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 
	string valor_dst = obterValorAlocado(1);
	string valor_src = obterValorAlocado(2);

	acessarMemoria(end_lin, "XOR");
	this->offset.EIP.increment(2);
  
	this->offset.mostrar_dados();

	//CALCULANDO E ACESSANDO OS NOVOS ENDEREÇOS LINEARES
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,DST.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_EDI(DST.end_hex);
	this->offset.set_ESI(DST.end_hex);
  
	this->offset.mostrar_dados();

	//acessando o endereço destino em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_dst);
	this->gerais.set_EAX(valor_dst);
  
	this->gerais.mostrar_dados();

	//repetindo processo para segundo endereço
	end_lin= obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,SRC.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_ESI(SRC.end_hex);

	this->offset.mostrar_dados();

	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_src);
	this->gerais.set_EBX(valor_src);
  
	this->gerais.mostrar_dados(); 
	//fazendo a operação XOR
	long resultado = (this->gerais.EAX.toLong() ^ this->gerais.EBX.toLong());
	this->gerais.EAX = HexNumber(resultado,true);
	//armazenando
	this->gerais.mostrar_dados();

	//movendo eax para destino
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.EDI);
	inserirMemoria(end_lin,this->gerais.EAX);


};
