package aula03;

import java.util.Scanner;

public class Ex6 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Frase: ");
        String frase = sc.nextLine();

        System.out.println("Frase em minúsculas: " + frase.toLowerCase());
        System.out.println("Último caracter da frase: " + frase.charAt(frase.length() - 1));
        System.out.println("3 primeiros caracteres: " + frase.substring(0, 3));
        
        sc.close();
    }
}
