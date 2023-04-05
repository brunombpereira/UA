package Class;

import java.util.Objects;


public class Rectangle extends Forma {
    private double lenght, height;

    public Rectangle(String color, double lenght, double height) {
        super(color);
        if (sideVerification(lenght, height)) {
            this.lenght = lenght;
            this.height = height;
        }
    }

    static boolean sideVerification(double lenght, double height){
        if (height <= 0 || lenght <= 0) {
            System.out.println("\nOs lados têm que ser maior que 0.");
            return false;
        }
        return true;
    }

    public double area() {

        return height * lenght;
    }

    public double perimeter() {

        return (2 * lenght) + (2 * height);
    }

    public double getLenght() {
        return lenght;
    }

    public void setLenght(double lenght) {
        this.lenght = lenght;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Rectangle rectangle = (Rectangle) o;
        return Double.compare(rectangle.lenght, lenght) == 0 && Double.compare(rectangle.height, height) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(lenght, height);
    }

    @Override
    public String toString() {
        return "Rectangle{" +
                "lenght=" + lenght +
                ", height=" + height +
                '}';
    }
}