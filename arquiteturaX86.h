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
	{}

	void add (Endereco<32> &END1, Endereco<32> &END2);
	void inc (Endereco<32> &END);
	void dec (Endereco<32> &END);
	void mov (Endereco<32> &END1, Endereco<32> &END2);
	void xchg (Endereco<32> &END1, Endereco<32> &END2);
	void push (Endereco<32> &END1);
	void pop (Endereco<32> &END1);
	void cmp (Endereco<32> &END1, Endereco<32> &END2);
	void jmp (Endereco<32> &END);
	void jmp_cond(Endereco<32> &END);
	void jxx (Endereco<32> &END, string tipo);
	void mul (Endereco<32> &END1, Endereco<32> &END2);
	void sub (Endereco<32> &END1, Endereco<32> &END2);
  	void neg (Endereco<32> &END);
	void AND (Endereco<32> &DST, Endereco<32> &SRC);
	void OR (Endereco<32> &DST, Endereco<32> &SRC);
	void XOR (Endereco<32> &DST, Endereco<32> &SRC);
	void NOT (Endereco<32> &DST);
	void call (Endereco<32> &END);
	void ret (Endereco<32> &END);
	void iret ();
	void loop (Endereco<32> &END);
  
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
	
	string obterValorAlocado (string n)
	{
		string valor;
		cout << "O que estaria presente no endereço " << n << "? ";
		cin >> valor;
		return valor;
	}

	Endereco<32> obterEnderecoLinear (DescritorSegmento &descritor, Endereco<32> &end)
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
    // Obtem endereço linear de END1 e solicita um valor para estar presente nesse endereço
    Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
    this->memoria[end_linear.toLong()] = obterValorAlocado (1);

    // Obtem endereço linear de END2 e solicita um valor para estar presente nesse endereço
    end_linear = obterEnderecoLinear (tabela.data_segm, END2);
    this->memoria[end_linear.toLong()] = obterValorAlocado (2);

    //Calcula endereço linear de código, acessa a memória e retorna a instrução add, atualiza IP
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, "ADD");

    this->offset.EIP.increment (2);

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 1, atualiza IP, atualiza ESI com END1, Atualiza EDI com END1
    offset.mostrar_dados();
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END1.end_hex);
    this->offset.ESI.end_hex = END1.end_hex;
    this->offset.EDI.end_hex = END1.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END1, guarda-o em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.value = memoria[end_linear.toLong()];
    this->gerais.mostrar_dados();

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 2, atualiza IP, atualiza ESI com END2
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END2.end_hex);
    this->offset.ESI.end_hex = END2.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END2, soma-o com o valor de EAX, guarda o resultado em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.add (memoria[end_linear.toLong()]);
    this->gerais.mostrar_dados();

    //Insere o valor de EAX no endereço de destino
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    inserirMemoria (end_linear, gerais.EAX);
    memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::mov (Endereco<32> &END1, Endereco<32> &END2)
{
	Endereco<32> end_linear;
	end_linear = obterEnderecoLinear (tabela.data_segm, END1);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.data_segm, END2);
	this->memoria[end_linear.toLong()] = obterValorAlocado (2);

	// Obtém instrução MOV em código
	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, "MOV");
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	// Obtém END1 em código
	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, END1.end_hex);
	this->offset.EDI = (END1.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	// Obtém END1 em código
	end_linear = obterEnderecoLinear (tabela.code_segm, offset.EIP);
	acessarMemoria (end_linear, END2.end_hex); // Obtém END2
	this->offset.ESI = (END2.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, offset.ESI);
	acessarMemoria (
	    end_linear,memoria[end_linear.toLong()]);
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
	// obtem endereço linear do endereco e pede um valor que esta alocado ali
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "INC"); // obtem DEC
	this->offset.EIP.increment (4); // avanca EIP

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END.end_hex);
	// this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END.end_hex; // atualiza EDI
	this->offset.EIP.increment (4); // avanca EIP
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, END);
	acessarMemoria (this->offset.EDI, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	// this->gerais.mostrar_dados();

	gerais.EAX.inc(); // incrementa eax
	// this->gerais.mostrar_dados();

	inserirMemoria (end_linear, this->gerais.EAX); // armazena de volta
	memoria[offset.EDI.toLong()] = gerais.EAX.value;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::dec (Endereco<32> &END)
{
	// obtem endereço linear do endereco e pede um valor que esta alocado ali
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, "DEC"); // obtem DEC
	this->offset.EIP.increment (4); // avanca EIP
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
	acessarMemoria (end_linear, END.end_hex);
	// this->offset.mostrar_dados();

	this->offset.EDI.end_hex = END.end_hex; // atualiza EDI
	this->offset.EIP.increment (4); // avanca EIP
	// this->offset.mostrar_dados();

	end_linear = obterEnderecoLinear (tabela.data_segm, END);
	acessarMemoria (this->offset.EDI, memoria[end_linear.toLong()]);
	gerais.EAX.value = memoria[end_linear.toLong()];
	// this->gerais.mostrar_dados();

	gerais.EAX.dec(); // decrementa EAX
	// this->gerais.mostrar_dados();

	inserirMemoria (end_linear, this->gerais.EAX); // armazena de volta
	memoria[end_linear.toLong()] = gerais.EAX.value;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::cmp (Endereco<32> &END1, Endereco<32> &END2)
{
	string valor1 = obterValorAlocado(1);
	string valor2 = obterValorAlocado(2);

	this->memoria[END1.toLong()] = valor1;
	this->memoria[END2.toLong()] = valor2;
	
	//acessando a instrução
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, "CMP");
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	//acessando o proximo endereço em code
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, END1.end_hex);
	this->offset.set_EDI(END1.end_hex);
	this->offset.set_ESI(END1.end_hex);
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	//acessando o primeiro endereço em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria (end_lin, memoria[END1.toLong()]);
	HexNumber valorReg1 (memoria[END1.toLong()]);

	//acessando o segundo endereço em code
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, END2.end_hex);
	this->offset.ESI.end_hex = END2.end_hex;
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	//acessando o segundo endereço em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria (end_lin, memoria[END2.toLong()]);
	HexNumber valorReg2 (memoria[END2.toLong()]);


	gerais.EAX.value = valorReg1.value;
	gerais.EBX.value = valorReg2.value;

	this->gerais.mostrar_dados();
	
	HexNumber resultado (valorReg1.value);
	resultado.sub (valorReg2.value);

	if (valorReg1.equals (valorReg2)) {
		this->flag.ZF.value = "1"; // ZF = 1 se os valores forem iguais
	} else {
		this->flag.ZF.value = "0";
	}

	if (valorReg1.toLong()<valorReg2.toLong()) {
		this->flag.SF.value = "1"; // SF = 1 se o resultado for negativo
	} else {
		this->flag.SF.value = "0";
	}

	// Pega o bit de sinal para fazer a comparação
	bool sinalOperando1 = (valorReg1.toLong() >> 31) & 1;
	bool sinalOperando2 = (valorReg2.toLong() >> 31) & 1;
	bool sinalResultado = (resultado.toLong() >> 31) & 1;

	// OF = (sinalOperando1 == sinalOperando2) && (sinalResultado !=
	// sinalOperando1)
	if ((sinalOperando1 == sinalOperando2) &&
	    (sinalResultado != sinalOperando1)) {
		this->flag.OF.value = "1"; // OF = 1 se ocorreu overflow
	} else {
		this->flag.OF.value = "0";
	}

	cout << "Resultado da comparação (valorReg1 - valorReg2): " << resultado.value
	     << endl;
	this->flag.mostrar_dados();

}

void ArquiteturaX86::jmp (Endereco<32> &END)
{
	//buscando a instrução
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, "JMP");
	this->offset.EIP.increment (4);
	this->offset.mostrar_dados();

	//acessando endereço
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, END.end_hex);
	// Atualiza EIP para endereço de destino
	this->offset.EIP = END.end_hex;

	
	//acessarMemoria (this->offset.EIP, memoria[END.toLong()]); #acho que não precisa

	cout << "\nNovo valor do EIP: " << this->offset.EIP.end_hex;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();
}

void ArquiteturaX86::jmp_cond(Endereco<32> &END){ //executa um jump, mas assume que jxx já foi resgatado do segmento de código
	//acessando endereço
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria (end_lin, END.end_hex);
	// Atualiza EIP para endereço de destino
	this->offset.EIP = END.end_hex;

	
	//acessarMemoria (this->offset.EIP, memoria[END.toLong()]); #acho que não precisa

	cout << "\nNovo valor do EIP: " << this->offset.EIP.end_hex;
	this->offset.mostrar_dados();
	this->gerais.mostrar_dados();

}

void ArquiteturaX86::jxx (Endereco<32> &END,string tipo){
	//buscando a instrução
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 

	for(auto &c : tipo){
		c = toupper(c);
	}

	acessarMemoria(end_lin, "J"+tipo);
	this->offset.EIP.increment(4);

	this->offset.mostrar_dados();

	// verificando qual tipo de jump será
	bool willjmp = false;
	enum jumps {G,GE,E,NE,L,LE};
	map<string,jumps> tipo_jump= {
		{"G",G},{"GE",GE},{"E",E},{"NE",NE},{"L",L},{"LE",LE}
	};
	switch (tipo_jump[tipo])
	{
		case G: { // >
			if(this->flag.SF.value == "0" && this->flag.ZF.value == "0"){
				willjmp = true;
			}
		}break;
		case GE: { // >=
			if(this->flag.SF.value == "0"){// independente de ZF - se for 0 ou 1 o resultado é o mesmo
				willjmp = true;
			}
		}break;
		case E: { // ==
			if(this->flag.ZF.value == "1"){
				willjmp = true;
			}
		}break;
		case NE: { // !=
			if(this->flag.ZF.value == "0"){
				willjmp = true;
			}
		}break;
		case L: { // <
			if(this->flag.SF.value == "1"){
				willjmp = true;
			}
		}break;
		case LE: {// <=
			if(this->flag.SF.value == "1" || this->flag.ZF.value == "1"){
				willjmp = true;
			}
		}break;
		default:{
		}break;
	}

	if(willjmp){
		this->jmp_cond(END);
	}else{
		this->offset.EIP.increment(4); // pula endereço fornecido ao jump se a condição for falsa
		this->offset.mostrar_dados();
	}


};

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
    // Obtem endereço linear de END1 e solicita um valor para estar presente nesse endereço
    Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
    this->memoria[end_linear.toLong()] = obterValorAlocado (1);

    // Obtem endereço linear de END2 e solicita um valor para estar presente nesse endereço
    end_linear = obterEnderecoLinear (tabela.data_segm, END2);
    this->memoria[end_linear.toLong()] = obterValorAlocado (2);

    //Calcula endereço linear de código, acessa a memória e retorna a instrução sub, atualiza IP
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, "SUB");

    this->offset.EIP.increment (2);

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 1, atualiza IP, atualiza ESI com END1, Atualiza EDI com END1
    offset.mostrar_dados();
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END1.end_hex);
    this->offset.ESI.end_hex = END1.end_hex;
    this->offset.EDI.end_hex = END1.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END1, guarda-o em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.value = memoria[end_linear.toLong()];
    this->gerais.mostrar_dados();

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 2, atualiza IP, atualiza ESI com END2
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END2.end_hex);
    this->offset.ESI.end_hex = END2.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END2, subtrai-o com o valor de EAX, guarda o resultado em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.sub (memoria[end_linear.toLong()]);
    this->gerais.mostrar_dados();

    //Insere o valor de EAX no endereço de destino
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    inserirMemoria (end_linear, gerais.EAX);
    memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::mul (Endereco<32> &END1, Endereco<32> &END2)
{
    // Obtem endereço linear de END1 e solicita um valor para estar presente nesse endereço
    Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END1);
    this->memoria[end_linear.toLong()] = obterValorAlocado (1);

    // Obtem endereço linear de END2 e solicita um valor para estar presente nesse endereço
    end_linear = obterEnderecoLinear (tabela.data_segm, END2);
    this->memoria[end_linear.toLong()] = obterValorAlocado (2);

    //Calcula endereço linear de código, acessa a memória e retorna a instrução mul, atualiza IP
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, "MUL");

    this->offset.EIP.increment (2);

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 1, atualiza IP, atualiza ESI com END1, Atualiza EDI com END1
    offset.mostrar_dados();
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END1.end_hex);
    this->offset.ESI.end_hex = END1.end_hex;
    this->offset.EDI.end_hex = END1.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END1, guarda-o em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.value = memoria[end_linear.toLong()];
    this->gerais.mostrar_dados();

    //Calcula endereço linear de código, acessa memória e retorna o Endereço 2, atualiza IP, atualiza ESI com END2
    end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    acessarMemoria (end_linear, END2.end_hex);
    this->offset.ESI.end_hex = END2.end_hex;
    this->offset.EIP.increment (4);
    this->offset.mostrar_dados();

    //acessa o valor presente em END2, multiplica-o com o valor de EAX, guarda o resultado em EAX
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.ESI);
    acessarMemoria (end_linear, memoria[end_linear.toLong()]);
    gerais.EAX.mul (memoria[end_linear.toLong()]);
    this->gerais.mostrar_dados();

    //Insere o valor de EAX no endereço de destino
    end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    inserirMemoria (end_linear, gerais.EAX);
    memoria[end_linear.toLong()] = gerais.EAX.value;
}

void ArquiteturaX86::neg(Endereco<32> &END){
	// Obtem endereço linear e solicita um valor para estar presente nesse endereço
	Endereco<32> end_linear = obterEnderecoLinear (tabela.data_segm, END);
	this->memoria[end_linear.toLong()] = obterValorAlocado (1);

	//Calcula endereço linear de código, acessa a memória e retorna a instrução NEG, atualiza IP
	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    	acessarMemoria(end_linear, "NEG");
    	this->offset.EIP.increment (2);
    	offset.mostrar_dados();

	//Calcula endereço linear de código, acessa memória e retorna o Endereço, atualiza IP, atualiza EDI com o endereço
    	end_linear = obterEnderecoLinear (tabela.code_segm, this->offset.EIP);
    	acessarMemoria(end_linear, END.end_hex);
    	this->offset.EDI.end_hex = END.end_hex;
    	this->offset.EIP.increment (4);
    	this->offset.mostrar_dados();

	//acessa o valor presente no endereço, subtrai-o de 0, guarda o resultado em EAX
   	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    	acessarMemoria(end_linear, memoria[end_linear.toLong()]);
   	gerais.EAX.value="0";
    	gerais.EAX.sub(memoria[end_linear.toLong()]);
    	this->gerais.mostrar_dados();

	//Insere o valor de EAX no endereço de destino
   	end_linear = obterEnderecoLinear (tabela.data_segm, this->offset.EDI);
    	inserirMemoria (end_linear, this->gerais.EAX);
    	memoria[offset.EDI.toLong()] = gerais.EAX.value;

}

void ArquiteturaX86::AND (Endereco<32> &DST,Endereco<32> &SRC){
	//end_lin = endereço base de codigo + EIP
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP); 
	string valor_dst = obterValorAlocado(1);
	string valor_src = obterValorAlocado(2);

	acessarMemoria(end_lin, "AND");
	this->offset.EIP.increment(4);
  
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
	this->offset.EIP.increment(4);
  
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
	long resultado = (this->gerais.EAX.toLong() | this->gerais.EBX.toLong());
	this->gerais.EAX = HexNumber(resultado,true);
	//armazenando
	this->gerais.mostrar_dados();

	//movendo eax para destino
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.EDI);
	inserirMemoria(end_lin,this->gerais.EAX);

};


void ArquiteturaX86::XOR (Endereco<32> &DST,Endereco<32> &SRC){
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 
	string valor_dst = obterValorAlocado("destino");
	string valor_src = obterValorAlocado("fonte");

	acessarMemoria(end_lin, "XOR");
	this->offset.EIP.increment(4);
  
	this->offset.mostrar_dados();

	//CALCULANDO E ACESSANDO OS NOVOS ENDEREÇOS LINEARES - DESTINO
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

	//REPETINDO PROCESSO PARA SEGUNDO ENDEREÇO - FONTE
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

void ArquiteturaX86::NOT (Endereco<32> &DST){
	//buscando a instrução
	Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);//end_lin = endereço base de codigo + EIP 
	string valor_dst = obterValorAlocado("destino");

	acessarMemoria(end_lin, "NOT");
	this->offset.EIP.increment(4);

	this->offset.mostrar_dados();
	
	//CALCULANDO E ACESSANDO O PRÓXIMO ENDEREÇO LINEAR -DESTINO
	end_lin = obterEnderecoLinear(this->tabela.code_segm,this->offset.EIP);
	acessarMemoria(end_lin,DST.end_hex);
	this->offset.EIP.increment(4);
	this->offset.set_EDI(DST.end_hex);
	this->offset.set_ESI(DST.end_hex);
	this->offset.mostrar_dados();

	//acessando o endereço destino em dados
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.ESI);
	acessarMemoria(end_lin,valor_dst);
	this->gerais.set_EBX(valor_dst);
  
	this->gerais.mostrar_dados();

	long complemento_de_1 = ~ this->gerais.EAX.toLong();
	this->gerais.EAX = HexNumber(complemento_de_1,true);

	this->gerais.mostrar_dados();

	//movendo eax para destino
	end_lin = obterEnderecoLinear(this->tabela.data_segm,this->offset.EDI);
	inserirMemoria(end_lin,this->gerais.EAX);
};

void ArquiteturaX86::call (Endereco<32> &END){
    // Obter o endereço linear da instrução CALL
    Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_lin, "CALL");
    this->offset.EIP.increment(4); 

    // Exibir os dados após acessar a instrução CALL
    this->offset.mostrar_dados();

    // Reservando espaço na pilha para o endereço de retorno (EIP)
	HexNumber number = HexNumber(this->offset.EIP.end_hex);
    offset.ESP.decrement(4);
		end_lin = obterEnderecoLinear(this->tabela.stack_segm, offset.ESP);
		HexNumber novo_eip(offset.EIP.end_hex);
    inserirMemoria(end_lin, novo_eip); 

    // Exibir os dados após a atualização da pilha
    this->offset.mostrar_dados();

    // Atualizando o EIP com o endereço de destino
    this->offset.EIP = END.end_hex;

    // Exibir o estado final após a atualização do EIP
    this->offset.mostrar_dados();
};

void ArquiteturaX86::ret (Endereco<32> &END){
    Endereco<32> end_lin = obterEnderecoLinear(this->tabela.stack_segm, END);
		memoria[end_lin.toLong()] = obterValorAlocado(1);

		// Obter o endereço linear da instrução RET
    end_lin = obterEnderecoLinear(this->tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_lin, "RET"); 
    this->offset.EIP.increment(4);  

    // Exibir os dados após acessar a instrução RET
    this->offset.mostrar_dados();

    // Recuperando o endereço de retorno da pilha
		end_lin = obterEnderecoLinear(this->tabela.stack_segm, this->offset.ESP);
    acessarMemoria(offset.ESP, memoria[offset.ESP.toLong()]);
    offset.EIP = memoria[offset.ESP.toLong()]; 

    // Exibir os dados após a atualização do EIP
    this->offset.mostrar_dados();

    // Desempilha o endereço de retorno, incrementando o ponteiro ESP
    offset.ESP.increment(4);

    // Exibir o estado final após a execução do RET
    this->offset.mostrar_dados();
};

void ArquiteturaX86::iret (){
		Endereco<32> end_lin =  obterEnderecoLinear(this->tabela.stack_segm, this->offset.ESP);
		cout << "Digite o valor empilhado do flag: ";
		cin >> memoria[end_lin.toLong()+8];
		cout << "Digite o valor empilhado de CS: ";
		cin >> memoria[end_lin.toLong()+4];
		cout << "Digite o valor empilhado de EIP: ";
		cin >> memoria[end_lin.toLong()];

    // Obter o endereço linear da instrução IRET
     end_lin = obterEnderecoLinear(this->tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_lin, "IRET");
    this->offset.EIP.increment(4);  

    // Exibir os dados após acessar a instrução IRET
    this->offset.mostrar_dados();

    // Recuperando o endereço de retorno da pilha
		end_lin = obterEnderecoLinear(this->tabela.stack_segm, this->offset.ESP);
    acessarMemoria(end_lin, memoria[end_lin.toLong()]); 
    offset.EIP = memoria[end_lin.toLong()]; 

    // Exibir os dados após a atualização do EIP
    this->offset.mostrar_dados();

    // Desempilha o endereço de retorno, incrementando o ponteiro ESP
    offset.ESP.increment(4);

    // Recupera o CS da pilha e restaura o CS
		end_lin = obterEnderecoLinear(this->tabela.stack_segm, offset.ESP);
    acessarMemoria(end_lin, memoria[end_lin.toLong()]); 
    seletores_segmento.CS = memoria[end_lin.toLong()];  
    offset.ESP.increment(4);

    // Exibir os dados após restaurar o CS
    this->offset.mostrar_dados();

    // Recupera as flags da pilha e restaura as flags
		end_lin = obterEnderecoLinear(this->tabela.stack_segm, offset.ESP);
    acessarMemoria(end_lin, memoria[end_lin.toLong()]); 
    flag.set(memoria[end_lin.toLong()]);  
    offset.ESP.increment(4);

    // Exibir o estado final após a execução do IRET
    this->offset.mostrar_dados();
};

void ArquiteturaX86::loop (Endereco<32> &END){
    // Obter o endereço linear da instrução LOOP
    Endereco<32> end_lin = obterEnderecoLinear(this->tabela.code_segm, this->offset.EIP);
    acessarMemoria(end_lin, "LOOP");
    this->offset.EIP.increment(4); 

    // Exibir os dados após acessar a instrução LOOP
    this->offset.mostrar_dados();

    // Decrementa o registrador ECX
    gerais.ECX.dec();

    // Exibir o conteúdo do registrador ECX após a decremetação
    this->gerais.mostrar_dados();

    // Verifica se ECX é diferente de zero
    if (gerais.ECX.toLong() != 0) {
        offset.EIP = END.end_hex;
    }

    // Exibir o estado final após a execução do LOOP
    this->offset.mostrar_dados();
};
