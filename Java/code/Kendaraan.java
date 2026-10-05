import java.util.ArrayList;
import java.util.List;

/**
 * Menyimpan identitas kendaraan dan masalah yang menjadi bagian dari
 * kendaraan tersebut. Daftar masalah mengikuti siklus hidup kendaraan
 * (composition pada ERD).
 */
public class Kendaraan {
    private final String Brand;
    private final String Tipe;
    private final JenisKendaraan Jenis;
    private final int TahunPembuatan;
    private final String AsalProdusen;
    private final List<MasalahKendaraan> DaftarMasalah = new ArrayList<>();

    /**
     * Membuat kendaraan dengan identitas produsen dan kategorinya.
     *
     * @param brand merek kendaraan
     * @param tipe model atau tipe kendaraan
     * @param jenis kategori kendaraan
     * @param tahun tahun pembuatan
     * @param asal negara asal produsen
     */
    public Kendaraan(String brand, String tipe, JenisKendaraan jenis,
                     int tahun, String asal) {
        this.Brand = brand;
        this.Tipe = tipe;
        this.Jenis = jenis;
        this.TahunPembuatan = tahun;
        this.AsalProdusen = asal;
    }

    /**
     * Mengambil kategori kendaraan untuk pencocokan spesialisasi pegawai.
     *
     * @return jenis kendaraan
     */
    public JenisKendaraan getJenis() {
        return Jenis;
    }

    /**
     * Mengambil masalah yang melekat pada kendaraan.
     *
     * @return daftar masalah kendaraan
     */
    public List<MasalahKendaraan> getDaftarMasalah() {
        return DaftarMasalah;
    }

    /**
     * Menambahkan masalah sebagai bagian dari kendaraan ini.
     *
     * @param masalah masalah baru yang dilaporkan pada kendaraan
     */
    public void tambahMasalah(MasalahKendaraan masalah) {
        DaftarMasalah.add(masalah);
    }

    /**
     * Membentuk ringkasan identitas kendaraan dan jumlah masalah.
     *
     * @return detail kendaraan untuk ditampilkan
     */
    public String getDetailKendaraan() {
        return Brand + " " + Tipe + " [" + Jenis + "] - " + TahunPembuatan
                + " - Produsen: " + AsalProdusen
                + " - Jumlah masalah: " + DaftarMasalah.size();
    }
}
