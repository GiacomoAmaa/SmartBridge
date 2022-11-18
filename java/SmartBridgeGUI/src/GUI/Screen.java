package GUI;

import java.awt.Dimension;
import java.awt.Toolkit;

/**
 * <p>The {@link Screen} interface can be used for accessing {@link ScreenHandler} methods.</p>
 * 
 * <p>The {@link ScreenHandler} stores all the basic screen information.</p>
 */
public interface Screen {

    /**
     * A {@link Dimension} containing the current screen resolution used by the system.
     */
    Dimension SYSTEM_RESOLUTION = Toolkit.getDefaultToolkit().getScreenSize();

    ////     DEFAULT VALUES    ////
    /**
     * Default size of a screen tile.
     */
    int BASE_TILE_SIZE = 32;

    /**
     * The current horizontal aspect ratio of the game.
     */
    int HORIZONTAL_RATIO = 16;
    /**
     * The current vertical aspect ratio of the game.
     */
    int VERTICAL_RATIO = 9;

    /**
     * Default scaling proportion of game screen.
     */
    double BASE_SCALING = 2;

    /**
     * The current proportion of the system screen compared to the game screen.
     */
    double PROPORTION = 1.5;

    /**
     * @return a {@link Dimension} containing the size of the screen
     */
    Dimension getScreenSize();
    /**
     * @return the size for each tile of the screen
     */
    int getTileSize();
    /**
     * @return the horizontal resolution of the screen
     */
    int getWidth();
    /**
     * @return the vertical resolution of the screen
     */
    int getHeight();
}
