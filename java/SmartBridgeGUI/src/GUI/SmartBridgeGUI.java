package GUI;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import comunication.SerialCommChannel;
import jssc.SerialPortList;

import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;

public final class SmartBridgeGUI extends JFrame {
	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Stores the screen information (resolution, size of each tile, etc).
	 */
	public static final Screen SCREEN = new ScreenHandler();
	
	private final JPanel northPanel = new JPanel();
	private final JComboBox<String> ports = new JComboBox<>();
	private final JButton connect = new JButton("Connect");

	private SerialCommChannel serialChannel;
	 
	public SmartBridgeGUI() {
		initializeFrame();
		initializeNorthPanel();
		initializeGraph();
	    this.setVisible(true);
	}

	private void initializeFrame() {
		this.setTitle("Smart Bridge GUI");
	    this.setSize(SCREEN.getWidth(), SCREEN.getHeight());
	    this.setLayout(new BorderLayout());
	    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private void initializeNorthPanel() {
	    this.add(northPanel, BorderLayout.NORTH);
	    northPanel.add(ports);
	    northPanel.add(connect);
	    String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    ports.addItem(portNames[i]);
		}
		connect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				boolean portSet = true;
				if (connect.getText().equals("Connect")) {
					try {
						serialChannel = new SerialCommChannel(ports.getSelectedItem().toString(), 9600);
					} catch (Exception e1) {
						portSet = false;
					}
					if(portSet) {
						connect.setText("Stop Connection");
						ports.setEnabled(false);
					}
				} else {
					
				}
			}
			
		});
	}
	
	private void initializeGraph() {
		//final XYSeries luminosity = new XYSeries("Luminosity");
		final XYSeries waterLevel = new XYSeries("Water Level");
		final XYSeriesCollection dataset = new XYSeriesCollection();
		//dataset.addSeries(luminosity);
		dataset.addSeries(waterLevel);
		JFreeChart chart = ChartFactory.createXYLineChart("Water Level","Time (s)", "Distance (cm)", dataset);
		this.add(new ChartPanel(chart), BorderLayout.CENTER);
		NumberAxis time = new NumberAxis();
		
		
	}
}

