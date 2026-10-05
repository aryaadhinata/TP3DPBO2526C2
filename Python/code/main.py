"""Antarmuka CLI untuk mengelola bengkel dan menjalankan layanan kendaraan.

Data contoh dimuat tetapi hanya ditampilkan atas permintaan pengguna. Pembaca
input mengembalikan ``None`` saat EOF agar proses dapat berhenti tanpa
mendaftarkan objek yang belum lengkap.
"""

if __package__:
    from .Bengkel import Bengkel
    from .Kendaraan import Kendaraan
    from .Mekanik import Mekanik
    from .MasalahKendaraan import MasalahKendaraan
    from .Montir import Montir
    from .enums import FokusBagian, JenisKendaraan, to_string
else:
    import sys
    from pathlib import Path

    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
    from Python.code.Bengkel import Bengkel
    from Python.code.Kendaraan import Kendaraan
    from Python.code.Mekanik import Mekanik
    from Python.code.MasalahKendaraan import MasalahKendaraan
    from Python.code.Montir import Montir
    from Python.code.enums import FokusBagian, JenisKendaraan, to_string


def baca_teks(prompt: str) -> str | None:
    """Baca teks wajib dan kembalikan ``None`` jika input standar berakhir."""
    while True:
        try:
            hasil = input(prompt)
        except EOFError:
            return None
        if hasil.strip():
            return hasil.strip()
        print("Input tidak boleh kosong.")


def baca_angka(prompt: str, minimum: int, maksimum: int) -> int | None:
    """Baca integer dalam rentang inklusif; ulangi jika input tidak valid."""
    while True:
        try:
            input_pengguna = input(prompt)
        except EOFError:
            return None
        try:
            hasil = int(input_pengguna)
        except ValueError:
            hasil = None
        if hasil is not None and minimum <= hasil <= maksimum:
            return hasil
        print(f"Masukkan angka antara {minimum} dan {maksimum}.")


def baca_jenis_kendaraan() -> JenisKendaraan | None:
    """Tampilkan kategori kendaraan dan kembalikan enum pilihan pengguna."""
    print("Jenis kendaraan:\n1. Mobil\n2. Motor")
    pilihan = baca_angka("Pilih jenis: ", 1, 2)
    if pilihan is None:
        return None
    return JenisKendaraan.MOBIL if pilihan == 1 else JenisKendaraan.MOTOR


def baca_fokus() -> FokusBagian | None:
    """Tampilkan katalog bagian dan kembalikan fokus enum yang dipilih."""
    pilihan_fokus = list(FokusBagian)
    print("Bagian bermasalah:")
    for index, fokus in enumerate(pilihan_fokus, start=1):
        print(f"{index}. {to_string(fokus)}")
    pilihan = baca_angka("Pilih bagian: ", 1, len(pilihan_fokus))
    if pilihan is None:
        return None
    return pilihan_fokus[pilihan - 1]


def tambah_pegawai(bengkel: Bengkel) -> bool:
    """Buat Montir atau Mekanik dari input, lalu daftarkan ke bengkel aktif.

    Returns:
        ``False`` bila input berakhir sebelum proses pendaftaran selesai.
    """
    print("\nJenis pegawai:\n1. Montir\n2. Mekanik")
    jenis_pegawai = baca_angka("Pilih jenis pegawai: ", 1, 2)
    if jenis_pegawai is None:
        return False

    id_pegawai = baca_teks("ID pegawai: ")
    nama = baca_teks("Nama pegawai: ")
    performa = baca_angka("Performa (bulan): ", 0, 1_000_000)
    spesialisasi = baca_jenis_kendaraan()
    if id_pegawai is None or nama is None or performa is None or spesialisasi is None:
        return False

    if jenis_pegawai == 1:
        keahlian = baca_teks("Keahlian montir: ")
        if keahlian is None:
            return False
        pegawai = Montir(id_pegawai, nama, performa, spesialisasi, keahlian)
    else:
        jumlah_fokus = baca_angka(
            "Jumlah fokus mekanik (0 untuk semua bagian): ", 0, len(FokusBagian)
        )
        if jumlah_fokus is None:
            return False
        fokus: list[FokusBagian] = []
        for _ in range(jumlah_fokus):
            bagian = baca_fokus()
            if bagian is None:
                return False
            fokus.append(bagian)
        pegawai = Mekanik(id_pegawai, nama, performa, spesialisasi, fokus)

    bengkel.tambahPegawai(pegawai)
    print("Pegawai berhasil ditambahkan.")
    return True


def tambah_kendaraan(bengkel: Bengkel) -> bool:
    """Buat kendaraan dan masalahnya, lalu minta bengkel menerima kendaraan.

    Kapasitas diperiksa sebelum pengumpulan input dan kembali divalidasi saat
    kendaraan diserahkan kepada objek bengkel.

    Returns:
        ``False`` bila input berakhir sebelum data kendaraan lengkap.
    """
    if bengkel.kapasitasPenuh():
        print("Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.")
        return True

    brand = baca_teks("Brand kendaraan: ")
    tipe = baca_teks("Tipe kendaraan: ")
    jenis = baca_jenis_kendaraan()
    tahun = baca_angka("Tahun pembuatan: ", 1886, 9999)
    asal = baca_teks("Asal produsen: ")
    jumlah_masalah = baca_angka("Jumlah masalah: ", 0, 100)
    if (
        brand is None
        or tipe is None
        or jenis is None
        or tahun is None
        or asal is None
        or jumlah_masalah is None
    ):
        return False

    kendaraan = Kendaraan(brand, tipe, jenis, tahun, asal)
    for index in range(jumlah_masalah):
        print(f"Masalah ke-{index + 1}:")
        nama_masalah = baca_teks("Nama masalah: ")
        bagian = baca_fokus()
        if nama_masalah is None or bagian is None:
            return False
        kendaraan.tambahMasalah(MasalahKendaraan(nama_masalah, bagian))

    if not bengkel.terimaKendaraan(kendaraan):
        print("Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.")
        return True
    print("Kendaraan berhasil ditambahkan.")
    return True


def proses_kendaraan(bengkel: Bengkel) -> bool:
    """Tampilkan kendaraan pada bengkel dan proses pilihan pengguna."""
    kendaraan_list = bengkel.getDaftarKendaraan()
    if not kendaraan_list:
        print("Belum ada kendaraan untuk diproses.")
        return True

    print("\nPilih kendaraan yang akan diproses:")
    for index, kendaraan in enumerate(kendaraan_list, start=1):
        print(f"{index}. {kendaraan.getDetailKendaraan()}")

    pilihan = baca_angka("Nomor kendaraan: ", 1, len(kendaraan_list))
    if pilihan is None:
        return False
    bengkel.prosesKendaraan(pilihan - 1)
    return True


def tambah_bengkel(
    bengkel_list: list[Bengkel], bengkel_aktif: int
) -> int | None:
    """Tambahkan bengkel dan kembalikan indeksnya sebagai bengkel aktif."""
    nama = baca_teks("Nama bengkel: ")
    kapasitas = baca_angka("Kapasitas kendaraan: ", 1, 1_000_000)
    if nama is None or kapasitas is None:
        return None

    bengkel_list.append(Bengkel(nama, kapasitas))
    bengkel_aktif = len(bengkel_list) - 1
    print(
        "Bengkel berhasil ditambahkan. Bengkel aktif sekarang: "
        f"{bengkel_list[bengkel_aktif].getNamaBengkel()}"
    )
    return bengkel_aktif


def ganti_bengkel(bengkel_list: list[Bengkel], bengkel_aktif: int) -> int | None:
    """Pilih bengkel aktif dari seluruh bengkel dalam sesi CLI."""
    print("\nDaftar bengkel:")
    for index, bengkel in enumerate(bengkel_list, start=1):
        aktif = " (aktif)" if index - 1 == bengkel_aktif else ""
        print(f"{index}. {bengkel.getNamaBengkel()}{aktif}")

    pilihan = baca_angka("Pilih bengkel: ", 1, len(bengkel_list))
    if pilihan is None:
        return None
    bengkel_aktif = pilihan - 1
    print(f"Bengkel aktif: {bengkel_list[bengkel_aktif].getNamaBengkel()}")
    return bengkel_aktif


def tampilkan_laporan_montir(bengkel: Bengkel) -> None:
    """Cetak laporan Montir di bengkel atau pesan jika belum ada Montir."""
    montir_list = [
        pegawai
        for pegawai in bengkel.getDaftarPegawai()
        if isinstance(pegawai, Montir)
    ]
    if not montir_list:
        print("Belum ada montir di bengkel ini.")
        return
    for montir in montir_list:
        print(montir.buatLaporan(), end="")


def isi_data_awal(bengkel: Bengkel) -> None:
    """Muat pegawai dan kendaraan contoh tanpa menampilkannya otomatis."""
    bengkel.tambahPegawai(
        Montir(
            "P-001",
            "Budi Santoso",
            48,
            JenisKendaraan.MOBIL,
            "Mesin & Sistem Pendingin",
        )
    )
    bengkel.tambahPegawai(
        Mekanik(
            "P-002",
            "Sari Wulandari",
            36,
            JenisKendaraan.MOBIL,
            [
                FokusBagian.MESIN,
                FokusBagian.SISTEM_PENDINGIN,
                FokusBagian.REM,
            ],
        )
    )

    avanza = Kendaraan(
        "Toyota", "Avanza (MPV)", JenisKendaraan.MOBIL, 2018, "Jepang"
    )
    avanza.tambahMasalah(
        MasalahKendaraan("Radiator bocor", FokusBagian.SISTEM_PENDINGIN)
    )
    avanza.tambahMasalah(MasalahKendaraan("Kampas rem aus", FokusBagian.REM))
    avanza.tambahMasalah(
        MasalahKendaraan("AC tidak dingin", FokusBagian.INTERIOR_AC)
    )
    bengkel.terimaKendaraan(avanza)


def main() -> None:
    """Jalankan menu interaktif hingga pengguna keluar atau input berakhir."""
    bengkel_list = [Bengkel("Bengkel Maju Jaya", 5)]
    isi_data_awal(bengkel_list[0])
    bengkel_aktif = 0

    while True:
        bengkel = bengkel_list[bengkel_aktif]
        print(
            f"\n========== {bengkel.getNamaBengkel()} ==========\n"
            "1. Tambah pegawai\n"
            "2. Tambah kendaraan\n"
            "3. Tampilkan ringkasan\n"
            "4. Proses kendaraan\n"
            "5. Tambah bengkel\n"
            "6. Ganti bengkel\n"
            "7. Tampilkan laporan montir\n"
            "0. Keluar"
        )
        pilihan = baca_angka("Pilih menu: ", 0, 7)
        if pilihan is None or pilihan == 0:
            break

        if pilihan == 1:
            lanjut = tambah_pegawai(bengkel)
        elif pilihan == 2:
            lanjut = tambah_kendaraan(bengkel)
        elif pilihan == 3:
            bengkel.cetakRingkasan()
            lanjut = True
        elif pilihan == 4:
            lanjut = proses_kendaraan(bengkel)
        elif pilihan == 5:
            bengkel_aktif_baru = tambah_bengkel(bengkel_list, bengkel_aktif)
            lanjut = bengkel_aktif_baru is not None
            if lanjut:
                bengkel_aktif = bengkel_aktif_baru
        elif pilihan == 6:
            bengkel_aktif_baru = ganti_bengkel(bengkel_list, bengkel_aktif)
            lanjut = bengkel_aktif_baru is not None
            if lanjut:
                bengkel_aktif = bengkel_aktif_baru
        else:
            tampilkan_laporan_montir(bengkel)
            lanjut = True

        if not lanjut:
            break

    print("Program selesai.")


if __name__ == "__main__":
    main()
