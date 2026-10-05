#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Kendaraan.cpp"
#include "MasalahKendaraan.cpp"
#include "PegawaiBengkel.cpp"

// Pegawai teknisi yang memperbaiki kendaraan dan menyusun laporan perawatan.
class Montir : public PegawaiBengkel {
private:
    std::string Keahlian;
    std::vector<MasalahKendaraan> LaporanPerawatan;

public:
    Montir(std::string id, std::string nama, int performa,
            JenisKendaraan spesialisasi, std::string keahlian)
        : PegawaiBengkel(std::move(id), std::move(nama), performa, spesialisasi),
            Keahlian(std::move(keahlian)) {}

    void perbaikan(Kendaraan& kendaraan) {
        if (kendaraan.getJenis() != getSpesialisasi()) {
            std::cout << "  [Montir " << getNama() << "] Menolak: kendaraan "
                        << toString(kendaraan.getJenis()) << " bukan spesialisasinya ("
                        << toString(getSpesialisasi()) << ").\n";
            return;
        }
        for (auto& masalah : kendaraan.getDaftarMasalah()) {
            if (masalah.sudahDiperbaiki()) continue;
            std::cout << "  [Montir " << getNama() << "] Memperbaiki '"
                        << masalah.getNamaMasalah() << "' ("
                        << masalah.getBagianBermasalah() << ", estimasi "
                        << masalah.getEstimasiWaktu() << " jam)\n";
            masalah.updateStatusPerbaikan();
            LaporanPerawatan.push_back(masalah);
        }
    }

    std::string buatLaporan() const {
        std::ostringstream os;
        os << "LAPORAN PERAWATAN - Montir " << getNama() << " (Keahlian: "
            << Keahlian << ")\n";
        if (LaporanPerawatan.empty()) os << "  (belum ada perbaikan)\n";
        for (std::size_t i = 0; i < LaporanPerawatan.size(); ++i) {
            const auto& m = LaporanPerawatan[i];
            os << "  " << (i + 1) << ". " << m.getNamaMasalah() << " ["
                << m.getBagianBermasalah() << "] - selesai: "
                << m.getTerakhirDiperbaiki() << "\n";
        }
        return os.str();
    }

    // Performa dasar + 2 poin per perbaikan yang dilaporkan
    int hitungPerfoma() const override {
        return PegawaiBengkel::hitungPerfoma() +
               static_cast<int>(LaporanPerawatan.size()) * 2;
    }

    std::string getDetailPegawai() const override {
        std::ostringstream os;
        os << "MONTIR  " << PegawaiBengkel::getDetailPegawai()
            << " | Keahlian: " << Keahlian
            << " | Laporan: " << LaporanPerawatan.size();
        return os.str();
    }

    void tanganiKendaraan(Kendaraan& kendaraan) override { perbaikan(kendaraan); }
};
