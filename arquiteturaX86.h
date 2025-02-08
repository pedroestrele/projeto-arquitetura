#include <bits/stdc++.h>
#include "tabela.h"
#include "registradores.h"

using namespace std;
#pragma once

class ArquiteturaX86{
  public:
    RegGerais gerais;
    RegSeletorSegmentos seletores_segmento;
    RegOffsets offset;
    TabelaDescritorSegmento tabela;
    int flag;
    map <int, string> memoria;

	ArquiteturaX86(RegGerais gerais, RegSeletorSegmentos seletores_segmento, RegOffsets offset, int flag, map <int, string> memoria, TabelaDescritorSegmento tabela){
        this->gerais = gerais;
        this->seletores_segmento = seletores_segmento;
        this->offset = offset;
        this->flag = flag;
        this->memoria = memoria;
        this->tabela=tabela;
	}
    void mostrar_dados();
    void add(int END1,int END2);
    void inc();

};
void ArquiteturaX86::mostrar_dados(){
    cout<<"Registradores Gerais: "<<endl;
    cout<<"EAX: "<<gerais.EAX<<endl;
    cout<<"EBX: "<<gerais.EBX<<endl;
    cout<<"ECX: "<<gerais.ECX<<endl;
    cout<<"EDX: "<<gerais.EDX<<endl;
    cout<<endl<<"Offset: "<<endl;
    cout<<"EIP: "<<offset.EIP<<endl;
    cout<<"EBP: "<<offset.EBP<<endl;
    cout<<"ESP: "<<offset.ESP<<endl;
    cout<<"ESI: "<<offset.ESI<<endl;
    cout<<"EDI: "<<offset.EDI<<endl;
  }

void ArquiteturaX86::add(int END1,int END2){
  this->offset.EIP+=4;


  cout<<" o que estaria presente no endereço 1?";
  string valor1;
  cin>>valor1;

  cout<<" o que estaria presente no endereço 2?";
  string valor2;
  cin>>valor2;
  this->memoria[END1]=valor1;
  this->memoria[END2]=valor2;


}
