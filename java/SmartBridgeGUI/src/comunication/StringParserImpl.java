package comunication;

import java.util.Map;

public class StringParserImpl implements StringParser {
	static private String SEPARATOR = ";";

	public StringParserImpl() {
	}
	
	public Map<DataRead, String> parse(String msg) throws ArrayIndexOutOfBoundsException {
		final String[] parsed = msg.split(StringParserImpl.SEPARATOR);
		return Map.of(DataRead.ALERT_STATE, parsed[0], DataRead.LIGHTING, parsed[1],
				DataRead.VALVE_CONTROL, parsed[2], DataRead.WATER_LEVEL, parsed[3],
				DataRead.LIGHT_LEVEL, parsed[4], DataRead.VALVE_OPENING, parsed[5]);
	}
}
