package aula07;

import Class.DateYMD;

import java.util.Scanner;

public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        DateYMD[] date = new DateYMD[1];
        date[0] = new DateYMD(2022, 3, 11);

        while (true) {
            System.out.println("Date operations: \n");
            System.out.println("1 - Create new date");
            System.out.println("2 - Show current date");
            System.out.println("3 - Increment date");
            System.out.println("4 - Decrement date");
            System.out.println("0 - Exit\n");
            System.out.println("Option: ");
            int option = sc.nextInt();

            if (option == 1) {
                do {
                    System.out.println("\nDay: ");
                    int day = sc.nextInt();
                    System.out.println("Month: ");
                    int month = sc.nextInt();
                    System.out.println("Year: ");
                    int year = sc.nextInt();

                    date[0] = new DateYMD(year, month, day);

                } while (date[0].getDay() == 0);
            }
            else if (option == 2) {
                System.out.println(date[0]);
            }
            else if (option == 3) {
                date[0].increment();

                System.out.println("Nova data: " + date[0]);
            }
            else if (option == 4) {
                date[0].decrement();

                System.out.println("Nova data: " + date[0]);
            }
            else if (option == 0) {
                break;
            }
        }
    }
}
