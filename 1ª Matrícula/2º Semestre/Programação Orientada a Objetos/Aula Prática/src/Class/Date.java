package Class;

public class Date {
    private int year, month, day;

    public Date(int year, int month, int day) {
        if (validateDate(year, month, day)) {
            this.year = year;
            this.month = month;
            this.day = day;
        }
    }

    public static boolean validateMonth(int month) {
        if (1 <= month && month <= 12) {
            return true;
        }
        else {
            System.out.println("Mês inválido.\nO mês tem que estar entre 1 e 12.");
            return false;
        }
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
