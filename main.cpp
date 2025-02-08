#include <bits/stdc++.h>
#include "registradores.h"
#include "tabela.h"
#include "arquiteturaX86.h"
#include "endereco.h"

using namespace std;


int main(){
	RegGerais gerais;
	RegSeletorSegmentos seletores_segmento;
	RegOffsets offset;
	map <long, string> memoria;

	seletores_segmento.obter_entrada();
	TabelaDescritorSegmento tabela = TabelaDescritorSegmento(seletores_segmento);

	tabela.entrada_de_tabela();
	tabela.mostrar_tabela();

	offset.obter_entrada();
	//tabela.verifica_GPF(offset);

	ArquiteturaX86 PC = ArquiteturaX86(gerais, seletores_segmento, offset, 0, memoria, tabela);

	string instrucao;
	cout<<"Digite a instrução que será simulada"<<endl;
	cin>>instrucao;

	if (instrucao=="add"){
		//coletar todos os dados necesários no main
		string end_hex1, end_hex2;
		cin>>end_hex1>>end_hex2;
		
		Endereco<32> END1(end_hex1), END2(end_hex2);

		PC.add(END1.toLong(),END2.toLong());//calculos,barramentos e etc na função
	}

	return 0;
}
