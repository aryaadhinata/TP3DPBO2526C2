"""Model kendaraan dan hubungan komposisinya dengan masalah kendaraan."""

from .enums import JenisKendaraan, to_string
from .MasalahKendaraan import MasalahKendaraan


class Kendaraan:
    """Menyimpan identitas kendaraan dan masalah yang melekat padanya.

    Daftar masalah merupakan composition: masalah dimiliki kendaraan dan
    direpresentasikan dengan objek ``MasalahKendaraan``.
    """

    def __init__(
        self,
        brand: str,
        tipe: str,
        jenis: JenisKendaraan,
        tahun: int,
        asal: str,
    ) -> None:
        """Buat kendaraan dari merek, tipe, jenis, tahun, dan negara produsen."""
        self.Brand = brand
        self.Tipe = tipe
        self.Jenis = jenis
        self.TahunPembuatan = tahun
        self.AsalProdusen = asal
        self.DaftarMasalah: list[MasalahKendaraan] = []

    def getJenis(self) -> JenisKendaraan:
        """Kembalikan jenis untuk validasi spesialisasi pegawai."""
        return self.Jenis

    def getDaftarMasalah(self) -> list[MasalahKendaraan]:
        """Kembalikan masalah yang menjadi bagian dari kendaraan."""
        return self.DaftarMasalah

    def tambahMasalah(self, masalah: MasalahKendaraan) -> None:
        """Tambahkan masalah ke daftar komposisi kendaraan."""
        self.DaftarMasalah.append(masalah)

    def getDetailKendaraan(self) -> str:
        """Format identitas kendaraan dan jumlah masalah untuk CLI."""
        return (
            f"{self.Brand} {self.Tipe} [{to_string(self.Jenis)}] - "
            f"{self.TahunPembuatan} - Produsen: {self.AsalProdusen} - "
            f"Jumlah masalah: {len(self.DaftarMasalah)}"
        )
