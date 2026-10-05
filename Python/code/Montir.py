"""Implementasi pegawai Montir untuk perbaikan dan laporan perawatan."""

from .enums import JenisKendaraan, to_string
from .Kendaraan import Kendaraan
from .MasalahKendaraan import MasalahKendaraan
from .PegawaiBengkel import PegawaiBengkel


class Montir(PegawaiBengkel):
    """Pegawai teknisi yang memperbaiki masalah dan menyimpan laporan.

    Montir menolak kendaraan di luar spesialisasi dan menyimpan salinan masalah
    yang selesai sebagai catatan historis perawatan.
    """

    def __init__(
        self,
        id_pegawai: str,
        nama: str,
        performa: int,
        spesialisasi: JenisKendaraan,
        keahlian: str,
    ) -> None:
        """Buat Montir dengan keahlian teknis dan spesialisasi kendaraan."""
        super().__init__(id_pegawai, nama, performa, spesialisasi)
        self.Keahlian = keahlian
        self.LaporanPerawatan: list[MasalahKendaraan] = []

    def perbaikan(self, kendaraan: Kendaraan) -> None:
        """Perbaiki masalah yang belum selesai pada kendaraan yang cocok.

        Masalah yang telah diperbaiki dilewati agar tidak dilaporkan dua kali.
        """
        if kendaraan.getJenis() != self.getSpesialisasi():
            print(
                f"  [Montir {self.getNama()}] Menolak: kendaraan "
                f"{to_string(kendaraan.getJenis())} bukan spesialisasinya "
                f"({to_string(self.getSpesialisasi())})."
            )
            return

        for masalah in kendaraan.getDaftarMasalah():
            if masalah.sudahDiperbaiki():
                continue
            print(
                f"  [Montir {self.getNama()}] Memperbaiki "
                f"'{masalah.getNamaMasalah()}' "
                f"({masalah.getBagianBermasalah()}, estimasi "
                f"{masalah.getEstimasiWaktu()} jam)"
            )
            masalah.updateStatusPerbaikan()
            self.LaporanPerawatan.append(
                MasalahKendaraan(
                    masalah.getNamaMasalah(), masalah.getBagianBermasalah()
                )
            )
            self.LaporanPerawatan[-1].TerakhirDiperbaiki = (
                masalah.getTerakhirDiperbaiki()
            )

    def buatLaporan(self) -> str:
        """Susun laporan teks dari seluruh perbaikan yang pernah dicatat."""
        lines = [
            f"LAPORAN PERAWATAN - Montir {self.getNama()} "
            f"(Keahlian: {self.Keahlian})"
        ]
        if not self.LaporanPerawatan:
            lines.append("  (belum ada perbaikan)")
        for index, masalah in enumerate(self.LaporanPerawatan, start=1):
            lines.append(
                f"  {index}. {masalah.getNamaMasalah()} "
                f"[{masalah.getBagianBermasalah()}] - selesai: "
                f"{masalah.getTerakhirDiperbaiki()}"
            )
        return "\n".join(lines) + "\n"

    def hitungPerfoma(self) -> int:
        """Tambahkan dua poin performa untuk setiap perbaikan tercatat."""
        return super().hitungPerfoma() + len(self.LaporanPerawatan) * 2

    def getDetailPegawai(self) -> str:
        """Format detail pegawai beserta keahlian dan jumlah laporan."""
        return (
            f"MONTIR  {super().getDetailPegawai()} | "
            f"Keahlian: {self.Keahlian} | Laporan: {len(self.LaporanPerawatan)}"
        )

    def tanganiKendaraan(self, kendaraan: Kendaraan) -> None:
        """Implementasikan dispatch pegawai ke operasi perbaikan."""
        self.perbaikan(kendaraan)
