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
 	RegFlag flag;
  	map <long, string> memoria;

  	seletores_segmento.obter_entrada();

  	TabelaDescritorSegmento tabela = TabelaDescritorSegmento(seletores_segmento);
  	tabela.entrada_de_tabela();
  	tabela.mostrar_tabela();


  	offset.obter_entrada();
  	//tabela.verifica_GPF(offset);

  	ArquiteturaX86 PC = ArquiteturaX86(gerais, seletores_segmento, offset, memoria, tabela, flag);

  	string instrucao;
  	cout<<"Digite a instrução que será simulada: ";
  	cin>>instrucao;

  	if (instrucao=="add"){
    		//coletar todos os dados necesários no main
    		string end_hex1, end_hex2;
    		cin>>end_hex1>>end_hex2;

    		Endereco<32> END1(end_hex1), END2(end_hex2);

    		PC.add(END1,END2);//calculos,barramentos e etc na função
  	} 
	else if (instrucao=="push"){
   	 	//coletar todos os dados necesários no main
    		string end_hex1;
    		cin>>end_hex1;

    		Endereco<32> END1(end_hex1);

    		PC.push(END1);//calculos,barramentos e etc na função
 	}

  	if (instrucao=="inc" or instrucao=="INC"){
    		string end_hex;
        	cout<<"Digite o endereço: ";
        	cin>>end_hex;
		
        	Endereco<32> END(end_hex);

        	PC.inc(END);
      	}

  	if (instrucao=="dec" or instrucao=="DEC"){
        	string end_hex;
      		cout<<"Digite o endereço: ";
        	cin>>end_hex;
		
    		Endereco<32> END(end_hex);
		
        	PC.dec(END);
      	}

  	if (instrucao=="cmp" or instrucao=="CMP"){
        	string end_hex1, end_hex2;
        	cout<<"Digite o endereço 1: ";
        	cin>>end_hex1;
        	cout<<"Digite o endereço 2: ";
        	cin>>end_hex2;
		
        	Endereco<32> END1(end_hex1), END2(end_hex2);
		
        	PC.cmp(END1,END2);
 	}
	return 0;
}
