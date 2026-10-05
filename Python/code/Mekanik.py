from copy import copy

from .enums import FokusBagian, JenisKendaraan, to_string
from .Kendaraan import Kendaraan
from .MasalahKendaraan import MasalahKendaraan
from .PegawaiBengkel import PegawaiBengkel


class Mekanik(PegawaiBengkel):
    def __init__(
        self,
        id_pegawai: str,
        nama: str,
        performa: int,
        spesialisasi: JenisKendaraan,
        fokus: list[FokusBagian],
    ) -> None:
        super().__init__(id_pegawai, nama, performa, spesialisasi)
        self.DaftarPemeriksaan: list[MasalahKendaraan] = []
        self.FokusPemeriksaan = list(fokus)

    def sesuaiFokus(self, masalah: MasalahKendaraan) -> bool:
        if not self.FokusPemeriksaan:
            return True
        return any(
            to_string(fokus) == masalah.getBagianBermasalah()
            for fokus in self.FokusPemeriksaan
        )

    def periksaKendaraan(self, kendaraan: Kendaraan) -> None:
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
        self.DaftarPemeriksaan.sort(
            key=lambda masalah: masalah.getEstimasiWaktu(), reverse=True
        )

    def getDaftarPemeriksaan(self) -> list[MasalahKendaraan]:
        return self.DaftarPemeriksaan

    def hitungPerfoma(self) -> int:
        return super().hitungPerfoma() + len(self.DaftarPemeriksaan)

    def getDetailPegawai(self) -> str:
        fokus = ", ".join(to_string(item) for item in self.FokusPemeriksaan)
        return (
            f"MEKANIK {super().getDetailPegawai()} | Fokus: {fokus} "
            f"| Temuan: {len(self.DaftarPemeriksaan)}"
        )

    def tanganiKendaraan(self, kendaraan: Kendaraan) -> None:
        self.periksaKendaraan(kendaraan)
