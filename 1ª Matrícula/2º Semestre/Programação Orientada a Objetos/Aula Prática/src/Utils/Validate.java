package Utils;

import java.util.regex.Pattern;

public class Validate {
    public static boolean validatePlate(String plate) {
        return Pattern.matches("^[A-Z]{2}-\\d{2}-\\d{2}|\\d{2}-[A-Z]{2}-\\d{2}|\\d{2}-\\d{2}-[A-Z]{2}|[A-Z]{2}-\\d{2}-[A-Z]{2}|[A-Z]{2}-[A-Z]{2}-\\d{2}|\\d{2}-[A-Z]{2}-[A-Z]{2}$", plate);
    }

    public static boolean validatePotency(int potency) {
        return potency > 0;
    }

    public static boolean validateType(String type) {
        if (type.equalsIgnoreCase("desportivo") || type.equalsIgnoreCase("estrada")) {
            return true;
        }else {
            System.out.println("O tipo tem de ser ou 'Desportivo' ou 'Estrada'.");
            return false;
        }
    }

    public static boolean validateSerialNumber(int serialNumber) {
        return serialNumber > 0;
    }

    public static boolean validateLuggageCapacity(int luggageCapacity) {
        return luggageCapacity > 0;
    }

    public static boolean validateLicenceNumber(int licenceNUmber) {
        return licenceNUmber > 0;
    }

    public static boolean validateWeight(int weight) {
        return weight > 0;
    }

    public static boolean validateMaxLoad(int maxLoad) {
        return maxLoad > 0;
    }

    public static boolean validateMaxPassengers(int maxPassengers) {
        return maxPassengers > 0;
    }

    public static boolean validatePostalCode(String postalCode) {
        if (Pattern.matches("^\\d{4}-\\d{3}$", postalCode)) {
            return true;
        } else {
            System.out.println("\nCódigo Postal inválido. Formato: xxxx-xxx\n");
            return false;
        }
    }

    public static boolean validateEmail(String email) {
        if (email.contains("@") && (email.endsWith(".com") || email.endsWith(".pt"))) {
            return true;
        } else {
            System.out.println("Email inválido.");

            if (!email.contains("@")) {
                System.out.println("O email tem de conter um '@'.\n");
            } else {
                System.out.println("O email tem de acabar com '.com' ou '.pt'.\n");
            }
            return false;
        }
    }

    public static boolean validateAutonomy(int autonomy) {
        if (autonomy >= 0) {
            return true;
        } else {
            System.out.println("A autonomia tem de ser igual ou superior a 0.");

            return false;
        }
    }

    public static boolean validateAliment(double proteins, double calories, double weight) {
        if (proteins <= 0) {
            System.out.println("As proteínas têm que ser superior a 0.");
            return false;
        } else if (calories <= 0) {
            System.out.println("As calorias têm que ser maior que 0.");
            return false;
        } else if (weight <= 0) {
            System.out.println("O peso tem que ser maior que 0.");
            return false;
        }
        return true;
    }

    public static boolean validateProduct(int stock, double price) {
        if (stock < 0) {
            System.out.println("O valor do stock tem que ser igual ou maior que 0.");
            return false;
        } else if (price <= 0) {
            System.out.println("O valor do produto tem que ser maior que 0.");
            return false;
        } else {
            return true;
        }
    }

    public static boolean validateDiscount(int discount) {
        if (discount <= 0) {
            System.out.println("O desconto tem que ser maior que 0%.");
            return false;
        } else {
            return true;
        }
    }
}
