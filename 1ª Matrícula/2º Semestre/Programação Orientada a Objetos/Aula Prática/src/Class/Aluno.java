package Class;

public class Aluno extends Pessoa{
    private int nMec;
    private static int nextNMec = 100;
    private Date rDate;

    public Aluno(String name, int cc, Date birthDate, Date rDate) {
        super(name, cc, birthDate);
        this.nMec = nextNMec;
        nextNMec++;
        this.rDate = rDate;
    }

    public int getnMec() {
        return nMec;
    }

    public void setnMec(int nMec) {
        this.nMec = nMec;
    }

    public Date getrDate() {
        return rDate;
    }

    public void setrDate(Date rDate) {
        this.rDate = rDate;
    }

    public String toString() {
        return getName() + ":\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento: " + getBirthDate().toString() + "\nNúmero Mecanográfico: " + getnMec() + "\nData de Inscrição: " + getrDate().toString();
    }
}
