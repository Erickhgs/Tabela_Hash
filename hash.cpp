#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Pessoa {
    string chave;
    string nome;

    Pessoa(string c, string n) : chave(c), nome(n) {}
};

class HashTable {
private:
    int n;
    int tamanhoNivel2;
    vector<vector<list<Pessoa>>> tabela;

    int hash1(const string& chave) {
        int soma = 0;
        for (char c : chave) soma += c;
        return soma % 10;
    }

    int hash2(const string& chave) {
        int soma = 0;
        for (char c : chave) soma += c;
        return soma % tamanhoNivel2;
    }

public:
    HashTable(int totalElementos) {
        n = totalElementos;
        tamanhoNivel2 = n / 10;

        tabela.resize(10); // nível 1
        for (int i = 0; i < 10; i++) {
            tabela[i].resize(tamanhoNivel2); // nível 2
        }
    }

    void inserir(const string& chave, const string& nome) {
        int idx1 = hash1(chave);
        int idx2 = hash2(chave);
        tabela[idx1][idx2].emplace_back(chave, nome);
    }

    Pessoa* buscar(const string& chave) {
        int idx1 = hash1(chave);
        int idx2 = hash2(chave);

        for (Pessoa& p : tabela[idx1][idx2]) {
            if (p.chave == chave)
                return &p;
        }
        return nullptr;
    }

    void exibir() {
        for (int i = 0; i < 10; i++) {
            cout << "Tabela[" << i << "]:\n";
            for (int j = 0; j < tamanhoNivel2; j++) {
                cout << "  Subtabela[" << j << "]: ";
                for (auto& p : tabela[i][j]) {
                    cout << "[" << p.chave << ": " << p.nome << "] -> ";
                }
                cout << "NULL\n";
            }
        }
    }
};
int main() {
    HashTable ht(50); // exemplo com n = 100

    ht.inserir("123", "Joao");
    ht.inserir("456", "Marco");
    ht.inserir("789", "Julia");
    ht.inserir("321", "Marina");
    ht.inserir("654", "Antonio");
    ht.inserir("987", "Jose");
    ht.inserir("123", "Ana");

    ht.exibir();

    Pessoa* p = ht.buscar("987");
    if (p) {
        cout << "Encontrado: " << p->nome << endl;
    } else {
        cout << "Pessoa nao encontrada." << endl;
    }

    return 0;
}
