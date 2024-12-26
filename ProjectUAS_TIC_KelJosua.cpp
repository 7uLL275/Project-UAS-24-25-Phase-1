#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct DataDiri {
    string nama;
    int umur, nomorKursi;
};

struct Film {
    string judul;
    int harga;
};

struct Snack {
    string namaSnack;
    int harga;
};

// Daftar film
const Film daftarFilm[] = {
    {"Avengers: Endgame", 50000},
    {"Spider-Man: No Way Home", 50000},
    {"The Batman", 50000},
    {"Joker", 50000},
    {"Pee Maak", 50000},
    {"Sekawan Limo", 35000},
    {"Agak Laen", 35000}
};
const int jumlahFilm = sizeof(daftarFilm) / sizeof(daftarFilm[0]);

const Snack daftarSnack[] = {
    {"Popcorn Karamel", 30000},
    {"Popcorn Keju", 20000},
    {"Pop Mie", 15000},
    {"Teh Pucuk", 10000},
    {"Le Mineral", 5000}
};
const int jumlahSnack = sizeof(daftarSnack) / sizeof(daftarSnack[0]);

vector<bool> kursiTerisi(30, false); 
vector<bool> kursiVIP(10, false);    

void simpanDataTransaksi(const string& nama, int umur, int nomorKursi, const string& judulFilm,
                         int hargaFilm, bool isVIP, Snack* snackPilihan, int jumlahSnackDipilih, const string& lokasi) {
    ofstream file("tiketbioskop.txt", ios::app);
    if (file.is_open()) {
        file << "============================" << endl;
        file << "Lokasi Bioskop: " << lokasi << endl;
        file << "Judul Film: " << judulFilm << ", Harga: Rp" << hargaFilm << endl;
        file << "Nama: " << nama << ", Umur: " << umur << ", Nomor Kursi: " << nomorKursi;
        file << (isVIP ? " (VIP)" : " (Reguler)") << endl;

        file << "Snack yang dibeli: " << endl;
        for (int i = 0; i < jumlahSnackDipilih; ++i) {
            file << "- " << snackPilihan[i].namaSnack << " (Rp" << snackPilihan[i].harga << ")" << endl;
        }
        file << "============================" << endl;
        file.close();
        cout << "Data telah disimpan ke tiketbioskop.txt." << endl;
    } else {
        cout << "Gagal menyimpan data." << endl;
    }
}

void tampilkanDaftarFilm() {
    cout << "===============================" << endl;
    cout << "       DAFTAR FILM BIOSKOP     " << endl;
    cout << "===============================" << endl;
    for (int i = 0; i < jumlahFilm; ++i) {
        cout << i + 1 << ". " << daftarFilm[i].judul << " - Harga: Rp" << daftarFilm[i].harga << endl;
    }
}

// Fungsi untuk menampilkan daftar snack
void tampilkanDaftarSnack() {
    cout << "===============================" << endl;
    cout << "          DAFTAR SNACK         " << endl;
    cout << "===============================" << endl;
    for (int i = 0; i < jumlahSnack; ++i) {
        cout << i + 1 << ". " << daftarSnack[i].namaSnack << " - Harga: Rp" << daftarSnack[i].harga << endl;
    }
}

Snack* pilihSnack(int& jumlahSnackDipilih) {
    tampilkanDaftarSnack();

    cout << "Berapa snack yang ingin Anda beli? ";
    cin >> jumlahSnackDipilih;

    if (jumlahSnackDipilih <= 0) {
        cout << "Anda tidak membeli snack." << endl;
        return nullptr;
    }

    Snack* snackPilihan = new Snack[jumlahSnackDipilih];
    for (int i = 0; i < jumlahSnackDipilih; ++i) {
        int pilihanSnack;
        cout << "Pilih snack ke-" << i + 1 << " (1-" << jumlahSnack << "): ";
        cin >> pilihanSnack;

        if (pilihanSnack < 1 || pilihanSnack > jumlahSnack) {
            cout << "Pilihan tidak valid. Snack ke-" << i + 1 << " tidak akan dimasukkan." << endl;
            --i; 
        } else {
            snackPilihan[i] = daftarSnack[pilihanSnack - 1];
        }
        
    }

    return snackPilihan;
}

int hitungTotalHarga(Snack* snackPilihan, int jumlahSnackDipilih, int hargaKursi, int index = 0) {
    if (index == jumlahSnackDipilih) {
        return hargaKursi;
    }
    return snackPilihan[index].harga + hitungTotalHarga(snackPilihan, jumlahSnackDipilih, hargaKursi, index + 1);
}

void pilihKursi(const string& nama, int umur, const string& judulFilm, int &hargaFilm, const string& lokasi) {
    cout << "===============================" << endl;
    cout << "   PILIH JENIS KURSI (1-2)    " << endl;
    cout << "===============================" << endl;
    cout << "1. Reguler" << endl;
    cout << "2. VIP (Tambahan Rp20000)" << endl;

    int jenisKursi;
    cout << "Pilihan: ";
    cin >> jenisKursi;

    int nomorKursi;
    bool isVIP = false;

    if (jenisKursi == 1) {
        cout << "Kursi Reguler yang tersedia: ";
        for (int i = 0; i < 30; ++i) {
            if (!kursiTerisi[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;

        cout << "Pilih nomor kursi (1-30): ";
        cin >> nomorKursi;

        if (nomorKursi < 1 || nomorKursi > 30 || kursiTerisi[nomorKursi - 1]) {
            cout << "Nomor kursi tidak valid atau sudah terisi. Silakan coba lagi." << endl;
            return;
        }

        kursiTerisi[nomorKursi - 1] = true; 
        cout << "Kursi nomor " << nomorKursi << " berhasil dipesan." << endl;
    } 
    else if (jenisKursi == 2) {
        cout << "Kursi VIP yang tersedia: ";
        for (int i = 0; i < 10; ++i) {
            if (!kursiVIP[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;

        cout << "Pilih nomor kursi VIP (1-10): ";
        cin >> nomorKursi;

        if (nomorKursi < 1 || nomorKursi > 10 || kursiVIP[nomorKursi - 1]) {
            cout << "Nomor kursi tidak valid atau sudah terisi. Silakan coba lagi." << endl;
            return;
        }

        kursiVIP[nomorKursi - 1] = true; 
        isVIP = true;
        cout << "Kursi VIP nomor " << nomorKursi << " berhasil dipesan." << endl;
        hargaFilm += 20000; 
    } else {
        cout << "Pilihan jenis kursi tidak valid. Silakan coba lagi." << endl;
        return;
    }

    int jumlahSnackDipilih;
    Snack* snackPilihan = pilihSnack(jumlahSnackDipilih);

    int totalHarga = hitungTotalHarga(snackPilihan, jumlahSnackDipilih, hargaFilm);
    cout << "Total harga yang harus dibayar: Rp" << totalHarga << endl;

    simpanDataTransaksi(nama, umur, nomorKursi, judulFilm, hargaFilm, isVIP, snackPilihan, jumlahSnackDipilih, lokasi);
    delete[] snackPilihan; 
}

void pilihFilm(const string& lokasi) {
    tampilkanDaftarFilm();

    int pilihanFilm;
    cout << "\nPilih film yang ingin Anda tonton (1-" << jumlahFilm << "): ";
    cin >> pilihanFilm;

    if (pilihanFilm < 1 || pilihanFilm > jumlahFilm) {
        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        return;
    }

    Film filmTerpilih = daftarFilm[pilihanFilm - 1];
    cout << "\nAnda telah memilih film: " << filmTerpilih.judul << endl;
    cout << "Harga tiket: Rp" << filmTerpilih.harga << endl;

    string nama;
    int umur;
    cout << "Masukkan nama Anda: ";
    cin >> nama;
    cout << "Masukkan umur Anda: ";
    cin >> umur;
    cout << endl;

    if (umur < 18){
        cout << "=================================" << endl;
        cout << "Harus didampingi kedua orang tua!" << endl;
        cout << "=================================" << endl;
        return;
    }else{
        pilihKursi(nama, umur, filmTerpilih.judul, filmTerpilih.harga, lokasi);
    }
}

void bioskopMenu(const string& namaBioskop) {
    while (true) {
        cout << "=================================================" << endl;
        cout << "  ---BIOSKOP YANG DIPILIH: " << namaBioskop << "---" << endl;
        cout << "=================================================" << endl;

        int pilihanMenu;
        cout << "Pilih menu berikut: " << endl;
        cout << "1. Pilih film" << endl;
        cout << "2. Kembali ke menu utama" << endl;
        cout << endl;

        cout << "Pilihanmu: ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1:
                pilihFilm(namaBioskop);
                break;
            case 2:
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        cout << endl;
    }
}

void menuAwal() {
    while (true) {
        cout << endl;
        cout << "===============================================" << endl;
        cout << "   SELAMAT DATANG DI PEMBELIAN TIKET BIOSKOP   " << endl;
        cout << "===============================================" << endl;
        cout << endl;
        cout << "Pilih lokasi bioskop XXI yang kamu sukai di bawah ini: " << endl;
        cout << "1. Royal XXI" << endl;
        cout << "2. Pakuwon Mall XXI" << endl;
        cout << "3. Galaxy Mall XXI" << endl;
        cout << "4. Keluar" << endl;

        int pilihanTempat;
        cout << "Pilihanmu: ";
        cin >> pilihanTempat;

        switch (pilihanTempat) {
            case 1:
                bioskopMenu("Royal XXI Surabaya");
                break;
            case 2:
                bioskopMenu("Pakuwon Mall XXI");
                break;
            case 3:
                bioskopMenu("Galaxy Mall XXI Surabaya");
                break;
            case 4:
                cout << "Sampai jumpa lagi :)" << endl;
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main() {
    menuAwal();
    return 0;
}