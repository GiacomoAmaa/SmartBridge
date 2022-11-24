package GUI;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSlider;
import javax.swing.JTable;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import comunication.DataRead;
import comunication.SerialCommChannel;
import comunication.StringParser;
import comunication.StringParserImpl;
import jssc.SerialPortList;

import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.util.Map;

public final class SmartBridgeGUI extends JFrame {
	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Stores the screen information (resolution, size of each tile, etc).
	 */
	public static final Screen SCREEN = new ScreenHandler();
	
	/**
	 * Finite states machine implemented on arduino clock time
	 */
	private static final double FSM_CLOCK_TIME = 0.15;
	
	/**
	 * GUI components
	 */
	private final JPanel northPanel = new JPanel();
	private final JPanel southPanel = new JPanel();
	private final JComboBox<String> ports = new JComboBox<>();
	private final JButton connect = new JButton("Connect");
	private final JButton search = new JButton("Search Ports");
	private final JButton takeControl = new JButton("Take valve control");
	private final JButton confirm = new JButton("Confirm");
	private final JSlider valveOpening = new JSlider();
	private JTable statesTable;
	
	private Thread update;

	/**
	 * Graph data to plot
	 */
	private final XYSeriesCollection dataset = new XYSeriesCollection();
	
	private Map<DataRead, String> dataRead;
	
	/**
	 * Classes to handle serial communication
	 */
	private SerialCommChannel serialChannel;
	private final StringParser parser = new StringParserImpl();
	
	private boolean threadRun = false;
	private double timeElapsed = 0;
	
	/**
	 * Initializes the GUI
	 */
	public SmartBridgeGUI() {
		this.initData();
		this.initializeFrame();
		this.scanPorts();
		this.initializeButtons();
		this.initializeTable();
		this.initializeNorthPanel();
		this.initializeGraph();
		this.initializeSouthPanel();
		this.initThread();
		update.start();
	    this.setVisible(true);
	}

	/**
	 * Restores the default values in the data structure that contains read data
	 */
	private void initData() {
		dataRead = Map.of(DataRead.ALERT_STATE, "normal", DataRead.LIGHTING, "off",
				DataRead.VALVE_CONTROL, "auto", DataRead.WATER_LEVEL, "0",
				DataRead.LIGHT_LEVEL, "0", DataRead.VALVE_OPENING, "0");
	}
	
	/**
	 * Basic frame's initialization procedure
	 */
	private void initializeFrame() {
		this.setTitle("Smart Bridge GUI");
	    this.setSize(SCREEN.getWidth(), SCREEN.getHeight());
	    this.setLayout(new BorderLayout());
	    this.setResizable(false);
	    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	/**
	 * Connects all the elements of the north panel and locates it on the frame
	 */
	private void initializeNorthPanel() {
	    this.add(northPanel, BorderLayout.NORTH);
	    northPanel.add(search);
	    northPanel.add(ports);
	    northPanel.add(connect);
	}
	
	/**
	 * Creates a chart containing the significant data to be displayed
	 */
	private void initializeGraph() {
		dataset.addSeries(new XYSeries("Luminosity"));
		dataset.addSeries(new XYSeries("Water Level"));
		dataset.addSeries(new XYSeries("Valve Opening"));
		JFreeChart chart = ChartFactory.createXYLineChart("Statistics Monitoring",
				"Time (s)", "Percentage %", dataset);
		this.add(new ChartPanel(chart), BorderLayout.CENTER);
	}

	/**
	 * Connects all the elements of the south panel and locates it on the frame
	 */
	private void initializeSouthPanel() {
		final JScrollPane pane  = new JScrollPane(statesTable);
		pane.setPreferredSize(new Dimension(270,39));
	    this.add(southPanel, BorderLayout.SOUTH);
	    southPanel.add(takeControl);
	    southPanel.add(valveOpening);
	    southPanel.add(confirm);
	    southPanel.add(pane);
	    takeControl.setEnabled(false);

	}
	
	/**
	 * Creates a table displaying the most significant states
	 */
	private void initializeTable() {
		final String[] colnames = {"State","Light","Valve Control"};
		final String[][] data = {{dataRead.get(DataRead.ALERT_STATE),
				dataRead.get(DataRead.LIGHTING), dataRead.get(DataRead.VALVE_CONTROL)}};
	    statesTable = new JTable(data,colnames);
	    statesTable.setEnabled(false);
	}
	
	/**
	 * Looks for available serial ports to connect to
	 */
	private void scanPorts() {
	    String[] portNames = SerialPortList.getPortNames();
		ports.removeAllItems();
		for (int i = 0; i < portNames.length; i++){
		    ports.addItem(portNames[i]);
		}
	}
	
	/**
	 * Assigns each button its own function
	 */
	private void initializeButtons() {
	    valveOpening.setEnabled(false);
	    confirm.setEnabled(false);
	    
	    takeControl.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(takeControl.getText().equals("Take valve control")) {
					setToRemote();
				} else {
					setToAuto();
				}
			}
	    });
	    
		connect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (connect.getText().equals("Connect")) {
					try {
						serialChannel = new SerialCommChannel(ports.getSelectedItem().toString(),
								9600);
						startConnection();
					} catch (Exception e1) {
						System.err.println("Failed Connection to the selected port");
					}
				} else {
					stopConnection();
				}
			}
			
		});
		
		search.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				scanPorts();
			}
		});
		
		confirm.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				serialChannel.sendMsg(String.valueOf(valveOpening.getValue()));
			}
		});
	}
	
	/**
	 * Initializes the thread to read/update data
	 */
	private void initThread(){
		update = new Thread() {
			@Override
			public void run() {
				while(true) {
					if(threadRun) {
						try {
							dataRead = parser.parse(serialChannel.receiveMsg());
							update();
						} catch (InterruptedException e) {
							stopConnection();
							timeElapsed = -SmartBridgeGUI.FSM_CLOCK_TIME;
							System.err.println("Interrupted while waiting for serial data...");
						}
						timeElapsed += SmartBridgeGUI.FSM_CLOCK_TIME;
					}
					try {
						Thread.sleep(150);
					} catch (InterruptedException e) {
						System.err.println("Interrupted while sleeping for serial data...");
					}
				}
			}
		};
	}
	
	/**
	 * Method to setup the gui for the established connection handling
	 */
	private void startConnection() {
		threadRun = true;
		connect.setText("Stop Connection");
		ports.setEnabled(false);
		takeControl.setEnabled(true);
	}
	
	/**
	 * Method to setup the gui for the disabled/lost connestion
	 */
	private void stopConnection() {
		threadRun = false;
		timeElapsed = 0;
		cleanChart();
		serialChannel.sendMsg("auto");
		serialChannel.close();
		connect.setText("Connect");
		ports.setEnabled(true);
		takeControl.setEnabled(false);
		valveOpening.setEnabled(false);
		confirm.setEnabled(false);
	}
	
	/**
	 * Method to setup the gui for remote valve control
	 */
	private void setToRemote(){
		takeControl.setText("Back to Auto");
		valveOpening.setEnabled(true);
		confirm.setEnabled(true);
		statesTable.setValueAt("remote", 0, 2);
		serialChannel.sendMsg("remote");
	}
	
	/**
	 * Method to setup the gui for auto valve control
	 */
	private void setToAuto() {
		takeControl.setText("Take valve control");
		valveOpening.setEnabled(false);
		confirm.setEnabled(false);
		statesTable.setValueAt("auto", 0, 2);
		serialChannel.sendMsg("auto");
	}
	
	/**
	 * Updates the GUI data at a given instant
	 */
	private void update() {
		dataset.getSeries(0).add(timeElapsed, Integer.parseInt(dataRead
				.get(DataRead.LIGHT_LEVEL)));
		dataset.getSeries(1).add(timeElapsed, Integer.parseInt(dataRead
				.get(DataRead.WATER_LEVEL)));
		dataset.getSeries(2).add(timeElapsed, Integer.parseInt(dataRead
				.get(DataRead.VALVE_OPENING)));
		statesTable.setValueAt(dataRead.get(DataRead.ALERT_STATE), 0, 0);
		statesTable.setValueAt(dataRead.get(DataRead.LIGHTING), 0, 1);
		statesTable.setValueAt(dataRead.get(DataRead.VALVE_CONTROL), 0, 2);
	}
	
	/**
	 * Resets the graph data
	 */
	private void cleanChart() {
		for (int i = 0; i< dataset.getSeriesCount(); i++) {
			dataset.getSeries(i).clear();
		}
	}
	
}

