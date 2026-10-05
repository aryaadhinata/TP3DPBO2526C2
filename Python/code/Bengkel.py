"""Model bengkel yang mengelola kapasitas, pegawai, kendaraan, dan layanan."""

from .Kendaraan import Kendaraan
from .PegawaiBengkel import PegawaiBengkel


class Bengkel:
    """Mewakili satu bengkel beserta pegawai dan kendaraan yang dikelolanya.

    Pegawai disimpan dengan tipe dasar ``PegawaiBengkel`` agar Montir dan
    Mekanik dapat menangani kendaraan melalui dispatch polimorfik. Penerimaan
    kendaraan dibatasi oleh ``Kapasitas``.
    """

    def __init__(self, nama: str, kapasitas: int) -> None:
        """Inisialisasi bengkel kosong dengan nama dan kapasitas tertentu."""
        self.NamaBengkel = nama
        self.DaftarPegawai: list[PegawaiBengkel] = []
        self.DaftarKendaraan: list[Kendaraan] = []
        self.Kapasitas = kapasitas

    def getNamaBengkel(self) -> str:
        """Kembalikan nama bengkel untuk menu dan ringkasan."""
        return self.NamaBengkel

    def tambahPegawai(self, pegawai: PegawaiBengkel) -> None:
        """Daftarkan Montir atau Mekanik pada bengkel."""
        self.DaftarPegawai.append(pegawai)

    def terimaKendaraan(self, kendaraan: Kendaraan) -> bool:
        """Terima kendaraan jika kapasitas masih tersedia.

        Returns:
            ``True`` jika kendaraan diterima; ``False`` jika bengkel penuh.
        """
        if self.kapasitasPenuh():
            return False
        self.DaftarKendaraan.append(kendaraan)
        return True

    def kapasitasPenuh(self) -> bool:
        """Kembalikan apakah jumlah kendaraan telah mencapai kapasitas."""
        return len(self.DaftarKendaraan) >= self.Kapasitas

    def prosesKendaraan(self, indeks_kendaraan: int) -> None:
        """Minta semua pegawai menangani kendaraan pada indeks berbasis nol.

        Indeks yang tidak valid diabaikan. Penanganan masing-masing pegawai
        dijalankan melalui metode polimorfik ``tanganiKendaraan``.
        """
        if indeks_kendaraan < 0 or indeks_kendaraan >= len(self.DaftarKendaraan):
            return
        kendaraan = self.DaftarKendaraan[indeks_kendaraan]
        for pegawai in self.DaftarPegawai:
            pegawai.tanganiKendaraan(kendaraan)

    def getDaftarPegawai(self) -> list[PegawaiBengkel]:
        """Kembalikan daftar pegawai untuk ringkasan dan pemilihan laporan."""
        return self.DaftarPegawai

    def getDaftarKendaraan(self) -> list[Kendaraan]:
        """Kembalikan daftar kendaraan yang diterima bengkel."""
        return self.DaftarKendaraan

    def cetakRingkasan(self) -> None:
        """Cetak kapasitas, performa pegawai, kendaraan, dan status masalah."""
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
