#include <bits/stdc++.h>
#include "tabela.h"
#include "registradores.h"

using namespace std;
#pragma once 

class ArquiteturaX86{
public:
  reg_gerais gerais;
  reg_seletores_segmento seletores_segmento;
  reg_offset offset;
  segment_register_table tabela;
  int flag;
  map <int, string> memoria;

    ArquiteturaX86(reg_gerais gerais, reg_seletores_segmento seletores_segmento, reg_offset offset, int flag, map <int, string> memoria, segment_register_table tabela){
        this->gerais = gerais;
        this->seletores_segmento = seletores_segmento;
        this->offset = offset;
        this->flag = flag;
        this->memoria = memoria;
        this->tabela=tabela;
  }
  void add(int END1,int END2);  
  void inc();
};

void ArquiteturaX86::add(int END1,int END2){
  this->offset.EIP+=2;
  
  
  cout<<" o que estaria presente no endereço 1?";
  string valor1;
  cin>>valor1;
  
  cout<<" o que estaria presente no endereço 2?";
  string valor2;
  cin>>valor2;
  this->memoria[END1]=valor1;
  this->memoria[END2]=valor2;
  
  
  }

void ArquiteturaX86::inc(){
    this->offset;

}


