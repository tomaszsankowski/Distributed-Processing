package zad1;

import java.util.concurrent.ThreadLocalRandom;

public class Consumer extends Thread{

    private final Warehouse warehouse;
    private final int number;
    private volatile boolean running = true;

    public Consumer(Warehouse warehouse, int number){
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

            Class<? extends Fruit> fruitClass = switch (fruit_num) {
                case 0 -> Apple.class;
                case 1 -> Banana.class;
                case 2 -> Strawberry.class;
                default -> throw new IllegalStateException(STR."Unexpected value: \{fruit_num}");
            };

            warehouse.getProduct(fruitClass, amount, number, fruit_num);

            int sleepTime = ThreadLocalRandom.current().nextInt(1000, 5000);
            try {
                sleep(sleepTime);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }
}
