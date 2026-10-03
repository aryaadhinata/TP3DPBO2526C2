#pragma once
#include <string>

enum class JenisKendaraan { MOBIL, MOTOR };

enum class FokusBagian {
    MESIN, TRANSMISI, REM, SUSPENSI_KEMUDI, KELISTRIKAN, SISTEM_PENDINGIN,
    SISTEM_PEMBUANGAN, RANGKA_CHASIS, BODY_EKSTERIOR, INTERIOR_AC, RODA_BAN
};

inline std::string toString(JenisKendaraan j) {
    return (j == JenisKendaraan::MOBIL) ? "MOBIL" : "MOTOR";
}

inline std::string toString(FokusBagian f) {
    switch (f) {
        case FokusBagian::MESIN:             return "MESIN";
        case FokusBagian::TRANSMISI:         return "TRANSMISI";
        case FokusBagian::REM:               return "REM";
        case FokusBagian::SUSPENSI_KEMUDI:   return "SUSPENSI_KEMUDI";
        case FokusBagian::KELISTRIKAN:       return "KELISTRIKAN";
        case FokusBagian::SISTEM_PENDINGIN:  return "SISTEM_PENDINGIN";
        case FokusBagian::SISTEM_PEMBUANGAN: return "SISTEM_PEMBUANGAN";
        case FokusBagian::RANGKA_CHASIS:     return "RANGKA_CHASIS";
        case FokusBagian::BODY_EKSTERIOR:    return "BODY_EKSTERIOR";
        case FokusBagian::INTERIOR_AC:       return "INTERIOR_AC";
        case FokusBagian::RODA_BAN:          return "RODA_BAN";
    }
    return "TIDAK_DIKETAHUI";
}
