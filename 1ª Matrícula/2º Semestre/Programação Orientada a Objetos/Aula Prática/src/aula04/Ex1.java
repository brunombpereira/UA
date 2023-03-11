package aula04;

import java.util.Scanner;

class Circle {
    private double ray;

    public Circle(double ray) {
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

    public double calculateArea() {

        return Math.PI * ray * ray;
    }

    public double calculatePerimeter() {

        return 2 * Math.PI * ray;
    }

    // Métodos especiais
    
    @Override
    
    public String toString() {

        return "Círculo de raio " + getRay();
    }

    @Override

    public boolean equals(Object object) {
        if (this == object) {
            return true;
        }else if (object == null) {
            return false;
        }else if (getClass() != object.getClass()) {
            return false;
        }

        Circle other = (Circle) object;

        return Double.doubleToLongBits(ray) == Double.doubleToLongBits(other.ray);
    }

    @Override

    public Circle clone() throws CloneNotSupportedException {

        return (Circle) super.clone();
    }
    
    public double getRay() {
        return ray;
    }

}


class Triangle {
    private double side1, side2, side3;

    public Triangle(double side1, double side2, double side3) {
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

    public double calculateArea() {
        double p = side1 + side2 + (2 * side3);

        return Math.sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }

    public double calculatePerimeter() {

        return side1 + side2 + side3;
    }

    // Métodos especiais
    
    @Override
    
    public String toString() {
        StringBuilder sides = new StringBuilder("\nTriângulo de lados: \n");
    
        int i = 1;
        for (double side : getSide()) {
            sides.append("\nLado ").append(i++).append(": ").append(side);
        }
    
        return sides.toString();
    }
    

    @Override

    public boolean equals(Object object) {
        if (this == object) {
            return true;
        }else if (object == null) {
            return false;
        }else if (getClass() != object.getClass()) {
            return false;
        }

        Triangle other = (Triangle) object;

        return Double.doubleToLongBits(side1) == Double.doubleToLongBits(other.side1) && Double.doubleToLongBits(side2) == Double.doubleToLongBits(other.side2) && Double.doubleToLongBits(side3) == Double.doubleToLongBits(other.side3);
    }

    @Override

    public Triangle clone() throws CloneNotSupportedException {

        return (Triangle) super.clone();
    }
    
    public double[] getSide() {

        return new double[]{side1, side2, side3};
    }

}


class Rectangle {
    private double lenght, height;

    public Rectangle(double lenght, double height) {
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

    public double calculateArea() {

        return height * lenght;
    }

    public double calculatePerimeter() {

        return (2 * lenght) + (2 * height);
    }

    // Métodos especiais
    
    @Override
    
    public String toString() {
        String sides = "\nRetângulo de: \n";
        
        sides += "\nComprimento = " + getSide()[0];
        sides += "\nAltura = " + getSide()[1];
    
        return sides;
    }
    

    @Override

    public boolean equals(Object object) {
        if (this == object) {
            return true;
        }else if (object == null) {
            return false;
        }else if (getClass() != object.getClass()) {
            return false;
        }

        Rectangle other = (Rectangle) object;

        return Double.doubleToLongBits(lenght) == Double.doubleToLongBits(other.lenght) && Double.doubleToLongBits(height) == Double.doubleToLongBits(other.height);
    }

    @Override

    public Rectangle clone() throws CloneNotSupportedException {

        return (Rectangle) super.clone();
    }
    
    public double[] getSide() {

        return new double[]{lenght, height};
    }

}


public class Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("Escolha uma das seguintes opções (1-4): ");
            System.out.println("1 - Círculo");
            System.out.println("2 - Triângulo");
            System.out.println("3 - Retângulo");
            System.out.println("4 - Fechar programa\n");
            System.out.print("Opção: ");
            int option = sc.nextInt();
            System.out.println("-------------------------------------------------------");

            if(option == 1) {
                while(true){
                    try {
                        System.out.print("\nQuantos círculos quer criar? ");
                        int numberCircles = sc.nextInt();

                        Circle[] circles = new Circle[numberCircles];

                        for(int i = 0; i < numberCircles; i++) {
                            do {
                                System.out.print("\nRaio círculo " + (i + 1) + ": ");
                                double ray = sc.nextDouble();
                                circles[i] = new Circle(ray);

                            } while (circles[i].getRay() == 0.0);
                        }

                        System.out.println("-------------------------------------------------------");

                        for (int i = 0; i < circles.length; i++) {
                            if (circles[i].getRay() != 0.0) {
                                System.out.println("\nCírculo " + (i + 1) + ": " + circles[i].toString() + "\n");
                                System.out.println("Area: " + circles[i].calculateArea() + "\n");
                                System.out.println("Perímetro: " + circles[i].calculatePerimeter() + "\n");

                                for (int j = i+1; j < circles.length; j++) {
                                    if (circles[i].equals(circles[j])) {
                                        System.out.println("O círculo " + (i+1) + " é igual ao círculo " + (j+1) + "\n");
                                    } 
                                    else {
                                        System.out.println("O círculo " + (i+1) + " é diferente do círculo " + (j+1) + "\n");
                                    }
                                }

                                System.out.println("-------------------------------------------------------");
                            }
                        }
                        
                        break;                        
                    } 
                    catch (Exception ignored) {
                    }
                }                
            }
            else if (option == 2) {
                while(true){
                    try {
                        System.out.print("\nQuantos triângulos quer criar? ");
                        int numberTriangles = sc.nextInt();

                        Triangle[] triangles = new Triangle[numberTriangles];

                        for(int i = 0; i < numberTriangles; i++) {
                            do {
                                System.out.println("-------------------------------------------------------");
                                System.out.println("\nTriângulo " + (i + 1) + ":");

                                System.out.print("\nLado 1: ");
                                double side1 = sc.nextDouble();
                                System.out.print("\nLado 2: ");
                                double side2 = sc.nextDouble();
                                System.out.print("\nLado 3: ");
                                double side3 = sc.nextDouble();

                                triangles[i] = new Triangle(side1, side2, side3);

                            } while (triangles[i].getSide()[0] == 0.0 || triangles[i].getSide()[1] == 0.0 || triangles[i].getSide()[2] == 0.0);
                        }

                        System.out.println("-----------------------------------------------");

                        for (int i = 0; i < triangles.length; i++) {
                            if (triangles[i].getSide()[0] != 0.0 && triangles[i].getSide()[1] != 0.0 && triangles[i].getSide()[2] != 0.0) {
                                System.out.println("\nTriângulo " + (i + 1) + "\n" + triangles[i].toString() + "\n");
                                System.out.println("Area: " + triangles[i].calculateArea() + "\n");
                                System.out.println("Perímetro: " + triangles[i].calculatePerimeter() + "\n");

                                for (int j = i+1; j < triangles.length; j++) {
                                    if (triangles[i].equals(triangles[j])) {
                                        System.out.println("O triângulo " + (i+1) + " é igual ao triângulo " + (j+1) + "\n");
                                    }
                                    else {
                                        System.out.println("O triângulo " + (i+1) + " é diferente do triângulo " + (j+1) + "\n");
                                    }
                                }

                                System.out.println("-----------------------------------------------");
                            }
                        }
                        
                        break;                  
                    } 
                    catch (Exception ignored) {
                    }
                }
            }
            else if (option == 3) {
                while(true){
                    try {
                        System.out.print("\nQuantos retângulos quer criar? ");
                        int numberRectangles = sc.nextInt();

                        Rectangle[] rectangles = new Rectangle[numberRectangles];

                        for(int i = 0; i < numberRectangles; i++) {
                            do {
                                System.out.println("-------------------------------------------------------");
                                System.out.println("\nRetângulo " + (i + 1) + ":");

                                System.out.print("\nComprimento: ");
                                double lenght = sc.nextDouble();
                                System.out.print("\nAltura: ");
                                double height = sc.nextDouble();

                                rectangles[i] = new Rectangle(lenght, height);

                            } while (rectangles[i].getSide()[0] == 0.0 || rectangles[i].getSide()[1] == 0.0);
                        }

                        System.out.println("-----------------------------------------------");

                        for (int i = 0; i < rectangles.length; i++) {
                            if (rectangles[i].getSide()[0] != 0.0 && rectangles[i].getSide()[1] != 0.0) {
                                System.out.println("\nRetângulo " + (i + 1) + "\n" + rectangles[i].toString() + "\n");
                                System.out.println("Area: " + rectangles[i].calculateArea() + "\n");
                                System.out.println("Perímetro: " + rectangles[i].calculatePerimeter() + "\n");

                                for (int j = i+1; j < rectangles.length; j++) {
                                    if (rectangles[i].equals(rectangles[j])) {
                                        System.out.println("O triângulo " + (i+1) + " é igual ao triângulo " + (j+1) + "\n");
                                    }
                                    else {
                                        System.out.println("O triângulo " + (i+1) + " é diferente do triângulo " + (j+1) + "\n");
                                    }
                                }

                                System.out.println("-----------------------------------------------");
                            }
                        }
                        
                        break;                  
                    } 
                    catch (Exception ignored) {
                    }
                }
            }
            else {
                sc.close();
                break;
            }
        }
    }  
}
