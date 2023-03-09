package Utils;

import java.util.Scanner;

public class positiveNumber {
    public static int ispositive(String i) { 
        try (Scanner sc = new Scanner(System.in)) {
            int value;

            while (true) {
                System.out.print(i);
                try {
                    value = sc.nextInt();
                    if (value < 0) {
                        System.out.println("O valor tem que ser igual ou maior que 0.");
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
