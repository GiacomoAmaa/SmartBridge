package comunication;

public class StringParser {
	static private String SEPARATOR = ";";
	private String alertState;
	private String lighting;
	private String valveControl;
	private int waterLevel;
	private int lightLevel;
	private int valveOpening;
	
	public StringParser() {
		reset();
	}
	

	public void parse(String msg) {
		final String[] parsed = msg.split(StringParser.SEPARATOR);
		alertState = parsed[0];
		lighting = parsed[1];
		valveControl = parsed[2];
		waterLevel = Integer.parseInt(parsed[3]);
		lightLevel = Integer.parseInt(parsed[4]);
		valveOpening = Integer.parseInt(parsed[5]);
	}
	
	public void reset() {
		alertState = "normal";
		lighting = "off";
		valveControl = "auto";
		waterLevel = 0;
		lightLevel = 0;
		valveOpening = 0;
	}
	
	
	public String getAlertState() {
		return alertState;
	}

	public String getLighting() {
		return lighting;
	}

	public String getValveControl() {
		return valveControl;
	}

	public int getWaterLevel() {
		return waterLevel;
	}

	public int getLightLevel() {
		return lightLevel;
	}

	public int getValveOpening() {
		return valveOpening;
	}
	
	public void setValveControl(String valveControl) {
		this.valveControl = valveControl;
	}
	
	
}
