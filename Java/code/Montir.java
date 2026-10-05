import java.util.ArrayList;
import java.util.List;

public class Montir extends PegawaiBengkel {
    private final String Keahlian;
    private final List<MasalahKendaraan> LaporanPerawatan = new ArrayList<>();

    public Montir(String id, String nama, int performa,
                  JenisKendaraan spesialisasi, String keahlian) {
        super(id, nama, performa, spesialisasi);
        this.Keahlian = keahlian;
    }

    public void perbaikan(Kendaraan kendaraan) {
        if (kendaraan.getJenis() != getSpesialisasi()) {
            System.out.println("  [Montir " + getNama() + "] Menolak: kendaraan "
                    + kendaraan.getJenis() + " bukan spesialisasinya ("
                    + getSpesialisasi() + ").");
            return;
        }

        for (MasalahKendaraan masalah : kendaraan.getDaftarMasalah()) {
            if (masalah.sudahDiperbaiki()) {
                continue;
            }
            System.out.println("  [Montir " + getNama() + "] Memperbaiki '"
                    + masalah.getNamaMasalah() + "' ("
                    + masalah.getBagianBermasalah() + ", estimasi "
                    + masalah.getEstimasiWaktu() + " jam)");
            masalah.updateStatusPerbaikan();
            LaporanPerawatan.add(new MasalahKendaraan(masalah));
        }
    }

    public String buatLaporan() {
        StringBuilder laporan = new StringBuilder()
                .append("LAPORAN PERAWATAN - Montir ")
                .append(getNama())
                .append(" (Keahlian: ")
                .append(Keahlian)
                .append(")\n");
        if (LaporanPerawatan.isEmpty()) {
            laporan.append("  (belum ada perbaikan)\n");
        }
        for (int i = 0; i < LaporanPerawatan.size(); i++) {
            MasalahKendaraan masalah = LaporanPerawatan.get(i);
            laporan.append("  ").append(i + 1).append(". ")
                    .append(masalah.getNamaMasalah()).append(" [")
                    .append(masalah.getBagianBermasalah())
                    .append("] - selesai: ")
                    .append(masalah.getTerakhirDiperbaiki()).append('\n');
        }
        return laporan.toString();
    }

    @Override
    public int hitungPerfoma() {
        return super.hitungPerfoma() + LaporanPerawatan.size() * 2;
    }

    @Override
    public String getDetailPegawai() {
        return "MONTIR  " + super.getDetailPegawai() + " | Keahlian: "
                + Keahlian + " | Laporan: " + LaporanPerawatan.size();
    }

    @Override
    public void tanganiKendaraan(Kendaraan kendaraan) {
        perbaikan(kendaraan);
    }
}
