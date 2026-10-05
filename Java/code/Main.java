import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final Scanner INPUT = new Scanner(System.in);

    private static String bacaTeks(String prompt) {
        while (true) {
            System.out.print(prompt);
            if (!INPUT.hasNextLine()) {
                return null;
            }
            String hasil = INPUT.nextLine().trim();
            if (!hasil.isEmpty()) {
                return hasil;
            }
            System.out.println("Input tidak boleh kosong.");
        }
    }

    private static Integer bacaAngka(String prompt, int minimum, int maksimum) {
        while (true) {
            System.out.print(prompt);
            if (!INPUT.hasNextLine()) {
                return null;
            }
            String input = INPUT.nextLine().trim();
            try {
                int hasil = Integer.parseInt(input);
                if (hasil >= minimum && hasil <= maksimum) {
                    return hasil;
                }
            } catch (NumberFormatException ignored) {
                // Input is validated below and the user is prompted again.
            }
            System.out.println("Masukkan angka antara " + minimum + " dan " + maksimum + ".");
        }
    }

    private static JenisKendaraan bacaJenisKendaraan() {
        System.out.println("Jenis kendaraan:\n1. Mobil\n2. Motor");
        Integer pilihan = bacaAngka("Pilih jenis: ", 1, 2);
        if (pilihan == null) {
            return null;
        }
        return pilihan == 1 ? JenisKendaraan.MOBIL : JenisKendaraan.MOTOR;
    }

    private static FokusBagian bacaFokus() {
        FokusBagian[] pilihanFokus = FokusBagian.values();
        System.out.println("Bagian bermasalah:");
        for (int i = 0; i < pilihanFokus.length; i++) {
            System.out.println((i + 1) + ". " + pilihanFokus[i]);
        }
        Integer pilihan = bacaAngka("Pilih bagian: ", 1, pilihanFokus.length);
        return pilihan == null ? null : pilihanFokus[pilihan - 1];
    }

    private static boolean tambahPegawai(Bengkel bengkel) {
        System.out.println("\nJenis pegawai:\n1. Montir\n2. Mekanik");
        Integer jenisPegawai = bacaAngka("Pilih jenis pegawai: ", 1, 2);
        if (jenisPegawai == null) {
            return false;
        }

        String id = bacaTeks("ID pegawai: ");
        String nama = bacaTeks("Nama pegawai: ");
        Integer performa = bacaAngka("Performa (bulan): ", 0, 1_000_000);
        JenisKendaraan spesialisasi = bacaJenisKendaraan();
        if (id == null || nama == null || performa == null || spesialisasi == null) {
            return false;
        }

        PegawaiBengkel pegawai;
        if (jenisPegawai == 1) {
            String keahlian = bacaTeks("Keahlian montir: ");
            if (keahlian == null) {
                return false;
            }
            pegawai = new Montir(id, nama, performa, spesialisasi, keahlian);
        } else {
            Integer jumlahFokus = bacaAngka(
                    "Jumlah fokus mekanik (0 untuk semua bagian): ",
                    0, FokusBagian.values().length);
            if (jumlahFokus == null) {
                return false;
            }
            List<FokusBagian> fokus = new ArrayList<>();
            for (int i = 0; i < jumlahFokus; i++) {
                FokusBagian bagian = bacaFokus();
                if (bagian == null) {
                    return false;
                }
                fokus.add(bagian);
            }
            pegawai = new Mekanik(id, nama, performa, spesialisasi, fokus);
        }

        bengkel.tambahPegawai(pegawai);
        System.out.println("Pegawai berhasil ditambahkan.");
        return true;
    }

    private static boolean tambahKendaraan(Bengkel bengkel) {
        if (bengkel.kapasitasPenuh()) {
            System.out.println("Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.");
            return true;
        }

        String brand = bacaTeks("Brand kendaraan: ");
        String tipe = bacaTeks("Tipe kendaraan: ");
        JenisKendaraan jenis = bacaJenisKendaraan();
        Integer tahun = bacaAngka("Tahun pembuatan: ", 1886, 9999);
        String asal = bacaTeks("Asal produsen: ");
        Integer jumlahMasalah = bacaAngka("Jumlah masalah: ", 0, 100);
        if (brand == null || tipe == null || jenis == null || tahun == null
                || asal == null || jumlahMasalah == null) {
            return false;
        }

        Kendaraan kendaraan = new Kendaraan(brand, tipe, jenis, tahun, asal);
        for (int i = 0; i < jumlahMasalah; i++) {
            System.out.println("Masalah ke-" + (i + 1) + ":");
            String namaMasalah = bacaTeks("Nama masalah: ");
            FokusBagian bagian = bacaFokus();
            if (namaMasalah == null || bagian == null) {
                return false;
            }
            kendaraan.tambahMasalah(new MasalahKendaraan(namaMasalah, bagian));
        }

        if (!bengkel.terimaKendaraan(kendaraan)) {
            System.out.println("Kendaraan tidak dapat ditambahkan: bengkel sudah penuh.");
            return true;
        }
        System.out.println("Kendaraan berhasil ditambahkan.");
        return true;
    }

    private static boolean prosesKendaraan(Bengkel bengkel) {
        List<Kendaraan> kendaraanList = bengkel.getDaftarKendaraan();
        if (kendaraanList.isEmpty()) {
            System.out.println("Belum ada kendaraan untuk diproses.");
            return true;
        }

        System.out.println("\nPilih kendaraan yang akan diproses:");
        for (int i = 0; i < kendaraanList.size(); i++) {
            System.out.println((i + 1) + ". " + kendaraanList.get(i).getDetailKendaraan());
        }
        Integer pilihan = bacaAngka("Nomor kendaraan: ", 1, kendaraanList.size());
        if (pilihan == null) {
            return false;
        }
        bengkel.prosesKendaraan(pilihan - 1);
        return true;
    }

    private static boolean tambahBengkel(List<Bengkel> bengkelList,
                                         int[] bengkelAktif) {
        String nama = bacaTeks("Nama bengkel: ");
        Integer kapasitas = bacaAngka("Kapasitas kendaraan: ", 1, 1_000_000);
        if (nama == null || kapasitas == null) {
            return false;
        }

        bengkelList.add(new Bengkel(nama, kapasitas));
        bengkelAktif[0] = bengkelList.size() - 1;
        System.out.println("Bengkel berhasil ditambahkan. Bengkel aktif sekarang: "
                + bengkelList.get(bengkelAktif[0]).getNamaBengkel());
        return true;
    }

    private static boolean gantiBengkel(List<Bengkel> bengkelList,
                                        int[] bengkelAktif) {
        System.out.println("\nDaftar bengkel:");
        for (int i = 0; i < bengkelList.size(); i++) {
            String aktif = i == bengkelAktif[0] ? " (aktif)" : "";
            System.out.println((i + 1) + ". " + bengkelList.get(i).getNamaBengkel() + aktif);
        }

        Integer pilihan = bacaAngka("Pilih bengkel: ", 1, bengkelList.size());
        if (pilihan == null) {
            return false;
        }
        bengkelAktif[0] = pilihan - 1;
        System.out.println("Bengkel aktif: "
                + bengkelList.get(bengkelAktif[0]).getNamaBengkel());
        return true;
    }

    private static void tampilkanLaporanMontir(Bengkel bengkel) {
        boolean adaMontir = false;
        for (PegawaiBengkel pegawai : bengkel.getDaftarPegawai()) {
            if (pegawai instanceof Montir) {
                Montir montir = (Montir) pegawai;
                System.out.print(montir.buatLaporan());
                adaMontir = true;
            }
        }
        if (!adaMontir) {
            System.out.println("Belum ada montir di bengkel ini.");
        }
    }

    private static void isiDataAwal(Bengkel bengkel) {
        bengkel.tambahPegawai(new Montir(
                "P-001", "Budi Santoso", 48, JenisKendaraan.MOBIL,
                "Mesin & Sistem Pendingin"));
        bengkel.tambahPegawai(new Mekanik(
                "P-002", "Sari Wulandari", 36, JenisKendaraan.MOBIL,
                List.of(FokusBagian.MESIN, FokusBagian.SISTEM_PENDINGIN,
                        FokusBagian.REM)));

        Kendaraan avanza = new Kendaraan(
                "Toyota", "Avanza (MPV)", JenisKendaraan.MOBIL, 2018, "Jepang");
        avanza.tambahMasalah(new MasalahKendaraan(
                "Radiator bocor", FokusBagian.SISTEM_PENDINGIN));
        avanza.tambahMasalah(new MasalahKendaraan(
                "Kampas rem aus", FokusBagian.REM));
        avanza.tambahMasalah(new MasalahKendaraan(
                "AC tidak dingin", FokusBagian.INTERIOR_AC));
        bengkel.terimaKendaraan(avanza);
    }

    public static void main(String[] args) {
        List<Bengkel> bengkelList = new ArrayList<>();
        bengkelList.add(new Bengkel("Bengkel Maju Jaya", 5));
        isiDataAwal(bengkelList.get(0));
        int[] bengkelAktif = {0};

        while (true) {
            Bengkel bengkel = bengkelList.get(bengkelAktif[0]);
            System.out.println("\n========== " + bengkel.getNamaBengkel() + " ==========\n"
                    + "1. Tambah pegawai\n"
                    + "2. Tambah kendaraan\n"
                    + "3. Tampilkan ringkasan\n"
                    + "4. Proses kendaraan\n"
                    + "5. Tambah bengkel\n"
                    + "6. Ganti bengkel\n"
                    + "7. Tampilkan laporan montir\n"
                    + "0. Keluar");

            Integer pilihan = bacaAngka("Pilih menu: ", 0, 7);
            if (pilihan == null || pilihan == 0) {
                break;
            }

            boolean lanjut = true;
            switch (pilihan) {
                case 1:
                    lanjut = tambahPegawai(bengkel);
                    break;
                case 2:
                    lanjut = tambahKendaraan(bengkel);
                    break;
                case 3:
                    bengkel.cetakRingkasan();
                    break;
                case 4:
                    lanjut = prosesKendaraan(bengkel);
                    break;
                case 5:
                    lanjut = tambahBengkel(bengkelList, bengkelAktif);
                    break;
                case 6:
                    lanjut = gantiBengkel(bengkelList, bengkelAktif);
                    break;
                case 7:
                    tampilkanLaporanMontir(bengkel);
                    break;
                default:
                    throw new IllegalStateException("Pilihan menu tidak valid.");
            }
            if (!lanjut) {
                break;
            }
        }
        System.out.println("Program selesai.");
    }
}
