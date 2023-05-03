package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class Empresa {
    private String name, postalCode, email;

    public Empresa(String name, String postalCode, String email) {
        if (validatePostalCode(postalCode) && validateEmail(email)) {
            this.name = name;
            this.postalCode = postalCode;
            this.email = email;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPostalCode() {
        return postalCode;
    }

    public void setPostalCode(String postalCode) {
        this.postalCode = postalCode;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (getClass() != o.getClass()) return false;
        Empresa empresa = (Empresa) o;
        return Objects.equals(name, empresa.name) && Objects.equals(postalCode, empresa.postalCode) && Objects.equals(email, empresa.email);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, postalCode, email);
    }

    @Override
    public String toString() {
        return "Nome: " + name + "\nCódigo Postal: " + postalCode + "\nEmail: " + email;
    }
}
