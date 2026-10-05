public abstract class PegawaiBengkel {
    private final String IdPegawai;
    private final String Nama;
    private final int Performa;
    private final JenisKendaraan Spesialisasi;

    protected PegawaiBengkel(String id, String nama, int performa,
                             JenisKendaraan spesialisasi) {
        this.IdPegawai = id;
        this.Nama = nama;
        this.Performa = performa;
        this.Spesialisasi = spesialisasi;
    }

    public String getIdPegawai() {
        return IdPegawai;
    }

    public String getNama() {
        return Nama;
    }

    public int getPerforma() {
        return Performa;
    }

    public JenisKendaraan getSpesialisasi() {
        return Spesialisasi;
    }

    public int hitungPerfoma() {
        return Performa;
    }

    public String getDetailPegawai() {
        return "[" + IdPegawai + "] " + Nama + " | Spesialisasi: "
                + Spesialisasi + " | Performa: " + Performa + " bulan";
    }

    public abstract void tanganiKendaraan(Kendaraan kendaraan);
}
