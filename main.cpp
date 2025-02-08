#include <bits/stdc++.h>
#include "registradores.h"
#include "tabela.h"
#include "arquiteturaX86.h"

using namespace std;


int main(){
	RegGerais gerais;
	RegSeletorSegmentos seletores_segmento;
	RegOffsets offset;
	map <int, string> memoria;

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
		int END1,END2;
		cin>>END1>>END2;
		PC.add(END1,END2);//calculos,barramentos e etc na função
	}

	return 0;
}
