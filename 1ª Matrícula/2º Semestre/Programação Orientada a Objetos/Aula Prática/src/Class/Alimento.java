package Class;

import Enums.AlimentOrigin;

import java.util.Objects;

public abstract class Alimento {
    private double proteins, calories, weight;

    public Alimento(double proteins, double calories, double weight) {
        this.proteins = proteins;
        this.calories = calories;
        this.weight = weight;
    }

    public abstract AlimentOrigin getAlimentOrigin();
    public double getProteins() {
        return proteins;
    }

    public void setProteins(double proteins) {
        this.proteins = proteins;
    }

    public double getCalories() {
        return calories;
    }

    public void setCalories(double calories) {
        this.calories = calories;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Alimento alimento = (Alimento) o;
        return Double.compare(alimento.proteins, proteins) == 0 && Double.compare(alimento.calories, calories) == 0 && Double.compare(alimento.weight, weight) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(proteins, calories, weight);
    }

    @Override
    public String toString() {
        return "A carne tem " + proteins + " proteínas, " + calories + "calorias e " + weight + "g.";
    }
}
