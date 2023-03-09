package Utils;

public class isPrime {
    public static boolean isPrime(int n) {
        int primeCounter = 0;
        
        for(int i = n; i >= 1; i--) {
            int remainder = n % i;

            if(remainder == 0) {
                primeCounter++;
            }
        }

        return primeCounter == 2;
    }
}
