#include "endereco.h"
#include "registradores.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;
#pragma once

class DescritorSegmento
{
  public:
	Endereco<16> seletor;
	Endereco<32> end_base;
	Endereco<32> end_lim;
	int segm_acc;

	DescritorSegmento()
	    : seletor (Endereco<16>()), end_base (Endereco<32>()),
	      end_lim (Endereco<32>()), segm_acc (3)
	{
	}
	void imprimirLinhaTabela (int tamanho)
	{
		cout << "| " << left << setw (tamanho) << this->seletor.end_hex << "| "
		     << left << setw (tamanho) << this->end_base.end_hex << "| " << left
		     << setw (tamanho) << this->end_lim.end_hex << "| " << left
		     << setw (tamanho) << this->segm_acc << "| " << endl;
	}

	bool ehGPF (Endereco<32> &end_linear)
	{
		return end_linear.toLong() > this->end_lim.toLong();
	}
};

class TabelaDescritorSegmento
{
  public:
	DescritorSegmento code_segm;
	DescritorSegmento stack_segm;
	DescritorSegmento data_segm;

	TabelaDescritorSegmento()
	    : code_segm (DescritorSegmento()), stack_segm (DescritorSegmento()),
	      data_segm (DescritorSegmento())
	{
	}
	TabelaDescritorSegmento (RegSeletorSegmentos &seletores_segmento)
	{
		this->code_segm.seletor.end_hex = seletores_segmento.CS.end_hex;
		this->stack_segm.seletor.end_hex = seletores_segmento.SS.end_hex;
		this->data_segm.seletor.end_hex = seletores_segmento.DS.end_hex;
	}

	void mostrar_tabela()
	{
		int tamanho = 12;
		cout << "| " << left << setw (tamanho) << "Seletor"
		     << "| " << left << setw (tamanho) << "End base"
		     << "| " << left << setw (tamanho) << "End limite"
		     << "| " << left << setw (tamanho) << "Nível de Acesso"
		     << " |" << endl;

		cout << string (4 * (tamanho + 2) + 1, '-') << endl;

		code_segm.imprimirLinhaTabela (tamanho);
		stack_segm.imprimirLinhaTabela (tamanho);
		data_segm.imprimirLinhaTabela (tamanho);
	}

	bool verifica_GPF (RegOffsets offset);
	void entrada_de_tabela();
	void criar_descritores (RegSeletorSegmentos seletores_segmento);
};

void TabelaDescritorSegmento::entrada_de_tabela()
{
	cout << "\nDigite os endereços de inicio de cada segmento da tabela de "
	        "segmentos:";
	cout << "\nCod_Seg: ";
	cin >> this->code_segm.end_base.end_hex;

	cout << "Stack_Seg: ";
	cin >> this->stack_segm.end_base.end_hex;
	this->code_segm.end_lim.end_hex = this->stack_segm.end_base.end_hex;
	this->code_segm.end_lim.increment (-1);

	/*if(this->code_segm.end_base.toLong() >= this->stack_segm.end_base){
	    cout<< "GPF: O endereço de inicio do segmento de código deve ser menor
	que o endereço de inicio do segmento de pilha.\n";
	}*/

	cout << "Data_Seg: ";
	cin >> this->data_segm.end_base.end_hex;
	this->stack_segm.end_lim.end_hex = this->data_segm.end_base.end_hex;
	this->stack_segm.end_lim.increment (-1);

	/*if(this->data_segm.end_base <= this->stack_segm.end_base){
	    cout<<"GPF: O endereço de inicio do segmento de pilha deve ser menor que
	o endereço de inicio do segmento de dados.\n";
	}*/

	cout << "Digite o endereço limite do segmento de dados: ";
	cin >> this->data_segm.end_lim.end_hex;
}

bool TabelaDescritorSegmento::verifica_GPF (RegOffsets offset)
{
	if (code_segm.ehGPF (offset.EIP)) {
		cout << "GPF: endereço linear do segmento maior que o limite do "
		        "segmento de código"
		     << endl;
		return true;
	}

	if (stack_segm.ehGPF (offset.EBP)) {
		cout << "GPF: endereço linear do segmento maior que o limite do "
		        "segmento de pilha"
		     << endl;
		return true;
	}

	return false;
}
