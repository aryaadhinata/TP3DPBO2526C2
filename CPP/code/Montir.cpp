#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Kendaraan.cpp"
#include "MasalahKendaraan.cpp"
#include "PegawaiBengkel.cpp"

/**
 * @brief Pegawai teknisi yang memperbaiki masalah dan mencatat hasil kerja.
 *
 * Montir hanya memperbaiki kendaraan yang cocok dengan spesialisasinya.
 * Setiap masalah selesai disalin ke laporan perawatan sebagai catatan historis.
 */
class Montir : public PegawaiBengkel {
private:
    std::string Keahlian;
    std::vector<MasalahKendaraan> LaporanPerawatan;

public:
    /**
     * @brief Membuat Montir dengan keahlian dan spesialisasi kendaraan.
     * @param id Identitas pegawai.
     * @param nama Nama Montir.
     * @param performa Performa dasar dalam bulan.
     * @param spesialisasi Kategori kendaraan yang dapat diperbaiki.
     * @param keahlian Deskripsi keahlian teknis Montir.
     */
    Montir(std::string id, std::string nama, int performa,
            JenisKendaraan spesialisasi, std::string keahlian)
        : PegawaiBengkel(std::move(id), std::move(nama), performa, spesialisasi),
            Keahlian(std::move(keahlian)) {}

    /**
     * @brief Memperbaiki seluruh masalah yang belum selesai pada kendaraan.
     * @param kendaraan Kendaraan yang akan diperbaiki.
     *
     * Kendaraan di luar spesialisasi ditolak. Masalah yang sudah diperbaiki
     * dilewati agar tidak tercatat ulang sebagai perbaikan baru.
     */
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

    /// @return Laporan historis perbaikan Montir dalam format teks.
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

    /// @return Performa dasar ditambah dua poin untuk setiap perbaikan.
    int hitungPerfoma() const override {
        return PegawaiBengkel::hitungPerfoma() +
               static_cast<int>(LaporanPerawatan.size()) * 2;
    }

    /// @return Detail pegawai beserta keahlian dan jumlah laporan perawatan.
    std::string getDetailPegawai() const override {
        std::ostringstream os;
        os << "MONTIR  " << PegawaiBengkel::getDetailPegawai()
            << " | Keahlian: " << Keahlian
            << " | Laporan: " << LaporanPerawatan.size();
        return os.str();
    }

    /// Meneruskan dispatch polimorfik ke operasi perbaikan Montir.
    void tanganiKendaraan(Kendaraan& kendaraan) override { perbaikan(kendaraan); }
};
