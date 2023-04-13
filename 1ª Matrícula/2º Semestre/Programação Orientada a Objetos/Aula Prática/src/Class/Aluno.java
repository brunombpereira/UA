package Class;

public class Aluno extends Pessoa{
    private int nMec;
    private static int nextNMec = 100;
    private DateYMD rDate;

    public Aluno(String name, int cc, DateYMD birthDate, DateYMD rDate) {
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

    public DateYMD getrDate() {
        return rDate;
    }

    public void setrDate(DateYMD rDate) {
        this.rDate = rDate;
    }

    public String toString() {
        return getName() + ":\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento: " + getBirthDate().toString() + "\nNúmero Mecanográfico: " + getnMec() + "\nData de Inscrição: " + getrDate().toString();
    }
}
