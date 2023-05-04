package Enums;

public enum WeekDay {
    SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO, DOMINGO;

    public static WeekDay fromString(String string) {
        return switch (string.toLowerCase()) {
            case "segunda" -> SEGUNDA;
            case "terca" -> TERCA;
            case "quarta" -> QUARTA;
            case "quinta" -> QUINTA;
            case "sexta" -> SEXTA;
            case "sabado" -> SABADO;
            case "domingo" -> DOMINGO;
            default -> null;
        };
    }

    @Override
    public String toString() {
        return switch (this) {
            case SEGUNDA -> "Segunda";
            case TERCA -> "Terca";
            case QUARTA -> "Quarta";
            case QUINTA -> "Quinta";
            case SEXTA -> "Sexta";
            case SABADO -> "Sabado";
            case DOMINGO -> "Domingo";
        };
    }
}
