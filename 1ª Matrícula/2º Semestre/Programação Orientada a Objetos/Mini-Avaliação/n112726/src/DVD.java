import java.util.Objects;

public class DVD extends Book {
    private int duration;

    public DVD(String title, String author, int duration) {
        super(title, author);
        this.duration = duration;
    }

    @Override
    public String toString() {
        return "DVD{" +
                "title='" + super.getTitle() + '\'' +
                ", id=" + super.getId() +
                ", available=" + super.isAvailable() + '\'' +
                "duration=" + duration +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        DVD dvd = (DVD) o;
        return duration == dvd.duration;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), duration);
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }
}