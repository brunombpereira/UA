def hms2sec(h, m, s):
    sec = h * 3600 + m * 60 + s
    return sec


def sec2hms(sec):
    h = sec // 3600
    m = (sec // 60) % 60
    s = sec % 60
    return h, m, s


def main():
    h = int(input("Horas: "))
    m = int(input("Minutos: "))
    s = int(input("Segundos: "))
    sec = hms2sec(h, m, s)
    print(sec)
    h, m, s = sec2hms(sec)
    print(f"{h:02d}:{m:02d}:{s:02d}")


main()
