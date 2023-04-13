package Class;

import java.util.Objects;


public class Triangle extends Forma {
    private double side1, side2, side3;

    public Triangle(String color, double side1, double side2, double side3) {
        super(color);
        if (sideVerification(side1, side2, side3)) {
            this.side1 = side1;
            this.side2 = side2;
            this.side3 = side3;
        }
    }

    static boolean sideVerification(double side1, double side2, double side3){
        if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
            System.out.println("\nOs lados têm que ser maior que 0.");
            return false;
        }
        else if ((side1 + side2) < side3 || (side1 + side3) < side2 || (side2 + side3) < side1) {
            System.out.println("\nOs lados não sastifazem a desigualdade triangular.");
            return false;
        }
        return true;
    }

    public double area() {
        double p = side1 + side2 + (2 * side3);

        return Math.sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }

    public double perimeter() {

        return side1 + side2 + side3;
    }

    public double getSide1() {
        return side1;
    }

    public void setSide1(double side1) {
        this.side1 = side1;
    }

    public double getSide2() {
        return side2;
    }

    public void setSide2(double side2) {
        this.side2 = side2;
    }

    public double getSide3() {
        return side3;
    }

    public void setSide3(double side3) {
        this.side3 = side3;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Triangle triangle = (Triangle) o;
        return Double.compare(triangle.side1, side1) == 0 && Double.compare(triangle.side2, side2) == 0 && Double.compare(triangle.side3, side3) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(side1, side2, side3);
    }

    @Override
    public String toString() {
        return "Triangle{" +
                "side1=" + side1 +
                ", side2=" + side2 +
                ", side3=" + side3 +
                ", color='" + color + '\'' +
                '}';
    }
}