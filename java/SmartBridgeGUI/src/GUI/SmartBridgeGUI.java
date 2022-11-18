package GUI;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import comunication.SerialCommChannel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public final class SmartBridgeGUI extends JFrame {
	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Stores the screen information (resolution, size of each tile, etc).
	 */
	public static final Screen GAME_SCREEN = new ScreenHandler();
	
	private final JLabel display = new JLabel();
	private final JButton stop = new JButton("stop");
	private final JButton up = new JButton("up");
	private final JButton down = new JButton("down");
	 
	private SerialCommChannel serialChannel;
	 
	public SmartBridgeGUI() {
	    this.setSize(GAME_SCREEN.getWidth(), GAME_SCREEN.getHeight());
	    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	    final JPanel panel = new JPanel();
	    panel.add(display);
	    panel.add(up);
	    panel.add(down);
	    panel.add(stop);
	    this.getContentPane().add(panel);
	    this.setVisible(true);
	    try {
	    	this.serialChannel = new SerialCommChannel("COM3", 9600);
	    } catch(Exception e1) {
	    	e1.printStackTrace();
	    }
	    up.addActionListener(new ActionListener() {
	    	@Override
	    	public void actionPerformed(ActionEvent e) {
	    		try {
	    			serialChannel.receiveMsg();
	    		} catch (InterruptedException e1) {
	    			// TODO Auto-generated catch block
	    			e1.printStackTrace();
	    		}
			}
	    });
	    down.addActionListener(new ActionListener() {
	    	@Override
	    	public void actionPerformed(final ActionEvent e) {
	    		// TODO Auto-generated method stub
	        }
	    });
	    stop.addActionListener(new ActionListener() {
	    	@Override
	    	public void actionPerformed(final ActionEvent e) {
	    		// TODO Auto-generated method stub
	   	    }
	    });
	}
}

