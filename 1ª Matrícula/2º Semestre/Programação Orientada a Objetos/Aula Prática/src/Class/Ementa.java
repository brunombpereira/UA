package Class;

import Enums.WeekDay;

import java.util.LinkedList;
import java.util.Objects;

public class Ementa {
    private String name, local;
    private final LinkedList<Prato> pratos = new LinkedList<>() {
        @Override
        public String toString() {
            StringBuilder stringBuilder = new StringBuilder();
            for (Prato prato : this) {
                stringBuilder.append(prato).append("\n");
            }
            return stringBuilder.toString();
        }
    };

    public Ementa(String name, String local) {
        this.name = name;
        this.local = local;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getLocal() {
        return local;
    }

    public void setLocal(String local) {
        this.local = local;
    }

    public LinkedList<Prato> getPratos() {
        return pratos;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Ementa ementa = (Ementa) o;
        return Objects.equals(name, ementa.name) && Objects.equals(local, ementa.local) && Objects.equals(pratos, ementa.pratos);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, local, pratos);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();

        for (Prato prato : pratos) {
            if (prato.getClass().equals(PratoDieta.class)) {
                stringBuilder.append(prato.toString()).append(", dia ").append(WeekDay.values()[pratos.indexOf(prato)]).append("\n");
            } else {
                stringBuilder.append(prato.toString()).append(", dia ").append(WeekDay.values()[pratos.indexOf(prato)]).append("\n");
            }
        }
        return "Ementa " + name + "\n--------------------\n" + stringBuilder.toString();
    }

    public void addMeal(Prato prato, WeekDay weekDay) {
        pratos.add(prato);
    }

    public void removeMeal(Prato prato) {
        pratos.remove(prato);
    }
}
