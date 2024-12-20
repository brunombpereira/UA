package Class;

public class Bolseiro extends Aluno{
    private Professor tadvisor;
    private int scholarship;

    public Bolseiro(String name, int cc, DateYMD birthDate, DateYMD rDate, Professor tadvisor, int scholarship) {
        super(name, cc, birthDate, rDate);
        this.tadvisor = tadvisor;
        this.scholarship = scholarship;
    }

    public Professor getTadvisor() {
        return tadvisor;
    }

    public void setTadvisor(Professor tadvisor) {
        this.tadvisor = tadvisor;
    }

    public int getScholarship() {
        return scholarship;
    }

    public void setScholarship(int scholarship) {
        this.scholarship = scholarship;
    }

    public String toString() {
        return "\n------Bolseiro------\n\n" + getName() + ":\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento: " + getBirthDate().toString() + "\nNúmero Mecanográfico: " + getnMec() + "\nData de Inscrição: " + getrDate().toString() + "\n------Professor Orientador------\n" + tadvisor.getName() + ":\nNúmero de Cartão de Cidadão: " + tadvisor.getCc() + "\nData de Nascimento" + tadvisor.getBirthDate().toString() + "\nCategoria: " + tadvisor.getCategory() + "\nDepartamento: " + tadvisor.getDepartment() + "\nBolsa: " + getScholarship();
    }
}
