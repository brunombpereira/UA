package aula03;

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

        if (counter == frase.length()) {
            return true;
        }else {
            return false;
        }
    }
    
}
