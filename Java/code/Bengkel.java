import java.util.ArrayList;
import java.util.List;

/**
 * Mengelola data dan layanan untuk satu bengkel.
 *
 * <p>Pegawai disimpan menggunakan tipe dasar {@link PegawaiBengkel} agar
 * {@link Montir} dan {@link Mekanik} dapat diproses secara polimorfik.
 * Penerimaan kendaraan dibatasi oleh kapasitas bengkel.</p>
 */
public class Bengkel {
    private final String NamaBengkel;
    private final List<PegawaiBengkel> DaftarPegawai = new ArrayList<>();
    private final List<Kendaraan> DaftarKendaraan = new ArrayList<>();
    private final int Kapasitas;

    /**
     * Membuat bengkel dengan nama dan kapasitas maksimum kendaraan.
     *
     * @param nama nama bengkel
     * @param kapasitas jumlah maksimum kendaraan yang dapat diterima
     */
    public Bengkel(String nama, int kapasitas) {
        this.NamaBengkel = nama;
        this.Kapasitas = kapasitas;
    }

    /**
     * Mengambil nama bengkel yang ditampilkan pada menu dan ringkasan.
     *
     * @return nama bengkel
     */
    public String getNamaBengkel() {
        return NamaBengkel;
    }

    /**
     * Mendaftarkan pegawai ke bengkel.
     *
     * @param pegawai pegawai Montir atau Mekanik yang akan didaftarkan
     */
    public void tambahPegawai(PegawaiBengkel pegawai) {
        if (pegawai != null) {
            DaftarPegawai.add(pegawai);
        }
    }

    /**
     * Menerima kendaraan selama kapasitas belum tercapai.
     *
     * @param kendaraan kendaraan yang diminta masuk ke bengkel
     * @return {@code true} jika diterima; {@code false} jika bengkel penuh
     */
    public boolean terimaKendaraan(Kendaraan kendaraan) {
        if (kapasitasPenuh()) {
            return false;
        }
        DaftarKendaraan.add(kendaraan);
        return true;
    }

    /**
     * Memeriksa apakah jumlah kendaraan sudah mencapai kapasitas.
     *
     * @return {@code true} jika bengkel sudah penuh
     */
    public boolean kapasitasPenuh() {
        return DaftarKendaraan.size() >= Kapasitas;
    }

    /**
     * Meminta semua pegawai menangani kendaraan pada indeks yang diberikan.
     *
     * @param indeksKendaraan indeks berbasis nol dalam daftar kendaraan;
     *                        indeks di luar daftar tidak melakukan perubahan
     */
    public void prosesKendaraan(int indeksKendaraan) {
        if (indeksKendaraan < 0 || indeksKendaraan >= DaftarKendaraan.size()) {
            return;
        }
        Kendaraan kendaraan = DaftarKendaraan.get(indeksKendaraan);
        for (PegawaiBengkel pegawai : DaftarPegawai) {
            pegawai.tanganiKendaraan(kendaraan);
        }
    }

    /**
     * Mengambil daftar pegawai yang terdaftar untuk pemrosesan polimorfik.
     *
     * @return daftar pegawai bengkel
     */
    public List<PegawaiBengkel> getDaftarPegawai() {
        return DaftarPegawai;
    }

    /**
     * Mengambil daftar kendaraan beserta masalah yang dimilikinya.
     *
     * @return daftar kendaraan bengkel
     */
    public List<Kendaraan> getDaftarKendaraan() {
        return DaftarKendaraan;
    }

    /** Mencetak kapasitas, pegawai, kendaraan, dan status masalahnya. */
    public void cetakRingkasan() {
        System.out.println("Bengkel   : " + NamaBengkel
                + "\nKapasitas : " + DaftarKendaraan.size() + "/" + Kapasitas
                + " kendaraan\n");

        System.out.println("-- DaftarPegawai (" + DaftarPegawai.size() + ") --");
        for (int i = 0; i < DaftarPegawai.size(); i++) {
            PegawaiBengkel pegawai = DaftarPegawai.get(i);
            System.out.println((i + 1) + ". " + pegawai.getDetailPegawai()
                    + " | Skor: " + pegawai.hitungPerfoma());
        }

        System.out.println("\n-- DaftarKendaraan (" + DaftarKendaraan.size() + ") --");
        for (int i = 0; i < DaftarKendaraan.size(); i++) {
            Kendaraan kendaraan = DaftarKendaraan.get(i);
            System.out.println((i + 1) + ". " + kendaraan.getDetailKendaraan());
            for (MasalahKendaraan masalah : kendaraan.getDaftarMasalah()) {
                System.out.println("     * " + masalah.getNamaMasalah() + " ["
                        + masalah.getBagianBermasalah() + "] estimasi "
                        + masalah.getEstimasiWaktu() + " jam, terakhir diperbaiki: "
                        + masalah.getTerakhirDiperbaiki());
            }
        }
    }
}
