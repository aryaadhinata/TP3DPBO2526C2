"""Model masalah kendaraan beserta status perbaikan dan estimasi waktunya."""

from datetime import datetime

from .enums import FokusBagian


class MasalahKendaraan:
    """Mencatat deskripsi, bagian terkait, dan riwayat status perbaikan.

    Nama bagian diselaraskan dengan ``FokusBagian`` agar dapat dicocokkan
    terhadap fokus inspeksi Mekanik. Tanda ``"-"`` berarti belum diperbaiki.
    """

    def __init__(self, nama: str, bagian: str | FokusBagian) -> None:
        """Buat masalah baru dengan waktu perbaikan yang belum diisi."""
        self.NamaMasalah = nama
        self.BagianBermasalah = (
            bagian.name if isinstance(bagian, FokusBagian) else bagian
        )
        self.TerakhirDiperbaiki = "-"

    def getNamaMasalah(self) -> str:
        """Kembalikan deskripsi masalah."""
        return self.NamaMasalah

    def getBagianBermasalah(self) -> str:
        """Kembalikan nama bagian yang terkait dengan masalah."""
        return self.BagianBermasalah

    def getTerakhirDiperbaiki(self) -> str:
        """Kembalikan waktu perbaikan terakhir atau ``"-"``."""
        return self.TerakhirDiperbaiki

    def sudahDiperbaiki(self) -> bool:
        """Tentukan apakah waktu perbaikan sudah pernah dicatat."""
        return self.TerakhirDiperbaiki != "-"

    def updateStatusPerbaikan(self) -> None:
        """Catat waktu lokal saat masalah dinyatakan selesai diperbaiki."""
        self.TerakhirDiperbaiki = datetime.now().strftime("%Y-%m-%d %H:%M")

    def getEstimasiWaktu(self) -> int:
        """Kembalikan estimasi durasi perbaikan dalam jam.

        Bagian yang tidak dikenali menggunakan nilai bawaan tiga jam.
        """
        estimasi = {
            "MESIN": 8,
            "TRANSMISI": 6,
            "RANGKA_CHASIS": 10,
            "SUSPENSI_KEMUDI": 5,
            "SISTEM_PENDINGIN": 4,
            "KELISTRIKAN": 4,
            "SISTEM_PEMBUANGAN": 3,
            "BODY_EKSTERIOR": 6,
            "INTERIOR_AC": 3,
            "REM": 2,
            "RODA_BAN": 1,
        }
        return estimasi.get(self.BagianBermasalah, 3)
