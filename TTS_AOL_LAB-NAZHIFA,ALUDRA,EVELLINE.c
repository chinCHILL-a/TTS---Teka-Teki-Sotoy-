#include <stdio.h>

#define MAX_USERS 200

struct User {
    char username[40];
    int score;
    int levelTerakhir; 
    int soalTerakhir;  
};

struct QA {
    char question[200];
    char answer[60];
    char comment[250];
};

struct User dataAkun[MAX_USERS];
int jumlahAkun = 0;

// ==== MODULE UI & UTILITY ====

void bersihinLayar() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void tekanEnter() {
    char temp[5];
    printf("\nTekan ENTER untuk lanjut...");
    fgets(temp, 5, stdin);
}

int hitungPanjang(char kata[]) {
    int i = 0;
    while (kata[i] != '\0') {
        i++;
    }
    return i;
}

void hapusEnter(char kata[]) {
    int panjang = hitungPanjang(kata);
    if (panjang > 0 && (kata[panjang - 1] == '\n' || kata[panjang - 1] == '\r')) {
        kata[panjang - 1] = '\0';
    }
    panjang = hitungPanjang(kata);
    if (panjang > 0 && (kata[panjang - 1] == '\n' || kata[panjang - 1] == '\r')) {
        kata[panjang - 1] = '\0';
    }
}

void inputKalimat(char teks[], int max) {
    if (fgets(teks, max, stdin) == NULL) {
        teks[0] = '\0';
        return;
    }
    hapusEnter(teks);
}

int inputAngka() {
    char teks[50];
    int i = 0, angka = 0;
    inputKalimat(teks, 50);
    while (teks[i] >= '0' && teks[i] <= '9') {
        angka = (angka * 10) + (teks[i] - '0');
        i++;
    }
    return angka;
}

int bandingkanString(char kata1[], char kata2[]) {
    int i = 0;
    while (1) {
        if (kata1[i] != kata2[i]) return 0;
        if (kata1[i] == '\0' && kata2[i] == '\0') return 1;
        i++;
    }
}

// ==== MODULE FILE & DATA ====

void simpanSemuaUser() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) return;

    // --- SORTING (Bubble Sort) ---
    // Mengurutkan user berdasarkan skor tertinggi ke terendah
    int i, j;
    for (i = 0; i < jumlahAkun - 1; i++) {
        for (j = 0; j < jumlahAkun - i - 1; j++) {
            if (dataAkun[j].score < dataAkun[j + 1].score) {
                struct User temp = dataAkun[j];
                dataAkun[j] = dataAkun[j + 1];
                dataAkun[j + 1] = temp;
            }
        }
    }

    fprintf(fp, "NO | USERNAME             | LEVEL | SKOR  | SOAL\n");
    fprintf(fp, "------------------------------------------------\n");

    for (i = 0; i < jumlahAkun; i++) {
        fprintf(fp, "%-2d | %-20s | %-5d | %-5d | %-d\n", 
                (i + 1),
                dataAkun[i].username, 
                dataAkun[i].levelTerakhir, 
                dataAkun[i].score,
                dataAkun[i].soalTerakhir); 
    }
    fclose(fp);
}

void loadUser() {
    FILE *fp = fopen("users.txt", "r");
    jumlahAkun = 0;
    if (fp == NULL) return;

    char buffer[200];
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    int noUrut;
    while (jumlahAkun < MAX_USERS) {
        if (fscanf(fp, " %d | %[^|] | %d | %d | %d\n", 
            &noUrut,
            dataAkun[jumlahAkun].username, 
            &dataAkun[jumlahAkun].levelTerakhir, 
            &dataAkun[jumlahAkun].score,
            &dataAkun[jumlahAkun].soalTerakhir) != 5) {
            break;
        }
        
        int p = hitungPanjang(dataAkun[jumlahAkun].username);
        while(p > 0 && dataAkun[jumlahAkun].username[p-1] == ' ') {
            dataAkun[jumlahAkun].username[p-1] = '\0';
            p--;
        }
        jumlahAkun++;
    }
    fclose(fp);
}

int cariUser(char username[]) {
    int i;
    for (i = 0; i < jumlahAkun; i++) {
        if (bandingkanString(dataAkun[i].username, username) == 1) return i;
    }
    return -1;
}

// ==== VISUAL TTS ASCII ====

void tampilTTSLevel1() {
    printf("\n=== HASIL TTS LEVEL 1 ===\n");
    printf("                  2 \n");
    printf("                5[D][I][P][I][L][I][H]\n");
    printf("1 [S][E][K][A][L][I]\n");
    printf("          3[N]   [P]\n");
    printf("           [C]4[M][A][N][A][Y][A]\n");
    printf("           [U]   [K]\n");
    printf("           [R]   [E]\n");
}

void tampilTTSLevel2() {
    printf("\n=== HASIL TTS LEVEL 2 ===\n");
    printf("             1[B]\n");
    printf("              [U]\n");
    printf("              [K]\n");
    printf("          3[M][A][L][E][M][M][A][L][E][M]\n");
    printf("              [N]\n");
    printf("              [G]\n");
    printf("    4[D]      [U]\n");
    printf("2 [N][A][N][C][E][P]\n");
    printf("     [L]\n");
    printf("     [A]\n");
    printf("     [M]\n");
    printf("     [N]\n");
    printf("     [Y]\n");
    printf("5 [R][A][M][A][I]\n");
}

void tampilTTSLevel3() {
    printf("\n=== HASIL TTS LEVEL 3 ===\n");
    printf("          2[A]\n");
    printf("          5[D][I][K][I][T]\n");
    printf("           [A]\n");
    printf("1 [S][E][N][D][I][R][I]\n");
    printf("3 [M][U][L][U][T]\n");
    printf("4 [P][E][M][A][I][N][N][Y][A]\n");
}

void tampilTTSLevel4() {
    printf("\n=== HASIL TTS LEVEL 4 ===\n");
    printf("                        1\n");
    printf("                      5[S][U][D][A][H]\n");
    printf("         3           4 [E]\n");
    printf("        [M]         [W][R]\n");
    printf("2 [O][R][A][N][G][B][A][I][K]\n");
    printf("        [R]         [K][N]\n");
    printf("        [I]         [T][G]\n");
    printf("        [N]         [U]\n");
}

void tampilTTSLevel5() {
    printf("\n=== HASIL TTS LEVEL 5 ===\n");
    printf("   1                   [S]\n");
    printf("2 [B][E][D][A][B][E][D][A]\n");
    printf("  3[S][E][N][D][I][R][I]   [M]\n");
    printf("  [N]                  [A]\n");
    printf("  [G]              5[R][A][I][B]\n");
    printf("  [O]                  [N]\n");
    printf("  [N]\n");
    printf("  [G]\n");
}

void tampilHasilTTS(int nomorLevel, int poin) {
    printf("\nAZEKK SELESAI NIH, total poin kamu %d\n", poin);
    if (nomorLevel == 1) tampilTTSLevel1();
    else if (nomorLevel == 2) tampilTTSLevel2();
    else if (nomorLevel == 3) tampilTTSLevel3();
    else if (nomorLevel == 4) tampilTTSLevel4();
    else if (nomorLevel == 5) tampilTTSLevel5();
}

void tampilKotakJawabanDenganClue(char jawabanBenar[], int tipeClue) {
    int panjang = hitungPanjang(jawabanBenar);
    int tengah = panjang / 2;
    int i;
    for (i = 0; i < panjang; i++) {
        if (tipeClue == 1) {
            if (i == 0 || i == panjang - 1) printf("[%c]", jawabanBenar[i]);
            else printf("[ ]");
        } else {
            if (i == tengah) printf("[%c]", jawabanBenar[i]);
            else printf("[ ]");
        }
    }
    printf("\n");
}

// ==== DATA SOAL (QA) ====

struct QA level1[5] = {
    {"Untuk menyalakan lampu kita harus pencet?", "SEKALI", "Loh bener kan? Kalau pencet 2x ya mati lagi dong!"},
    {"Baju yang digunakan untuk tidur pasti?", "DIPAKE", "Pasti dipakai dong, masa dipajang doang?"},
    {"Buah berwarna oranye yang dijus pasti?", "ANCUR", "Sebenernya... buah apa aja kalau dijus pasti ancur!"},
    {"Saat senggang paling enak kita berlibur ke...?", "MANAYA", "Ke mana ya? Enaknyaa~"},
    {"Presiden pertama Indonesia pasti?", "DIPILIH", "(Ya iyalah, masa hasil undian ??)"}
};

struct QA level2[5] = {
    {"Penemu benua Amerika?", "BUKANGUE", "Bukan gue kan yang nemu?"},
    {"Tumbuhan yang hidup di padang pasir pasti?", "NANCEP", "Pasti nancep kan? Masa melayang."},
    {"Yang membagikan hadiah lewat cerobong asap saat Natal biasanya?", "MALEMMALEM", "Kalau siang mah panassss."},
    {"Dulu, ibu kota Turki ada di?", "DALAMNYA", "Pasti di dalamnya dong, masa di luar Turki."},
    {"Negara yang dulunya Uni Soviet sekarang jadi?", "RAMAI", "Udah banyak orang tuh sekarang."}
};

struct QA level3[5] = {
    {"Saudara satu ibu dan satu bapak disebut saudara?", "SENDIRI", "yaa iya saudara sendiri kan itu?"},
    {"Perhiasan wanita yang dipasang di telinga biasanya?", "ADADUA", "biasanya sih ada dua, satu dikanan, satu dikiri"},
    {"Yang selalu berkata apa adanya sesuai fakta pasti?", "MULUT", "mau bicara fakta kek mohong kek yaa yang ngomong sih mulut"},
    {"Untuk olahraga basket kita butuh bola dan...", "PEMAINNYA", "kalau gaada pemain ya gamain dong???"},
    {"Bulan yang tidak utuh, namanya bulan...", "DIKIT", "ga utuh nihh sedikit"}
};

struct QA level4[5] = {
    {"Yang setiap hari kerja di sawah namanya?", "SERING", "kalau tiap hari berarti dia sering ke sawahnya kaan"},
    {"Petugas yang membantu menggunakan sabuk pengaman dan melayani kita di pesawat disebut?", "ORANGBAIK", "loh baik ya dia mau bantuin kita..."},
    {"Untuk melihat Taj Mahal, kita bisa pergi ke...", "MARIN", "ya berangkatnya dari kemarin dong biar bisa ngelihat Taj Mahal"},
    {"Yang mengatur pertandingan sepak bola?", "WAKTU", "harus diatur tuhh biar ga kebablasan"},
    {"Dini hari tadi disebut?", "SUDAH", "yaa sudahh kelewat dongg?"}
};

struct QA level5[5] = {
    {"Hewan yang berubah warna saat bertemu musuhnya...", "BENGONG", "yaa bengong aja kalau gerak ya ketauan"},
    {"Saat membuka tabungan di bank, kita mendapatkan nomor?", "BEDABEDA", "Kalau sama semua, bank-nya pusing."},
    {"Kanguru adalah hewan yang punya kaki panjang, ekor panjang, dan punya?", "SENDIRI", "kaki sama ekornya punya dia sendiri kan?"},
    {"Orang-orang yang lahir di 22 Juni - 22 Juli berzodiak?", "SAMAAN", "zodiaknya Cancer semua tuhh"},
    {"Yang kita makan saat sarapan, biasanya...", "RAIB", "Raib dong..kan dimakan"}
};

// ==== LOGIKA GAME ====

int mainLevel(int nomorLevel, struct QA soalLevel[], int jumlahSoal, int *totalPoin, int startSoal) {
    int i = startSoal - 1;
    int poinAwalLevel = *totalPoin;

    if (i < 0 || i >= jumlahSoal) i = 0;

    while (i < jumlahSoal) {
        int jumlahSalah = 0;
        int poinSoal = 5; 
        char jawabanUser[200];
        int tipeClue = (nomorLevel <= 2) ? 1 : 2;

        while (jumlahSalah < 3) {
            bersihinLayar();
            printf("=== LEVEL %d - SOAL %d ===\n\n", nomorLevel, i + 1);
            printf("Pertanyaan: %s\n", soalLevel[i].question);
            tampilKotakJawabanDenganClue(soalLevel[i].answer, tipeClue);
            printf("\nTotal Poin: %d\n", *totalPoin);
            printf("Jawab (KAPITAL): ");
            inputKalimat(jawabanUser, 200);

            if (bandingkanString(jawabanUser, soalLevel[i].answer) == 1) {
                *totalPoin += poinSoal;
                printf("\nYEEE BENERR! %s\n", soalLevel[i].comment);
                printf("Poin didapat: +%d\n", poinSoal);
                tekanEnter();
                break; 
            } else {
                jumlahSalah++;
                if (nomorLevel >= 3) {
                    if (poinSoal > 2) poinSoal--; 
                }
                
                if (jumlahSalah < 3) {
                    printf("Salah... coba lagi (%d/3)\n", jumlahSalah);
                    tekanEnter();
                }
            }
        }

        if (jumlahSalah >= 3) {
            if (nomorLevel <= 2) {
                printf("\nSALAH 3x! Kamu harus ulang dari SOAL NOMOR 1 di LEVEL %d.\n", nomorLevel);
                printf("Poin level ini di-reset ke awal.\n");
                *totalPoin = poinAwalLevel;
                tekanEnter();
                i = 0; 
                continue; 
            } else {
                printf("\nUdah 3x salah nih. Jawaban benernya: %s\n", soalLevel[i].answer);
                *totalPoin += poinSoal; 
                tekanEnter();
            }
        }

        bersihinLayar();
        printf("------------------------------------\n");
        printf("total poin kamu segini nih: %d!\n", *totalPoin);
        printf("------------------------------------\n");
        printf("\n1. Lanjut ke Soal Berikutnya\n2. Simpan & Exit Ke Menu\nPilih: ");
        
        if (inputAngka() == 2) {
            return (i + 1); 
        }
        i++;
    }

    tampilHasilTTS(nomorLevel, *totalPoin);
    tekanEnter();
    return 100; 
}

void mainGame(int idx) {
    while (dataAkun[idx].levelTerakhir <= 5) {
        struct QA *paket;
        if (dataAkun[idx].levelTerakhir == 1) paket = level1;
        else if (dataAkun[idx].levelTerakhir == 2) paket = level2;
        else if (dataAkun[idx].levelTerakhir == 3) paket = level3;
        else if (dataAkun[idx].levelTerakhir == 4) paket = level4;
        else paket = level5;

        int hasil = mainLevel(dataAkun[idx].levelTerakhir, paket, 5, &dataAkun[idx].score, dataAkun[idx].soalTerakhir);
        
        if (hasil != 100) { 
            dataAkun[idx].soalTerakhir = hasil;
            simpanSemuaUser();
            return;
        }

        dataAkun[idx].levelTerakhir++;
        dataAkun[idx].soalTerakhir = 1;
        simpanSemuaUser();
    }
    
    // ==== SERTIFIKAT PENGHARGAAN ====
    bersihinLayar();
    printf("========================================================\n");
    printf("||                                                    ||\n");
    printf("||              SERTIFIKAT PENGHARGAAN                ||\n");
    printf("||                                                    ||\n");
    printf("||  Diberikan Kepada : %-30s ||\n", dataAkun[idx].username);
    printf("||  Total skor       : %-30d ||\n", dataAkun[idx].score);
    printf("||                                                    ||\n");
    printf("||  Atas keniatannya sudah mau bermain game           ||\n");
    printf("||  teka teki sotoy                                   ||\n");
    printf("||                                                    ||\n");
    printf("========================================================\n");
    tekanEnter();
}

// ==== MAIN MENU ====

int main() {
    loadUser();
    while (1) {
        bersihinLayar();
        printf("=========================\n");
        printf(" TEKA TEKI SOTOY (TTS)\n");
        printf("=========================\n");
        printf("1. Register\n2. Login\n3. Exit\nPilih: ");
        int pil = inputAngka();

        if (pil == 1) {
            char nama[40];
            printf("Username (KAPITAL): ");
            inputKalimat(nama, 40);
            if (cariUser(nama) == -1 && jumlahAkun < MAX_USERS) {
                int i;
                for(i=0; i<40; i++) dataAkun[jumlahAkun].username[i] = nama[i];
                dataAkun[jumlahAkun].score = 0;
                dataAkun[jumlahAkun].levelTerakhir = 1;
                dataAkun[jumlahAkun].soalTerakhir = 1;
                jumlahAkun++;
                simpanSemuaUser();
                printf("Berhasil daftar!\n");
            } else printf("Gagal daftar/Username sudah ada.\n");
            tekanEnter();
        } else if (pil == 2) {
            char nama[40];
            printf("Username: ");
            inputKalimat(nama, 40);
            int idx = cariUser(nama);
            if (idx != -1) mainGame(idx);
            else { printf("User tidak ditemukan.\n"); tekanEnter(); }
        } else if (pil == 3) break;
    }
    return 0;
}
