#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "globals.h"
#include "world.h"
#include <windows.h>

using namespace std;

// Definizione dei colori
enum ConsoleColor {
    DEFAULT_COLOR = 7,  // Colore predefinito: Bianco su sfondo nero
    BLUE_COLOR = 9,     // Blu su sfondo nero
    YELLOW_COLOR = 14,  // Giallo su sfondo nero
};

// Funzione per impostare il colore del testo
void SetConsoleTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Funzione per reimpostare il colore del testo al predefinito
void ResetConsoleTextColor() {
    SetConsoleTextColor(DEFAULT_COLOR);
}

// Funzione per centrare il testo in base alla larghezza della console
void CenterText(const string& text, int color) {
    int consoleWidth;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - text.length()) / 2;
    SetConsoleTextColor(color); // Imposta il colore specificato
    for (int i = 0; i < padding; i++) {
        cout << " ";
    }
    cout << text;
    ResetConsoleTextColor(); // Ripristina il colore del testo al predefinito
}

// Funzione per stampare il teschio con il colore specificato
void PrintSkull(int color) {
    string skull[] = {
        "               _________             ",
        "/           \\",
        "//            \\\\",
        "|              |",
        "|,  .-.  .-.  ,|",
        "| )(__/  \\__)( |",
        "|/     /\\     \\|",
        "(_     ^^     _)",
        "\\__|IIIIII|__/",
        "| \\IIIIII/ |",
        "\\          /",
        "`--------`"
    };

    int maxLineWidth = 0;

    // Trova la larghezza massima tra le righe del teschio
    for (const string& line : skull) {
        if (line.length() > maxLineWidth) {
            maxLineWidth = line.length();
        }
    }

    // Stampa il teschio con le righe centrate
    for (const string& line : skull) {
        CenterText(line, color);
        cout << endl;
    }
}

int main() {
    // Imposta la larghezza della finestra del cmd a 200 pixel
    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = 199; // 200 pixel di larghezza
    rect.Bottom = 49; // L'altezza rimane invariata (50 linee)

    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);

    char key;
    string player_input;
    vector<string> args;
    args.reserve(10);

    ResetConsoleTextColor(); // Imposta il colore del testo al predefinito

    CenterText("Welcome to +ZORKGHOST+!", YELLOW_COLOR); // Imposta il colore giallo
    cout << endl; // Vai a una nuova riga

    PrintSkull(BLUE_COLOR); // Stampa il teschio con il colore blu

    World my_world;

    args.push_back("look");

    while (1) {
        if (_kbhit() != 0) {
            key = _getch();
            if (key == '\b') { // Backspace
                if (player_input.length() > 0) {
                    player_input.pop_back();
                    cout << "\b \b";
                }
            }
            else if (key != '\r') { // Invio
                SetConsoleTextColor(BLUE_COLOR); // Imposta il colore del testo in blu
                player_input += key;
                cout << key;
                ResetConsoleTextColor(); // Ripristina il colore del testo al predefinito
            }
            else {
                Tokenize(player_input, args);
                cout << endl; // Vai a una nuova riga prima di stampare il testo dell'utente
                SetConsoleTextColor(BLUE_COLOR); // Imposta il colore del testo in blu
                cout << player_input << endl;
                ResetConsoleTextColor(); // Ripristina il colore del testo al predefinito
            }
        }

        if (args.size() > 0 && Same(args[0], "quit"))
            break;

        if (my_world.Tick(args) == false) {
            cout << "\nSorry, I do not understand your command." << endl;
        }

        if (my_world.isDead()) {
            break;
        }
        if (my_world.youWin)
        {
            break;
        }

        if (args.size() > 0) {
            args.clear();
            player_input = "";
            cout << "> ";
        }
    }

    cout << "Thanks for playing, Bye!" << endl;
    system("pause");

    return 0;
}
