import java.util.ArrayList;
import java.util.List;

/**
 * Pegawai teknisi turunan {@link PegawaiBengkel} yang memperbaiki masalah
 * kendaraan dan menyimpan salinan setiap perbaikan pada laporan historis.
 * Kendaraan yang tidak sesuai spesialisasi tidak akan diproses.
 */
public class Montir extends PegawaiBengkel {
    private final String Keahlian;
    private final List<MasalahKendaraan> LaporanPerawatan = new ArrayList<>();

    /**
     * Membuat Montir dengan keahlian teknis dan spesialisasi kendaraan.
     *
     * @param id identitas pegawai
     * @param nama nama Montir
     * @param performa performa dasar dalam bulan
     * @param spesialisasi kategori kendaraan yang dapat diperbaiki
     * @param keahlian ringkasan keahlian teknis
     */
    public Montir(String id, String nama, int performa,
                    JenisKendaraan spesialisasi, String keahlian) {
        super(id, nama, performa, spesialisasi);
        this.Keahlian = keahlian;
    }

    /**
     * Memperbaiki seluruh masalah yang belum selesai pada kendaraan.
     *
     * @param kendaraan kendaraan yang akan diperbaiki
     *
     * Masalah selesai dilewati pada pemanggilan berikutnya untuk mencegah
     * pencatatan perbaikan yang sama lebih dari satu kali.
     */
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

    /**
     * Membentuk laporan yang berisi seluruh perbaikan historis Montir.
     *
     * @return laporan perawatan berformat teks
     */
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

    /** @return performa dasar ditambah dua poin untuk setiap perbaikan */
    @Override
    public int hitungPerfoma() {
        return super.hitungPerfoma() + LaporanPerawatan.size() * 2;
    }

    /** @return detail pegawai termasuk keahlian dan jumlah laporan */
    @Override
    public String getDetailPegawai() {
        return "MONTIR  " + super.getDetailPegawai() + " | Keahlian: "
                + Keahlian + " | Laporan: " + LaporanPerawatan.size();
    }

    /** Meneruskan pemanggilan polimorfik ke {@link #perbaikan(Kendaraan)}. */
    @Override
    public void tanganiKendaraan(Kendaraan kendaraan) {
        perbaikan(kendaraan);
    }
}
