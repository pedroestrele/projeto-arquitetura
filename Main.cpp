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
  int ES;
  int FS;
  int GS;
  reg_seletores_segmento() : CS(0), SS(0), DS(0), ES(0), FS(0), GS(0) {}
  reg_seletores_segmento(int CS, int SS, int DS, int ES, int FS, int GS){
    this->CS = CS;
    this->SS = SS;
    this->DS = DS;
    this->ES = ES;
    this->FS = FS;
    this->GS = GS;
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

map <int,string> memoria;
class arquiteturaX86{
public:
  reg_gerais gerais;
  reg_seletores_segmento seletores_segmento;
  reg_offset offset;
  string flag;
  map <int, string> memoria;
  arquiteturaX86(reg_gerais gerais, reg_seletores_segmento seletores_segmento, reg_offset offset, string flag, map <int, string> memoria){
    this->gerais = gerais;
    this->seletores_segmento = seletores_segmento;
    this->offset = offset;
    this->flag = flag;
    this->memoria = memoria;
    
    }
  
  };
int main(){
}
