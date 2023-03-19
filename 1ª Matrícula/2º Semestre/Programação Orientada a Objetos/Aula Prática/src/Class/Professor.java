package Class;

public class Professor extends Pessoa{
    private String category, department;

    public Professor(String name, int cc, Date birthDate, String category, String department) {
        super(name, cc, birthDate);
        this.category = category;
        this.department = department;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String toString() {
        return getName() + ":\nNúmero de Cartão de Cidadão: " + getCc() + "\nData de Nascimento" + getBirthDate().toString() + "\nCategoria: " + getCategory() + "\nDepartamento: " + getDepartment();
    }
}
