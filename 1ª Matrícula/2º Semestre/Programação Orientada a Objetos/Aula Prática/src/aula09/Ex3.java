package aula09;

import java.util.Scanner;

public class Ex3 {
    public static void main(String[] args) {
        PlaneManager planeManager = new PlaneManager();
        Scanner scanner = new Scanner(System.in);
        int choice;

        do {
            System.out.println("\nPlane Fleet Menu:");
            System.out.println("1. Add a plane to the fleet");
            System.out.println("2. Remove a plane from the fleet");
            System.out.println("3. Search for a plane");
            System.out.println("4. Print summary of all planes in the fleet");
            System.out.println("5. Print list of all commercial planes in the fleet");
            System.out.println("6. Print list of all military planes in the fleet");
            System.out.println("7. Print the fastest plane in the fleet");
            System.out.println("0. Exit");

            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.println("---------------------------\nWhich plane do you want to add?\n1 - Commercial Plane\n2 - Military Plane\nOption: ");
                    int option = scanner.nextInt();
                    if (option == 1) {
                        System.out.println("Enter the plane's ID: ");
                        String id = scanner.next();
                        System.out.println("Enter the plane's manufacturer: ");
                        String manufacturer = scanner.next();
                        System.out.println("Enter the plane's model: ");
                        String model = scanner.next();
                        System.out.println("Enter the plane's year of production: ");
                        int yearOfProduction = scanner.nextInt();
                        System.out.println("Enter the plane's maximum number of passengers: ");
                        int maxPassengers = scanner.nextInt();
                        System.out.println("Enter the plane's maximum velocity: ");
                        int maxVelocity = scanner.nextInt();
                        System.out.println("Enter the plane's number of crew members: ");
                        int numberOfCrewMembers = scanner.nextInt();
                        CommercialPlane commercialPlane = new CommercialPlane(id, manufacturer, model, yearOfProduction, maxPassengers, maxVelocity, numberOfCrewMembers);
                        planeManager.addPlane(commercialPlane);
                    } else if (option == 2) {
                        System.out.println("Enter the plane's ID: ");
                        String id = scanner.next();
                        System.out.println("Enter the plane's manufacturer: ");
                        String manufacturer = scanner.next();
                        System.out.println("Enter the plane's model: ");
                        String model = scanner.next();
                        System.out.println("Enter the plane's year of production: ");
                        int yearOfProduction = scanner.nextInt();
                        System.out.println("Enter the plane's maximum number of passengers: ");
                        int maxPassengers = scanner.nextInt();
                        System.out.println("Enter the plane's maximum velocity: ");
                        int maxVelocity = scanner.nextInt();
                        System.out.println("Enter the plane's number of crew members: ");
                        int numberOfCrewMembers = scanner.nextInt();
                        MilitaryPlane militaryPlane = new MilitaryPlane(id, manufacturer, model, yearOfProduction, maxPassengers, maxVelocity, numberOfCrewMembers);
                        planeManager.addPlane(militaryPlane);
                    } else {
                        System.out.println("Invalid option.");
                    }
                    break;
                case 2:
                    planeManager.printAllPlanes();
                    System.out.println("Which plane do you want to remove? (Enter the plane's ID)");
                    planeManager.removePlane(scanner.next());
                    break;
                case 3:
                    planeManager.printAllPlanes();
                    System.out.println("Which plane do you want to search? (Enter the plane's ID)");
                    planeManager.searchPlane(scanner.next());
                    break;
                case 4:
                    planeManager.printAllPlanes();
                    break;
                case 5:
                    planeManager.getComercialPlanes();
                    break;
                case 6:
                    planeManager.getMilitaryPlanes();
                    break;
                case 7:
                    planeManager.getFastestPlanes();
                    break;
                case 0:
                    System.out.println("Exiting program...");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
                    break;
            }
        } while (choice != 0);

        scanner.close();
    }
}
