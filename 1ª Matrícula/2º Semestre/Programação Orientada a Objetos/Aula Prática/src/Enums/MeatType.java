package Enums;

public enum MeatType {
    VACA, PORCO, PERU, FRANGO, OUTRA;

    public static MeatType fromString(String string) {
        return switch (string.toLowerCase()) {
            case "vaca" -> VACA;
            case "porco" -> PORCO;
            case "peru" -> PERU;
            case "frango" -> FRANGO;
            default -> OUTRA;
        };
    }

    public String toString() {
        return switch (this) {
            case VACA -> "Vaca";
            case PORCO -> "Porco";
            case PERU -> "Peru";
            case FRANGO -> "Frango";
            case OUTRA -> "Outra";
        };
    }
}
