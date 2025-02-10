#include "arquiteturaX86.h"
#include "endereco.h"
#include "registradores.h"
#include "tabela.h"
#include <bits/stdc++.h>

using namespace std;

enum instrucoes {
	ADD,
	INC,
	DEC,
	MOV,
	PUSH,
	POP,
	CMP,
	JMP,
	XCHG,
	SUB,
	MUL,
	NEG,
	AND,
	OR,
	XOR,
	NOT,
	JXX,
	CALL,
	RET,
	IRET,
	LOOP,
	STOP
};

map<string, instrucoes> instrucao_map = {
    {"add", ADD}, {"inc", INC}, {"dec", DEC}, {"mov", MOV},   {"push", PUSH},
    {"pop", POP}, {"cmp", CMP}, {"jmp", JMP}, {"xchg", XCHG}, {"sub", SUB},
    {"mul", MUL}, {"neg", NEG}, {"and", AND}, {"or", OR},     {"xor", XOR},
    {"not", NOT}, {"call",CALL},{"ret",RET} , {"iret", IRET}, {"loop", LOOP},
	{"je", JXX} , {"jg", JXX} , {"jge", JXX}, {"jne", JXX} ,  {"jl", JXX},  
	{"jle", JXX}, {"stop", STOP}};

int main()
{
	RegGerais gerais;
	RegSeletorSegmentos seletores_segmento;
	RegOffsets offset;
	RegFlag flag;
	map<long, string> memoria;

	seletores_segmento.obter_entrada();
  seletores_segmento.mostrar_dados();

	TabelaDescritorSegmento tabela (seletores_segmento);
	tabela.entrada_de_tabela();
	tabela.mostrar_tabela();

	offset.obter_entrada();
	offset.mostrar_dados();

	ArquiteturaX86 PC (gerais, seletores_segmento, offset, memoria, tabela, flag);
	string instrucao;
	bool continuar = true;

	while (continuar) {
		cout << "para sair digite 'stop'" << endl;
		cout << "Digite a instrucao que serah simulada: ";
		cin >> instrucao;

		for (auto &c : instrucao) {
			c = tolower (c);
		}

		switch (instrucao_map[instrucao]) {
			case MOV: {
				string end_hex1, end_hex2;
				cout << "Digite o endereco 1: ";
				cin >> end_hex1;
				cout << "Digite o endereco 2: ";
				cin >> end_hex2;

				Endereco<32> END1 (end_hex1), END2 (end_hex2);
				PC.mov (END1, END2);
			} break;
			case PUSH: {
				// coletar todos os dados necesários no main
				cout << "Digite o endereco: ";
				string end_hex;
				cin >> end_hex;

				Endereco<32> END (end_hex);
				PC.push (END); // calculos,barramentos e etc na função
			} break;
			case POP: {
				// coletar todos os dados necesários no main
				cout << "Digite o endereco: ";
				string end_hex;
				cin >> end_hex;

				Endereco<32> END (end_hex);
				PC.pop (END); // calculos,barramentos e etc na função
			} break;
			case XCHG: {
				// coletar todos os dados necesários no main
				string end_hex1, end_hex2;
				cout << "Digite o endereco 1: ";
				cin >> end_hex1;
				cout << "Digite o endereco 2: ";
				cin >> end_hex2;

				Endereco<32> END1 (end_hex1), END2 (end_hex2);
				PC.xchg (END1, END2); // calculos,barramentos e etc na função
			} break;
			case ADD: {
				// coletar todos os dados necesários no main
				string end_hex1, end_hex2;
				cin >> end_hex1 >> end_hex2;

				Endereco<32> END1 (end_hex1), END2 (end_hex2);

				PC.add (END1, END2); // calculos,barramentos e etc na função
			} break;
			case INC: {
				string end_hex;
				cout << "Digite o endereco: ";
				cin >> end_hex;

				Endereco<32> END (end_hex);

				PC.inc (END);
			} break;
			case DEC: {
				string end_hex;
				cout << "Digite o endereco: ";
				cin >> end_hex;

				Endereco<32> END (end_hex);
				PC.dec (END);
			} break;
			case CMP: {
				string end_hex1, end_hex2;
				cout << "Digite o endereco 1: ";
				cin >> end_hex1;
				cout << "Digite o endereco 2: ";
				cin >> end_hex2;

				Endereco<32> END1 (end_hex1), END2 (end_hex2);

				PC.cmp (END1, END2);
			} break;
			case JMP: {
				string end_hex;
				cout << "Digite o endereco: ";
				cin >> end_hex;
				Endereco<32> END (end_hex);
				PC.jmp (END);
			}
			case SUB: {
				string end_hex1, end_hex2;
				cin >> end_hex1;
				cin >> end_hex2;
				Endereco<32> END1 (end_hex1);
				Endereco<32> END2 (end_hex2);
				PC.sub (END1, END2);
			} break;
			case MUL: {
				string end_hex1, end_hex2;
				cin >> end_hex1;
				cin >> end_hex2;
				Endereco<32> END1 (end_hex1);
				Endereco<32> END2 (end_hex2);
				PC.mul (END1, END2);
			} break;
			case NEG: {
				string end_hex;
				cin >> end_hex;
				Endereco<32> END (end_hex);
				PC.neg (END);
			} break;
			case AND: {
				string end_dest, end_fonte;
				cout << "Digite o endereco destino: ";
				cin >> end_dest;
				cout << "Digite o endereco fonte: ";
				cin >> end_fonte;
				Endereco<32> DST (end_dest);
				Endereco<32> SRC (end_fonte);
				PC.AND (DST, SRC);
			} break;
			case OR: {
				string end_dest, end_fonte;
				cout << "Digite o endereco destino: ";
				cin >> end_dest;
				cout << "Digite o endereco fonte: ";
				cin >> end_fonte;
				Endereco<32> DST (end_dest);
				Endereco<32> SRC (end_fonte);
				PC.OR (DST, SRC);
			} break;
			case XOR: {
				string end_dest, end_fonte;
				cout << "Digite o endereco destino: ";
				cin >> end_dest;
				cout << "Digite o endereco fonte: ";
				cin >> end_fonte;
				Endereco<32> DST (end_dest);
				Endereco<32> SRC (end_fonte);
				PC.XOR (DST, SRC);
			} break;
			case NOT: {
				string end_dest;
				cout << "Digite o endereco destino: ";
				cin >> end_dest;
				Endereco<32> DST (end_dest);
				PC.NOT (DST);
			} break;
			case JXX: {
				string tipo = "";
				for (int i = 1; i < instrucao.length(); i++) {
					tipo = tipo + instrucao[i];
				}
				string end_hex;
				cout << "Digite o endereco: ";
				cin >> end_hex;
				Endereco<32> END (end_hex);
				PC.jxx (END, tipo);

			} break;
			case CALL: {
				string end_hex;
				cout << "Digite o endereco para chamada: ";
				cin >> end_hex;
				Endereco<32> END (end_hex);
				PC.call(END);
			} break;
			case RET: {
				string end_hex, valor;
				cout << "Digite o endereco: ";
				cin >> end_hex;
				cout << "Digite o valor: ";
				cin >> valor;
				Endereco<32> END (end_hex);
				PC.ret(END, valor);
			} break;
			case IRET: {
				PC.iret();
			} break;
			case LOOP_: {
				string end_hex;
				cout << "Digite o endereco de destino do loop: ";
				cin >> end_hex;
				Endereco<32> END (end_hex);
				PC.loop_(END);
			} break;
			case STOP: {
				continuar = false;
			} break;
			default:
				break;
		}
	}
	return 0;
}
