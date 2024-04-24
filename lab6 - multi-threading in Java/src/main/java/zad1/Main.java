package zad1;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) throws InterruptedException {

        Warehouse warehouse = new Warehouse(10);

        Producer[] producers = {
                new Producer(warehouse, 1),
                new Producer(warehouse, 2)
        };

        Consumer[] consumers = {
                new Consumer(warehouse, 1),
                new Consumer(warehouse, 2)
        };

        ExecutorService executorProducers = Executors.newFixedThreadPool(2);
        ExecutorService executorConsumers = Executors.newFixedThreadPool(2);

        for (Producer producer : producers) {
            executorProducers.submit(producer);
        }

        for (Consumer consumer : consumers) {
            executorConsumers.submit(consumer);
        }

        try {
            System.in.read();
        } catch (IOException e) {
            e.printStackTrace();
        }

        for (Producer producer : producers) {
            producer.terminate();
        }

        for (Consumer consumer : consumers) {
            consumer.terminate();
        }

        executorProducers.shutdown();
        executorConsumers.shutdown();
        executorConsumers.awaitTermination(1, TimeUnit.MINUTES);
        executorProducers.awaitTermination(1, TimeUnit.MINUTES);
    }
}