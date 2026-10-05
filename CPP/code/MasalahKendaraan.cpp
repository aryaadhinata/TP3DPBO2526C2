#pragma once
#include <ctime>
#include <string>
#include <utility>

// Menyimpan kondisi perbaikan, lokasi masalah, dan estimasi waktu layanan.
class MasalahKendaraan {
private:
    std::string NamaMasalah;
    std::string BagianBermasalah;   // nama FokusBagian, mis. "REM"
    std::string TerakhirDiperbaiki; // "-" = belum pernah diperbaiki

    static std::string waktuSekarang() {
        std::time_t t = std::time(nullptr);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&t));
        return buf;
    }

public:
    MasalahKendaraan(std::string nama, std::string bagian)
        : NamaMasalah(std::move(nama)), BagianBermasalah(std::move(bagian)),
            TerakhirDiperbaiki("-") {}

    const std::string& getNamaMasalah() const { return NamaMasalah; }
    const std::string& getBagianBermasalah() const { return BagianBermasalah; }
    const std::string& getTerakhirDiperbaiki() const { return TerakhirDiperbaiki; }
    bool sudahDiperbaiki() const { return TerakhirDiperbaiki != "-"; }

    void updateStatusPerbaikan() { TerakhirDiperbaiki = waktuSekarang(); }

    // Estimasi waktu perbaikan (jam) berdasarkan bagian yang bermasalah
    int getEstimasiWaktu() const {
        if (BagianBermasalah == "MESIN")             return 8;
        if (BagianBermasalah == "TRANSMISI")         return 6;
        if (BagianBermasalah == "RANGKA_CHASIS")     return 10;
        if (BagianBermasalah == "SUSPENSI_KEMUDI")   return 5;
        if (BagianBermasalah == "SISTEM_PENDINGIN")  return 4;
        if (BagianBermasalah == "KELISTRIKAN")       return 4;
        if (BagianBermasalah == "SISTEM_PEMBUANGAN") return 3;
        if (BagianBermasalah == "BODY_EKSTERIOR")    return 6;
        if (BagianBermasalah == "INTERIOR_AC")       return 3;
        if (BagianBermasalah == "REM")               return 2;
        if (BagianBermasalah == "RODA_BAN")          return 1;
        return 3;
    }
};
