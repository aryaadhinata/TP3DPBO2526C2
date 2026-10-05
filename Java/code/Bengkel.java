import java.util.ArrayList;
import java.util.List;

public class Bengkel {
    private final String NamaBengkel;
    private final List<PegawaiBengkel> DaftarPegawai = new ArrayList<>();
    private final List<Kendaraan> DaftarKendaraan = new ArrayList<>();
    private final int Kapasitas;

    public Bengkel(String nama, int kapasitas) {
        this.NamaBengkel = nama;
        this.Kapasitas = kapasitas;
    }

    public String getNamaBengkel() {
        return NamaBengkel;
    }

    public void tambahPegawai(PegawaiBengkel pegawai) {
        if (pegawai != null) {
            DaftarPegawai.add(pegawai);
        }
    }

    public boolean terimaKendaraan(Kendaraan kendaraan) {
        if (kapasitasPenuh()) {
            return false;
        }
        DaftarKendaraan.add(kendaraan);
        return true;
    }

    public boolean kapasitasPenuh() {
        return DaftarKendaraan.size() >= Kapasitas;
    }

    public void prosesKendaraan(int indeksKendaraan) {
        if (indeksKendaraan < 0 || indeksKendaraan >= DaftarKendaraan.size()) {
            return;
        }
        Kendaraan kendaraan = DaftarKendaraan.get(indeksKendaraan);
        for (PegawaiBengkel pegawai : DaftarPegawai) {
            pegawai.tanganiKendaraan(kendaraan);
        }
    }

    public List<PegawaiBengkel> getDaftarPegawai() {
        return DaftarPegawai;
    }

    public List<Kendaraan> getDaftarKendaraan() {
        return DaftarKendaraan;
    }

    public void cetakRingkasan() {
        System.out.println("Bengkel   : " + NamaBengkel
                + "\nKapasitas : " + DaftarKendaraan.size() + "/" + Kapasitas
                + " kendaraan\n");

        System.out.println("-- DaftarPegawai (" + DaftarPegawai.size() + ") --");
        for (int i = 0; i < DaftarPegawai.size(); i++) {
            PegawaiBengkel pegawai = DaftarPegawai.get(i);
            System.out.println((i + 1) + ". " + pegawai.getDetailPegawai()
                    + " | Skor: " + pegawai.hitungPerfoma());
        }

        System.out.println("\n-- DaftarKendaraan (" + DaftarKendaraan.size() + ") --");
        for (int i = 0; i < DaftarKendaraan.size(); i++) {
            Kendaraan kendaraan = DaftarKendaraan.get(i);
            System.out.println((i + 1) + ". " + kendaraan.getDetailKendaraan());
            for (MasalahKendaraan masalah : kendaraan.getDaftarMasalah()) {
                System.out.println("     * " + masalah.getNamaMasalah() + " ["
                        + masalah.getBagianBermasalah() + "] estimasi "
                        + masalah.getEstimasiWaktu() + " jam, terakhir diperbaiki: "
                        + masalah.getTerakhirDiperbaiki());
            }
        }
    }
}
