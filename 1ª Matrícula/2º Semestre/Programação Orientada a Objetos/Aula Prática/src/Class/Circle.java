package Class;

import java.util.Objects;


public class Circle extends Forma{
    private double ray;

    public Circle(String color, double ray) {
        super(color);
        if (rayVerification(ray)) {
            this.ray = ray;
        }
    }

    static boolean rayVerification(double ray){
        if (ray <= 0) {
            System.out.println("O raio tem de ser maior que 0.");
            return false;
        }
        return true;
    }

    public double area() {

        return Math.PI * ray * ray;
    }

    public double perimeter() {

        return 2 * Math.PI * ray;
    }

    public double getRay() {
        return ray;
    }

    public void setRay(double ray) {
        this.ray = ray;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Circle circle = (Circle) o;
        return Double.compare(circle.ray, ray) == 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(ray);
    }

    @Override
    public String toString() {
        super.toString();
        return "Circle{" +
                "ray=" + ray +
                '}';
    }
}
