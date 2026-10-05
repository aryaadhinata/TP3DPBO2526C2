#pragma once
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Enums.cpp"
#include "MasalahKendaraan.cpp"

/**
 * @brief Merepresentasikan kendaraan beserta masalah yang melekat padanya.
 *
 * DaftarMasalah dimiliki kendaraan dan disimpan berdasarkan nilai, sehingga
 * masa hidup masalah mengikuti masa hidup kendaraan (composition).
 */
class Kendaraan {
private:
    std::string Brand;
    std::string Tipe; // pickup, box, sport, dsb.
    JenisKendaraan Jenis;
    int TahunPembuatan;
    std::string AsalProdusen;
    // COMPOSITION: objek disimpan by value, lifetime dikelola Kendaraan
    std::vector<MasalahKendaraan> DaftarMasalah;

public:
    /**
     * @brief Membuat kendaraan dengan identitas dan kategori yang diberikan.
     * @param brand Merek kendaraan.
     * @param tipe Model atau tipe kendaraan.
     * @param jenis Kategori mobil atau motor.
     * @param tahun Tahun pembuatan.
     * @param asal Negara asal produsen.
     */
    Kendaraan(std::string brand, std::string tipe, JenisKendaraan jenis,
                int tahun, std::string asal)
        : Brand(std::move(brand)), Tipe(std::move(tipe)), Jenis(jenis),
            TahunPembuatan(tahun), AsalProdusen(std::move(asal)) {}

    /// @return Kategori kendaraan untuk validasi spesialisasi pegawai.
    JenisKendaraan getJenis() const { return Jenis; }

    /// @return Daftar masalah yang dapat diperbarui selama kendaraan ditangani.
    std::vector<MasalahKendaraan>& getDaftarMasalah() { return DaftarMasalah; }

    /// @return Tampilan baca-saja untuk seluruh masalah kendaraan.
    const std::vector<MasalahKendaraan>& getDaftarMasalah() const { return DaftarMasalah; }

    /// Menambahkan masalah yang menjadi bagian dari kendaraan ini.
    void tambahMasalah(MasalahKendaraan masalah) {
        DaftarMasalah.push_back(std::move(masalah));
    }

    /// @return Ringkasan identitas kendaraan dan jumlah masalahnya.
    std::string getDetailKendaraan() const {
        std::ostringstream os;
        os << Brand << " " << Tipe << " [" << toString(Jenis) << "] - "
            << TahunPembuatan << " - Produsen: " << AsalProdusen
            << " - Jumlah masalah: " << DaftarMasalah.size();
        return os.str();
    }
};
