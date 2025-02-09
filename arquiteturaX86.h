#include <bits/stdc++.h>
#include "tabela.h"
#include "endereco.h"
#include "registradores.h"

using namespace std;
#pragma once

class ArquiteturaX86{
public:
  RegGerais gerais;
  RegSeletorSegmentos& seletores_segmento;
  RegOffsets& offset;
  map <long, string> memoria; //evitar wreorder
  TabelaDescritorSegmento tabela;
  int flag;
  ArquiteturaX86(RegGerais gerais, RegSeletorSegmentos& seletores_segmento, RegOffsets& offset, map <long, string> memoria, TabelaDescritorSegmento tabela, int flag)
  : gerais(gerais), seletores_segmento(seletores_segmento), offset(offset), memoria(memoria), tabela(tabela), flag(flag) {}

  void add(Endereco<32>& END1, Endereco<32>& END2);
  void inc(Endereco<32>& END);
  void dec(Endereco<32>& END);

  void acessarMemoria(Endereco<32>& end, string retorno){
    cout<<end.end_hex<<endl;
    cout<<"-------->"<<endl;
    cout<<"BUS END"<<endl;
    //cout<<endl;
    cout<<retorno<<endl;
    cout<<"<--------"<<endl;
    cout<<"BUS DATA"<<endl;
  };

  void inserirMemoria(int valor){
    cout<<valor<<endl;
    cout<<"-------->"<<endl;
    cout<<"BUS DATA"<<endl;
  };

};

void ArquiteturaX86::add(Endereco<32>& END1, Endereco<32>& END2){
  this->offset.EIP.increment(2);

  cout<<"O que estaria presente no endereço 1? ";
  string valor1;
  cin>>valor1;

  cout<<"O que estaria presente no endereço 2? ";
  string valor2;
  cin>>valor2;
  this->memoria[END1.end_long]=valor1;
  this->memoria[END2.end_long]=valor2;

  acessarMemoria(this->offset.EIP, "ADD");
  this->offset.EIP.increment(4);
  acessarMemoria(this->offset.EIP, END1.end_hex);
  this->offset.mostrar_dados();

  this->offset.EDI.end_hex = END1.end_hex; 
  this->offset.EIP.increment(4);
  this->offset.mostrar_dados();

  acessarMemoria(this->offset.EIP, END2.end_hex);
  this->offset.ESI.end_hex = END2.end_hex;
  this->offset.EIP.increment(4);
  this->offset.mostrar_dados();

  acessarMemoria(this->offset.EDI, memoria[END1.end_long]);
  gerais.EAX=stoi(memoria[END1.end_long]);

  this->gerais.mostrar_dados();

  acessarMemoria(this->offset.ESI, memoria[END2.end_long]);
  gerais.EAX=stoi(memoria[END2.end_long]);
  this->gerais.mostrar_dados();

  gerais.EAX += stoi(memoria[END2.end_long]);
  this->gerais.mostrar_dados();

  inserirMemoria(this->gerais.EAX);
  memoria[offset.EDI.end_long]=to_string(gerais.EAX);

}

void ArquiteturaX86::inc(Endereco<32>& END) {
    this->offset.EIP.increment(2);

    cout<< "O que estaria presente no endereço? ";
    string valor;
    cin>>valor;
    cout<<endl;
    this->memoria[END.end_long]=valor;

    acessarMemoria(this->offset.EIP, "INC");
    this->offset.EIP.increment(4);
    acessarMemoria(this->offset.EIP, END.end_hex);
    //this->offset.mostrar_dados();

    this->offset.EDI.end_hex = END.end_hex;
    this->offset.EIP.increment(4);
    //this->offset.mostrar_dados();

    acessarMemoria(this->offset.EDI, memoria[END.end_long]);
    gerais.EAX = stoi(memoria[END.end_long]);
    //this->gerais.mostrar_dados();

    gerais.EAX+=1;
    //this->gerais.mostrar_dados();

    inserirMemoria(this->gerais.EAX);
    memoria[offset.EDI.end_long]=to_string(gerais.EAX);
    this->offset.mostrar_dados();
    this->gerais.mostrar_dados();
}

void ArquiteturaX86::dec(Endereco<32>& END) {
    this->offset.EIP.increment(2);

    cout << "O que estaria presente no endereço? ";
    string valor;
    cin >> valor;
    cout<<endl;
    this->memoria[END.end_long] = valor;

    acessarMemoria(this->offset.EIP, "DEC");
    this->offset.EIP.increment(4);
    acessarMemoria(this->offset.EIP, END.end_hex);
    //this->offset.mostrar_dados();

    this->offset.EDI.end_hex = END.end_hex;
    this->offset.EIP.increment(4);
    //this->offset.mostrar_dados();

    acessarMemoria(this->offset.EDI, memoria[END.end_long]);
    gerais.EAX = stoi(memoria[END.end_long]);
    //this->gerais.mostrar_dados();

    gerais.EAX -= 1;
    //this->gerais.mostrar_dados();

    inserirMemoria(this->gerais.EAX);
    memoria[offset.EDI.end_long] = to_string(gerais.EAX);
    this->offset.mostrar_dados();
    this->gerais.mostrar_dados();
}


