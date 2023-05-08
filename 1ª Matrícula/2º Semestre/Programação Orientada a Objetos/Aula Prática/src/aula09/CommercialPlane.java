package aula09;

import java.util.Objects;

public class CommercialPlane extends Plane {
    private int numberOfCrewMembers;

    public CommercialPlane(String id, String fabricante, String model, int yearOfProduction, int maxPassengers, int maxVelocity, int numberOfCrewMembers) {
        super(id, fabricante, model, yearOfProduction, maxPassengers, maxVelocity);

        if (numberOfCrewMembers > 0) {
            this.numberOfCrewMembers = numberOfCrewMembers;
        }
    }

    public int getNumberOfCrewMembers() {
        return numberOfCrewMembers;
    }

    public void setNumberOfCrewMembers(int numberOfCrewMembers) {
        this.numberOfCrewMembers = numberOfCrewMembers;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        CommercialPlane that = (CommercialPlane) o;
        return numberOfCrewMembers == that.numberOfCrewMembers;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), numberOfCrewMembers);
    }

    @Override
    public String toString() {
        return "CommercialPlane{" +
                "numberOfCrewMembers=" + numberOfCrewMembers +
                '}';
    }
}
