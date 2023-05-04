package Class;

import java.util.LinkedList;
import java.util.Objects;

public class Prato {
    private String name;
    private final LinkedList<Alimento> alimentos = new LinkedList<>() {
        @Override
        public String toString() {
            StringBuilder stringBuilder = new StringBuilder();
            for (Alimento alimento : this) {
                stringBuilder.append(alimento).append("\n");
            }
            return stringBuilder.toString();
        }
    };

    public Prato(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public LinkedList<Alimento> getAlimentos() {
        return alimentos;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Prato prato = (Prato) o;
        return Objects.equals(name, prato.name) && Objects.equals(alimentos, prato.alimentos);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, alimentos);
    }

    @Override
    public String toString() {
        return "Prato '" + getName() + "', composto por " + alimentos.size() + " Ingredientes";
    }

    public void addIngrediant(Alimento alimento) {
        alimentos.add(alimento);
    }

    public void removeIngrediant(Alimento alimento) {
        alimentos.remove(alimento);
    }
}
