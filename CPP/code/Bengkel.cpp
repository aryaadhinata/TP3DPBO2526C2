#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Kendaraan.cpp"
#include "PegawaiBengkel.cpp"

/**
 * @brief Mengelola pegawai dan kendaraan yang terdaftar pada satu bengkel.
 *
 * Pegawai disimpan melalui pointer dasar agar Montir dan Mekanik tetap
 * diproses secara polimorfik. Jumlah kendaraan dibatasi oleh Kapasitas.
 */
class Bengkel {
private:
    std::string NamaBengkel;
    std::vector<std::unique_ptr<PegawaiBengkel>> DaftarPegawai; // polimorfik
    std::vector<Kendaraan> DaftarKendaraan;
    int Kapasitas;

public:
    /**
     * @brief Membuat bengkel dengan nama dan kapasitas kendaraan tertentu.
     * @param nama Nama bengkel yang ditampilkan pada ringkasan.
     * @param kapasitas Jumlah maksimum kendaraan yang dapat diterima.
     */
    Bengkel(std::string nama, int kapasitas)
        : NamaBengkel(std::move(nama)), Kapasitas(kapasitas) {}

    /// @return Nama bengkel.
    const std::string& getNamaBengkel() const {
        return NamaBengkel;
    }

    /// Menambahkan pegawai non-null ke daftar pegawai bengkel.
    void tambahPegawai(std::unique_ptr<PegawaiBengkel> pegawai) {
        if (pegawai) DaftarPegawai.push_back(std::move(pegawai));
    }

    /**
     * @brief Menerima kendaraan jika kapasitas bengkel masih tersedia.
     * @return true jika kendaraan diterima; false jika bengkel penuh.
     */
    bool terimaKendaraan(Kendaraan kendaraan) {
        if (static_cast<int>(DaftarKendaraan.size()) >= Kapasitas) return false;
        DaftarKendaraan.push_back(std::move(kendaraan));
        return true;
    }

    /// @return true jika jumlah kendaraan sudah mencapai kapasitas.
    bool kapasitasPenuh() const {
        return static_cast<int>(DaftarKendaraan.size()) >= Kapasitas;
    }

    /**
     * @brief Meminta seluruh pegawai menangani kendaraan pada indeks tertentu.
     * @param indeksKendaraan Indeks berbasis nol pada daftar kendaraan.
     *
     * Pemanggilan metode virtual meneruskan penanganan ke implementasi Montir
     * atau Mekanik. Indeks di luar daftar tidak mengubah data bengkel.
     */
    void prosesKendaraan(std::size_t indeksKendaraan) {
        if (indeksKendaraan >= DaftarKendaraan.size()) return;
        Kendaraan& k = DaftarKendaraan[indeksKendaraan];
        for (auto& pegawai : DaftarPegawai) pegawai->tanganiKendaraan(k);
    }

    /// @return Daftar pegawai polimorfik yang terdaftar pada bengkel.
    const std::vector<std::unique_ptr<PegawaiBengkel>>& getDaftarPegawai() const {
        return DaftarPegawai;
    }

    /// @return Daftar kendaraan yang diterima bengkel.
    const std::vector<Kendaraan>& getDaftarKendaraan() const {
        return DaftarKendaraan;
    }

    /// Mencetak kapasitas, detail pegawai, kendaraan, dan status masalah.
    void cetakRingkasan() const {
        std::cout << "Bengkel   : " << NamaBengkel << "\n"
                    << "Kapasitas : " << DaftarKendaraan.size() << "/" << Kapasitas
                    << " kendaraan\n\n";

        std::cout << "-- DaftarPegawai (" << DaftarPegawai.size() << ") --\n";
        for (std::size_t i = 0; i < DaftarPegawai.size(); ++i)
            std::cout << (i + 1) << ". " << DaftarPegawai[i]->getDetailPegawai()
                        << " | Skor: " << DaftarPegawai[i]->hitungPerfoma() << "\n";

        std::cout << "\n-- DaftarKendaraan (" << DaftarKendaraan.size() << ") --\n";
        for (std::size_t i = 0; i < DaftarKendaraan.size(); ++i) {
            const Kendaraan& k = DaftarKendaraan[i];
            std::cout << (i + 1) << ". " << k.getDetailKendaraan() << "\n";
            for (const auto& m : k.getDaftarMasalah())
                std::cout << "     * " << m.getNamaMasalah() << " ["
                            << m.getBagianBermasalah() << "] estimasi "
                            << m.getEstimasiWaktu() << " jam, terakhir diperbaiki: "
                            << m.getTerakhirDiperbaiki() << "\n";
        }
    }
};
