package Class;

import Enums.AlimentOrigin;
import Enums.MeatType;

import java.util.Objects;

public class Carne extends Alimento {
    private MeatType meatType;

    public Carne(double proteins, double calories, double weight, MeatType meatType) {
        super(proteins, calories, weight);
        this.meatType = meatType;
    }

    public MeatType getMeatType() {
        return meatType;
    }

    public void setMeatType(MeatType meatType) {
        this.meatType = meatType;
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
        Carne carne = (Carne) o;
        return meatType == carne.meatType;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), meatType);
    }

    @Override
    public String toString() {
        return super.toString() + ", tipo de carne: " + meatType.toString();
    }
}
