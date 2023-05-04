package Enums;

public enum FishState {
    CONGELADO, FRESCO;

    public static FishState fromString(String string) {
        return switch (string.toLowerCase()) {
            case "congelado" -> CONGELADO;
            case "fresco" -> FRESCO;
            default -> null;
        };
    }

    @Override
    public String toString() {
        return switch (this) {
            case CONGELADO -> "Congelado";
            case FRESCO -> "Fresco";
        };
    }
}
