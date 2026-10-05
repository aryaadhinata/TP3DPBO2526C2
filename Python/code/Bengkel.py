from .Kendaraan import Kendaraan
from .PegawaiBengkel import PegawaiBengkel


class Bengkel:
    def __init__(self, nama: str, kapasitas: int) -> None:
        self.NamaBengkel = nama
        self.DaftarPegawai: list[PegawaiBengkel] = []
        self.DaftarKendaraan: list[Kendaraan] = []
        self.Kapasitas = kapasitas

    def getNamaBengkel(self) -> str:
        return self.NamaBengkel

    def tambahPegawai(self, pegawai: PegawaiBengkel) -> None:
        self.DaftarPegawai.append(pegawai)

    def terimaKendaraan(self, kendaraan: Kendaraan) -> bool:
        if self.kapasitasPenuh():
            return False
        self.DaftarKendaraan.append(kendaraan)
        return True

    def kapasitasPenuh(self) -> bool:
        return len(self.DaftarKendaraan) >= self.Kapasitas

    def prosesKendaraan(self, indeks_kendaraan: int) -> None:
        if indeks_kendaraan < 0 or indeks_kendaraan >= len(self.DaftarKendaraan):
            return
        kendaraan = self.DaftarKendaraan[indeks_kendaraan]
        for pegawai in self.DaftarPegawai:
            pegawai.tanganiKendaraan(kendaraan)

    def getDaftarPegawai(self) -> list[PegawaiBengkel]:
        return self.DaftarPegawai

    def getDaftarKendaraan(self) -> list[Kendaraan]:
        return self.DaftarKendaraan

    def cetakRingkasan(self) -> None:
        print(
            f"Bengkel   : {self.NamaBengkel}\n"
            f"Kapasitas : {len(self.DaftarKendaraan)}/{self.Kapasitas} "
            "kendaraan\n"
        )
        print(f"-- DaftarPegawai ({len(self.DaftarPegawai)}) --")
        for index, pegawai in enumerate(self.DaftarPegawai, start=1):
            print(
                f"{index}. {pegawai.getDetailPegawai()} | "
                f"Skor: {pegawai.hitungPerfoma()}"
            )

        print(f"\n-- DaftarKendaraan ({len(self.DaftarKendaraan)}) --")
        for index, kendaraan in enumerate(self.DaftarKendaraan, start=1):
            print(f"{index}. {kendaraan.getDetailKendaraan()}")
            for masalah in kendaraan.getDaftarMasalah():
                print(
                    f"     * {masalah.getNamaMasalah()} "
                    f"[{masalah.getBagianBermasalah()}] estimasi "
                    f"{masalah.getEstimasiWaktu()} jam, terakhir diperbaiki: "
                    f"{masalah.getTerakhirDiperbaiki()}"
                )
