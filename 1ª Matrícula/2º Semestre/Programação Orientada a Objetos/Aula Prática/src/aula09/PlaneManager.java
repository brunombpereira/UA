package aula09;

import java.util.*;

public class PlaneManager {
    LinkedList<Plane> planes = new LinkedList<>();

    public void addPlane(Plane plane) {
        planes.add(plane);
    }

    public void removePlane(String id) {
        planes.removeIf(plane -> plane.getId().equals(id));
    }

    public void searchPlane(String id) {
        for (Plane plane : planes) {
            if (plane.getId().equals(id)) {
                System.out.println(plane);
            }
        }

    }

    public void getComercialPlanes() {
        for (Plane plane : planes) {
            if (plane instanceof CommercialPlane) {
                System.out.println(plane);
            }
        }

    }

    public void getMilitaryPlanes() {
        for (Plane plane : planes) {
            if (!(plane instanceof MilitaryPlane)) {
                System.out.println(plane);
            }
        }

    }

    public void printAllPlanes() {
        int couter = 1;
        for (Plane plane : planes) {
            System.out.println(couter + " - " + plane);
            couter++;
        }

    }

    public void getFastestPlanes() {
        int maxVelocity = 0;
        Plane fastestPlane = null;

        for (Plane plane : planes) {
            if (plane.getMaxVelocity() > maxVelocity) {
                maxVelocity = plane.getMaxVelocity();
                fastestPlane = plane;
            }
        }
        System.out.println(fastestPlane);

    }
}
