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

/**
 * @brief Pegawai pemeriksa yang mencatat masalah sesuai fokusnya.
 *
 * Pemeriksaan hanya berlaku pada kategori kendaraan yang menjadi spesialisasi.
 * Fokus kosong berarti seluruh bagian diperiksa; daftar temuan diurutkan
 * berdasarkan estimasi waktu terlama sebagai prioritas tertinggi.
 */
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
    /**
     * @brief Membuat Mekanik dengan spesialisasi dan daftar fokus.
     * @param id Identitas pegawai.
     * @param nama Nama Mekanik.
     * @param performa Performa dasar dalam bulan.
     * @param spesialisasi Kategori kendaraan yang dapat diperiksa.
     * @param fokus Bagian kendaraan yang diperiksa; kosong berarti semua bagian.
     */
    Mekanik(std::string id, std::string nama, int performa,
            JenisKendaraan spesialisasi, std::vector<FokusBagian> fokus)
        : PegawaiBengkel(std::move(id), std::move(nama), performa, spesialisasi),
            FokusPemeriksaan(std::move(fokus)) {}

    /**
     * @brief Memeriksa kendaraan dan mencatat masalah yang sesuai fokus.
     * @param kendaraan Kendaraan yang akan diperiksa.
     *
     * Temuan disimpan sebagai salinan agar status saat pemeriksaan tetap
     * tercatat walaupun status masalah kendaraan berubah setelahnya.
     */
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

    /// Mengurutkan temuan dengan estimasi waktu terlama sebagai prioritas.
    void updatePemeriksaan() {
        std::stable_sort(DaftarPemeriksaan.begin(), DaftarPemeriksaan.end(),
                        [](const MasalahKendaraan& a, const MasalahKendaraan& b) {
                            return a.getEstimasiWaktu() > b.getEstimasiWaktu();
                        });
    }

    /// @return Daftar temuan pemeriksaan yang telah diurutkan berdasarkan durasi.
    const std::vector<MasalahKendaraan>& getDaftarPemeriksaan() const {
        return DaftarPemeriksaan;
    }

    /// @return Performa dasar ditambah satu poin untuk setiap temuan.
    int hitungPerfoma() const override {
        return PegawaiBengkel::hitungPerfoma() +
                static_cast<int>(DaftarPemeriksaan.size());
    }

    /// @return Detail pegawai beserta fokus dan jumlah temuan pemeriksaan.
    std::string getDetailPegawai() const override {
        std::ostringstream os;
        os << "MEKANIK " << PegawaiBengkel::getDetailPegawai() << " | Fokus: ";
        for (std::size_t i = 0; i < FokusPemeriksaan.size(); ++i)
            os << (i ? ", " : "") << toString(FokusPemeriksaan[i]);
        os << " | Temuan: " << DaftarPemeriksaan.size();
        return os.str();
    }

    /// Meneruskan dispatch polimorfik ke operasi pemeriksaan Mekanik.
    void tanganiKendaraan(Kendaraan& kendaraan) override { periksaKendaraan(kendaraan); }
};
