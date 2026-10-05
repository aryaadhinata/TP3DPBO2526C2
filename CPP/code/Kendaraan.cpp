#pragma once
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Enums.cpp"
#include "MasalahKendaraan.cpp"

// Merepresentasikan kendaraan dan menyimpan masalah yang menjadi bagiannya.
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
    Kendaraan(std::string brand, std::string tipe, JenisKendaraan jenis,
                int tahun, std::string asal)
        : Brand(std::move(brand)), Tipe(std::move(tipe)), Jenis(jenis),
            TahunPembuatan(tahun), AsalProdusen(std::move(asal)) {}

    JenisKendaraan getJenis() const { return Jenis; }
    std::vector<MasalahKendaraan>& getDaftarMasalah() { return DaftarMasalah; }
    const std::vector<MasalahKendaraan>& getDaftarMasalah() const { return DaftarMasalah; }

    void tambahMasalah(MasalahKendaraan masalah) {
        DaftarMasalah.push_back(std::move(masalah));
    }

    std::string getDetailKendaraan() const {
        std::ostringstream os;
        os << Brand << " " << Tipe << " [" << toString(Jenis) << "] - "
            << TahunPembuatan << " - Produsen: " << AsalProdusen
            << " - Jumlah masalah: " << DaftarMasalah.size();
        return os.str();
    }
};
