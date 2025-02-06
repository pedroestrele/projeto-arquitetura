#include <bits/stdc++.h>
#include "registradores.h"
#include "tabela.h"
#include "arquiteturaX86.h"

using namespace std;


int main(){
  reg_gerais gerais;
  reg_seletores_segmento seletores_segmento;
  reg_offset offset;
  map <int, string> memoria;
  segment_register_table tabela;
  tabela.entradaderegistradores(seletores_segmento);
  //seletores_segmento.mostrar_dados();

  tabela.CS = seletores_segmento.CS;
  tabela.SS = seletores_segmento.SS;
  tabela.DS = seletores_segmento.DS;
  tabela.entradadetabela();
  tabela.mostrar_tabela();
  tabela.entrada_offset(offset);
  ArquiteturaX86 PC = ArquiteturaX86(gerais, seletores_segmento, offset, 0, memoria, tabela);
  
  string instrucao;
  cout<<"digite a instrução que será simulada"<<endl;
  
  cin>>instrucao;
 
  if (instrucao=="add"){
    //coletar todos os dados necesários no main
    int END1,END2;
    cin>>END1>>END2;
    PC.add(END1,END2);//calculos,barramentos e etc na função
    }
}
