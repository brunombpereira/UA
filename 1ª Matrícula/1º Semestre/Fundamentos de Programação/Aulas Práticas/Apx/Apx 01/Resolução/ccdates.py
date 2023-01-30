def isLeapYear(year):
    if (year % 100 == 0 and year % 400 == 0):
        year = True

        return year
    elif (year % 100 == 0 and year % 400 != 0):
        year = False

        return year
    else:
        return year % 4 == 0


def monthDays(year, month):
    if (isLeapYear(year) == True):
        MONTHDAYS = (0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
        days = MONTHDAYS[month]
    else:
        MONTHDAYS = (0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
        days = MONTHDAYS[month]

    return days


def nextDay(year, month, day):
    if (monthDays(year, month) != day):
        day += 1
    else:
        if (month != 12):
            month += 1
            day = 1
        else:
            year += 1
            month = 1
            day = 1

    return year, month, day

def previousDay(year, month, day):
    if (day != 1):
        day -= 1
    else:
        if (month != 1):
            month -= 1
            day = monthDays(year, month)
        else:
            year -= 1
            month = 12
            day = 31

    return year, month, day


def dateIsValid(year, month, day):
    if (day < 1 or month > 12 or month < 1):
        validation = False

        return validation       
    else:
        if (monthDays(year, month) < day):
            validation = False

            return validation   
        elif (monthDays(year, month) == day):
            validation = True

            return validation   
        else:
            if(day >= 1):
                validation = True

                return validation   
            else:
                validation = False

                return validation       


def main():
    print("Was", 2017, "a leap year?", isLeapYear(2017))    # False?
    print("Was", 2016, "a leap year?", isLeapYear(2016))    # True?
    print("Was", 2000, "a leap year?", isLeapYear(2000))    # True?
    print("Was", 1900, "a leap year?", isLeapYear(1900))    # False?
    
    print("January 2017 had", monthDays(2017, 1), "days")   # 31?
    print("February 2017 had", monthDays(2017, 2), "days")  # 28?
    print("February 2016 had", monthDays(2016, 2), "days")  # 29?
    print("February 2000 had", monthDays(2000, 2), "days")  # 29?
    print("February 1900 had", monthDays(1900, 2), "days")  # 28?
    
    y, m, d = nextDay(2017, 1, 30)
    print(y, m, d)    # 2017 1 31 ?
    y, m, d = nextDay(2017, 1, 31)
    print(y, m, d)    # 2017 2 1 ?
    y, m, d = nextDay(2017, 2, 28)
    print(y, m, d)    # 2017 3 1 ?
    y, m, d = nextDay(2016, 2, 29)
    print(y, m, d)    # 2016 3 1 ?
    y, m, d = nextDay(2017, 12, 31)
    print(y, m, d)    # 2018 1 1 ?
    y, m, d = previousDay(2000, 1, 1)
    print(y, m, d)
    y, m, d = previousDay(2001, 5, 1)
    print(y, m, d)
    y, m, d = previousDay(2000, 2, 11)
    print(y, m, d)
    valid = dateIsValid(1980, 12, 32)
    print(valid)
    valid = dateIsValid(1980, 2, 29)
    print(valid)


main()
