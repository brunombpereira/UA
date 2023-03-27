package aula02;

import java.util.Scanner;

public class Ex6 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Segundos: ");
        int s = sc.nextInt();

        int h = s / 3600;
        int m = (s % 3600) / 60;
        int s2 = (s % 3600) % 60;

        System.out.printf("%2d %1s %2d %1s %2d", h, ":", m, ":", s2);

        sc.close();
    }
}
