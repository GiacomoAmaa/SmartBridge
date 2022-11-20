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

import comunication.SerialCommChannel;
import jssc.SerialPortList;

import java.awt.event.ActionEvent;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;

public final class SmartBridgeGUI extends JFrame {
	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Stores the screen information (resolution, size of each tile, etc).
	 */
	public static final Screen SCREEN = new ScreenHandler();
	
	/**
	 * GUI components
	 */
	private final JPanel northPanel = new JPanel();
	private final JPanel southPanel = new JPanel();
	private final JComboBox<String> ports = new JComboBox<>();
	private final JButton connect = new JButton("Connect");
	private final JButton search = new JButton("Search Ports");
	private final JButton takeControl = new JButton("Take valve control");
	private final JSlider valveOpening = new JSlider();
	private JTable statesTable;

	/**
	 * Graph data to plot
	 */
	private final XYSeriesCollection dataset = new XYSeriesCollection();
	
	/**
	 * Class to handle serial communication
	 */
	private SerialCommChannel serialChannel;
	 
	public SmartBridgeGUI() {
		this.initializeFrame();
		this.scanPorts();
		this.initializeButtons();
		this.initializeTable();
		this.initializeNorthPanel();
		this.initializeGraph();
		this.initializeSouthPanel();
	    this.setVisible(true);
	}

	private void initializeFrame() {
		this.setTitle("Smart Bridge GUI");
	    this.setSize(SCREEN.getWidth(), SCREEN.getHeight());
	    this.setLayout(new BorderLayout());
	    this.setResizable(false);
	    this.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private void initializeNorthPanel() {
	    this.add(northPanel, BorderLayout.NORTH);
	    northPanel.add(search);
	    northPanel.add(ports);
	    northPanel.add(connect);
	}
	
	private void initializeGraph() {
		dataset.addSeries(new XYSeries("Luminosity"));
		dataset.addSeries(new XYSeries("Water Level"));
		dataset.addSeries(new XYSeries("Valve Opening"));
		JFreeChart chart = ChartFactory.createXYLineChart("Statistics Monitoring",
				"Time (s)", "Percentage %", dataset);
		this.add(new ChartPanel(chart), BorderLayout.CENTER);
	}

	private void initializeSouthPanel() {
		final JScrollPane pane  = new JScrollPane(statesTable);
		pane.setPreferredSize(new Dimension(270,39));
	    this.add(southPanel, BorderLayout.SOUTH);
	    southPanel.add(takeControl);
	    southPanel.add(valveOpening);
	    southPanel.add(pane);

	}
	
	private void initializeTable() {
		final String[] colnames = {"State","Lighting","Remote"};
		final String[][] data = {{"NO DANGER","ON","Auto"}};
	    statesTable = new JTable(data,colnames);
	    statesTable.setEnabled(false);
	}
	
	private void scanPorts() {
	    String[] portNames = SerialPortList.getPortNames();
		ports.removeAllItems();
		for (int i = 0; i < portNames.length; i++){
		    ports.addItem(portNames[i]);
		}
	}
	
	private void initializeButtons() {
	    valveOpening.setEnabled(false);
	    takeControl.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(!takeControl.getText().equals("Back to Auto")) {
					takeControl.setText("Back to Auto");
					valveOpening.setEnabled(true);
					statesTable.setValueAt("Remote", 0, 2);
				} else {
					takeControl.setText("Take valve control");
					valveOpening.setEnabled(false);
					statesTable.setValueAt("Auto", 0, 2);
				}
			}
	    });
		connect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				boolean portSet = true;
				if (connect.getText().equals("Connect")) {
					try {
						serialChannel = new SerialCommChannel(ports.getSelectedItem().toString(),
								9600);
					} catch (Exception e1) {
						portSet = false;
					}
					if(portSet) {
						connect.setText("Stop Connection");
						ports.setEnabled(false);
					}
				} else {
					serialChannel.close();
					ports.setEnabled(true);
					connect.setText("Connect");
				}
			}
			
		});
		search.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				scanPorts();
			}
		});
	}
}

