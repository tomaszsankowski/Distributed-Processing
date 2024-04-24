package zad1;

import java.util.concurrent.ThreadLocalRandom;

public class Producer extends Thread{

    private final Warehouse warehouse;
    private final int number;
    private volatile boolean running = true;

    public Producer(Warehouse warehouse, int number){
        this.warehouse = warehouse;
        this.number = number;
    }

    public void terminate(){
        running = false;
    }

    public void run(){
        while(running)
        {

            int amount = ThreadLocalRandom.current().nextInt(1,5);
            int fruit_num = ThreadLocalRandom.current().nextInt(0, 3);

            Fruit product = switch (fruit_num) {
                case 0 -> new Apple();
                case 1 -> new Banana();
                case 2 -> new Strawberry();
                default -> throw new IllegalStateException(STR."Unexpected value: \{fruit_num}");
            };

            warehouse.addProduct(product, amount, number, fruit_num);

            int sleepTime = ThreadLocalRandom.current().nextInt(1000, 5000);
            try {
                sleep(sleepTime);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }
}
