import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Pegawai pemeriksa turunan {@link PegawaiBengkel} yang mencatat temuan
 * sesuai kategori spesialisasi dan daftar fokus bagian.
 *
 * <p>Daftar fokus kosong berarti seluruh bagian diperiksa. Temuan disimpan
 * sebagai salinan status saat inspeksi dan diurutkan dari estimasi terlama.</p>
 */
public class Mekanik extends PegawaiBengkel {
    private final List<MasalahKendaraan> DaftarPemeriksaan = new ArrayList<>();
    private final List<FokusBagian> FokusPemeriksaan;

    /**
     * Membuat Mekanik dengan spesialisasi kendaraan dan fokus pemeriksaan.
     *
     * @param id identitas pegawai
     * @param nama nama Mekanik
     * @param performa performa dasar dalam bulan
     * @param spesialisasi kategori kendaraan yang dapat diperiksa
     * @param fokus bagian yang diperiksa; daftar kosong berarti semua bagian
     */
    public Mekanik(String id, String nama, int performa,
                    JenisKendaraan spesialisasi, List<FokusBagian> fokus) {
        super(id, nama, performa, spesialisasi);
        this.FokusPemeriksaan = new ArrayList<>(fokus);
    }

    private boolean sesuaiFokus(MasalahKendaraan masalah) {
        return FokusPemeriksaan.isEmpty()
                || FokusPemeriksaan.stream()
                .anyMatch(fokus -> fokus.name().equals(masalah.getBagianBermasalah()));
    }

    /**
     * Memeriksa masalah yang sesuai spesialisasi dan fokus Mekanik.
     *
     * @param kendaraan kendaraan yang akan diinspeksi
     *
     * Masalah yang tidak sesuai fokus dilewati dan tidak masuk daftar temuan.
     */
    public void periksaKendaraan(Kendaraan kendaraan) {
        if (kendaraan.getJenis() != getSpesialisasi()) {
            System.out.println("  [Mekanik " + getNama() + "] Menolak: kendaraan "
                    + kendaraan.getJenis() + " bukan spesialisasinya ("
                    + getSpesialisasi() + ").");
            return;
        }

        System.out.println("  [Mekanik " + getNama() + "] Memeriksa "
                + kendaraan.getDetailKendaraan());
        for (MasalahKendaraan masalah : kendaraan.getDaftarMasalah()) {
            if (!sesuaiFokus(masalah)) {
                System.out.println("    - Dilewati (di luar fokus): "
                        + masalah.getNamaMasalah() + " ["
                        + masalah.getBagianBermasalah() + "]");
                continue;
            }
            String status = masalah.sudahDiperbaiki()
                    ? "SUDAH diperbaiki" : "BELUM diperbaiki";
            System.out.println("    - Dicatat: " + masalah.getNamaMasalah()
                    + " [" + masalah.getBagianBermasalah() + "] status: " + status);
            DaftarPemeriksaan.add(new MasalahKendaraan(masalah));
        }
        updatePemeriksaan();
    }

    /** Mengurutkan temuan berdasarkan estimasi waktu menurun. */
    public void updatePemeriksaan() {
        DaftarPemeriksaan.sort(
                Comparator.comparingInt(MasalahKendaraan::getEstimasiWaktu).reversed());
    }

    /**
     * Mengambil temuan pemeriksaan yang telah diprioritaskan.
     *
     * @return daftar masalah hasil inspeksi
     */
    public List<MasalahKendaraan> getDaftarPemeriksaan() {
        return DaftarPemeriksaan;
    }

    /** @return performa dasar ditambah satu poin untuk setiap temuan */
    @Override
    public int hitungPerfoma() {
        return super.hitungPerfoma() + DaftarPemeriksaan.size();
    }

    /** @return detail pegawai beserta fokus dan jumlah temuan */
    @Override
    public String getDetailPegawai() {
        String fokus = FokusPemeriksaan.stream()
                .map(Enum::name)
                .collect(Collectors.joining(", "));
        return "MEKANIK " + super.getDetailPegawai() + " | Fokus: "
                + fokus + " | Temuan: " + DaftarPemeriksaan.size();
    }

    /** Meneruskan pemanggilan polimorfik ke {@link #periksaKendaraan(Kendaraan)}. */
    @Override
    public void tanganiKendaraan(Kendaraan kendaraan) {
        periksaKendaraan(kendaraan);
    }
}
