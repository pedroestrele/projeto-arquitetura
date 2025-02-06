#include <bits/stdc++.h>
#include "registradores.h"

using namespace std;
#pragma once 


class segment_register_table{
public:
  int CS;
  int SS;
  int DS;
  int Cod_Seg;
  int Stack_Seg;
  int Data_Seg;
  int CodLIM;
  int StackLIM;
  int DataLIM;
  int Cod_acc;
  int Stack_acc;
  int Data_acc;
  segment_register_table() : Cod_Seg(0), Stack_Seg(0), Data_Seg(0), CodLIM(0), StackLIM(0), DataLIM(0), Cod_acc(3), Stack_acc(3), Data_acc(3){}

  void mostrar_tabela(){
    int tamanho = 20;
    cout << "| " << left << setw(tamanho) << "Seletor" << "| " << left << setw(tamanho) << "End base" << "| " << left << setw(tamanho) << "End limite" << "| " 
    << left << setw(tamanho) << "Nível de Acesso" << " |" << endl;

    cout << string(4 * (tamanho + 2) + 1, '-') << endl;

    cout<< "| " << left << setw(tamanho) << CS << "| " << left << setw(tamanho) << Cod_Seg << "| " << left << setw(tamanho) << CodLIM << "| "  
    << left << setw(tamanho) << Cod_acc << "| " << endl;

    cout << "| " << left << setw(tamanho) << SS << "| "<< left << setw(tamanho) << Stack_Seg << "| " << left << setw(tamanho) << StackLIM << "| " 
    << left << setw(tamanho) << Stack_acc << "| " << endl;

    cout << "| " << left << setw(tamanho) << DS << "| " << left << setw(tamanho) << Data_Seg << "| " << left << setw(tamanho) << DataLIM << "| " 
    << left << setw(tamanho) << Data_acc << "| " << endl;
  }
  
  bool verifica_GPF(reg_offset offset);
  void entradadetabela();
  void entradaderegistradores(reg_seletores_segmento &seletores_segmento);
  void entrada_offset(reg_offset &offset);

  };

   void segment_register_table::entradadetabela(){
    cout<<"\nDigite os valores de inicio de cada segmento da tabela de segmentos:";
    cout<<"\nCod_Seg: ";
    cin>>this->Cod_Seg;
    cout<<"\nStack_Seg: ";
    cin>>this->Stack_Seg;
    if(this->Cod_Seg>=this->Stack_Seg){
      cout<<"\nGPF: O endereço de inicio do segmento de código deve ser menor que o endereço de inicio do segmento de pilha.";
      }
    this->CodLIM=this->Stack_Seg -1;
    cout<<"\nData_Seg: ";
    cin>>this->Data_Seg;
    if(this->Data_Seg<=this->Stack_Seg){
      cout<<"\nGPF: O endereço de inicio do segmento de pilha deve ser menor que o endereço de inicio do segmento de dados.";
      }
    this->StackLIM=this->Data_Seg -1;
    cout<<"\ndigite o valor limite do segmento de dados";
    cin>>this->DataLIM;
    }

bool segment_register_table::verifica_GPF(reg_offset offset){
  if(this->Cod_Seg+offset.EIP > this->CodLIM){
      cout<<"GPF: endereço linear do segmento maior que o limite do segmento de código"<<endl;
      return true;
    }
  if(this->Stack_Seg+offset.EBP > this->StackLIM){
      cout<<"GPF: endereço linear do segmento maior que o limite do segmento de pilha"<<endl;
      return true;
    }
    return false;
    }
  
  void segment_register_table::entradaderegistradores(reg_seletores_segmento &seletores_segmento){
    cout<<"Digite os seletores de cada segmento:";
    cout<<"\nCS: ";
    cin>>seletores_segmento.CS;
    cout<<"\nSS: ";
    cin>>seletores_segmento.SS;
    cout<<"\nDS: ";
    cin>>seletores_segmento.DS;
  }

  void  segment_register_table::entrada_offset(reg_offset &offset){
  cout<<"digite o endereço inicial do segmento EIP: ";
  cin>>offset.EIP;
  if(verifica_GPF(offset)){
    exit(2);
    }

  cout<<"digite o endereço inicial do segmento EBP: ";
  cin>>offset.EBP;
  if(verifica_GPF(offset)){
      exit(2);
      }

  offset.ESP=offset.EBP;

  }
  