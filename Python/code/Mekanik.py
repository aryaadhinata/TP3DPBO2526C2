"""Implementasi pegawai Mekanik untuk inspeksi dan prioritas temuan."""

from copy import copy

from .enums import FokusBagian, JenisKendaraan, to_string
from .Kendaraan import Kendaraan
from .MasalahKendaraan import MasalahKendaraan
from .PegawaiBengkel import PegawaiBengkel


class Mekanik(PegawaiBengkel):
    """Pegawai pemeriksa yang mencatat temuan sesuai fokus inspeksi.

    Kendaraan harus cocok dengan spesialisasi. Fokus kosong berarti seluruh
    bagian diperiksa; temuan menyimpan salinan status saat inspeksi dan
    diprioritaskan berdasarkan estimasi waktu terlama.
    """

    def __init__(
        self,
        id_pegawai: str,
        nama: str,
        performa: int,
        spesialisasi: JenisKendaraan,
        fokus: list[FokusBagian],
    ) -> None:
        """Buat Mekanik dengan spesialisasi kendaraan dan daftar fokus."""
        super().__init__(id_pegawai, nama, performa, spesialisasi)
        self.DaftarPemeriksaan: list[MasalahKendaraan] = []
        self.FokusPemeriksaan = list(fokus)

    def sesuaiFokus(self, masalah: MasalahKendaraan) -> bool:
        """Tentukan apakah bagian masalah termasuk dalam fokus pemeriksaan."""
        if not self.FokusPemeriksaan:
            return True
        return any(
            to_string(fokus) == masalah.getBagianBermasalah()
            for fokus in self.FokusPemeriksaan
        )

    def periksaKendaraan(self, kendaraan: Kendaraan) -> None:
        """Catat masalah yang sesuai spesialisasi dan fokus Mekanik.

        Masalah di luar fokus dilaporkan sebagai dilewati dan tidak menjadi
        temuan pada daftar pemeriksaan.
        """
        if kendaraan.getJenis() != self.getSpesialisasi():
            print(
                f"  [Mekanik {self.getNama()}] Menolak: kendaraan "
                f"{to_string(kendaraan.getJenis())} bukan spesialisasinya "
                f"({to_string(self.getSpesialisasi())})."
            )
            return

        print(
            f"  [Mekanik {self.getNama()}] Memeriksa "
            f"{kendaraan.getDetailKendaraan()}"
        )
        for masalah in kendaraan.getDaftarMasalah():
            if not self.sesuaiFokus(masalah):
                print(
                    f"    - Dilewati (di luar fokus): "
                    f"{masalah.getNamaMasalah()} "
                    f"[{masalah.getBagianBermasalah()}]"
                )
                continue
            status = "SUDAH diperbaiki" if masalah.sudahDiperbaiki() else "BELUM diperbaiki"
            print(
                f"    - Dicatat: {masalah.getNamaMasalah()} "
                f"[{masalah.getBagianBermasalah()}] status: {status}"
            )
            self.DaftarPemeriksaan.append(copy(masalah))
        self.updatePemeriksaan()

    def updatePemeriksaan(self) -> None:
        """Urutkan temuan dari estimasi perbaikan terlama ke tercepat."""
        self.DaftarPemeriksaan.sort(
            key=lambda masalah: masalah.getEstimasiWaktu(), reverse=True
        )

    def getDaftarPemeriksaan(self) -> list[MasalahKendaraan]:
        """Kembalikan daftar temuan yang telah diurutkan berdasarkan estimasi."""
        return self.DaftarPemeriksaan

    def hitungPerfoma(self) -> int:
        """Tambahkan satu poin performa untuk setiap temuan pemeriksaan."""
        return super().hitungPerfoma() + len(self.DaftarPemeriksaan)

    def getDetailPegawai(self) -> str:
        """Format detail pegawai beserta fokus dan jumlah temuannya."""
        fokus = ", ".join(to_string(item) for item in self.FokusPemeriksaan)
        return (
            f"MEKANIK {super().getDetailPegawai()} | Fokus: {fokus} "
            f"| Temuan: {len(self.DaftarPemeriksaan)}"
        )

    def tanganiKendaraan(self, kendaraan: Kendaraan) -> None:
        """Implementasikan dispatch pegawai ke operasi pemeriksaan."""
        self.periksaKendaraan(kendaraan)
