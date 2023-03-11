package aula03;

import java.util.Scanner;

public class Ex8 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Frase: ");
        String frase = sc.nextLine();

        String[] x = frase.split(" ");

        StringBuilder y = new StringBuilder();

        for (String word : x) {
            if (word.length() < 3) {
            }else {
                y.append(word.charAt(0));
            }
        }

        System.out.println(y);

        sc.close();
    }
}
