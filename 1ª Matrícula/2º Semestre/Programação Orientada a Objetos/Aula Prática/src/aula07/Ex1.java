package aula07;

import java.util.Scanner;
import Class.Circle;
import Class.Triangle;
import Class.Rectangle;


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
                                circles[i] = new Circle("vermelho",ray);

                            } while (circles[i].getRay() == 0.0);
                        }

                        System.out.println("-------------------------------------------------------");

                        for (int i = 0; i < circles.length; i++) {
                            if (circles[i].getRay() != 0.0) {
                                System.out.println("\nCírculo " + (i + 1) + ": " + circles[i].toString() + "\n");
                                System.out.println("Area: " + circles[i].area() + "\n");
                                System.out.println("Perímetro: " + circles[i].perimeter() + "\n");

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

                                triangles[i] = new Triangle("jhbjbh", side1, side2, side3);

                            } while (triangles[i].getSide1() == 0.0 || triangles[i].getSide2() == 0.0 || triangles[i].getSide3() == 0.0);
                        }

                        System.out.println("-----------------------------------------------");

                        for (int i = 0; i < triangles.length; i++) {
                            if (triangles[i].getSide1() != 0.0 && triangles[i].getSide2() != 0.0 && triangles[i].getSide3() != 0.0) {
                                System.out.println("\nTriângulo " + (i + 1) + "\n" + triangles[i].toString() + "\n");
                                System.out.println("Area: " + triangles[i].area() + "\n");
                                System.out.println("Perímetro: " + triangles[i].perimeter() + "\n");

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

                                rectangles[i] = new Rectangle("serfer",lenght, height);

                            } while (rectangles[i].getHeight() == 0.0 || rectangles[i].getLenght() == 0.0);
                        }

                        System.out.println("-----------------------------------------------");

                        for (int i = 0; i < rectangles.length; i++) {
                            if (rectangles[i].getHeight() != 0.0 && rectangles[i].getLenght() != 0.0) {
                                System.out.println("\nRetângulo " + (i + 1) + "\n" + rectangles[i].toString() + "\n");
                                System.out.println("Area: " + rectangles[i].area() + "\n");
                                System.out.println("Perímetro: " + rectangles[i].perimeter() + "\n");

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
