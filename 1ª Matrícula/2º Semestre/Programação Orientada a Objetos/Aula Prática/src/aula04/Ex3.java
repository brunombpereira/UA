package aula04;

import java.util.Scanner;

class Car {
    public String make;
    public String model;
    public int year;
    public int kms;

    public Car(String make, String model, int year, int kms) {
        this.make = make;
        this.model = model;
        this.year = year;
        this.kms = kms;
    }

    public void drive(int distance) {
        this.kms = kms + distance;
    }
}

public class Ex3 {

    static Scanner sc = new Scanner(System.in);

    static void listCars(Car[] cars) {
        System.out.println("Carros registados: \n");

        for (Car car : cars) {
            System.out.println(car.make + " " + car.model + ", " + car.year + ", kms: " + car.kms);
        }
    }

    public static void main(String[] args) {

        Car[] cars = new Car[3];
        cars[0] = new Car("Renault", "Megane Sport Tourer", 2015, 35356);
        cars[1] = new Car("Toyota", "Camry", 2010, 32456);
        cars[2] = new Car("Mercedes", "Vito", 2008, 273891);

        listCars(cars);

        System.out.println(" ");

        for (int i = 0; i < 10; i++) {
            int j = (int) Math.round(Math.random() * 2);
            int kms = (int) Math.round(Math.random() * 1000);
            
            System.out.printf("Carry %d viajou %d quilómetros.\n", j, kms);
            
            cars[j].drive(kms);
        }

        System.out.println(" ");

        listCars(cars);

        sc.close();

    }
}
