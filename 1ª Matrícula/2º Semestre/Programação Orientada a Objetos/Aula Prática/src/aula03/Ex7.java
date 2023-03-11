package aula03;

import java.util.Scanner;

public class Ex7 {
    public static int countDigits(String frase) {
        int counter = 0;
        for(int i = 0; i < frase.length(); i++) {
            if(Character.isDigit(frase.charAt(i))) {
                counter++;
            }
        }

        return counter;
    }

    public static int countSpaces(String frase) {
        int counter = 0;
    
        for (int i = 0; i < frase.length(); i++) {
            if (Character.isWhitespace(frase.charAt(i))) {
                counter++;
            }
        }
    
        return counter;
    }

    public static boolean isLower(String frase) {
        int counter = 0;

        for (int i = 0; i < frase.length(); i++) {
            if (Character.isLowerCase(frase.charAt(i))) {
                counter++;
            }
        }

        return counter == frase.length();
    }

    public static String noSpaces(String frase) {
        frase = frase.replaceAll("\\s+", " ");

        return frase;
    }
    
    public static boolean isPalindromo(String frase) {
        String fraseNoSpaces = frase.replaceAll("[^a-zA-Z]", "").toLowerCase();
        char[] letters = fraseNoSpaces.toCharArray();
        StringBuilder reverse = new StringBuilder();

        for (int i = letters.length - 1; i >= 0; i--) {
            reverse.append(letters[i]);
        }

        return frase.equalsIgnoreCase(reverse.toString());
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Frase: ");
        String frase = sc.nextLine();

        int numberDigits = countDigits(frase);
        int numberSpaces = countSpaces(frase);
        boolean lower = isLower(frase);
        frase = noSpaces(frase);
        boolean pol = isPalindromo(frase);

        System.out.println("A frase contém " + numberDigits + " dígitos.");
        System.out.println("A frase contém " + numberSpaces + " espaços.");
        System.out.println("A frase está toda em minúsculas: " + lower);
        System.out.println(frase);
        System.out.println("A frase é um palíndromo: " + pol);

        sc.close();
        
    }

}
