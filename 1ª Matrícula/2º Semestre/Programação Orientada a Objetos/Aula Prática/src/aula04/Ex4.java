package aula04;

import java.util.Scanner;

public class Ex4 {
    static Scanner sc = new Scanner(System.in);

    static boolean validateCarData(String[] data) {
        if (data.length != 4) {
            return false;
        }
        else if (!data[0].matches("[a-zA-Z]+")) {
            return false;
        }
        else if (!data[2].matches("\\d{4}")) {
            return false;
        }
        return data[3].matches("\\d+");
    }

    static int registerCars(Car[] cars) {
        int counter = 0;
        String car = "";

        do {
            System.out.print("Insira os dados do carro (marca modelo ano kilómetros): ");
            car = sc.nextLine();
            String[] data = car.split(" ");

            if (validateCarData(data)) {
                Car c = new Car(data[0], data[1], Integer.parseInt(data[2]), Integer.parseInt(data[3]));
                cars[counter] = c;
                counter++;
            } else {
                System.out.println("Os dados introduzidos são inválidos.");
            }
        } while (!car.isEmpty());

        return counter;
    }

    static void registerTrips(Car[] cars, int numCars) {
        System.out.println("Registe uma viagem no formato \"carro:distância\": ");
        String trip = sc.nextLine();

        while (!trip.isEmpty()) {
            String[] data = trip.split(":");

            if (data.length == 2 && data[0].matches("\\d+") && Integer.parseInt(data[0]) < numCars
                    && data[1].matches("\\d+")) {
                int carIndex = Integer.parseInt(data[0]);
                int distance = Integer.parseInt(data[1]);
                cars[carIndex].drive(distance);
            }
            else {
                System.out.println("Dados mal formatados.");
            }

            System.out.println("Registe uma viagem no formato \"carro:distância\": ");
            trip = sc.nextLine();
        }
    }

    static void listCars(Car[] cars) {
        System.out.println("\nCarros registados:");

        for (int i = 0; i < cars.length && cars[i] != null; i++) {
            System.out.println(cars[i].make + " " + cars[i].model + ", " + cars[i].year + ", kms: " + cars[i].kms);
        }

        System.out.println();
    }

    public static void main(String[] args) {

        Car[] cars = new Car[10];

        int numCars = registerCars(cars);

        if (numCars > 0) {
            listCars(cars);
            registerTrips(cars, numCars);
            listCars(cars);
        }

        sc.close();

    }
}
