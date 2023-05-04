package Class;

import Enums.AlimentOrigin;

import java.util.Objects;

public class Cereal extends Alimento{
    private String name;
    private AlimentOrigin alimentOrigin;

    public Cereal(double proteins, double calories, double weight, String name) {
        super(proteins, calories, weight);
        this.name = name;
        this.alimentOrigin = AlimentOrigin.VEGETARIANO;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public AlimentOrigin getAlimentOrigin() {
        return alimentOrigin;
    }

    public void setAlimentOrigin(AlimentOrigin alimentOrigin) {
        this.alimentOrigin = alimentOrigin;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Cereal cereal = (Cereal) o;
        return Objects.equals(name, cereal.name) && alimentOrigin == cereal.alimentOrigin;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), name, alimentOrigin);
    }

    @Override
    public String toString() {
        return super.toString() + ", cereal: " + name + ", origem: " + alimentOrigin.toString();
    }
}
