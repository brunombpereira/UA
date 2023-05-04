package Enums;

public enum AlimentOrigin {
    ANIMAL, VEGETARIANO;

    public static AlimentOrigin alimentOrigin(String string) {
        return switch (string.toLowerCase()) {
            case "vegetariano" -> VEGETARIANO;
            default -> ANIMAL;
        };
    }

    @Override
    public String toString() {
        return switch (this) {
            case ANIMAL -> "Animal";
            case VEGETARIANO -> "Vegetariano";
        };
    }
}
