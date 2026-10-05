#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Kendaraan.cpp"
#include "MasalahKendaraan.cpp"
#include "PegawaiBengkel.cpp"

// Pegawai pemeriksa yang mencatat masalah sesuai spesialisasi dan fokusnya.
class Mekanik : public PegawaiBengkel {
private:
    std::vector<MasalahKendaraan> DaftarPemeriksaan;
    std::vector<FokusBagian> FokusPemeriksaan;

    bool sesuaiFokus(const MasalahKendaraan& m) const {
        if (FokusPemeriksaan.empty()) return true; // tanpa fokus = periksa semua
        return std::any_of(FokusPemeriksaan.begin(), FokusPemeriksaan.end(),
                            [&](FokusBagian f) {
                                return toString(f) == m.getBagianBermasalah();
                            });
    }

public:
    Mekanik(std::string id, std::string nama, int performa,
            JenisKendaraan spesialisasi, std::vector<FokusBagian> fokus)
        : PegawaiBengkel(std::move(id), std::move(nama), performa, spesialisasi),
            FokusPemeriksaan(std::move(fokus)) {}

    void periksaKendaraan(const Kendaraan& kendaraan) {
        if (kendaraan.getJenis() != getSpesialisasi()) {
            std::cout << "  [Mekanik " << getNama() << "] Menolak: kendaraan "
                        << toString(kendaraan.getJenis()) << " bukan spesialisasinya ("
                        << toString(getSpesialisasi()) << ").\n";
            return;
        }

        std::cout << "  [Mekanik " << getNama() << "] Memeriksa "
                    << kendaraan.getDetailKendaraan() << "\n";
        for (const auto& masalah : kendaraan.getDaftarMasalah()) {
            if (!sesuaiFokus(masalah)) {
                std::cout << "    - Dilewati (di luar fokus): "
                            << masalah.getNamaMasalah() << " ["
                            << masalah.getBagianBermasalah() << "]\n";
                continue;
            }
            std::cout << "    - Dicatat: " << masalah.getNamaMasalah() << " ["
                        << masalah.getBagianBermasalah() << "] status: "
                        << (masalah.sudahDiperbaiki() ? "SUDAH diperbaiki"
                                                    : "BELUM diperbaiki") << "\n";
            DaftarPemeriksaan.push_back(masalah);
        }
        updatePemeriksaan();
    }

    // Estimasi waktu terlama = prioritas tertinggi
    void updatePemeriksaan() {
        std::stable_sort(DaftarPemeriksaan.begin(), DaftarPemeriksaan.end(),
                        [](const MasalahKendaraan& a, const MasalahKendaraan& b) {
                            return a.getEstimasiWaktu() > b.getEstimasiWaktu();
                        });
    }

    const std::vector<MasalahKendaraan>& getDaftarPemeriksaan() const {
        return DaftarPemeriksaan;
    }

    // Performa dasar + 1 poin per temuan pemeriksaan
    int hitungPerfoma() const override {
        return PegawaiBengkel::hitungPerfoma() +
                static_cast<int>(DaftarPemeriksaan.size());
    }

    std::string getDetailPegawai() const override {
        std::ostringstream os;
        os << "MEKANIK " << PegawaiBengkel::getDetailPegawai() << " | Fokus: ";
        for (std::size_t i = 0; i < FokusPemeriksaan.size(); ++i)
            os << (i ? ", " : "") << toString(FokusPemeriksaan[i]);
        os << " | Temuan: " << DaftarPemeriksaan.size();
        return os.str();
    }

    void tanganiKendaraan(Kendaraan& kendaraan) override { periksaKendaraan(kendaraan); }
};
