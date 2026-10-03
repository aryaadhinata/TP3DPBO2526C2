#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Bengkel.cpp"
#include "Mekanik.cpp"
#include "Montir.cpp"

using namespace std;

static void garis(const string& judul) {
    cout << "\n==================== " << judul << " ====================\n";
}

int main() {
    // 1. Membuat 1 Bengkel
    garis("1. MEMBUAT BENGKEL");
    Bengkel bengkel("Bengkel Maju Jaya", 5);
    cout << "Bengkel 'Bengkel Maju Jaya' dibuat (kapasitas 5).\n";

    // 2. Merekrut Montir & Mekanik lewat polimorfisme
    garis("2. MEREKRUT PEGAWAI (POLIMORFISME)");
    auto montir = make_unique<Montir>("P-001", "Budi Santoso", 48,
                                        JenisKendaraan::MOBIL,
                                        "Mesin & Sistem Pendingin");
    auto mekanik = make_unique<Mekanik>(
        "P-002", "Sari Wulandari", 36, JenisKendaraan::MOBIL,
        vector<FokusBagian>{FokusBagian::MESIN, FokusBagian::SISTEM_PENDINGIN,
                            FokusBagian::REM});
    bengkel.tambahPegawai(move(montir));
    bengkel.tambahPegawai(move(mekanik));
    for (const auto& p : bengkel.getDaftarPegawai())
        cout << "Direkrut: " << p->getDetailPegawai() << "\n";

    // 3. Kendaraan dengan >= 2 MasalahKendaraan (COMPOSITION)
    garis("3. MEMBUAT KENDARAAN + MASALAH (COMPOSITION)");
    Kendaraan avanza("Toyota", "Avanza (MPV)", JenisKendaraan::MOBIL, 2018, "Jepang");
    avanza.tambahMasalah(MasalahKendaraan("Radiator bocor", toString(FokusBagian::SISTEM_PENDINGIN)));
    avanza.tambahMasalah(MasalahKendaraan("Kampas rem aus", toString(FokusBagian::REM)));
    avanza.tambahMasalah(MasalahKendaraan("AC tidak dingin", toString(FokusBagian::INTERIOR_AC)));
    cout << avanza.getDetailKendaraan() << "\n";

    // 4. Bengkel menerima Kendaraan, ditangani pegawai
    garis("4. KENDARAAN DITERIMA & DITANGANI");
    if (bengkel.terimaKendaraan(move(avanza))) {
        cout << "Kendaraan diterima oleh bengkel.\n\n";
        bengkel.prosesKendaraan(0);
    } else {
        cout << "Kendaraan ditolak: bengkel penuh.\n";
    }

    // 5. Bukti data tersimpan di Array of Object
    garis("5. DATA TERSIMPAN DI ARRAY OF OBJECT");
    bengkel.cetakRingkasan();

    garis("LAPORAN MONTIR");
    for (const auto& p : bengkel.getDaftarPegawai())
        if (auto* m = dynamic_cast<Montir*>(p.get())) cout << m->buatLaporan();

    cout << "\nSimulasi selesai.\n";
    return 0;
}
