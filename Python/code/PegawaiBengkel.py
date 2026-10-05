"""Kontrak abstrak untuk identitas dan penanganan pegawai bengkel."""

from abc import ABC, abstractmethod

from .enums import JenisKendaraan, to_string
from .Kendaraan import Kendaraan


class PegawaiBengkel(ABC):
    """Kelas dasar abstrak untuk identitas dan perilaku pegawai bengkel.

    ``Bengkel`` menyimpan pegawai dengan tipe ini. Kelas turunan menyediakan
    implementasi konkret ``tanganiKendaraan`` untuk dispatch polimorfik.
    """

    def __init__(
        self, id_pegawai: str, nama: str, performa: int, spesialisasi: JenisKendaraan
    ) -> None:
        """Simpan identitas, performa dasar, dan spesialisasi kendaraan."""
        self.IdPegawai = id_pegawai
        self.Nama = nama
        self.Performa = performa
        self.Spesialisasi = spesialisasi

    def getIdPegawai(self) -> str:
        """Kembalikan identitas pegawai."""
        return self.IdPegawai

    def getNama(self) -> str:
        """Kembalikan nama pegawai."""
        return self.Nama

    def getPerforma(self) -> int:
        """Kembalikan performa dasar dalam bulan."""
        return self.Performa

    def getSpesialisasi(self) -> JenisKendaraan:
        """Kembalikan kategori kendaraan yang menjadi spesialisasi."""
        return self.Spesialisasi

    def hitungPerfoma(self) -> int:
        """Kembalikan performa dasar sebelum kontribusi kelas turunan."""
        return self.Performa

    def getDetailPegawai(self) -> str:
        """Format identitas, spesialisasi, dan performa untuk ringkasan."""
        return (
            f"[{self.IdPegawai}] {self.Nama} | Spesialisasi: "
            f"{to_string(self.Spesialisasi)} | Performa: {self.Performa} bulan"
        )

    @abstractmethod
    def tanganiKendaraan(self, kendaraan: Kendaraan) -> None:
        """Tangani kendaraan sesuai peran pegawai dan spesialisasinya."""
        raise NotImplementedError
