package Class;

import java.util.Arrays;

public class Conjunto {
    private int[] elements;
    private int size;

    public Conjunto() {
        this.elements = new int[10];
        this.size = 0;
    }

    public void insert(int n) {
        if (!contains(n)) {
            if (size == elements.length) {
                elements = Arrays.copyOf(elements, elements.length * 2);
            }
            elements[size] = n;
            size++;
        }
    }

    public boolean contains(int n) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == n) {
                return true;
            }
        }
        return false;
    }

    public void remove(int n) {
        int i = 0;
        while (i < size && elements[i] != n) {
            i++;
        }
        if (i < size) {
            for (int j = i; j < size - 1; j++) {
                elements[j] = elements[j + 1];
            }
            size--;
        }
    }

    public void empty() {
        elements = new int[10];
        size = 0;
    }

    public String toString() {
        if (size == 0) {
            return "{}";
        }
        String result = "{" + elements[0];
        for (int i = 1; i < size; i++) {
            result += ", " + elements[i];
        }
        result += "}";
        return result;
    }

    public int size() {
        return size;
    }

    public Conjunto combine(Conjunto add) {
        Conjunto result = new Conjunto();
        for (int i = 0; i < size; i++) {
            result.insert(elements[i]);
        }
        for (int i = 0; i < add.size; i++) {
            result.insert(add.elements[i]);
        }
        return result;
    }

    public Conjunto subtract(Conjunto dif) {
        Conjunto result = new Conjunto();
        for (int i = 0; i < size; i++) {
            if (!dif.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }

    public Conjunto intersect(Conjunto inter) {
        Conjunto result = new Conjunto();
        for (int i = 0; i < size; i++) {
            if (inter.contains(elements[i])) {
                result.insert(elements[i]);
            }
        }
        return result;
    }
}
