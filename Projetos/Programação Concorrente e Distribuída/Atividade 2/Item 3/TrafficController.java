import java.util.concurrent.Semaphore;

public class TrafficController {

    private final Semaphore bridgeSemaphore = new Semaphore(1, true);

    public void enterLeft() {
        acquireBridgeAccess();
    }

    public void enterRight() {
        acquireBridgeAccess();
    }

    public void leaveLeft() {
        releaseBridgeAccess();
    }

    public void leaveRight() {
        releaseBridgeAccess();
    }

    private void acquireBridgeAccess() {
        try {
            bridgeSemaphore.acquire();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt(); // restore the interrupt status
        }
    }

    private void releaseBridgeAccess() {
        bridgeSemaphore.release();
    }
}
