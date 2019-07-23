/*
	Source: NN
	Modified by: Rizky Khapidsyah
	IDE:VS2019
*/


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//////////////////////////////////////////////////////////////
//Deklarasi global variabel
int gameMode,
kotakTerisi = 0,
giliranPertama = 0,
pemenang = 0;

char 	papan[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
player1,
player2;

//////////////////////////////////////////////////////////////
//Daftar Void dan Fungsi
void menuUtama();
void intruksiBermain();
void memilihKarakter();
void memasukanChar();
void cetakPapan();
void gameMode1();
void hasilPermainan();
int AI();
int negamax();
int bilAcak();

//////////////////////////////////////////////////////////////
//Fungsi Main
int main(int argc, char const* argv[]) {

	system("color f");
	printf("\t\t\t================\n");
	printf("\t\t\tGAME TIC TAC TOE\n");
	printf("\t\t\t================\n\n");
	menuUtama();

	_getch();
	return 0;
}

//////////////////////////////////////////////////////////////
//Menampilkan papan permainan
void cetakPapan() {
	printf("\n\n");
	printf("\t\t\t+-----------+\n");
	int i = 0;
	while (i < 7) {
		printf("\t\t\t| %c | %c | %c |\n", papan[i], papan[i + 1], papan[i + 2]);
		if (i < 6)printf("\t\t\t|-----------|\n");
		i += 3;
	}
	printf("\t\t\t+-----------+\n");
	printf("\n\n");
}

//////////////////////////////////////////////////////////////
//Memilih Karakter X atau O
void memilihKarakter() {
	while (1) {
		printf("Player 1 --> Pilih X atau O : ");
		scanf_s(" %c", &player1);
		player1 = toupper(player1);
		if (player1 == 'X' || player1 == 'O') break;
		else printf("Inputan Salah..!! Coba lagi.\n");
	}
	if (player1 == 'X') player2 = 'O';
	else player2 = 'X';
	printf("\n\nPlayer 1 -------> %c\nPlayer 2 -------> %c\n", player1, player2);
}

//////////////////////////////////////////////////////////////
//Memasukan Karakter X atau O ke papan
void memasukanChar(char player) {
	int kotak;
	while (1) {
		if (player == player1) printf("Giliran Player 1 --> ");
		else printf("Giliran Player 2 --> ");
		printf("Masukan %c ke kotak no : ", player);
		scanf_s(" %d", &kotak);
		if (kotak < 1 || kotak > 9) printf("\nInputan tidak boleh kurang dari 1 atau lebih dari 9\n");
		else if (papan[kotak - 1] != ' ') printf("\nKotak telah terisi. Coba lagi\n");
		else break;
	}
	papan[kotak - 1] = player;
	kotakTerisi++;
}

//////////////////////////////////////////////////////////////
//Mengecek Pemenang
char cekMenang() {
	int kondisi[8][3] = {
		//horizontal
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		//vertical
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		//diagonal
		{0, 4, 8},
		{2, 4, 6}
	};
	for (int i = 0; i < 8; i++) {
		if ((papan[kondisi[i][0]] == papan[kondisi[i][1]] && papan[kondisi[i][0]] == papan[kondisi[i][2]]) && papan[kondisi[i][0]] != ' ') {
			return papan[kondisi[i][0]];
			break;
		}
	}
	return 'a';
}

//////////////////////////////////////////////////////////////
//Melihat hasil permainan
void hasilPermainan() {
	printf("\n\n\t\t\t");
	if (pemenang == 1) printf("PLAYER 1 MENANG...!!!\n");
	else if (pemenang == 2) printf("PLAYER 2 MENANG...!!!\n");
	else printf("PERMAINAN SERI\n");
	cetakPapan();
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//Algoritma Negamax
int negamax(char papanBaru[9], char p1, char p2) {
	int skorTerbaik = -9999;
	if (cekMenang() == p1) return 1000;
	else if (cekMenang() == p2) return -1000;

	for (int i = 0; i < 9; i++) {
		if (papanBaru[i] == ' ') {
			papanBaru[i] = p1;
			int skorGerakan = -(negamax(papanBaru, p2, p1));
			papanBaru[i] = ' ';
			if (skorGerakan >= skorTerbaik) {
				skorTerbaik = skorGerakan;
			}
		}
	}
	if (skorTerbaik == -9999 || skorTerbaik == 0) return 0;
	else if (skorTerbaik < 0) return skorTerbaik + 1;
	else if (skorTerbaik > 0) return skorTerbaik - 1;

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Kecerdasan buatan komputer
int AI(char papanBaru[9], char p1, char p2) {
	int skorTerbaik = -9999,
		gerakan = -9999,
		pilihanTerbaik = 0;
	for (int i = 0; i < 9; i++) {
		if (papanBaru[i] == ' ') {
			papanBaru[i] = p1;
			gerakan = -(negamax(papanBaru, p2, p1));
			papanBaru[i] = ' ';
			if (gerakan >= skorTerbaik) {
				skorTerbaik = gerakan;
				pilihanTerbaik = i;
			}
		}
	}
	return pilihanTerbaik;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Mengembalikan acak kotak kosong
int bilAcak() {
	while (1) {
		srand(time(NULL));
		int pilihAcak = rand() % 9;
		if (papan[pilihAcak] == ' ') {
			return pilihAcak;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////
//Game Mode 1 : Player VS Player
void gameMode1() {
	printf("\n\nGAME MODE 1 : Player VS Player\n");
	printf("---------------------------------------------------------\n\n");
	memilihKarakter();
	srand(time(NULL));
	giliranPertama = rand() % 2 + 1;
	if (giliranPertama == 1) printf("\n\nPlayer 1 mendapatkan giliran Pertama\n");
	else printf("\n\nPlayer 2 mendapatkan giliran Pertama\n");
	while (kotakTerisi < 9) {
		cetakPapan();
		if (giliranPertama == 1) {
			memasukanChar(player1);
			if (cekMenang() == player1) {
				pemenang = 1;
				break;
			}
			cetakPapan();
			memasukanChar(player2);
			if (cekMenang() == player2) {
				pemenang = 2;
				break;
			}
		}
		else {
			memasukanChar(player2);
			if (cekMenang() == player2) {
				pemenang = 2;
				break;
			}
			cetakPapan();
			memasukanChar(player1);
			if (cekMenang() == player1) {
				pemenang = 1;
				break;
			}
		}
	}
	hasilPermainan();
	printf("\nTekan Enter untuk kembali ke Menu Utama ");
	_getch();
	gameMode = 0;
	menuUtama();
}

//////////////////////////////////////////////////////////////
//Game Mode 1 : Player VS Player
void gameMode2() {
	printf("\n\nGAME MODE 2 : Player VS Computer\n");
	printf("---------------------------------------------------------\n\n");
	int levelCom;
	printf("Level Komputer :\n\n1. Mudah\n2. Sulit\n\n");
	while (1) {
		printf("Pilih level no : ");
		scanf_s(" %d", &levelCom);
		if (levelCom == 1 || levelCom == 2) break;
		else printf("Inputan Salah..!! Coba lagi.\n");
	}
	if (levelCom == 1) printf("\n\nAnda Memilih Computer Level Mudah\n\n");
	else printf("\n\nAnda Memilih Computer Level Sulit\n\n");
	memilihKarakter();
	srand(time(NULL));
	giliranPertama = rand() % 2 + 1;
	if (giliranPertama == 1) printf("\n\nPlayer 1 mendapatkan giliran Pertama\n");
	else printf("\n\nPlayer 2 mendapatkan giliran Pertama\n");
	int pilihanCom = 4; //pilihan default
	while (kotakTerisi < 9) {
		if (giliranPertama == 1) {
			cetakPapan();
			memasukanChar(player1);
			if (cekMenang() == player1) {
				pemenang = 1;
				break;
			}
			if (levelCom == 1) pilihanCom = bilAcak();
			else pilihanCom = AI(papan, player1, player2);
			printf("\nGiliran Player 2 --> Komputer memilih kotak no %d\n", pilihanCom + 1);
			papan[pilihanCom] = player2;
			kotakTerisi++;
			if (cekMenang() == player2) {
				pemenang = 2;
				break;
			}
		}
		else {
			if (kotakTerisi > 0) {
				if (levelCom == 1) pilihanCom = bilAcak();
				else pilihanCom = AI(papan, player1, player2);
			}
			printf("\nGiliran Player 2 --> Komputer memilih kotak no %d\n", pilihanCom + 1);
			papan[pilihanCom] = player2;
			kotakTerisi++;
			if (cekMenang() == player2) {
				pemenang = 2;
				break;
			}
			cetakPapan();
			memasukanChar(player1);
			if (cekMenang() == player1) {
				pemenang = 1;
				break;
			}
		}
	}
	hasilPermainan();
	printf("\nTekan Enter untuk kembali ke Menu Utama ");
	_getch();
	gameMode = 0;
	menuUtama();
}

//////////////////////////////////////////////////////////////
//Menampilkan intruksi bermain
void intruksiBermain() {
	printf("\n\nINTRUKSI BERMAIN\n");
	printf("---------------------------------------------------------\n\n");
	printf("1. Setiap kotak di papan memiliki nomor seperti berikut\n\n");
	printf("\t+-----------+\n");
	printf("\t| 1 | 2 | 3 |\n\t|-----------|\n");
	printf("\t| 4 | 5 | 6 |\n\t|-----------|\n");
	printf("\t| 7 | 8 | 9 |\n");
	printf("\t+-----------+\n\n");
	printf("2. Masukan karakter Anda (X atau O) kedalam kotak di papan\n\n");
	printf("3. Player pertama yang mendapatkan deret :\n");
	printf("\t- Vertikal\n\t- Horizontal\n\t- Diagonal\n");
	printf("   Maka dialah Pemenangnya\n");

	printf("\n\nTekan Enter untuk kembali ke Menu Utama");
	_getch();
	printf("\n\n\n");
	menuUtama();
	gameMode = 0;
}

//////////////////////////////////////////////////////////////
//Menampilkan menu utama
void menuUtama() {
	printf("\n\nMAIN MENU\n");
	printf("---------------------------------------------------------\n");
	printf("1. Player VS Player\n2. Player VS Computer\n");
	printf("3. Intruksi Bermain\n4. Keluar\n\n");
	while (1) {
		printf("Pilih Game Mode No (1-4) : ");
		scanf_s("%d", &gameMode);
		if (gameMode > 0 && gameMode < 5) break;
		else printf("\nInputan Salah..Coba lagi\n");
	}
	if (gameMode == 1) gameMode1();
	else if (gameMode == 2) gameMode2();
	else if (gameMode == 3) intruksiBermain();
	else exit(1);
}