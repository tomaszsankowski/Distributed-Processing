package zad2;

import java.util.Scanner;
import java.util.concurrent.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(4);
        CachingPrimeChecker cachingPrimeChecker = new CachingPrimeChecker();

        boolean leave = false;
        while(!leave)
        {
            final CyclicBarrier barrier = new CyclicBarrier(4);

            Scanner s = new Scanner(System.in);
            for(int i = 0; i < 4; i++)
            {
                try {
                    long x = s.nextInt();
                    if(x == 0)
                    {
                        leave = true;
                        break;
                    }
                    else
                    {
                        executorService.submit(() -> {
                            try {
                                barrier.await();
                                System.out.printf("Is %d prime? %b%n", x, cachingPrimeChecker.isPrime(x));
                            } catch (InterruptedException | BrokenBarrierException e) {
                                throw new RuntimeException(e);
                            }
                        });
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Invalid input! Ending program!");
                    leave = true;
                    break;
                }
            }

        }

        executorService.shutdown();
        if (!executorService.awaitTermination(20, TimeUnit.SECONDS)) {
            executorService.shutdownNow();
        }
    }
}