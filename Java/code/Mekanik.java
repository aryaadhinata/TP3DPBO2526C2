import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/** Pegawai pemeriksa yang mencatat masalah sesuai fokus dan spesialisasinya. */
public class Mekanik extends PegawaiBengkel {
    private final List<MasalahKendaraan> DaftarPemeriksaan = new ArrayList<>();
    private final List<FokusBagian> FokusPemeriksaan;

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

    public void updatePemeriksaan() {
        DaftarPemeriksaan.sort(
                Comparator.comparingInt(MasalahKendaraan::getEstimasiWaktu).reversed());
    }

    public List<MasalahKendaraan> getDaftarPemeriksaan() {
        return DaftarPemeriksaan;
    }

    @Override
    public int hitungPerfoma() {
        return super.hitungPerfoma() + DaftarPemeriksaan.size();
    }

    @Override
    public String getDetailPegawai() {
        String fokus = FokusPemeriksaan.stream()
                .map(Enum::name)
                .collect(Collectors.joining(", "));
        return "MEKANIK " + super.getDetailPegawai() + " | Fokus: "
                + fokus + " | Temuan: " + DaftarPemeriksaan.size();
    }

    @Override
    public void tanganiKendaraan(Kendaraan kendaraan) {
        periksaKendaraan(kendaraan);
    }
}
