package aula05;

class Property {
    private int id, numberRooms;
    private String location;
    private double price;
    private boolean available;
    private DateYMD initialDate, finalDate;

    private static int nextId = 1000;

    public Property(String location, int numberRooms, double price) {
        this.id = nextId;
        nextId++;
        this.location = location;
        this.numberRooms = numberRooms;
        this.available = true;
        this.initialDate = null;
        this.finalDate = null;
    }

    public String toString() {
        String status = "sim";

        if (!available) {
            status = "não";
        } else if (initialDate != null && finalDate != null) {
            status = "leilão " + initialDate + " : " + finalDate;
        }

        return "Imóvel: " + id + "; quartos: " +
                numberRooms + "; localidade: " + location + "; preço: " + price + "; disponível: " + status;
    }

    public int getId() {
        return id;
    }

    public int getNumberRooms() {
        return numberRooms;
    }

    public String getLocation() {
        return location;
    }

    public double getPrice() {
        return price;
    }

    public boolean isAvailable() {
        return available;
    }

    public DateYMD getInitialDate() {
        return initialDate;
    }

    public DateYMD getFinalDate() {
        return finalDate;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public void setInitialDate(DateYMD date) {
        this.initialDate = date;
    }

    public void setFinalDate(DateYMD finalDate) {
        this.finalDate = finalDate;
    }
}


class Agency {
    private Property[] properties = new Property[5];
    private int numberProperties = 0;

    public void newProperty(String location, int numberRooms, double price) {
        Property property = new Property(location, numberRooms, price);

        properties[numberProperties++] = property;
    }

    public  void sell(int id) {
        for (int i = 0; i < numberProperties; i++) {
            if (properties[i].getId() == id) {
                if (properties[i].isAvailable()) {
                    System.out.println("Imóvel " + id + "vendido.");
                    properties[i].setAvailable(false);
                }
                else{
                    System.out.println("Imóvel " + id + "não está disponível.");
                }
                return;
            }
        }
        System.out.println("Imóvel " + id + " não existe.");
    }

    public void setAuction(int id, DateYMD initialDate, int duration) {
        for (int i = 0; i < numberProperties; i++) {
            if (properties[i].getId() == id) {
                properties[i].setInitialDate(initialDate);

                for (int j = 0; j < duration; j++) {
                    initialDate.increment();
                }

                properties[i].setFinalDate(initialDate);
            }
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Propriedades:\n");

        for (int i = 0; i < numberProperties; i++) {
            sb.append(properties[i].toString());
            sb.append("\n");
        }
        return sb.toString();
    }
}


public class Ex3 {
    public static void main(String[] args) {
        Agency imobiliaria = new Agency();
        imobiliaria.newProperty("Glória", 2, 30000);
        imobiliaria.newProperty("Vera Cruz", 1, 25000);
        imobiliaria.newProperty("Santa Joana", 3, 32000);
        imobiliaria.newProperty("Aradas", 2, 24000);
        imobiliaria.newProperty("São Bernardo", 2, 20000);

        imobiliaria.sell(1001);
        imobiliaria.setAuction(1002, new DateYMD(2023, 3, 21), 4);
        imobiliaria.setAuction(1003, new DateYMD(2023, 4, 1), 3);
        imobiliaria.setAuction(1001, new DateYMD(2023, 4, 1), 4);
        imobiliaria.setAuction(1010, new DateYMD(2023, 4, 1), 4);

        System.out.println(imobiliaria);

    }
}