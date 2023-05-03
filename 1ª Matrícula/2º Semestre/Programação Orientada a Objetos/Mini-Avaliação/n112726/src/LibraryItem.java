import java.util.Objects;

public class LibraryItem {
    private String title;
    private int id, numberOfDays;

    private boolean available;
    private static int nextId = 101;

    public LibraryItem(String title) {
        this.title = title;
        this.id = LibraryItem.nextId;
        nextId++;
        this.available = true;
        this.numberOfDays = 0;
    }

    @Override
    public String toString() {
        return "LibraryItem{" +
                "title='" + title + '\'' +
                ", id=" + id +
                ", available=" + available +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LibraryItem that = (LibraryItem) o;
        return id == that.id && available == that.available && Objects.equals(title, that.title);
    }

    @Override
    public int hashCode() {
        return Objects.hash(title, id, available);
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public boolean isAvailable() {
        return available;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public static int getNextId() {
        return nextId;
    }

    public static void setNextId(int nextId) {
        LibraryItem.nextId = nextId;
    }

    public void checkout(String userName) {
        this.available = false;
    }

    public void returnItem() {
        this.available = true;
    }

    public int getNumberOfDays() {
        return numberOfDays;
    }

    public void setNumberOfDays(int numberOfDays) {
        this.numberOfDays = numberOfDays;
    }
}
