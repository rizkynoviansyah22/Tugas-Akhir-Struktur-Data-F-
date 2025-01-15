#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct KTP {
    string nama;
    string nik;
    string alamat;
};

struct Barang {
    string kodeItem;
    string tanggalMasuk;
};

struct Pembeli {
    string nik;
    string waktuKedatangan;
    string kodeItem;
};

void tambahDataKTP() {
    ofstream file("data_ktp.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    KTP ktp;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, ktp.nama);
    cout << "Masukkan NIK: ";
    cin >> ktp.nik;
    cout << "Masukkan Alamat: ";
    cin.ignore();
    getline(cin, ktp.alamat);

    file << ktp.nama << "," << ktp.nik << "," << ktp.alamat << endl;
    file.close();
    cout << "Data KTP berhasil ditambahkan!\n";
}

void cetakDaftarBarang(stack<Barang> lifoBarang) {
    cout << "Daftar Barang di Gudang (LIFO):\n";
    cout << "+------------------------+\n"; 
    cout << "| Kode  | Tanggal Masuk  |\n"; 
    cout << "+------------------------+\n";
    while (!lifoBarang.empty()) {
        Barang b = lifoBarang.top();
        cout << "| " << b.kodeItem << " | " << b.tanggalMasuk << "     |\n";
        lifoBarang.pop();
    }
    cout << "+------------------------+\n";
}

void cetakDaftarPembeli(queue<Pembeli> fifoPembeli) {
    cout << "Daftar Pembeli:\n";
    cout << "+------------------------+\n";
    cout << "| NIK     | Waktu Datang | Kode Item |\n";
    cout << "+------------------------+\n";
    while (!fifoPembeli.empty()) {
        Pembeli p = fifoPembeli.front();
        fifoPembeli.pop();
        cout << "| " << p.nik << " | " << p.waktuKedatangan << " | " << p.kodeItem << " |\n";
    }
    cout << "+------------------------+\n";
}

int main() {
    stack<Barang> lifoBarang;      // LIFO
    queue<Pembeli> fifoPembeli;   //  FIFO
    int pilihan;

    do {
        cout << "\n=== Menu Program ===\n";
        cout << "1. Admin Sign In\n";
        cout << "2. Entri Item Barang\n";
        cout << "3. Catat Pembeli\n";
        cout << "4. Jual Item Barang\n";
        cout << "5. Cetak Daftar Barang\n";
        cout << "6. Cetak Daftar Pembeli\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            tambahDataKTP();
            break;
        }
        case 2: {
            Barang barang;
            cout << "Masukkan Kode Item: ";
            cin >> barang.kodeItem;
            cout << "Masukkan Tanggal Masuk (YYYY-MM-DD): ";
            cin >> barang.tanggalMasuk;
            lifoBarang.push(barang);
            cout << "Barang berhasil ditambahkan!\n";
            break;
        }
        case 3: {
            Pembeli pembeli;
            cout << "Masukkan NIK Pembeli: ";
            cin >> pembeli.nik;
            cout << "Masukkan Waktu Kedatangan (HH:MM): ";
            cin >> pembeli.waktuKedatangan;
            cout << "Masukkan Kode Item Barang: ";
            cin >> pembeli.kodeItem;
            fifoPembeli.push(pembeli);
            cout << "Pembeli berhasil dicatat!\n";
            break;
        }
        case 4: {
            if (!fifoPembeli.empty() && !lifoBarang.empty()) {
                Pembeli pembeli = fifoPembeli.front();
                fifoPembeli.pop();

                Barang barang = lifoBarang.top();
                lifoBarang.pop();

                cout << "Barang " << barang.kodeItem << " dijual kepada pembeli dengan NIK " << pembeli.nik << endl;
            } else {
                cout << "Data pembeli atau barang kosong!\n";
            }
            break;
        }
        case 5: {
            cetakDaftarBarang(lifoBarang);
            break;
        }
        case 6: {
            cetakDaftarPembeli(fifoPembeli);
            break;
        }
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}

