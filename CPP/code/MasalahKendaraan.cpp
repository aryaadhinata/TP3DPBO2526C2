#pragma once
#include <ctime>
#include <string>
#include <utility>

/**
 * @brief Menyimpan deskripsi masalah, bagian terkait, dan status perbaikannya.
 *
 * Bagian bermasalah menggunakan nama FokusBagian agar dapat dicocokkan dengan
 * fokus Mekanik. Tanda "-" pada waktu berarti masalah belum diperbaiki.
 */
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
    /**
     * @brief Membuat masalah baru dengan status belum diperbaiki.
     * @param nama Deskripsi masalah yang dilaporkan.
     * @param bagian Nama bagian kendaraan yang bermasalah.
     */
    MasalahKendaraan(std::string nama, std::string bagian)
        : NamaMasalah(std::move(nama)), BagianBermasalah(std::move(bagian)),
            TerakhirDiperbaiki("-") {}

    /// @return Deskripsi masalah.
    const std::string& getNamaMasalah() const { return NamaMasalah; }

    /// @return Nama bagian yang terkait dengan masalah.
    const std::string& getBagianBermasalah() const { return BagianBermasalah; }

    /// @return Waktu perbaikan terakhir atau "-" jika belum diperbaiki.
    const std::string& getTerakhirDiperbaiki() const { return TerakhirDiperbaiki; }

    /// @return true jika waktu perbaikan telah dicatat.
    bool sudahDiperbaiki() const { return TerakhirDiperbaiki != "-"; }

    /// Mencatat waktu lokal saat masalah ditandai selesai diperbaiki.
    void updateStatusPerbaikan() { TerakhirDiperbaiki = waktuSekarang(); }

    /**
     * @brief Mengembalikan estimasi durasi perbaikan berdasarkan bagian.
     * @return Durasi estimasi dalam jam; bagian yang tidak dikenal memakai 3 jam.
     */
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
