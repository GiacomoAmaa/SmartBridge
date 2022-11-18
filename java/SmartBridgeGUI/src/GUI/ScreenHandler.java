package GUI;

import java.awt.Dimension;

/**
 * The {@link ScreenHandler} stores all the basic screen information.
 */
public class ScreenHandler implements Screen {

    private final Dimension currentSize;
    private final int tileSize;

    /**
     * Initialize a ScreenHandler with default screen values. 
     */
    public ScreenHandler() {
        tileSize = (int) ((SYSTEM_RESOLUTION.getWidth() / PROPORTION) / HORIZONTAL_RATIO);
        currentSize = new Dimension(tileSize * HORIZONTAL_RATIO, tileSize * VERTICAL_RATIO);
    }

    /**
     * {@inheritDoc}
     */
    public Dimension getScreenSize() {
        return currentSize;
    }
    /**
     * {@inheritDoc}
     */
    public int getTileSize() {
        return (int) tileSize;
    }
    /**
     * {@inheritDoc}
     */
    public int getWidth() {
        return (int) currentSize.getWidth();
    }
    /**
     * {@inheritDoc}
     */
    public int getHeight() {
        return (int) currentSize.getHeight();
    }
}
