from abc import ABC, abstractmethod

from .enums import JenisKendaraan, to_string
from .Kendaraan import Kendaraan


class PegawaiBengkel(ABC):
    """Kelas dasar abstrak bagi pegawai bengkel yang menangani kendaraan."""

    def __init__(
        self, id_pegawai: str, nama: str, performa: int, spesialisasi: JenisKendaraan
    ) -> None:
        self.IdPegawai = id_pegawai
        self.Nama = nama
        self.Performa = performa
        self.Spesialisasi = spesialisasi

    def getIdPegawai(self) -> str:
        return self.IdPegawai

    def getNama(self) -> str:
        return self.Nama

    def getPerforma(self) -> int:
        return self.Performa

    def getSpesialisasi(self) -> JenisKendaraan:
        return self.Spesialisasi

    def hitungPerfoma(self) -> int:
        return self.Performa

    def getDetailPegawai(self) -> str:
        return (
            f"[{self.IdPegawai}] {self.Nama} | Spesialisasi: "
            f"{to_string(self.Spesialisasi)} | Performa: {self.Performa} bulan"
        )

    @abstractmethod
    def tanganiKendaraan(self, kendaraan: Kendaraan) -> None:
        raise NotImplementedError
