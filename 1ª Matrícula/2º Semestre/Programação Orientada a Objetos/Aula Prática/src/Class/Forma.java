package Class;

import java.util.Objects;

public abstract class Forma {
    protected String color;

    public Forma(String color) {
        this.color = color;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Forma forma = (Forma) o;
        return Objects.equals(color, forma.color);
    }

    @Override
    public int hashCode() {
        return Objects.hash(color);
    }

    @Override
    public String toString() {
        return "Forma{" +
                "color='" + color + '\'' +
                '}';
    }

    public abstract double area();

    public abstract double perimeter();
}
