"""Nilai enumerasi bersama yang dipakai model domain bengkel."""

from enum import Enum


class JenisKendaraan(Enum):
    """Kategori kendaraan untuk data kendaraan dan spesialisasi pegawai."""

    MOBIL = "MOBIL"
    MOTOR = "MOTOR"


class FokusBagian(Enum):
    """Bagian kendaraan yang dapat diperiksa atau dilaporkan bermasalah."""

    MESIN = "MESIN"
    TRANSMISI = "TRANSMISI"
    REM = "REM"
    SUSPENSI_KEMUDI = "SUSPENSI_KEMUDI"
    KELISTRIKAN = "KELISTRIKAN"
    SISTEM_PENDINGIN = "SISTEM_PENDINGIN"
    SISTEM_PEMBUANGAN = "SISTEM_PEMBUANGAN"
    RANGKA_CHASIS = "RANGKA_CHASIS"
    BODY_EKSTERIOR = "BODY_EKSTERIOR"
    INTERIOR_AC = "INTERIOR_AC"
    RODA_BAN = "RODA_BAN"


def to_string(nilai: Enum) -> str:
    """Kembalikan nilai teks enum untuk pencocokan dan tampilan CLI."""
    return str(nilai.value)
