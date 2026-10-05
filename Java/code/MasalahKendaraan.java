import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Map;

/**
 * Mencatat deskripsi, bagian terkait, estimasi waktu, dan status perbaikan.
 *
 * <p>Nama bagian diselaraskan dengan {@link FokusBagian} agar dapat
 * dicocokkan terhadap fokus inspeksi Mekanik. Nilai waktu {@code "-"}
 * menandakan masalah belum pernah diperbaiki.</p>
 */
public class MasalahKendaraan {
    private static final DateTimeFormatter FORMAT_WAKTU =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
    private static final Map<String, Integer> ESTIMASI_WAKTU = Map.ofEntries(
            Map.entry("MESIN", 8),
            Map.entry("TRANSMISI", 6),
            Map.entry("RANGKA_CHASIS", 10),
            Map.entry("SUSPENSI_KEMUDI", 5),
            Map.entry("SISTEM_PENDINGIN", 4),
            Map.entry("KELISTRIKAN", 4),
            Map.entry("SISTEM_PEMBUANGAN", 3),
            Map.entry("BODY_EKSTERIOR", 6),
            Map.entry("INTERIOR_AC", 3),
            Map.entry("REM", 2),
            Map.entry("RODA_BAN", 1)
    );

    private final String NamaMasalah;
    private final String BagianBermasalah;
    private String TerakhirDiperbaiki;

    /**
     * Membuat masalah baru yang belum diperbaiki.
     *
     * @param nama deskripsi masalah
     * @param bagian bagian kendaraan yang bermasalah
     */
    public MasalahKendaraan(String nama, FokusBagian bagian) {
        this(nama, bagian.name());
    }

    /**
     * Membuat masalah baru dari nama bagian yang sudah dinormalisasi.
     *
     * @param nama deskripsi masalah
     * @param bagian nama bagian, biasanya nilai {@link FokusBagian#name()}
     */
    public MasalahKendaraan(String nama, String bagian) {
        this.NamaMasalah = nama;
        this.BagianBermasalah = bagian;
        this.TerakhirDiperbaiki = "-";
    }

    /**
     * Menyalin data masalah, termasuk waktu perbaikan yang sudah tercatat.
     *
     * @param masalah masalah sumber yang disalin
     */
    public MasalahKendaraan(MasalahKendaraan masalah) {
        this.NamaMasalah = masalah.NamaMasalah;
        this.BagianBermasalah = masalah.BagianBermasalah;
        this.TerakhirDiperbaiki = masalah.TerakhirDiperbaiki;
    }

    /**
     * Mengambil deskripsi masalah.
     *
     * @return nama masalah
     */
    public String getNamaMasalah() {
        return NamaMasalah;
    }

    /**
     * Mengambil nama bagian kendaraan yang bermasalah.
     *
     * @return nama bagian
     */
    public String getBagianBermasalah() {
        return BagianBermasalah;
    }

    /**
     * Mengambil waktu perbaikan terakhir.
     *
     * @return waktu perbaikan atau {@code "-"} jika belum diperbaiki
     */
    public String getTerakhirDiperbaiki() {
        return TerakhirDiperbaiki;
    }

    /**
     * Memeriksa apakah perbaikan sudah pernah dicatat.
     *
     * @return {@code true} jika waktu perbaikan bukan {@code "-"}
     */
    public boolean sudahDiperbaiki() {
        return !TerakhirDiperbaiki.equals("-");
    }

    /** Mencatat waktu lokal saat perbaikan dinyatakan selesai. */
    public void updateStatusPerbaikan() {
        TerakhirDiperbaiki = LocalDateTime.now().format(FORMAT_WAKTU);
    }

    /**
     * Mengambil estimasi durasi berdasarkan bagian yang bermasalah.
     *
     * @return waktu dalam jam; bagian yang tidak dikenal menggunakan nilai
     *         fallback tiga jam
     */
    public int getEstimasiWaktu() {
        return ESTIMASI_WAKTU.getOrDefault(BagianBermasalah, 3);
    }
}
