package aula09;

import java.util.*;

public class Ex2 {
    public static void main(String[] args) {
        int[] dimensions = {10000, 20000, 40000, 100000}; // dimensões da coleção
        Collection<Integer> arrayList = new ArrayList<>();
        Collection<Integer> linkedList = new LinkedList<>();

        System.out.println("Dimension\tArrayList\tLinkedList");
        for (int dim : dimensions) {
            long[] arrayListResults = checkPerformance(arrayList, dim);
            long[] linkedListResults = checkPerformance(linkedList, dim);
            System.out.printf("%d\t\t%d\t\t%d\n", dim, arrayListResults[0], linkedListResults[0]);
        }
    }
    private static long[] checkPerformance(Collection<Integer> col, int DIM) {
        Random random = new Random();
        long[] results = new long[3];

        // Add
        long start = System.nanoTime();
        for (int i = 0; i < DIM; i++) {
            col.add(random.nextInt());
        }
        long stop = System.nanoTime();
        results[0] = stop - start;

        // Search
        start = System.nanoTime();
        for (int i = 0; i < DIM; i++) {
            col.contains(random.nextInt());
        }
        stop = System.nanoTime();
        results[1] = stop - start;

        // Remove
        start = System.nanoTime();
        col.clear();
        stop = System.nanoTime();
        results[2] = stop - start;

        return results;
    }
}
