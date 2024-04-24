package zad2;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;

public class CachingPrimeChecker {
    private final Map<Long, Boolean> cache = new ConcurrentHashMap<>();

    public boolean isPrime(final long x)
    {
        return cache.computeIfAbsent(x, this::computeIfIsPrime);
    }

    private boolean computeIfIsPrime(long x)
    {
        final String currentThreadName = Thread.currentThread().getName();
        System.out.printf("\t[%s] Running computation for: %d%n", currentThreadName, x);
        try {
            Thread.sleep(TimeUnit.SECONDS.toMillis(10));
        }
        catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        if(x < 2) {
            return false;
        }

        for (long i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                return false;
            }
        }

        return true;
    }
}
