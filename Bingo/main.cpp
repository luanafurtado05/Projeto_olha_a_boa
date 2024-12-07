#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

const int TAMANHO = 5;

void inicializarCartela(int cartela[TAMANHO][TAMANHO]) {
    vector<int> usados;

    for (int col = 0; col < TAMANHO; col++) {
        int start = col * 15 + 1;
        int end = (col + 1) * 15;
        for (int row = 0; row < TAMANHO; row++) {
            int num;
            do {
                num = rand() % (end - start + 1) + start;
            } while (find(usados.begin(), usados.end(), num) != usados.end());
            cartela[row][col] = num;
            usados.push_back(num);
        }
    }

    cartela[2][2] = 0;
}

void exibirCartela(int cartela[TAMANHO][TAMANHO]) {
    cout << "\nCartela:\n";
    cout << " B   I   N   G   O\n";
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (cartela[i][j] == 0) {
                cout << "FREE ";
            } else {
                cout << cartela[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

void marcarNumero(int cartela[TAMANHO][TAMANHO], int num) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (cartela[i][j] == num) {
                cartela[i][j] = 0;
            }
        }
    }
}

void verificarVitoria(int cartela[TAMANHO][TAMANHO]) {
    bool linhaCompleta, colunaCompleta;

    for (int i = 0; i < TAMANHO; i++) {
        linhaCompleta = true;
        for (int j = 0; j < TAMANHO; j++) {
            if (cartela[i][j] != 0) {
                linhaCompleta = false;
                break;
            }
        }
        if (linhaCompleta) {
            cout << "LINHA COMPLETA!" << endl;
            return;
        }
    }

    for (int j = 0; j < TAMANHO; j++) {
        colunaCompleta = true;
        for (int i = 0; i < TAMANHO; i++) {
            if (cartela[i][j] != 0) {
                colunaCompleta = false;
                break;
            }
        }
        if (colunaCompleta) {
            cout << "COLUNA COMPLETA!" << endl;
            return;
        }
    }

    bool bingo = true;
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (cartela[i][j] != 0) {
                bingo = false;
                break;
            }
        }
        if (!bingo) break;
    }

    if (bingo) {
        cout << "BINGO! Cartela COMPLETA!" << endl;
    }
}

void salvarCartelaEmArquivo(int cartela[TAMANHO][TAMANHO], int id) {
    stringstream ss;
    ss << id;
    string id_str = ss.str();

    string nome_arquivo = "cartela_" + id_str + ".txt";

    ofstream arquivo(nome_arquivo.c_str());
    if (arquivo.is_open()) {
        arquivo << "Cartela " << id << ":\n";
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (cartela[i][j] == 0) {
                    arquivo << "FREE ";
                } else {
                    arquivo << cartela[i][j] << "   ";
                }
            }
            arquivo << "\n";
        }
        arquivo.close();
        cout << "Cartela salva em '" << nome_arquivo << "'" << endl;
    } else {
        cout << "Erro ao salvar cartela em arquivo!" << endl;
    }
}

int main() {
    srand(time(0));

    int cartela[TAMANHO][TAMANHO];
    int opcao, num, id = 1;

    do {
        cout << "\n--- Menu de Bingo ---" << endl;
        cout << "1. Gerar nova cartela" << endl;
        cout << "2. Exibir cartela" << endl;
        cout << "3. Marcar um numero" << endl;
        cout << "4. Verificar vitoria (linha/coluna)" << endl;
        cout << "5. Salvar cartela em arquivo" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                inicializarCartela(cartela);
                cout << "Nova cartela gerada!" << endl;
                break;
            case 2:
                exibirCartela(cartela);
                break;
            case 3:
                cout << "Informe o numero a ser marcado: ";
                cin >> num;
                marcarNumero(cartela, num);
                verificarVitoria(cartela);
                break;
            case 4:
                verificarVitoria(cartela);
                break;
            case 5:
                salvarCartelaEmArquivo(cartela, id);
                id++;
                break;
            case 6:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }

    } while (opcao != 6);

    return 0;
}

