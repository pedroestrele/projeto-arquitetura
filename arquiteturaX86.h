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
    cout<<endl;
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
    cout<<endl;
  }

void ArquiteturaX86::add(int END1,int END2){
   cout<<"O que estaria presente no endereço 1?";
  string valor1;
  cin>>valor1;

  cout<<"O que estaria presente no endereço 2?";
  string valor2;
  cin>>valor2;
  this->memoria[END1]=valor1;
  this->memoria[END2]=valor2;

  
  cout<<offset.EIP<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS END"<<endl;
  cout<<endl;
  cout<<"ADD"<<endl;
  cout<<"<--------"<<endl;
  cout<<"BUS DATA"<<endl;
  
  this->offset.EIP+=4;
  
  mostrar_dados(); 
  
  cout<<offset.EIP<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS END"<<endl;
  cout<<endl;
  cout<<END1<<endl;
  cout<<"<--------"<<endl;
  cout<<"BUS DATA"<<endl;
  
  this->offset.EDI=END1; 
  this->offset.EIP+=4;

  mostrar_dados();

  cout<<offset.EIP<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS END"<<endl;
  cout<<endl;
  cout<<END2<<endl;
  cout<<"<--------"<<endl;
  cout<<"BUS DATA"<<endl;
  this->offset.ESI=END2;
  this->offset.EIP+=4;
  
  mostrar_dados();

  cout<<offset.EDI<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS END"<<endl;
  cout<<endl;
  cout<<memoria[END1]<<endl;
  cout<<"<--------"<<endl;
  cout<<"BUS DATA"<<endl;
  gerais.EAX=stoi(memoria[END1]);

  mostrar_dados();

  cout<<offset.ESI<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS END"<<endl;
  cout<<endl;
  cout<<memoria[END2]<<endl;
  cout<<"<--------"<<endl;
  cout<<"BUS DATA"<<endl;
  gerais.EAX+=(stoi(memoria[END2]));

  mostrar_dados();
  cout<<gerais.EAX<<endl;
  cout<<"-------->"<<endl;
  cout<<"BUS DATA"<<endl;
  memoria[offset.EDI]=to_string(gerais.EAX);
  




}
