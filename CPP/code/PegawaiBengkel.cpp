#pragma once
#include <sstream>
#include <string>
#include <utility>
#include "Enums.cpp"
#include "Kendaraan.cpp"

// Kelas dasar abstrak untuk pegawai dengan spesialisasi kendaraan tertentu.
class PegawaiBengkel {
private:
    std::string IdPegawai;
    std::string Nama;
    int Performa; // dalam bulan
    JenisKendaraan Spesialisasi;

public:
    PegawaiBengkel(std::string id, std::string nama, int performa,
                    JenisKendaraan spesialisasi)
        : IdPegawai(std::move(id)), Nama(std::move(nama)), Performa(performa),
            Spesialisasi(spesialisasi) {}

    virtual ~PegawaiBengkel() = default;

    const std::string& getIdPegawai() const { return IdPegawai; }
    const std::string& getNama() const { return Nama; }
    int getPerforma() const { return Performa; }
    JenisKendaraan getSpesialisasi() const { return Spesialisasi; }

    virtual int hitungPerfoma() const { return Performa; }

    virtual std::string getDetailPegawai() const {
        std::ostringstream os;
        os << "[" << IdPegawai << "] " << Nama << " | Spesialisasi: "
            << toString(Spesialisasi) << " | Performa: " << Performa << " bulan";
        return os.str();
    }

    // Aksi polimorfik: tiap jenis pegawai menangani kendaraan dengan caranya
    virtual void tanganiKendaraan(Kendaraan& kendaraan) = 0;
};
