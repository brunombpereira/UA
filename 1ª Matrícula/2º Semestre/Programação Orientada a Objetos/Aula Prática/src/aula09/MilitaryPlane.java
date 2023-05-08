package aula09;

import java.util.Objects;

public class MilitaryPlane extends Plane {
    private int numMissiles;

    public MilitaryPlane(String id, String fabricante, String model, int yearOfProduction, int maxPassengers, int maxVelocity, int numMissiles) {
        super(id, fabricante, model, yearOfProduction, maxPassengers, maxVelocity);

        if (numMissiles >= 0) {
            this.numMissiles = numMissiles;
        }
    }


    public int getNumMissiles() {
        return numMissiles;
    }

    public void setNumMissiles(int numMissiles) {
        this.numMissiles = numMissiles;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        MilitaryPlane that = (MilitaryPlane) o;
        return numMissiles == that.numMissiles;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), numMissiles);
    }

    @Override
    public String toString() {
        return "MilitaryPlane{" +
                "numMissiles=" + numMissiles +
                '}';
    }
}