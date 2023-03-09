package aula03;

import java.util.Scanner;

public class Ex5 {
    public static String read(String prompt) {
        Scanner sc = new Scanner(System.in);

        System.out.print(prompt);
        String date = sc.nextLine();

        return date;
    }

    public static boolean validate(String date, int weekDay) {
        if (date.length() != 7) {
            System.out.println("Formato de data errado. A data tem de corresponder ao formato mm/yyyy");
            return false;
        } else {
            try {
                int month = Integer.parseInt(date.split("/")[0]);
                int year = Integer.parseInt(date.split("/")[1]);

                if (month < 1 || month > 12) {
                    System.out.println("Mês inválido. O mês deve estar entre 1 e 12.");
                    return false;
                }

                if (weekDay < 1 || weekDay > 7) {
                    System.out.println("Dia da semana inválido. O dia deve estar entre 1 e 7.");
                    return false;
                }

                return true;

            } catch (Exception e) {
                System.out.println("Tem de introduzir valores numéricos na data e no dia da semana.");
                return false;
            }
        }
    }

    public static boolean isLeapYear(int year) {
        if ((year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0)) {
            return true;
        } else {
            return false;
        }
    }

    public static int monthDays(int month, int year) {
        int[] days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (month == 2 && isLeapYear(year)) {
            return 29;
        } else {
            return days[month - 1];
        }
    }

    public static void printCalendar(int days, int month, int year, int weekDay) {
        String[] monthNames = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
        System.out.printf("%s %d\n", monthNames[month - 1], year);
        System.out.println("Su Mo Tu We Th Fr Sa");

        for (int i = 1; i < weekDay; i++) {
            System.out.print("   ");
        }
        for (int i = 1; i <= days; i++) {
            System.out.printf("%2d ", i);
            if ((i + weekDay - 1) % 7 == 0) {
                System.out.println();
            }
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            String date = read("Data (mm/yyyy): ");
            int weekDay;

            try {
                String[] weekdays = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"};
                System.out.println("Em que dia da semana começa o mês?");

                for(int i = 0; i < weekdays.length; i ++) {
                    System.out.println((i + 1) + "-->" + weekdays[i]);
                }

                System.out.print("Dia da semana (número): ");
                weekDay = sc.nextInt();

                if (validate(date, weekDay)) {
                    int month = Integer.parseInt(date.split("/")[0]);
                    int year = Integer.parseInt(date.split("/")[1]);
                    int days = monthDays(month, year);
                    printCalendar(days, month, year, weekDay);
                    break;
                }
            }catch(Exception e) {
                continue;
            }
        }
    }
}
