package zad1;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Warehouse {
    List<Fruit> products;
    int capacity;

    public Warehouse(int capacity) {
        products = new ArrayList<>();
        this.capacity = capacity;
    }

    public synchronized void addProduct(Fruit product, int count, int number, int fruit_num) {
        int taken = 0;
        while(taken < count && products.size() < capacity) {
            products.add(product);
            taken++;
        }

        String fruit_name = switch (fruit_num) {
            case 0 -> "Apple";
            case 1 -> "Banana";
            case 2 -> "Strawberry";
            default -> throw new IllegalStateException(STR."Unexpected value: \{fruit_num}");
        };

        System.out.println(STR."Producer \{number} produced \{count} of \{fruit_name} (warehouse took \{taken})");

        this.printProducts();
    }

    public synchronized void getProduct(Class<? extends Fruit> fruitClass, int count, int number, int fruit_num) {
        int taken = 0;
        Iterator<Fruit> iterator = products.iterator();
        while(iterator.hasNext() && taken < count)
        {
            Fruit product = iterator.next();
            if(fruitClass.isInstance(product))
            {
                iterator.remove();
                taken++;
            }
        }

        String fruit_name = switch (fruit_num) {
            case 0 -> "Apple";
            case 1 -> "Banana";
            case 2 -> "Strawberry";
            default -> throw new IllegalStateException(STR."Unexpected value: \{fruit_num}");
        };

        System.out.println(STR."Consumer \{number} consumed \{taken}/\{count} of \{fruit_name}.");

        this.printProducts();

    }

    public void printProducts() {
        System.out.println("Products:");
        for(Fruit product : products) {
            System.out.print(STR."\{product} ");
        }
        System.out.println();
    }
}
