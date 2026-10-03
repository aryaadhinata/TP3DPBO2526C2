#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Kendaraan.cpp"
#include "PegawaiBengkel.cpp"

class Bengkel {
private:
    std::string NamaBengkel;
    std::vector<std::unique_ptr<PegawaiBengkel>> DaftarPegawai; // polimorfik
    std::vector<Kendaraan> DaftarKendaraan;
    int Kapasitas;

public:
    Bengkel(std::string nama, int kapasitas)
        : NamaBengkel(std::move(nama)), Kapasitas(kapasitas) {}

    void tambahPegawai(std::unique_ptr<PegawaiBengkel> pegawai) {
        if (pegawai) DaftarPegawai.push_back(std::move(pegawai));
    }

    // false bila bengkel sudah penuh
    bool terimaKendaraan(Kendaraan kendaraan) {
        if (static_cast<int>(DaftarKendaraan.size()) >= Kapasitas) return false;
        DaftarKendaraan.push_back(std::move(kendaraan));
        return true;
    }

    // Seluruh pegawai menangani kendaraan (dispatch polimorfik)
    void prosesKendaraan(std::size_t indeksKendaraan) {
        if (indeksKendaraan >= DaftarKendaraan.size()) return;
        Kendaraan& k = DaftarKendaraan[indeksKendaraan];
        for (auto& pegawai : DaftarPegawai) pegawai->tanganiKendaraan(k);
    }

    const std::vector<std::unique_ptr<PegawaiBengkel>>& getDaftarPegawai() const {
        return DaftarPegawai;
    }

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
