/**
 * Kelas dasar abstrak untuk identitas dan perilaku bersama pegawai bengkel.
 *
 * <p>{@link Bengkel} menyimpan pegawai melalui kelas ini. Metode
 * {@link #tanganiKendaraan(Kendaraan)} menjadi titik dispatch polimorfik
 * untuk implementasi Montir dan Mekanik.</p>
 */
public abstract class PegawaiBengkel {
    private final String IdPegawai;
    private final String Nama;
    private final int Performa;
    private final JenisKendaraan Spesialisasi;

    /**
     * Membuat pegawai dengan identitas, performa dasar, dan spesialisasi.
     *
     * @param id identitas pegawai
     * @param nama nama pegawai
     * @param performa performa dasar dalam bulan
     * @param spesialisasi kategori kendaraan yang dapat ditangani
     */
    protected PegawaiBengkel(String id, String nama, int performa,
                            JenisKendaraan spesialisasi) {
        this.IdPegawai = id;
        this.Nama = nama;
        this.Performa = performa;
        this.Spesialisasi = spesialisasi;
    }

    /**
     * Mengambil identitas pegawai.
     *
     * @return ID pegawai
     */
    public String getIdPegawai() {
        return IdPegawai;
    }

    /**
     * Mengambil nama pegawai.
     *
     * @return nama pegawai
     */
    public String getNama() {
        return Nama;
    }

    /**
     * Mengambil performa dasar pegawai.
     *
     * @return performa dalam bulan
     */
    public int getPerforma() {
        return Performa;
    }

    /**
     * Mengambil kategori kendaraan yang menjadi spesialisasi pegawai.
     *
     * @return jenis kendaraan spesialisasi
     */
    public JenisKendaraan getSpesialisasi() {
        return Spesialisasi;
    }

    /**
     * Menghitung performa dasar sebelum kontribusi hasil kerja turunan.
     *
     * @return performa dasar dalam bulan
     */
    public int hitungPerfoma() {
        return Performa;
    }

    /**
     * Membentuk detail pegawai untuk ditampilkan pada ringkasan bengkel.
     *
     * @return teks identitas, spesialisasi, dan performa dasar
     */
    public String getDetailPegawai() {
        return "[" + IdPegawai + "] " + Nama + " | Spesialisasi: "
                + Spesialisasi + " | Performa: " + Performa + " bulan";
    }

    /**
     * Menangani kendaraan sesuai tanggung jawab kelas pegawai turunan.
     *
     * @param kendaraan kendaraan yang sedang dilayani bengkel
     */
    public abstract void tanganiKendaraan(Kendaraan kendaraan);
}
