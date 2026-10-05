from datetime import datetime

from .enums import FokusBagian


class MasalahKendaraan:
    """Mencatat masalah kendaraan, estimasi layanan, dan status perbaikannya."""

    def __init__(self, nama: str, bagian: str | FokusBagian) -> None:
        self.NamaMasalah = nama
        self.BagianBermasalah = (
            bagian.name if isinstance(bagian, FokusBagian) else bagian
        )
        self.TerakhirDiperbaiki = "-"

    def getNamaMasalah(self) -> str:
        return self.NamaMasalah

    def getBagianBermasalah(self) -> str:
        return self.BagianBermasalah

    def getTerakhirDiperbaiki(self) -> str:
        return self.TerakhirDiperbaiki

    def sudahDiperbaiki(self) -> bool:
        return self.TerakhirDiperbaiki != "-"

    def updateStatusPerbaikan(self) -> None:
        self.TerakhirDiperbaiki = datetime.now().strftime("%Y-%m-%d %H:%M")

    def getEstimasiWaktu(self) -> int:
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
