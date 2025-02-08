#include <bits/stdc++.h>
#include "registradores.h"

using namespace std;
#pragma once 

class DescritorSegmento {
	public:
		int seletor;
		int end_base;
		int end_lim;
		int segm_acc;
	DescritorSegmento() : seletor(0), end_base(0), end_lim(0), segm_acc(3){}

	void imprimirLinhaTabela(int tamanho){
		cout<< "| " << left << setw(tamanho) << this->seletor << "| " << left << setw(tamanho) << this->end_base << "| " << left << setw(tamanho) << this->end_lim << "| "  
		<< left << setw(tamanho) << this->segm_acc << "| " << endl;
	}

	bool ehGPF(int offset){
		return this->end_base + offset > this->end_lim;
	}

};

class TabelaDescritorSegmento {
	public:
		DescritorSegmento code_segm;
		DescritorSegmento stack_segm;
		DescritorSegmento data_segm;
		
	TabelaDescritorSegmento() : code_segm(DescritorSegmento()), stack_segm(DescritorSegmento()), data_segm(DescritorSegmento()){}

	TabelaDescritorSegmento(RegSeletorSegmentos seletores_segmento) {
		this->code_segm.seletor = seletores_segmento.CS;
    this->stack_segm.seletor = seletores_segmento.SS;
    this->data_segm.seletor = seletores_segmento.DS;
	}

	void mostrar_tabela(){
		int tamanho = 20;
		cout << "| " << left << setw(tamanho) << "Seletor" << "| " << left << setw(tamanho) << "End base" << "| " << left << setw(tamanho) << "End limite" << "| " 
		<< left << setw(tamanho) << "Nível de Acesso" << " |" << endl;

		cout << string(4 * (tamanho + 2) + 1, '-') << endl;

		code_segm.imprimirLinhaTabela(tamanho);
		stack_segm.imprimirLinhaTabela(tamanho);
		data_segm.imprimirLinhaTabela(tamanho);
	}

	bool verifica_GPF(RegOffsets offset);
	void entrada_de_tabela();
	void criar_descritores(RegSeletorSegmentos seletores_segmento);
	void entrada_offset(RegOffsets &offset);

};

void TabelaDescritorSegmento::entrada_de_tabela(){
	cout<<"\nDigite os endereços de inicio de cada segmento da tabela de segmentos:";
	cout<<"\nCod_Seg: ";
	cin>>this->code_segm.end_base;
	cout<<"Stack_Seg: ";
	cin>>this->stack_segm.end_base;

	if(this->code_segm.end_base >= this->stack_segm.end_base){
		cout<< "GPF: O endereço de inicio do segmento de código deve ser menor que o endereço de inicio do segmento de pilha.\n";
	}

	this->code_segm.end_lim = this->stack_segm.end_base -1;
	cout<<"Data_Seg: ";
	cin>>this->data_segm.end_base;

	if(this->data_segm.end_base <= this->stack_segm.end_base){
		cout<<"GPF: O endereço de inicio do segmento de pilha deve ser menor que o endereço de inicio do segmento de dados.\n";
	}

	this->stack_segm.end_lim = this->data_segm.end_base -1;
	cout<<"Digite o endereço limite do segmento de dados: ";
	cin>>this->data_segm.end_lim;
}

bool TabelaDescritorSegmento:: verifica_GPF(RegOffsets offset){
  	if(code_segm.ehGPF(offset.EIP)){
      cout<<"GPF: endereço linear do segmento maior que o limite do segmento de código"<<endl;
      return true;
		}

  	if(stack_segm.ehGPF(offset.EBP)){
      cout<<"GPF: endereço linear do segmento maior que o limite do segmento de pilha"<<endl;
      return true;
    }

    return false;
}