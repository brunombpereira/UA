package Class;

public class Contacto extends Pessoa {
    private int id, phoneNumber;
    private int nextid = 1;
    private String email;

    public Contacto(String name, int cc, Date birthDate, int phoneNumber, String email) {
        super(name, cc, birthDate);

        if (validateContact(phoneNumber, email)) {
            this.id = nextid;
            this.nextid++;
            this.phoneNumber = phoneNumber;
            this.email = email;
        }

    }

    public boolean validatePhoneNumber(int phoneNumber) {
        if (Integer.toString(phoneNumber).length() == 9 && (phoneNumber / 100000000) == 9) {
            return true;
        }
        else {
            System.out.println("Número de telemóvel inválido. O número tem de conter 9 dígitos e tem de começar por 9");
            return false;
        }
    }

    public boolean validateEmail(String email) {
        if (email.contains("@") && (email.endsWith(".com") || email.endsWith(".pt"))) {
            return true;
        }
        else {
            System.out.println("Email inválido. O email tem de conter um '@' e tem de acabar com '.com' ou '.pt'.");
            return false;
        }
    }

    public boolean validateContact(int phoneNumber, String email) {
        return validatePhoneNumber(phoneNumber) && validateEmail(email);
    }

    public int getId() {
        return id;
    }

    public int getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(int phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String toString() {
        return "ID: " + getId() + "\nNome: " + getName() + "\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento: " + getBirthDate() +"\nNúmero de Telemóvel: " + getPhoneNumber() + "\nEmail: " + getEmail();
    }
}
