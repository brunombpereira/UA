package Class;

public class Pessoa {
    private String name;
    private int cc;
    private Date birthDate;

    public Pessoa(String name, int cc, Date birthDate) {
        if (validateCC(cc)) {
            this.name = name;
            this.cc = cc;
            this.birthDate = birthDate;
        }
    }

    public  static boolean validateCC(int cc) {
        if (Integer.toString(cc).length() == 8) {
            return true;
        }
        else {
            System.out.println("Número de Cartão de Cidadão inválido.\nO número do Cartão de Cidadão deve conter apenas os primeiros 8 números.");
            return false;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCc() {
        return cc;
    }

    public void setCc(int cc) {
        this.cc = cc;
    }

    public Date getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(Date birthDate) {
        this.birthDate = birthDate;
    }

    public String toString() {
        return getName() + ":\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento: " + getBirthDate().toString();
    }
}
