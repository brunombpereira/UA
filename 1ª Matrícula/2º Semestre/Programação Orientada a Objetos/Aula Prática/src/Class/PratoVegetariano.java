package Class;

import Enums.AlimentOrigin;

import java.util.LinkedList;
import java.util.Objects;

public class PratoVegetariano extends Prato{
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

    public PratoVegetariano(String name) {
        super(name);
    }

    public void addIngrediant(Alimento alimento) {
        if (alimento.getAlimentOrigin() == AlimentOrigin.VEGETARIANO) {
            alimentos.add(alimento);
        } else {
            System.out.println("O alimento tem de ser de origem vegetal.");
        }
    }

    public void removeIngrediant(Alimento alimento) {
        alimentos.remove(alimento);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        PratoVegetariano that = (PratoVegetariano) o;
        return Objects.equals(alimentos, that.alimentos);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), alimentos);
    }

    @Override
    public String toString() {
        return super.toString() + " - Prato Vegetariano";
    }
}
