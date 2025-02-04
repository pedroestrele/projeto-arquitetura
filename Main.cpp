#include <bits/stdc++.h>
using namespace std;


class reg_gerais{
public:
  int EAX;
  int EBX;
  int ECX;
  int EDX;
  reg_gerais() : EAX(0), EBX(0), ECX(0), EDX(0) {}
  reg_gerais(int EAX, int EBX, int ECX, int EDX){
    this->EAX = EAX;
    this->EBX = EBX;
    this->ECX = ECX;
    this->EDX = EDX;
  }

};

class reg_seletores_segmento{
public:
  int CS;
  int SS;
  int DS;
  reg_seletores_segmento() : CS(0), SS(0), DS(0){}
  reg_seletores_segmento(int CS, int SS, int DS ){
    this->CS = CS;
    this->SS = SS;
    this->DS = DS;
    }
  void mostrar_dados(){
    cout << "CS: " << CS << endl;
    cout  << "SS: " << SS << endl;
    cout  << "DS: " << DS << endl;
    }
  };
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

  int tamanho = 20;

  segment_register_table() : Cod_Seg(0), Stack_Seg(0), Data_Seg(0), CodLIM(0), StackLIM(0), DataLIM(0), Cod_acc(3), Stack_acc(3), Data_acc(3){}

void mostrar_tabela(){
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

    };
class reg_offset{
public:
  int EIP;
  int EBP;
  int ESP;
  int ESI;
  int EDI;
  reg_offset() : EIP(0), EBP(0), ESP(0), ESI(0), EDI(0) {}
  reg_offset(int EIP, int EBP, int ESP, int ESI, int EDI){
    this->EIP = EIP;
    this->EBP = EBP;
    this->ESP = ESP;
    this->ESI = ESI;
    this->EDI = EDI;
    }
  };


class arquiteturaX86{
public:
  reg_gerais gerais;
  reg_seletores_segmento seletores_segmento;
  reg_offset offset;
  int flag;
  map <int, string> memoria;
  arquiteturaX86(reg_gerais gerais, reg_seletores_segmento seletores_segmento, reg_offset offset, int flag, map <int, string> memoria){
    this->gerais = gerais;
    this->seletores_segmento = seletores_segmento;
    this->offset = offset;
    this->flag = flag;
    this->memoria = memoria;
    
    }

  };

reg_seletores_segmento entradaderegistradores(reg_seletores_segmento  seletores_segmento){
  cout<<"Digite os seletores de cada segmento:";
  cout<<"\nCS: ";
  cin>>seletores_segmento.CS;
  cout<<"\nSS: ";
  cin>>seletores_segmento.SS;
  cout<<"\nDS: ";
  cin>>seletores_segmento.DS;
  return seletores_segmento;
  }

  segment_register_table entradadetabela(segment_register_table tabela){
    cout<<"\nDigite os valores de inicio de cada segmento da tabela de segmentos:";
    cout<<"\nCod_Seg: ";
    cin>>tabela.Cod_Seg;
    cout<<"\nStack_Seg: ";
    cin>>tabela.Stack_Seg;
    tabela.CodLIM=tabela.Stack_Seg -1;
    cout<<"\nData_Seg: ";
    cin>>tabela.Data_Seg;
    tabela.StackLIM=tabela.Data_Seg -1;
    cout<<"\ndigite o valor limite do segmento de dados";
    cin>>tabela.DataLIM;
    return tabela;
    }



int main(){
  reg_gerais gerais;
  reg_seletores_segmento seletores_segmento;
  reg_offset offset;
  map <int, string> memoria;
  segment_register_table tabela;
  //seletores_segmento = entradadedados(seletores_segmento);
  //seletores_segmento.mostrar_dados();

  tabela.CS = seletores_segmento.CS;
  tabela.SS = seletores_segmento.SS;
  tabela.DS = seletores_segmento.DS;
  //tabela=entradadetabela(tabela);
  //tabela.mostrar_tabela();

  
  cout<<"digite o endereço inicial do segmento EIP: ";
  cin>>offset.EIP;

  cout<<"digite o endereço inicial do segmento EBP: ";
  cin>>offset.EBP;
  

  string instrucao;
  cout<<"digite a instrução que será simulada"<<endl;
  cin>>instrucao;
  if (instrucao=="add"){
    int END1, END2;
    cin>>END1>>END2;
    
    }
  
}
