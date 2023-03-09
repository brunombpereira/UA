package aula02;

import java.util.Scanner;

public class Ex11 {
    public static int readIntWithinRange(String prompt, int min, int max) {
        try (Scanner sc = new Scanner(System.in)) {
            int value;
            while (true) {
                System.out.print(prompt);
                try {
                    value = sc.nextInt();
                    if (value < min || value > max) {
                        System.out.println("O valor deve estar dentro do intervalo [" + min + ", " + max + "].");
                    } else {
                        break;
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Digite um valor inteiro.");
                }
            }
            return value;
        }
    }
}
