#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 3

char papan[SIZE][SIZE];
const char PEMAIN = 'X';
const char KOMPUTER = 'O';

void resetPapan() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            papan[i][j] = ' ';
}

void tampilkanPapan() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", papan[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("-----------\n");
    }
    printf("\n");
}

bool cekMenang(char simbol) {
    for (int i = 0; i < SIZE; i++)
        if (papan[i][0] == simbol && papan[i][1] == simbol && papan[i][2] == simbol)
            return true;
    for (int i = 0; i < SIZE; i++)
        if (papan[0][i] == simbol && papan[1][i] == simbol && papan[2][i] == simbol)
            return true;
    if (papan[0][0] == simbol && papan[1][1] == simbol && papan[2][2] == simbol)
        return true;
    if (papan[0][2] == simbol && papan[1][1] == simbol && papan[2][0] == simbol)
        return true;
    return false;
}

bool penuh() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (papan[i][j] == ' ')
                return false;
    return true;
}

int minimax(bool isMax) {
    if (cekMenang(KOMPUTER)) return 1;
    if (cekMenang(PEMAIN)) return -1;
    if (penuh()) return 0;

    if (isMax) {
        int skorTerbaik = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (papan[i][j] == ' ') {
                    papan[i][j] = KOMPUTER;
                    int skor = minimax(false);
                    papan[i][j] = ' ';
                    if (skor > skorTerbaik) skorTerbaik = skor;
                }
            }
        }
        return skorTerbaik;
    } else {
        int skorTerbaik = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (papan[i][j] == ' ') {
                    papan[i][j] = PEMAIN;
                    int skor = minimax(true);
                    papan[i][j] = ' ';
                    if (skor < skorTerbaik) skorTerbaik = skor;
                }
            }
        }
        return skorTerbaik;
    }
}

void giliranKomputer() {
    int skorTerbaik = -1000;
    int baris = -1, kolom = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (papan[i][j] == ' ') {
                papan[i][j] = KOMPUTER;
                int skor = minimax(false);
                papan[i][j] = ' ';
                if (skor > skorTerbaik) {
                    skorTerbaik = skor;
                    baris = i;
                    kolom = j;
                }
            }
        }
    }
    papan[baris][kolom] = KOMPUTER;
    printf("Komputer memilih (%d, %d)\n", baris + 1, kolom + 1);
}

void giliranPemain() {
    int x, y;
    do {
        printf("Masukkan baris dan kolom (1-3): ");
        scanf("%d %d", &x, &y);
        x--; y--;
    } while (x < 0 || x >= SIZE || y < 0 || y >= SIZE || papan[x][y] != ' ');
    papan[x][y] = PEMAIN;
}

void tampilkanTutorial() {
    printf("\nTUTORIAL:\n");
    printf("Masukkan angka baris dan kolom dari 1 sampai 3 untuk menaruh tanda Anda.\n");
    printf("Pemain (X) akan bermain duluan, lalu giliran komputer (O).\n\n");
}

void mainGame() {
    int pilihan;
    while (1) {
        printf("\nMENU:\n1. Easy\n2. Medium\n3. Hard\n4. Tutorial\n5. Keluar\nPilihan: ");
        scanf("%d", &pilihan);
        if (pilihan == 4) {
            tampilkanTutorial();
        } else if (pilihan == 5) {
            printf("Terima kasih!\n");
            break;
        } else {
            resetPapan();
            while (1) {
                tampilkanPapan();
                giliranPemain();
                if (cekMenang(PEMAIN)) {
                    tampilkanPapan();
                    printf("Selamat! Kamu menang!\n");
                    break;
                }
                if (penuh()) {
                    tampilkanPapan();
                    printf("Seri!\n");
                    break;
                }
                giliranKomputer();
                if (cekMenang(KOMPUTER)) {
                    tampilkanPapan();
                    printf("Komputer menang!\n");
                    break;
                }
                if (penuh()) {
                    tampilkanPapan();
                    printf("Seri!\n");
                    break;
                }
            }
        }
    }
}

int login() {
    char username[20], password[20];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "123") == 0) {
        printf("Login berhasil!\n");
        return 1;
    } else {
        printf("Login gagal.\n");
        return 0;
    }
}

int main() {
    printf("Selamat datang di permainan Tic Tac Toe!\n");
    if (login()) {
        mainGame();
    } else {
        printf("Program keluar.\n");
    }
    return 0;
}

