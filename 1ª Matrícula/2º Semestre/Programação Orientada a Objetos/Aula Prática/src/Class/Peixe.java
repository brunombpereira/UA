package Class;

import Enums.AlimentOrigin;
import Enums.FishState;

import java.util.Objects;

public class Peixe extends Alimento{
    private FishState fishState;

    public Peixe(double proteins, double calories, double weight, FishState fishState) {
        super(proteins, calories, weight);
        this.fishState = fishState;
    }

    public FishState getFishState() {
        return fishState;
    }

    public void setFishState(FishState fishState) {
        this.fishState = fishState;
    }

    @Override
    public AlimentOrigin getAlimentOrigin() {
        return AlimentOrigin.ANIMAL;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Peixe peixe = (Peixe) o;
        return fishState == peixe.fishState;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), fishState);
    }

    @Override
    public String toString() {
        return super.toString() + ", estado do peixe " + fishState.toString();
    }
}
