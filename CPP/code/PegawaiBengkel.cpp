#pragma once
#include <sstream>
#include <string>
#include <utility>
#include "Enums.cpp"
#include "Kendaraan.cpp"

/**
 * @brief Kelas dasar abstrak untuk pegawai bengkel.
 *
 * Menyimpan identitas dan spesialisasi bersama, serta mendefinisikan kontrak
 * virtual agar kelas turunan dapat menangani kendaraan secara polimorfik.
 */
class PegawaiBengkel {
private:
    std::string IdPegawai;
    std::string Nama;
    int Performa; // dalam bulan
    JenisKendaraan Spesialisasi;

public:
    /**
     * @brief Membuat pegawai dengan identitas, performa, dan spesialisasi.
     * @param id Identitas unik pegawai.
     * @param nama Nama pegawai.
     * @param performa Nilai performa dasar dalam bulan.
     * @param spesialisasi Kategori kendaraan yang dapat ditangani.
     */
    PegawaiBengkel(std::string id, std::string nama, int performa,
                    JenisKendaraan spesialisasi)
        : IdPegawai(std::move(id)), Nama(std::move(nama)), Performa(performa),
            Spesialisasi(spesialisasi) {}

    virtual ~PegawaiBengkel() = default;

    /// @return Identitas pegawai.
    const std::string& getIdPegawai() const { return IdPegawai; }

    /// @return Nama pegawai.
    const std::string& getNama() const { return Nama; }

    /// @return Nilai performa dasar dalam bulan.
    int getPerforma() const { return Performa; }

    /// @return Kategori kendaraan yang menjadi spesialisasi pegawai.
    JenisKendaraan getSpesialisasi() const { return Spesialisasi; }

    /// @return Performa pegawai; kelas turunan menambahkan kontribusi kerjanya.
    virtual int hitungPerfoma() const { return Performa; }

    /// @return Identitas, spesialisasi, dan performa untuk ditampilkan.
    virtual std::string getDetailPegawai() const {
        std::ostringstream os;
        os << "[" << IdPegawai << "] " << Nama << " | Spesialisasi: "
            << toString(Spesialisasi) << " | Performa: " << Performa << " bulan";
        return os.str();
    }

    /**
     * @brief Menangani kendaraan sesuai tanggung jawab kelas pegawai turunan.
     * @param kendaraan Kendaraan yang sedang diproses bengkel.
     */
    virtual void tanganiKendaraan(Kendaraan& kendaraan) = 0;
};
