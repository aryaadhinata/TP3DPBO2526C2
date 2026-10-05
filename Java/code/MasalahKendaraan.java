import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Map;

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

    public MasalahKendaraan(String nama, FokusBagian bagian) {
        this(nama, bagian.name());
    }

    public MasalahKendaraan(String nama, String bagian) {
        this.NamaMasalah = nama;
        this.BagianBermasalah = bagian;
        this.TerakhirDiperbaiki = "-";
    }

    public MasalahKendaraan(MasalahKendaraan masalah) {
        this.NamaMasalah = masalah.NamaMasalah;
        this.BagianBermasalah = masalah.BagianBermasalah;
        this.TerakhirDiperbaiki = masalah.TerakhirDiperbaiki;
    }

    public String getNamaMasalah() {
        return NamaMasalah;
    }

    public String getBagianBermasalah() {
        return BagianBermasalah;
    }

    public String getTerakhirDiperbaiki() {
        return TerakhirDiperbaiki;
    }

    public boolean sudahDiperbaiki() {
        return !TerakhirDiperbaiki.equals("-");
    }

    public void updateStatusPerbaikan() {
        TerakhirDiperbaiki = LocalDateTime.now().format(FORMAT_WAKTU);
    }

    public int getEstimasiWaktu() {
        return ESTIMASI_WAKTU.getOrDefault(BagianBermasalah, 3);
    }
}
