package aula09;

import java.util.Objects;

public abstract class Plane {
    private int yearOfProduction, maxPassengers, maxVelocity;
    private String id, fabricante, model;

    public Plane(String id, String fabricante, String model, int yearOfProduction, int maxPassengers, int maxVelocity) {
        if (maxPassengers > 0 && maxVelocity > 0) {
            this.id = id;
            this.yearOfProduction = yearOfProduction;
            this.maxPassengers = maxPassengers;
            this.maxVelocity = maxVelocity;
            this.fabricante = fabricante;
            this.model = model;
        }
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public int getYearOfProduction() {
        return yearOfProduction;
    }

    public void setYearOfProduction(int yearOfProduction) {
        this.yearOfProduction = yearOfProduction;
    }

    public int getMaxPassengers() {
        return maxPassengers;
    }

    public void setMaxPassengers(int maxPassengers) {
        this.maxPassengers = maxPassengers;
    }

    public int getMaxVelocity() {
        return maxVelocity;
    }

    public void setMaxVelocity(int maxVelocity) {
        this.maxVelocity = maxVelocity;
    }

    public String getFabricante() {
        return fabricante;
    }

    public void setFabricante(String fabricante) {
        this.fabricante = fabricante;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Plane plane = (Plane) o;
        return yearOfProduction == plane.yearOfProduction && maxPassengers == plane.maxPassengers && maxVelocity == plane.maxVelocity && Objects.equals(id, plane.id) && Objects.equals(fabricante, plane.fabricante) && Objects.equals(model, plane.model);
    }

    @Override
    public int hashCode() {
        return Objects.hash(yearOfProduction, maxPassengers, maxVelocity, id, fabricante, model);
    }

    @Override
    public String toString() {
        return "Plane{" +
                "id=" + id +
                ", yearOfProduction=" + yearOfProduction +
                ", maxPassengers=" + maxPassengers +
                ", maxVelocity=" + maxVelocity +
                ", fabricante='" + fabricante + '\'' +
                ", model='" + model + '\'' +
                '}';
    }
}
