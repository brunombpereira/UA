package Class;

public abstract class Date implements Comparable{
    public static boolean validateMonth(int month) {
        if (1 <= month && month <= 12) {
            return true;
        }
        else {
            System.out.println("Mês inválido.\nO mês tem que estar entre 1 e 12.");
            return false;
        }
    }

    public static boolean isLeapYear(int year) {
        return (year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0);
    }

    public static int monthDays(int year, int month) {
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

    public static boolean validateDay(int year, int month, int day) {
        if (1 <= day && day <= monthDays(year, month)) {
            return true;
        }
        else {
            System.out.println("Dia inválido. O dia tem que estar entre 1 e " + monthDays(year, month));
            return false;
        }
    }

    public static boolean validateDate(int year, int month, int day) {
        return validateMonth(month) && validateDay(year, month, day);
    }

    public abstract String toString();

    public  abstract int getYear();

    public  abstract void setYear(int year);

    public  abstract int getMonth();

    public  abstract void setMonth(int month);

    public  abstract int getDay();

    public  abstract void setDay(int day);

    public abstract  void increment();

    public abstract  void decrement();
}
