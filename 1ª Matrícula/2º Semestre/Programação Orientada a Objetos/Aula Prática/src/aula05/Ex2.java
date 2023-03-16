package aula05;

import java.util.Scanner;


class Calendar {
    private int year, weekDay, x;
    private int c = 0;
    private int[][] events;

    public Calendar(int year, int weekDay) {
        if (validateWeekDay(weekDay)) {
            this.year = year;
            this.weekDay = weekDay;
            this.events = new int[12][];

            for (int i = 0; i < events.length; i++) {
                int numDays = monthDays(year)[i];
                this.events[i] = new int[numDays];
            }

            this.x = weekDay; // inicializa x com o valor de weekDay
        }
    }

    public void addEvent(DateYMD date) {
        int month = date.getMonth() - 1;
        int day = date.getDay();
        if (month < 0 || month >= events.length || day < 1 || day > events[month].length) {
            throw new IllegalArgumentException("Invalid date");
        }
        events[month][day - 1]++;
    }

    public void removeEvent(DateYMD date) {
        int month = date.getMonth() - 1;
        int day = date.getDay();
        if (month < 0 || month >= events.length || day < 1 || day > events[month].length) {
            throw new IllegalArgumentException("Invalid date");
        }
        if (events[month][day - 1] > 0) {
            events[month][day - 1]--;
        }
    }

    public void toString(int month) {
        String[] monthNames = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
        int numDays = monthDays(year)[month - 1];

        System.out.printf("%s %d\n", monthNames[month - 1], year);
        System.out.println("Su Mo Tu We Th Fr Sa");

        for (int i = 1; i < x; i++) {
            System.out.print("   ");
        }

        for (int i = 1; i <= numDays; i++) {
            if (events[month - 1][i - 1] > 0) {
                System.out.printf("*%2d ", i);
            } else {
                System.out.printf("%2d ", i);
            }
            if ((i + x - 1) % 7 == 0) {
                System.out.println();
            }
            if ((i + x) % 7 == 0) {
                if ((i + x - 1) % 7 == 6) {
                    c = 7;
                } else {
                    c = (i + x) % 7;
                }
            } else {
                c = (i + x) % 7;
            }
        }

        System.out.println();
    }



    public void printCalendar() {
        for (int i = 1; i <= 12; i++) {
            toString(i);
            x = c;
            System.out.println();
        }
        x = weekDay;
        c = 0;
    }

    public static boolean isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0);
    }

    public static int[] monthDays(int year) {
        int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (isLeapYear(year)) {
            return new int[]{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        }
        return days;
    }

    public boolean validateWeekDay(int weekDay) {
        return weekDay >= 1 && weekDay <= 7;
    }

    public int getWeekDay() {
        return weekDay;
    }

    public int getYear() {
        return year;
    }
}


public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        DateYMD[] date = new DateYMD[365];

        for (int i = 0; i < date.length; i ++) {
            date[i] = new DateYMD(2004, 1, 1);
        }

        Calendar[] calendar = new Calendar[1];
        calendar[0] = new Calendar(2023,1);

        while (true) {
            System.out.println("Calendar operations: \n");
            System.out.println("1 - Create new calendar");
            System.out.println("2 - Print calendar month");
            System.out.println("3 - Print calendar");
            System.out.println("4 - Add event");
            System.out.println("5 - Remove event");
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
            }
            else if (option == 4) {
                while (true){
                    System.out.println("Enter the date of the event:\n");
                    System.out.print("Month: ");
                    int month = sc.nextInt();
                    System.out.print("Day: ");
                    int day = sc.nextInt();
                    DateYMD eventDate = new DateYMD(calendar[0].getYear(), month, day);
                    if (eventDate.getDay() != 0) {
                        calendar[0].addEvent(eventDate);
                        System.out.println("Event added to the calendar.");
                        break;
                    }
                }
            } else if (option == 5) {
                while (true){
                    System.out.println("Enter the date of the event:\n");
                    System.out.print("Month: ");
                    int month = sc.nextInt();
                    System.out.print("Day: ");
                    int day = sc.nextInt();
                    DateYMD eventDate = new DateYMD(calendar[0].getYear(), month, day);
                    if (eventDate.getDay() != 0) {
                        calendar[0].removeEvent(eventDate);
                        System.out.println("Event removed to the calendar.");
                        break;
                    }
                }
            }
            else break;

        }
    }
}
