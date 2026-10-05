import java.util.ArrayList;
import java.util.List;

/** Menyimpan identitas kendaraan beserta masalah yang melekat padanya. */
public class Kendaraan {
    private final String Brand;
    private final String Tipe;
    private final JenisKendaraan Jenis;
    private final int TahunPembuatan;
    private final String AsalProdusen;
    private final List<MasalahKendaraan> DaftarMasalah = new ArrayList<>();

    public Kendaraan(String brand, String tipe, JenisKendaraan jenis,
                     int tahun, String asal) {
        this.Brand = brand;
        this.Tipe = tipe;
        this.Jenis = jenis;
        this.TahunPembuatan = tahun;
        this.AsalProdusen = asal;
    }

    public JenisKendaraan getJenis() {
        return Jenis;
    }

    public List<MasalahKendaraan> getDaftarMasalah() {
        return DaftarMasalah;
    }

    public void tambahMasalah(MasalahKendaraan masalah) {
        DaftarMasalah.add(masalah);
    }

    public String getDetailKendaraan() {
        return Brand + " " + Tipe + " [" + Jenis + "] - " + TahunPembuatan
                + " - Produsen: " + AsalProdusen
                + " - Jumlah masalah: " + DaftarMasalah.size();
    }
}
