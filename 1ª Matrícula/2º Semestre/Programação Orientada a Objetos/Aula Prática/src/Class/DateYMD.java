package Class;

public class DateYMD extends Date {
    private int year, month, day;

    public DateYMD(int year, int month, int day) {
        if (validateDate(year, month, day)) {
            this.year = year;
            this.month = month;
            this.day = day;
        }
    }

    public String toString(){
        return year + "-" + month + "-" + day;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public int getMonth() {
        return month;
    }

    public void setMonth(int month) {
        this.month = month;
    }

    public int getDay() {
        return day;
    }

    public void setDay(int day) {
        this.day = day;
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
