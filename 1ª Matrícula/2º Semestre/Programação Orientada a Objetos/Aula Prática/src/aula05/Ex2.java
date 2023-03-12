package aula05;

import java.util.Scanner;


class Calendar {
    private int year, weekDay;

    public Calendar(int year, int weekDay) {
        if (validateWeekDay(weekDay)) {
            this.year = year;
            this.weekDay = weekDay;
        }
    }

    public void toString(int month) {
        String[] monthNames = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
        int[] daysMonth = monthDays(year);
        int x = weekDay;
        int c = 0;
        System.out.printf("%s %d\n", monthNames[month - 1], year);
        System.out.println("Su Mo Tu We Th Fr Sa");

        for (int i = 0; i < month - 1; i ++) {
            for (int j = 1; j <= daysMonth[i]; j++) {
                if ((j + x) % 7 == 0) {
                    if((j + x - 1) % 7 == 6) {
                        c = 7;
                    }else {
                        c = (j + x) % 7;
                    }
                }else {
                    c = (j + x) % 7;
                }
            }
            x = c;
        }

        if (x == 0) {
            x = 7;
        }

        if (month == 2 && x == 7) {
            x = 0;
        }

        for (int k = 1; k < x; k++) {
            System.out.print("   ");
        }

        for (int j = 1; j <= daysMonth[month - 1]; j++) {
            System.out.printf("%2d ", j);
            if ((j + x - 1) % 7 == 0) {
                System.out.println();
            }
        }
        System.out.println("\n");
    }

    public void printCalendar() {
        String[] monthNames = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
        int[] daysMonth = monthDays(year);
        int x = weekDay;
        int c = 0;

        for (int i = 0; i < monthNames.length; i ++) {
            System.out.printf("%s %d\n", monthNames[i], year);
            System.out.println("Su Mo Tu We Th Fr Sa");

            for (int k = 1; k < x; k++) {
                System.out.print("   ");
            }

            for (int j = 1; j <= daysMonth[i]; j++) {
                System.out.printf("%2d ", j);
                if ((j + x - 1) % 7 == 0) {
                    System.out.println();
                }
                if ((j + x) % 7 == 0) {
                    if((j + x - 1) % 7 == 6) {
                        c = 7;
                    }else {
                        c = (j + x) % 7;
                    }
                }else {
                    c = (j + x) % 7;
                }
            }
            x = c;
            System.out.println("\n");
        }

        System.out.println();
    }

    public static boolean isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0);
    }

    public static int[] monthDays(int year) {
        if (isLeapYear(year)) {
            return new int[]{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        } else {
            return new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        }
    }

    public boolean validateWeekDay(int weekDay) {
        return weekDay >= 1 && weekDay <= 7;
    }

    public int getWeekDay() {
        return weekDay;
    }
}


public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        DateYMD[] date = new DateYMD[1];
        date[0] = new DateYMD(2022, 3, 11);

        Calendar[] calendar = new Calendar[1];
        calendar[0] = new Calendar(2023,1);

        while (true) {
            System.out.println("Calendar operations: \n");
            System.out.println("1 - Create new calendar");
            System.out.println("2 - Print calendar month");
            System.out.println("3 - Print calendar");
            System.out.println("0 - Exit\n");
            System.out.println("Option: ");
            int option = sc.nextInt();

            if (option == 1) {
                do {
                    System.out.println("-------------------------------------------------");
                    System.out.println("\nWhich year do you want the calendar to present? ");
                    int year = sc.nextInt();

                    date[0] = new DateYMD(year, 1, 1);

                } while (date[0].getDay() == 0);

                do {
                    String[] weekdays = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

                    System.out.println("-------------------------------------------------\n");
                    System.out.println("In which day of the week the month starts?");

                    for (int i = 0; i < weekdays.length; i++) {
                        System.out.println((i + 1) + "-->" + weekdays[i]);
                    }

                    System.out.print("Day of the week (number): ");
                    int weekDay = sc.nextInt();

                    calendar[0] = new Calendar(date[0].getYear(), weekDay);
                } while (calendar[0].getWeekDay() == 0);
                System.out.println("-------------------------------------------------\n");
            }
            else if (option == 2) {
                while (true) {
                    try {
                        System.out.println("-------------------------------------------------\n");
                        System.out.println("Which month do you wanna print? (1-12) ");
                        int month = sc.nextInt();
                        calendar[0].toString(month);
                        break;
                    } catch (Exception ignored) {
                    }
                }
            }
            else if (option == 3) {
                calendar[0].printCalendar();
            } else break;
        }
    }
}
