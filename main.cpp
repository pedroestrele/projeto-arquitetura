#include "arquiteturaX86.h"
#include "endereco.h"
#include "registradores.h"
#include "tabela.h"
#include <bits/stdc++.h>

using namespace std;

enum instrucoes { ADD, INC, DEC, MOV, PUSH, POP, CMP, JMP };

map<string, instrucoes> instrucao_map = {
    {"add", ADD},   {"inc", INC}, {"dec", DEC}, {"mov", MOV},
    {"push", PUSH}, {"pop", POP}, {"cmp", CMP}, {"jmp", JMP}};

int main()
{
	RegGerais gerais;
	RegSeletorSegmentos seletores_segmento;
	RegOffsets offset;
	RegFlag flag;
	map<long, string> memoria;

	seletores_segmento.obter_entrada();

	TabelaDescritorSegmento tabela (seletores_segmento);
	tabela.entrada_de_tabela();
	tabela.mostrar_tabela();

	ArquiteturaX86 PC (
	    gerais, seletores_segmento, offset, memoria, tabela, flag);
	string instrucao;
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

		default:
			break;
	}

	return 0;
}
