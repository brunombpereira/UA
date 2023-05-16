package aula12.Utils;

public class Validate {
    public static boolean validateScore(double score) {
        if (score < 0) {
            System.out.println("Score must be a positive number.");
            return false;
        } else {
            return true;
        }
    }

    public static boolean validateRunningTime(int runningTime) {
        if (runningTime <= 0) {
            System.out.println("Running time must be greater than 0.");
            return false;
        } else {
            return true;
        }
    }
}
