package aula05;

import java.util.Scanner;

class DateYMD {
    private int year, month, day;

    public DateYMD(int year, int month, int day) {
        if (validateDate(year, month, day)) {
            this.year = year;
            this.month = month;
            this.day = day;
        }
    }

    static boolean validateMonth(int month) {
        return 1 <= month && month <= 12;
    }

    static boolean validateDay(int year, int month, int day) {
        return  1 <= day && day <= monthDays(year, month);
    }

    static boolean validateDate(int year, int month, int day) {
        return validateMonth(month) && validateDay(year, month, day);
    }

    static boolean isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0);
    }

    static int monthDays(int year, int month) {
        int[] monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if(isLeapYear(year)) {
            if (month == 2) {
                return  29;
            }
            else{
                for(int i = 0; i < monthDays.length; i++) {
                    if (month == (i + 1)) {
                        return monthDays[i];
                    }
                }
            }
        }
        return monthDays[month - 1];
    }

    public String toString(){
        return year + "-" + month + "-" + day;
    }

    public int getDay() {
        return day;
    }

    public int getMonth() {
        return month;
    }

    public int getYear() {
        return year;
    }

    public void increment() {
        if (day != monthDays(year, month)){
            day += 1;
        }
        else if (day == monthDays(year, month) && month != 12) {
            day = 1;
            month += 1;
        } else if (day == monthDays(year, month) && month == 12) {
            day = 1;
            month = 1;
            year += 1;
        }
    }

    public void decrement() {
        if (day != 1){
            day -= 1;
        }
        else if (month != 1) {
            day = monthDays(year, month);
            month -= 1;
        } else {
            day = 31;
            month = 12;
            year -= 1;
        }
    }
}

public class Ex1 {
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
                System.out.println(date[0].toString());
            }
            else if (option == 3) {
                date[0].increment();

                System.out.println("Nova data: " + date[0].toString());
            }
            else if (option == 4) {
                date[0].decrement();

                System.out.println("Nova data: " + date[0].toString());
            }
            else if (option == 0) {
                break;
            }
            else {
                continue;
            }
        }
    }
}
