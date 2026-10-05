#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Bengkel.cpp"
#include "Mekanik.cpp"
#include "Montir.cpp"

using namespace std;

static const vector<FokusBagian>& daftarFokus() {
    static const vector<FokusBagian> fokus = {
        FokusBagian::MESIN, FokusBagian::TRANSMISI, FokusBagian::REM,
        FokusBagian::SUSPENSI_KEMUDI, FokusBagian::KELISTRIKAN,
        FokusBagian::SISTEM_PENDINGIN, FokusBagian::SISTEM_PEMBUANGAN,
        FokusBagian::RANGKA_CHASIS, FokusBagian::BODY_EKSTERIOR,
        FokusBagian::INTERIOR_AC, FokusBagian::RODA_BAN
    };
    return fokus;
}

static bool bacaTeks(const string& prompt, string& hasil) {
    while (true) {
        cout << prompt;
        if (!getline(cin, hasil)) return false;
        if (!hasil.empty()) return true;
        cout << "Input tidak boleh kosong.\n";
    }
}

static bool bacaAngka(const string& prompt, int minimum, int maksimum, int& hasil) {
    string input;
    while (true) {
        cout << prompt;
        if (!getline(cin, input)) return false;

        stringstream parser(input);
        char sisa;
        if ((parser >> hasil) && !(parser >> sisa) &&
            hasil >= minimum && hasil <= maksimum) {
            return true;
        }
        cout << "Masukkan angka antara " << minimum << " dan " << maksimum << ".\n";
    }
}

static bool bacaJenisKendaraan(JenisKendaraan& jenis) {
    int pilihan;
    cout << "Jenis kendaraan:\n1. Mobil\n2. Motor\n";
    if (!bacaAngka("Pilih jenis: ", 1, 2, pilihan)) return false;
    jenis = pilihan == 1 ? JenisKendaraan::MOBIL : JenisKendaraan::MOTOR;
    return true;
}

static bool bacaFokus(FokusBagian& fokus) {
    const auto& pilihanFokus = daftarFokus();
    cout << "Bagian bermasalah:\n";
    for (size_t i = 0; i < pilihanFokus.size(); ++i) {
        cout << i + 1 << ". " << toString(pilihanFokus[i]) << "\n";
    }

    int pilihan;
    if (!bacaAngka("Pilih bagian: ", 1, static_cast<int>(pilihanFokus.size()), pilihan))
        return false;
    fokus = pilihanFokus[static_cast<size_t>(pilihan - 1)];
    return true;
}

static bool tambahPegawai(Bengkel& bengkel) {
    int jenisPegawai;
    cout << "\nJenis pegawai:\n1. Montir\n2. Mekanik\n";
    if (!bacaAngka("Pilih jenis pegawai: ", 1, 2, jenisPegawai)) return false;

    string id, nama;
    int performa;
    JenisKendaraan spesialisasi;
    if (!bacaTeks("ID pegawai: ", id) ||
        !bacaTeks("Nama pegawai: ", nama) ||
        !bacaAngka("Performa (bulan): ", 0, 1000000, performa) ||
        !bacaJenisKendaraan(spesialisasi)) {
        return false;
    }

    if (jenisPegawai == 1) {
        string keahlian;
        if (!bacaTeks("Keahlian montir: ", keahlian)) return false;
        bengkel.tambahPegawai(make_unique<Montir>(
            id, nama, performa, spesialisasi, keahlian));
    } else {
        int jumlahFokus;
        if (!bacaAngka("Jumlah fokus mekanik (0 untuk semua bagian): ",
                       0, static_cast<int>(daftarFokus().size()), jumlahFokus)) {
            return false;
        }

        vector<FokusBagian> fokus;
        for (int i = 0; i < jumlahFokus; ++i) {
            FokusBagian bagian;
            if (!bacaFokus(bagian)) return false;
            fokus.push_back(bagian);
        }
        bengkel.tambahPegawai(make_unique<Mekanik>(
            id, nama, performa, spesialisasi, fokus));
    }

    cout << "Pegawai berhasil ditambahkan.\n";
    return true;
}

static bool tambahKendaraan(Bengkel& bengkel) {
    if (bengkel.kapasitasPenuh()) {
        cout << "Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.\n";
        return true;
    }

    string brand, tipe, asal;
    int tahun, jumlahMasalah;
    JenisKendaraan jenis;
    if (!bacaTeks("Brand kendaraan: ", brand) ||
        !bacaTeks("Tipe kendaraan: ", tipe) ||
        !bacaJenisKendaraan(jenis) ||
        !bacaAngka("Tahun pembuatan: ", 1886, 9999, tahun) ||
        !bacaTeks("Asal produsen: ", asal) ||
        !bacaAngka("Jumlah masalah: ", 0, 100, jumlahMasalah)) {
        return false;
    }

    Kendaraan kendaraan(brand, tipe, jenis, tahun, asal);
    for (int i = 0; i < jumlahMasalah; ++i) {
        string namaMasalah;
        FokusBagian bagian;
        cout << "Masalah ke-" << i + 1 << ":\n";
        if (!bacaTeks("Nama masalah: ", namaMasalah) || !bacaFokus(bagian))
            return false;
        kendaraan.tambahMasalah(
            MasalahKendaraan(namaMasalah, toString(bagian)));
    }

    if (!bengkel.terimaKendaraan(std::move(kendaraan))) {
        cout << "Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.\n";
        return true;
    }
    cout << "Kendaraan berhasil ditambahkan.\n";
    return true;
}

static bool prosesKendaraan(Bengkel& bengkel) {
    const auto& kendaraan = bengkel.getDaftarKendaraan();
    if (kendaraan.empty()) {
        cout << "Belum ada kendaraan untuk diproses.\n";
        return true;
    }

    cout << "\nPilih kendaraan yang akan diproses:\n";
    for (size_t i = 0; i < kendaraan.size(); ++i) {
        cout << i + 1 << ". " << kendaraan[i].getDetailKendaraan() << "\n";
    }

    int pilihan;
    if (!bacaAngka("Nomor kendaraan: ", 1, static_cast<int>(kendaraan.size()), pilihan))
        return false;
    bengkel.prosesKendaraan(static_cast<size_t>(pilihan - 1));
    return true;
}

static bool tambahBengkel(vector<unique_ptr<Bengkel>>& bengkelList,
                        size_t& bengkelAktif) {
    string nama;
    int kapasitas;
    if (!bacaTeks("Nama bengkel: ", nama) ||
        !bacaAngka("Kapasitas kendaraan: ", 1, 1000000, kapasitas)) {
        return false;
    }

    bengkelList.push_back(make_unique<Bengkel>(nama, kapasitas));
    bengkelAktif = bengkelList.size() - 1;
    cout << "Bengkel berhasil ditambahkan. Bengkel aktif sekarang: "
        << bengkelList[bengkelAktif]->getNamaBengkel() << "\n";
    return true;
}

static bool gantiBengkel(const vector<unique_ptr<Bengkel>>& bengkelList,
                        size_t& bengkelAktif) {
    cout << "\nDaftar bengkel:\n";
    for (size_t i = 0; i < bengkelList.size(); ++i) {
        cout << i + 1 << ". " << bengkelList[i]->getNamaBengkel()
            << (i == bengkelAktif ? " (aktif)" : "") << "\n";
    }

    int pilihan;
    if (!bacaAngka("Pilih bengkel: ", 1, static_cast<int>(bengkelList.size()), pilihan))
        return false;
    bengkelAktif = static_cast<size_t>(pilihan - 1);
    cout << "Bengkel aktif: " << bengkelList[bengkelAktif]->getNamaBengkel() << "\n";
    return true;
}

static void tampilkanLaporanMontir(const Bengkel& bengkel) {
    bool adaMontir = false;
    for (const auto& pegawai : bengkel.getDaftarPegawai()) {
        if (const auto* montir = dynamic_cast<const Montir*>(pegawai.get())) {
            cout << montir->buatLaporan();
            adaMontir = true;
        }
    }
    if (!adaMontir) cout << "Belum ada montir di bengkel ini.\n";
}

static void isiDataAwal(Bengkel& bengkel) {
    bengkel.tambahPegawai(make_unique<Montir>(
        "P-001", "Budi Santoso", 48, JenisKendaraan::MOBIL,
        "Mesin & Sistem Pendingin"));
    bengkel.tambahPegawai(make_unique<Mekanik>(
        "P-002", "Sari Wulandari", 36, JenisKendaraan::MOBIL,
        vector<FokusBagian>{FokusBagian::MESIN, FokusBagian::SISTEM_PENDINGIN,
                            FokusBagian::REM}));

    Kendaraan avanza("Toyota", "Avanza (MPV)", JenisKendaraan::MOBIL, 2018, "Jepang");
    avanza.tambahMasalah(MasalahKendaraan(
        "Radiator bocor", toString(FokusBagian::SISTEM_PENDINGIN)));
    avanza.tambahMasalah(MasalahKendaraan(
        "Kampas rem aus", toString(FokusBagian::REM)));
    avanza.tambahMasalah(MasalahKendaraan(
        "AC tidak dingin", toString(FokusBagian::INTERIOR_AC)));
    bengkel.terimaKendaraan(std::move(avanza));
}

int main() {
    vector<unique_ptr<Bengkel>> bengkelList;
    bengkelList.push_back(make_unique<Bengkel>("Bengkel Maju Jaya", 5));
    isiDataAwal(*bengkelList.front());
    size_t bengkelAktif = 0;
    int pilihan;

    while (true) {
        Bengkel& bengkel = *bengkelList[bengkelAktif];
        cout << "\n========== " << bengkel.getNamaBengkel() << " ==========\n"
            << "1. Tambah pegawai\n"
            << "2. Tambah kendaraan\n"
            << "3. Tampilkan ringkasan\n"
            << "4. Proses kendaraan\n"
            << "5. Tambah bengkel\n"
            << "6. Ganti bengkel\n"
            << "7. Tampilkan laporan montir\n"
            << "0. Keluar\n";

        if (!bacaAngka("Pilih menu: ", 0, 7, pilihan)) break;
        if (pilihan == 0) break;

        bool lanjut = true;
        switch (pilihan) {
            case 1:
                lanjut = tambahPegawai(bengkel);
                break;
            case 2:
                lanjut = tambahKendaraan(bengkel);
                break;
            case 3:
                bengkel.cetakRingkasan();
                break;
            case 4:
                lanjut = prosesKendaraan(bengkel);
                break;
            case 5:
                lanjut = tambahBengkel(bengkelList, bengkelAktif);
                break;
            case 6:
                lanjut = gantiBengkel(bengkelList, bengkelAktif);
                break;
            case 7:
                tampilkanLaporanMontir(bengkel);
                break;
        }
        if (!lanjut) break;
    }

    cout << "Program selesai.\n";
    return 0;
}
