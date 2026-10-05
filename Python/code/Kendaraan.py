from .enums import JenisKendaraan, to_string
from .MasalahKendaraan import MasalahKendaraan


class Kendaraan:
    """Menyimpan identitas kendaraan dan komposisi masalah yang dimilikinya."""

    def __init__(
        self,
        brand: str,
        tipe: str,
        jenis: JenisKendaraan,
        tahun: int,
        asal: str,
    ) -> None:
        self.Brand = brand
        self.Tipe = tipe
        self.Jenis = jenis
        self.TahunPembuatan = tahun
        self.AsalProdusen = asal
        self.DaftarMasalah: list[MasalahKendaraan] = []

    def getJenis(self) -> JenisKendaraan:
        return self.Jenis

    def getDaftarMasalah(self) -> list[MasalahKendaraan]:
        return self.DaftarMasalah

    def tambahMasalah(self, masalah: MasalahKendaraan) -> None:
        self.DaftarMasalah.append(masalah)

    def getDetailKendaraan(self) -> str:
        return (
            f"{self.Brand} {self.Tipe} [{to_string(self.Jenis)}] - "
            f"{self.TahunPembuatan} - Produsen: {self.AsalProdusen} - "
            f"Jumlah masalah: {len(self.DaftarMasalah)}"
        )
